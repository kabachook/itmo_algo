"""
Generate huge test for spantree task
"""

import random

n = 5000

v = set()

remain = n

while remain:
    u = (random.randint(-10000, 10000), random.randint(-10000, 10000))
    if not u in v:
        v.add(u)
        remain -= 1

with open("test.txt", "w+") as f:
    f.write(str(n)+'\n')
    for u in v:
        f.write(str(u[0]) + " " + str(u[1]) + "\n")
