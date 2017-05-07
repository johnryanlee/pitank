#!/usr/bin/python
import time
import smbus

bus = smbus.SMBus(1)

DELAY = 0.03
DEVICE_ADDRESS = 0x09
value = "T"

def sendRequest(device, value):
	charnum = 0
	print "Value length: ", len(value)
	for character in str(value):
		charnum = charnum + 1
		print "Char ", charnum, ": ", ord(character)
		bus.write_byte(device, ord(character))
		time.sleep(DELAY)

def readRequest(device):
	value = bus.read_byte(device)
	return value

print "Sending to ", DEVICE_ADDRESS, " | Value: ", value
sendRequest(DEVICE_ADDRESS, value)

time.sleep(DELAY)

# print "Received: ", readRequest(DRIVER_DEVICE_ADDRESS)
