import serial
import matplotlib.pyplot as plt
import time
import threading
from enum import Enum
import numpy as np
from PIL import Image

# from serialcommunication import process

intensity_list = []
state_list = []
time_list = []
bit_list = []
img = []
cou = 0
id = 0
step = 0


class DetectTarget(Enum):
    DETECT_FALL = 0
    DETECT_DIRECTION = 1
    STAND_BY = 2


class SerialCommunication:
    def __init__(self, port='com3', baud_rate=9600, timeout=0.0001):
        self.port = port
        self.baud_rate = baud_rate
        self.timeout = timeout
        self.serial = serial.Serial(
            port=self.port, baudrate=self.baud_rate, timeout=timeout)

    def openSerial(self):
        if self.serial.isOpen():
            print('串口已经打开!')
        else:
            self.serial.open()
            print('串口打开成功!')

    def printInfo(self):
        print('name: ', self.serial.name)
        print('port: ', self.serial.port)
        print('baud_rate: ', self.serial.baudrate)
        print('timeout: ', self.serial.timeout)

    def sendClass(self, class_index, delay_s):
        try:
            data = 'D' + str(class_index + 1) + '#'
            self.serial.write(data.encode())
            print('Message has been sent: ', data)
            time.sleep(delay_s)
        except:
            print('Transmit failed')
        # pass

    def sendMessage(self, buffer, delay_s):
        try:
            self.serial.write(buffer)
            print('Message has been sent: ', buffer)
            time.sleep(delay_s)
        except:
            print('Transmit failed')
        pass

    def closeSerial(self):
        self.serial.close()
        print('串口已关闭！')

    def readBytes(self, buffer_size):
        try:
            buffer = self.serial.read(buffer_size)
            print('Received Messages: ', buffer)
        except:
            print('Try receive', buffer_size, ' byte(s) messages but failed.')

    def readBytes_loop(self, buffer_size):
        while True:
            try:
                buffer = self.serial.readline()
                print('Received Messages: ', buffer.decode())
            except:
                print('Try receive', buffer_size,
                      ' byte(s) messages but failed.')


def get_data():
    buffer = serial.serial.readline()
    data = str(buffer[:-2])[2:-1]
    if len(data) > 0:
        return int(data)
    return


def loop():
    global step, intensity_list, state_list, bit_list
    step += 1
    if step < 10:
        return
    data_bit = get_data()
    if not data_bit == None:
        bit_list.append(data_bit)
    if len(bit_list) == 8:
        value = 0
        for i in range(8):
            value += bit_list[7-i]*pow(2, i)
        img.append(value)
        bit_list = []
    if len(img) == 25:
        return True
    return


if __name__ == '__main__':
    # read data
    serial = SerialCommunication(port='com5', baud_rate=9600, timeout=0.5)
    serial.openSerial()
    while True:
        if loop():
            break
    img=np.array(img).reshape((5,5))
    print(img.shape)
    img = Image.fromarray(img.astype('uint8'))
    img.save("Pic1.jpg")  
    serial.closeSerial()
    serial.printInfo()
