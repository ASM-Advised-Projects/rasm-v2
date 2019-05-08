#!/usr/bin/python2
import sys
import serial
import time
def main():
    data = sys.argv

    if data[1:]:
        ser = serial.Serial('/dev/ttyACM0', 9600, timeout=5)
        time.sleep(2)
        for d in data[1:]:
            print d
            ser.write(str(d))                            
        sent_by_arduino = ser.read();
        print sent_by_arduino;
        ser.close()

    else:
        print "No Input given!\n"

if __name__ == "__main__":
    main()
