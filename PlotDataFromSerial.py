import serial
import matplotlib.pyplot as plt
from drawnow import *

temperatureData=[]
humidityData=[]

def createDataPlot():
    plt.grid(True)
    plt.title('Temperature & Relative Humidity data from DHT11')
    #Settings for temperature graph
    plt.xlabel('Time [s]')
    plt.ylabel('Temperature [C]')
    plt.ylim(0, 50)
    plt.plot(temperatureData, 'ro-', label='Degrees C')
    plt.legend(loc='upper left')
    #Settings for the second relative humidity graph
    plt2 = plt.twinx()
    plt.xlabel('Time [s]')
    plt.ylabel('Relative hummidity [%]')
    plt.ylim(0, 100)
    plt2.plot(humidityData, 'b^-', label='Hummidity (Pa)')
    plt2.ticklabel_format(useOffset=False)
    plt2.legend(loc='upper right')

#Initialization of serial port
arduinoData = serial.Serial('com5', 9600)
#Turn the interactive mode on.
plt.ion()

if __name__ == '__main__':
    while True:
        #Get the number of bytes in the input buffer
        while (arduinoData.inWaiting() == 0):
            pass
        arduinoString = arduinoData.readline()
        # read the line of text from the serial port
        arduinoString=(arduinoString.decode('utf-8')).rstrip()
        # Split it into an array called dataArray
        dataArray = arduinoString.split(',')
        temp = float(dataArray[0])
        # Convert first element to floating number and put in temp
        hum=float(dataArray[1])
        # Convert second element to floating number and put in hum
        temperatureData.append(temp)
        humidityData.append(hum)
        #Plot drawing
        drawnow(createDataPlot)
        plt.pause(.000001)

