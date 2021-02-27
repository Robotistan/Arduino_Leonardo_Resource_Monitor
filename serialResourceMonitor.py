import psutil
import serial
import time

x = input("Seri port adını giriniz")

try:
    arduino = serial.Serial(port=x, baudrate=9600, timeout=.1)
except Exception as e:
    print("Port acarken hata olustu: %s" % x)
    print(e)
    exit()

print("Program calisiyor, cikmak icin: Ctrl+C")
while True:
    try:

        cpu_usage = psutil.cpu_percent()
        memories = psutil.virtual_memory().percent
        arduino.write(bytes("%f,%f\n" % (cpu_usage, memories), "utf-8"))
        time.sleep(1)

    except KeyboardInterrupt:
        arduino.close()
        break
