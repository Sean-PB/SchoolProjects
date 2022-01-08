import os
import time
import sys

done = False

f = open ('image-service.txt', 'r')
content = f.read()
if content.isdigit():
    f.close()
    f = open ('image-service.txt', 'w')
    f.write(os.getcwd() + "\images\\pic (" + content + ").jpg")
f.close()