#include <NewTone.h>

#define M1dir 4       // Motor 1 direction
#define M1 5          // Motor 1 PWM
#define M2 6          // Motor 2 PWM
#define M2dir 7       // Motor 2 direction
#define Buzzer 2
#define Red_LED 8     // Not connected yet
#define Blue_LED 9    // Not connected yet
#define ECHO 10
#define TRIG 11
#define Lights 3      // Not connected yet
#define FR 1;         // Fotoresistor - analog in 0 used for setting randomseed



enum Direction {
  FORWARD,
  BACKWARD,
  LEFT,
  RIGHT,
  FORWARD_LEFT,
  FORWARD_RIGHT,
  BACKWARD_LEFT,
  BACKWARD_RIGHT,
  STOP
};



const int M2_offset = 8;
const int M1_offset = 0;

int velocity = 200;
int random_dir = 0;
char c = 'S';
unsigned long elapsed = 0;   // alarm
unsigned long elapsed2 = 0;  // distance measurement
unsigned long elapsed3 = 0;  // data printing
unsigned long elapsed4 = 0;  // auto mode
double distance = 400;
bool lights_on = false;
bool alarm_on = false;
bool measurement_in_progress = false;
bool auto_mode_on = false;
Direction Dir = STOP;



void setup() {
  pinMode(ECHO, INPUT);
  pinMode(TRIG, OUTPUT);
  pinMode(Buzzer, OUTPUT);
  pinMode(M1dir, OUTPUT);
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  pinMode(M2dir, OUTPUT);
  pinMode(Red_LED, OUTPUT);
  pinMode(Blue_LED, OUTPUT);
  pinMode(Lights, OUTPUT);

  noNewTone(Buzzer);
  digitalWrite(Red_LED, LOW);
  digitalWrite(Blue_LED, LOW);
  digitalWrite(TRIG, LOW);
  digitalWrite(Lights, LOW);
  analogWrite(M1, 0);
  analogWrite(M2, 0);

  Serial1.begin(9600);
  while(!Serial1);
  Serial.begin(9600);

  randomSeed(analogRead(0));
}

//////////////////////////////////////////////////////////// Main loop

void loop() {
  read_data();
  analize_data();
  check_distance();
  check_collision();
  auto_mode();
  alarm();
  lights();
  print_data();
}

//////////////////////////////////////////////////////////// Functions

void forward(int spd) {
  digitalWrite(M1dir, HIGH);
  analogWrite(M1, spd + M1_offset);
  digitalWrite(M2dir, LOW);
  analogWrite(M2, spd + M2_offset);
  Dir = FORWARD;
}



void backward(int spd) {
  digitalWrite(M1dir, LOW);
  analogWrite(M1, spd + M1_offset);
  digitalWrite(M2dir, HIGH);
  analogWrite(M2, spd + M2_offset);
  Dir = BACKWARD;
}



void right(int spd) {
  digitalWrite(M1dir, LOW);
  analogWrite(M1, spd + M1_offset);
  digitalWrite(M2dir, LOW);
  analogWrite(M2, spd + M2_offset);
  Dir = RIGHT;
}



void left(int spd) {
  digitalWrite(M1dir, HIGH);
  analogWrite(M1, spd + M1_offset);
  digitalWrite(M2dir, HIGH);
  analogWrite(M2, spd + M2_offset);
  Dir = LEFT;
}



void forward_left(int spd) {
  digitalWrite(M1dir, HIGH);
  analogWrite(M1, spd + M1_offset);
  digitalWrite(M2dir, LOW);
  analogWrite(M2, spd - 100 + M2_offset);
  Dir = FORWARD_LEFT;
}



void forward_right(int spd) {
  digitalWrite(M1dir, HIGH);
  analogWrite(M1, spd - 100 + M1_offset);
  digitalWrite(M2dir, LOW);
  analogWrite(M2, spd + M2_offset);
  Dir = FORWARD_RIGHT;
}



void backward_left(int spd) {
  digitalWrite(M1dir, LOW);
  analogWrite(M1, spd + M1_offset);
  digitalWrite(M2dir, HIGH);
  analogWrite(M2, spd - 100 + M2_offset);
  Dir = BACKWARD_LEFT;
}



void backward_right(int spd) {
  digitalWrite(M1dir, LOW);
  analogWrite(M1, spd - 100 + M1_offset);
  digitalWrite(M2dir, HIGH);
  analogWrite(M2, spd + M2_offset);
  Dir = BACKWARD_RIGHT;
}



void engines_off() {
  analogWrite(M1, 0);
  analogWrite(M2, 0);
  Dir = STOP;
}



void read_data() {
  if (Serial1.available() > 0) {
    c = (char)Serial1.read();
  }
}



void analize_data() {
  switch (c) {
    case '0': velocity = 200; break;
    case '1': velocity = 204; break;
    case '2': velocity = 208; break;
    case '3': velocity = 212; break;
    case '4': velocity = 216; break;
    case '5': velocity = 220; break;
    case '6': velocity = 224; break;
    case '7': velocity = 228; break;
    case '8': velocity = 232; break;
    case '9': velocity = 236; break;
    case 'q': velocity = 240; break;

    case 'F': forward(velocity); auto_mode_on = false; break;
    case 'B': backward(velocity); auto_mode_on = false; break;
    case 'L': left(velocity); auto_mode_on = false; break;
    case 'R': right(velocity); auto_mode_on = false; break;
    case 'G': forward_left(velocity); auto_mode_on = false; break;
    case 'I': forward_right(velocity); auto_mode_on = false; break;
    case 'J': backward_right(velocity); auto_mode_on = false; break;
    case 'H': backward_left(velocity); auto_mode_on = false; break;
    case 'S': engines_off(); auto_mode_on = false; break;

    case 'W': lights_on = true; break;
    case 'w': lights_on = false; break;
    case 'V': alarm_on = true; break;
    case 'v': alarm_on = false; break;

    case 'U': break; // no function yet (Back lights)
    case 'u': break; // no function yet
    case 'X': auto_mode_on = true; break; // (Triangle)
    case 'x': auto_mode_on = false; engines_off(); break;
    case 'D': random_dir = 0; velocity = 200; lights_on = false; alarm_on = false; auto_mode_on = false; engines_off(); break; // (Stop all)
  }
}



void alarm() {
  if (alarm_on) {
    if (millis() - elapsed <= 255UL) {
      NewTone(Buzzer, 4500);
      digitalWrite(Red_LED, HIGH);
      digitalWrite(Blue_LED, LOW);
    } else {
      NewTone(Buzzer, 3500);
      digitalWrite(Red_LED, LOW);
      digitalWrite(Blue_LED, HIGH);
      if (millis() - elapsed > 510UL) {
        elapsed = millis();
      }
    }
  } else {
    noNewTone(Buzzer);
    digitalWrite(Red_LED, LOW);
    digitalWrite(Blue_LED, LOW);
  }
}



void lights() {
  if (lights_on) {
    digitalWrite(Lights, HIGH);
  } else {
    digitalWrite(Lights, LOW);
  }
}



void check_distance() {
  if (measurement_in_progress == false && micros()-elapsed >= 30UL) {
    digitalWrite(TRIG, LOW);
    digitalWrite(TRIG, HIGH);
    measurement_in_progress = true;
    elapsed2 = micros();
  }

  if ((micros() - elapsed2) >= 15UL) {
    digitalWrite(TRIG, LOW);
    double answer = pulseIn(ECHO, HIGH, 15000UL) / 58;
    measurement_in_progress = false;
    if (answer > 400 || answer < 2.50) {
      distance = 400.00;
    } else {
      distance = answer;
    }
  }
}



void check_collision() {
  if (distance < 20.00 && Dir == FORWARD) {
    engines_off();
    c = 'S';
  }
}



void print_data() {
  if ((millis() - elapsed3 >= 250UL) && Serial) {
    Serial.print("random_dir ");
    Serial.print(random_dir);
    Serial.print(", c ");
    Serial.print(c);
    Serial.print(", velocity ");
    Serial.print(velocity);

    if (auto_mode_on) {
      Serial.print(", auto mode on ");
    } else {
      Serial.print(", auto mode off ");
    }

    Serial.print(", distance ");
    Serial.print(distance);
    Serial.print(", M1 offset ");
    Serial.print(M1_offset);
    Serial.print(", M2 offset ");
    Serial.print(M2_offset);

    if (lights_on) {
      Serial.print(", lights on ");
    } else {
      Serial.print(", lights off ");
    }

    if (alarm_on) {
      Serial.print(", alarm on ");
    } else {
      Serial.print(", alarm off ");
    }

    Serial.print(", direction ");

    switch (Dir) {
      case FORWARD: Serial.println("forward"); break;
      case BACKWARD: Serial.println("backward"); break;
      case LEFT: Serial.println("left"); break;
      case RIGHT: Serial.println("right"); break;
      case FORWARD_LEFT: Serial.println("forward-left"); break;
      case FORWARD_RIGHT: Serial.println("forward-right"); break;
      case BACKWARD_LEFT: Serial.println("backward-left"); break;
      case BACKWARD_RIGHT: Serial.println("backward-right"); break;
      case STOP: Serial.println("stop"); break;
    }

    elapsed3 = millis();
  }
}

//////////////////////////////////////////////////////////// NOT DONE YET

void auto_mode() {
  if (auto_mode_on) {
    if (millis() - elapsed4 >= 500UL) {
      if (distance <= 40.00) {
        if (random_dir == 0) {
          random_dir = random(1, 3);
        }
        elapsed4 = millis();
      }
      else {
        random_dir = 0;
      }
    }

    switch (random_dir) {
      case 0: forward(velocity); break;
      case 1: left(velocity); break;
      case 2: right(velocity); break;
    }
  }
}

//////////////////////////////////////////////////////////// STILL IN PLANS

void dance() {

}



void check_brightness(){
  
}
