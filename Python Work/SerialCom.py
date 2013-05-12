import serial
import struct


Psoc=serial.Serial(port='\\.\COM6', baudrate=9600, bytesize=serial.EIGHTBITS, parity=serial.PARITY_NONE, stopbits=serial.STOPBITS_ONE, timeout=1)

def read():
    data=[]
    Psoc.write(1)
    for i in xrange(255):
        #data+=Psoc.read()
        data += struct.unpack('B',Psoc.read())
    print data
    
