from PIL import Image as im
import os
import scipy.io
#OS X side
os.chdir("/Users/ccheney10/Dropbox/6.115/Final Project/PSoC Work/Python Work")
#Windows side
#os.chdir("C:/Users/Craig/Dropbox/6.115/Final Project/Python Work")

data=[]
dataX=[]
pic1= im.new("RGB", (349,288))

for i in xrange(0,255):
    for j in xrange(0,255):
       #pic1.putpixel((i,j),(i,j,i))
       dataX.append((i,j,0))
    #data.append(dataX)
    #dataX=[]




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


#Bayer array for RGB image
def bayer2(array):

    data=[]
    for row in range(len(array)):
        for column in range(len(array[row])):
                    # if an even row
            if (row%2==0):
                #if an even column
                if  (column%2==0):
                    # Blue
                    try:
                        data.append((0,0,array[row][column]))
                    except:
                        print row, column
                    
                else:
                    # Green
                    data.append((0,array[row][column],0))
                    
            else:
                if  (column%2==0):
                    # green
                    data.append((0,array[row][column],0))
                    
                else:
                    # red
                    data.append((array[row][column],0,0))
                    
        
    return data

#Bayer array for grayscale image
def bayer3(array):

    data=[]
    for row in range(len(array)):
        for column in range(len(array[row])):
                    # if an even row
            if (row%2==0):
                #if an even column
                if  (column%2==0):
                    # Blue
                    try:
                        data.append((array[row][column]))
                    except:
                        print row, column
                    
                else:
                    # Green
                    data.append((array[row][column]))
                    
            else:
                if  (column%2==0):
                    # green
                    data.append((array[row][column]))
                    
                else:
                    # red
                    data.append((array[row][column]))
                    
        
    return data
                    

pic1= im.new("L", (349,288))    #"L" is grey scale, "RGB" is, well, RGB
#pic1= im.new("RGB", (349,288)) 
mat_pic=scipy.io.loadmat('picy.mat')
raw_data=mat_pic['raw_pic']

#use bayer2 for RGB, bayer3 for grayscale
pic1.putdata(bayer3(raw_data))
pic1.save("picyGrayScale.png")
dp=[]
for i in xrange(255*255):
    dp.append(i%255)
#t=bayer(dp,255,255)

#pic1.putdata(t)
#pic1.save("pic1.png")
#im.open("pic1.bmp","r")
