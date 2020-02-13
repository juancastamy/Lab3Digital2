#Lab3
#Digital 2
#Camilo Perafán Montoya
#17092


from tkinter import *
import serial
import time
import sys

#Definición de variables
volt_POT1 = 0.00
volt_POT2 = 0.00
real_POT1 = 0
real_POT2 = 0


#Configuración del Puerto Serial
puerto = 'COM10'
ser = serial.Serial(port = puerto, baudrate = 9600,
                    parity = serial.PARITY_NONE,
                    stopbits = serial.STOPBITS_ONE,
                    bytesize = serial. EIGHTBITS, timeout = 0)


#Configuración de la ventana
ventana = Tk()
ventana.title("Laboratorio 3: Comunicación UART")
ventana.geometry("670x250")
ventana.config(bg='cadetblue')

#Configuración de los botones
def gra1():
    ser.write('+') #Si se oprime este botón, se incrementa el contador en el PIC
    ser.flushOutput()
    time.sleep(.05)
    

def rep1():
    ser.write('-') #Si se oprime este botón, se decrementa el contador en el PIC
    ser.flushOutput()
    time.sleep(.05)


#Se definen los identificadores de las casillas
pot1 = Label(ventana, text="Potenciometro 1", background = 'pale turquoise', font=('Arial', 20)).place(x=60,y=20)
pot2 = Label(ventana, text="Potenciometro 2", background = 'pale turquoise', font=('Arial', 20)).place(x=400,y=20)
nombre1 = Label(ventana, text="Camilo Perafán M. \n17092", background = 'pale turquoise', font=('Arial', 16)).place(x=240,y=140)


#Se definen los botones
grabar1 = Button(ventana, text = "+", command=gra1).place(x=315,y=100)

repro1 = Button(ventana, text = "-", command=rep1).place(x=335,y=100)


#Se configuran las casillas en donde irá la información
POT_1 = Label(ventana,text=str(volt_POT1) ,fg="Deep Sky Blue2",font=(30))
POT1_1.place(x=470,y=85)

POT_2 = Label(ventana,text=str(volt_POT2) ,fg="Deep Sky Blue2",font=(18))
POT_2.place(x=130,y=85)

POT_1_1 = Label(ventana,text="V" ,fg="Deep Sky Blue2",font=(18))
POT_1_1.place(x=515,y=85)

POT_2_1 = Label(ventana,text="V" ,fg="Deep Sky Blue2",font=(18))
POT_2_1.place(x=175,y=85)


while True:
    dato = ser.read()
    try:
        if dato == '':
            pass
        else:
            dato_POT1 = ser.read()
            dato_POT2 = ser.read()

            real_POT1 = ord(dato_POT1)
            real_POT2 = ord(dato_POT2)

            print(str(real_POT1) + ',' + str(real_POT2))
            ser.flushInput()
            time.sleep(.05)
            
    except:
        print('.')
    volt_POT1 = float((real_POT1)/float (51))
    volt_POT2 = float((real_POT2)/float (51))
    voltaje_1.config(text = str(volt_POT1)[0:4])
    voltaje_2.config(text = str(volt_POT2)[0:4])
    ventana.update_idletasks()
    ventana.update() 
    time.sleep(.2)

ventana.mainloop()
