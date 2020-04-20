import serial
import struct
from time import sleep

ser = serial.Serial(port='/dev/cu.SLAB_USBtoUART', baudrate=9600)
ser.rts = False
ser.dtr = False

ser.write([0xA0])
print "sent: 0xA0"
cmd = bytearray([0x01, 0x01, 0x01, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6])
crc = 0

for b in cmd:
  ser.write([b])
  print "sent: " + hex(b)
  print "read: " + ser.read().encode('hex')
  crc = (crc + b) & 0xFF

ser.write([crc])
print "sent: " + hex(crc) + " <- CRC"

while True:
  data = ser.read().encode('hex')
  print "read: " + data

ser.close()