import subprocess
import argparse
import time
import serial


BAUDRATE = 9600


argParser = argparse.ArgumentParser()
argParser.add_argument('-c', '--connect', action='store')
argParser.add_argument('-d', '--disconnect', action='store')
argParser.add_argument('-r', '--rfcomm', action='store')
argParser.add_argument('-s', '--send', nargs=2, metavar=('mac', 'message'), action='store')
argParser.add_argument('-re', '--receive', action='store')


# function to connect to the passed mac address
def connect(mac: str) -> None:
    subprocess.Popen(['rfcomm', 'connect', 'hci0', mac])
    time.sleep(2)


# function to send data through serial port
def send(mac: str, msg: str) -> None:
    rfcomm = get_rfcomm(mac)
    with serial.Serial(f'/dev/{rfcomm}', BAUDRATE) as port:
        port.write(msg.encode('utf-8'))
        port.close()


# function to receive data through serial port
def receive(mac: str) -> None:
    rfcomm = get_rfcomm(mac)
    with serial.Serial(f'/dev/{rfcomm}', BAUDRATE) as port:
        while True:
            line = port.readline().decode('utf-8').strip()
            if line:
                print(line)
            else:
                break
        port.close()


# function to return used rfcomm
def get_rfcomm(mac: str) -> str:
    output = subprocess.check_output(['rfcomm']).decode('utf-8')
    for line in output.split('\n'):
        if 'rfcomm' in line and 'connected' in line and mac:
            return line.split()[0][:-1]
    return ''


# function to close connection
def disconnect(mac: str) -> None:
    subprocess.Popen(['rfcomm', 'release', 'hci0', mac])
    time.sleep(2)


def main() -> None:
    print("sending")
    args = argParser.parse_args()

    if args.connect is not None:
        if get_rfcomm(args.connect) != '':
            disconnect(args.connect)

        connect(args.connect)

    elif args.disconnect is not None:
        disconnect(args.disconnect)

    elif args.rfcomm is not None:
        print(get_rfcomm(args.rfcomm))

    elif args.send is not None:
        send(args.send[0], args.send[1])

    elif args.receive is not None:
        receive(args.receive)


if __name__ == "__main__":
    main()
