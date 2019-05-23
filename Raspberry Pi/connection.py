import pygame
import serial
port = "/dev/ttyACM0"

            

def avspilling(filnavn):
    pygame.mixer.music.load(filnavn)
    pygame.mixer.music.play()
    
pygame.init()
s1 = serial.Serial(port,9600)
s1.flushInput()

while True:
    if s1.inWaiting()>0:
        inputValue = s1.read(1)
        #print(ord(inputValue))
        tall = ord(inputValue)
        if tall == 1:
            print("Lyd 1 spiller")
            avspilling("1.wav")
        elif tall == 2:
            print("Lyd 2 spiller")
            avspilling("2.wav")
        elif tall == 3:
            print("Lyd 3 spiller")
            avspilling("3.wav")
        elif tall == 4:
            print("Lyd 4 spiller")
            avspilling("4.wav")
        elif tall == 5:
            print("Lyd 5 spiller")
            avspilling("5.wav")
        elif tall == 6:
            print("Lyd 6 spiller")
            avspilling("6.wav")
        elif tall == 7:
            print("Lyd 7 spiller")
            avspilling("7.wav")
        elif tall == 8:
            print("Lyd 8 spiller")
            avspilling("8.wav")
        elif tall == 9:
            print("Lyd 9 spiller")
            avspilling("9.wav")
        elif tall == 10:
            print("Lyd 10 spiller")
            avspilling("10.wav")
        elif tall == 11:
            print("Lyd 11 spiller")
            avspilling("11.wav")
        elif tall == 12:
            print("Lyd 12 spiller")
            avspilling("12.wav")
        elif tall == 13:
            print("Lyd 13 spiller")
            avspilling("13.wav")
        elif tall == 14:
            print("Lyd 14 spiller")
            avspilling("14.wav")
        elif tall == 15:
            print("Lyd 15 spiller")
            avspilling("15.wav")
        elif tall == 16:
            print("Lyd 16 spiller")
            avspilling("16.wav")
        elif tall == 17:
            print("Lyd 17 spiller")
            avspilling("17.wav")
        elif tall == 18:
            print("Lyd 18 spiller")
            avspilling("18.wav")
        elif tall == 19:
            print("Lyd 19 spiller")
            avspilling("19.wav")
        elif tall == 20:
            print("Lyd 20 spiller")
            avspilling("20.wav")


    