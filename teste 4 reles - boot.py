import time
from machine import Pin
led1=Pin(15,Pin.OUT) #default blue led
led2=Pin(2,Pin.OUT)
led3=Pin(0,Pin.OUT)
led4=Pin(4,Pin.OUT)
 
while True:
    led1.value(1)
    time.sleep(2)
    led1.value(0)
    time.sleep(1)
    led2.value(1)
    time.sleep(2)
    led2.value(0)
    time.sleep(1)
    led3.value(1)
    time.sleep(2)
    led3.value(0)
    time.sleep(1)
    led4.value(1)
    time.sleep(2)
    led4.value(0)
    time.sleep(1)
