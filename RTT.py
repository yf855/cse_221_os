import time
import requests

url = "http://www.google.com"
total = 0
for x in range(0,10):
    start= time.time()
    r = requests.get(url)
    end = time.time()
    total = total + end-start

average = str(total/10)
print("Time in seconds:"+ average)
