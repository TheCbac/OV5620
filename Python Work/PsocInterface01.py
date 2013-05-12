import serial
import struct
from PIL import Image as im
import os
#OS X side
#os.chdir("/Users/ccheney10/Dropbox/6.115/Final Project/Python Work")
#Windows side
os.chdir("C:/Users/Craig/Dropbox/6.115/Final Project/PSoc Work/Python Work")

try:
    Psoc=serial.Serial(port='\\.\COM5', baudrate=921600, bytesize=serial.EIGHTBITS, parity=serial.PARITY_NONE, stopbits=serial.STOPBITS_ONE, timeout=.001)
except:
    
    Psoc=serial.Serial(port='\\.\COM5', baudrate=921600, bytesize=serial.EIGHTBITS, parity=serial.PARITY_NONE, stopbits=serial.STOPBITS_ONE, timeout=.001)

def read():
    data=[]
    lineData=[]
    Psoc.write(1)
    for j in xrange(1):
        for i in xrange(1000):
        #data+=Psoc.read()
            try:
                #lineData +=Psoc.read()
                lineData += struct.unpack('B',Psoc.read())
                #lineData.append(struct.unpack('s',Psoc.read())[0])
            except:
                #print i
                #lineData.append('e')
                lineData.append(255)
                #return len(data)
        data+=lineData
        lineData=[]
    pic3=im.new("RGB",(650,320)) 
    pic3.putdata(bayer(data, 650,320))
    pic3.save("pic3.png")
    
    return data


#pic1= im.new("RGB", (649,255))



def direct(length):
    Psoc.write(1)
    for i in xrange(length):
        print i, " ", struct.unpack('B',Psoc.read())[0]

def bayer(array,xSize,ySize):
    row=0
    column=0

    data=[]
    for pix in xrange(len(array)):
        #print row, column
        
        # if an even row
        if (row%2==0):
            #if an even column
            if  (column%2==0):
                # Blue
                data.append((0,0,array[pix]))
                row+=1
            else:
                # Green
                data.append((0,array[pix],0))
                row+=1
        else:
            if  (column%2==0):
                # green
                data.append((0,array[pix],0))
                row+=1
            else:
                # red
                data.append((array[pix],0,0))
                row+=1
        if row==xSize:
            column+=1
            row=0
    return data
        

dp=[]
for i in xrange(255*255):
    dp.append(i%255)

#sampleData=read()    
#t=bayer(sampleData,649,255)

#pic1.putdata(t)
#pic1.save("pic1.png")
#im.open("pic1.bmp","r")
