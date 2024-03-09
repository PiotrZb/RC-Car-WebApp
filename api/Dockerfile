FROM eclipse-temurin:21.0.2_13-jdk
WORKDIR /rccarapp

COPY mvnw .
COPY mvnw.cmd .
COPY .mvn .mvn
COPY pom.xml .
COPY src src
COPY python python

RUN apt-get update && \
    apt-get install -y python3 python3-pip bluez libbluetooth3-dev

RUN pip3 install pyserial

RUN ./mvnw clean package

ENTRYPOINT ["java", "-jar", "./target/app-v1.jar"]