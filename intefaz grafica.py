import serial

from tkinter import *

serialPort = serial.Serial(port = 'com10', baudrate = 9600,
                    parity = serial.PARITY_NONE,
                    stopbits = serial.STOPBITS_ONE,
                    bytesize = serial.EIGHTBITS, timeout = 0)
contador = 0
def sumar():
    global contador
    contador +=  1
    print (contador)
    desplegar()
def resta():
    global contador
    contador -= 1
    print (contador)
    desplegar()
def desplegar():
    global contador
    print(contador.to_bytes(2,"big"))
    serialPort.write(contador.to_bytes(2,"big"))
    label0=Label(gui, text = contador)
    label0.grid(row=1,column=2)
    
#interfaz grafica    
gui = Tk()
gui.geometry ("265x125")
desplegar()
gui.title("Contador Comunicacion Serial")
button1 = Button(gui, text='+', fg = 'white', bg='blue', command=sumar, height= 2 , width = 10)
button1.grid (row = 2 , column = 2)
button2 = Button(gui, text='-', fg = 'blue', bg='white', command=resta, height= 2 , width = 10)
button2.grid (row = 2 , column = 3)
gui.mainloop()
while(1):
    if (serialPort.in_waiting >0):
        
        serialPort.flushOutput()
        time.sleep = 0.5
