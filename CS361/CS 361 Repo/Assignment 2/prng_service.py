import random
import sys

done = False

f = open('prng-service.txt', 'r')
content = f.read()
if content == "run":
    f.close()
    f = open('prng-service.txt', 'w')
    f.write(str(random.randrange(1, 377, 1)))
    done = True
f.close()
sys.exit(done)