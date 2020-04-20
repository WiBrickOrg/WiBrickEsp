import serial
import struct
import sys
from time import sleep

ser = serial.Serial(baudrate=9600)
ser.setPort('/dev/cu.SLAB_USBtoUART')
ser.setRTS(False)
ser.setDTR(False)
ser.open()

size = 10
packetStart = False
buff = [0,0,0,0,0,0,0,0,0,0]
buffPos = 0
while True:
  data = ser.read().encode('hex')
  # sys.stdout.write(data)
  # sys.stdout.write(" ")
  # buffPos = buffPos + 1
  if buffPos >= size:
    sys.stdout.write('\n')
    buffPos = 0
  if data == "a0" and packetStart == False:
    packetStart = True
    buffPos = 0
  if packetStart and buffPos <= size:
    buff[buffPos] = data
    buffPos = buffPos + 1
  if buffPos >= size:
    packetStart = False
    if buff[2] != '01':
      sys.stdout.write('\033[93m')
    print buff
    sys.stdout.write('\033[0m')
    if buff[1] == "27":
        print "==========================="


ser.close()