import serial
import os
from dotenv import load_dotenv 
import time
import csv

load_dotenv()

serial_port = os.environ['SERIAL_PORT']
type_file = os.environ['TYPE_FILE_MODEL']
headerModelList = ['accX', 'accY', 'accZ', 'gyroX', 'gyroY', 'gyroZ', 'up', 'down', 'right', 'left', 'side']
headerList = ['temp', 'pressure', 'proximity', 'r', 'g', 'b', 'a', 'accX', 'accY', 'accZ', 'gyroX', 'gyroY', 'gyroZ', 'up', 'down', 'right', 'left', 'side']

ser = serial.Serial(serial_port, timeout=1)

if type_file=='no':
    f = open('Churn--Federated-Learning-/churn/motion_data.csv', 'a', newline='')
else:
    f = open('Churn--Federated-Learning-/churn/motion_model_data.csv', 'a', newline='')

writer = csv.writer(f)

if type_file=='no':
    writer.writerow(headerList)
else:
    writer.writerow(headerModelList)

try:
    while True:
        s = ser.readline().decode()
        if s != "":
            rows = [x for x in s.split(',')]
            rows[-1] = rows[-1].rstrip()
            print(rows)

            writer.writerow(rows)
            
except KeyboardInterrupt:
    print("Closing file...")
    f.close()
