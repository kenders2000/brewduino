import serial
import time
import csv
import datetime

from tkinter import *

count = 1
count1 = 5
count2 = 0

ser = serial.Serial('/dev/ttyACM0', 9600)

if ser.isOpen():
    print(ser.name + ' is open')
    print('Initialising..')
    while (count1 >= 0):
        print(count1)
        count1 = count1-1
        time.sleep(1)

def Get_Date_Time():
    t = datetime.datetime.now()
    q = t.strftime('%d/%m/%y')
    w = t.strftime('%H:%M:%S')
    return q, w

def Print_Temp(a, b, c):
    print("Beer Temp = " + str(a))
    print("Fridge Temp = " + str(b))
    print("Ambient = " + str(c))

def Get_Temp():
    ser.write(b'a')                                 # write 'a' to Serial
    input = ser.read(5)                             # Read 5 bytes response from Arduino
    x = float(input)                                # write response as a float to x
    ser.write(b'b')                                 # write 'b' to Serial
    input = ser.read(5)                             # Read 5 bytes response from Arduino
    y = float(input)                                # write response as a float to y
    ser.write(b'c')                                 # write 'c' to Serial
    input = ser.read(5)                             # Read 5 bytes response from Arduino
    z = float(input)                                # write response as a float to z
    return x, y, z                                  # return results

def Save_Temps(d, t, p, q, r):
    with open('/home/pi/Documents/Brewmaster Log Files/TempContinual.csv', 'a', newline='') as csvfile:
        filewriter = csv.writer(csvfile, delimiter=',')
        filewriter.writerow([d, t, p, q, r])
        csvfile.close

def Draw_GUI(x, y, m, n, o):
    ml = PanedWindow()
    ml.pack(fill=BOTH, expand=1)
    left = Label(ml, padx=10, text="Technical Info")
    ml.add(left)
    date = Label(ml, text= str(x))
    ml.add(date)
    time = Label(ml, text= str(y))
    ml.add(time)
    m2 = PanedWindow(ml, orient=VERTICAL)
    ml.add(m2)
    top = Label(m2, padx=100, text="Beer facts")
    m2.add(top)
    text1 = Label(m2, text="Beer Temperature = " + str(m))
    m2.add(text1)
    text2 = Label(m2, text="Fridge Temperature = " + str(n))
    m2.add(text2)
    text3 = Label(m2, text="Ambient Temperature = " + str(0))
    m2.add(text3)
    bottom = Label(m2, text="Hopefully video here")
    m2.add(bottom)


while (TRUE):

    (BeerTemp, FridgeTemp, AmbientTemp) = Get_Temp()    # Call Get_Temp Function
    (Date, Time) = Get_Date_Time()
    Save_Temps(Date, Time, BeerTemp, FridgeTemp, AmbientTemp)
    Draw_GUI(Date, Time, BeerTemp, FridgeTemp, AmbientTemp)

    print(Date)
    print(Time)
    Print_Temp(BeerTemp, FridgeTemp, AmbientTemp)       # print temperatures

    time.sleep(10)
