import serial
import numpy
import matplotlib.pyplot as plt
from drawnow import *

temperatureData=[]
humidityData=[]

def createDataPlot():
    plt.grid(True)
    plt.title('Temperature data from DHT11')
    plt.xlabel('Time [s]')
    plt.ylabel('Temperature [C]')
    plt.ylim(0, 50)
    plt.plot(temperatureData, 'ro-', label='Degrees C')
    plt.legend(loc='upper left')
    plt2 = plt.twinx()
    plt.xlabel('Time [s]')
    plt.ylabel('Relative hummidity [%]')
    plt.ylim(0, 100)
    plt2.plot(humidityData, 'b^-', label='Hummidity (Pa)')
    plt2.ticklabel_format(useOffset=False)
    plt2.legend(loc='upper right')


arduinoData = serial.Serial('com4', 9600)
cnt=0
plt.ion()

if __name__ == '__main__':
    while True:
        while (arduinoData.inWaiting() == 0):
            pass
        arduinoString = arduinoData.readline()  # read the line of text from the serial port
        arduinoString=(arduinoString.decode('utf-8')).rstrip()
        dataArray = arduinoString.split(',')  # Split it into an array called dataArray
        temp = float(dataArray[0])  # Convert first element to floating number and put in temp
        hum=float(dataArray[1])
        temperatureData.append(temp)
        humidityData.append(hum)
        drawnow(createDataPlot)
        plt.pause(.000001)
        cnt = cnt + 1
        if (cnt > 50):
            humidityData.pop(0)