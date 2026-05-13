import time
import board
import busio
import adafruit_ads1x15.ads1115 as ADS
from adafruit_ads1x15.ads1115 import ADS1115
from adafruit_ads1x15.analog_in import AnalogIn
from adafruit_ads1x15 import ads1x15

from adafruit_ads1x15.analog_in import AnalogIn

i2c = busio.I2C(board.SCL, board.SDA)

ads = ADS.ADS1115(i2c)

ecg = AnalogIn(ads, ads1x15.Pin.A0)

ppg = AnalogIn(ads, ads1x15.Pin.A1)
while True:
    print("ECG:","2",ecg.value)
    print("PPG:","1",ppg.value)

    time.sleep(0.01)