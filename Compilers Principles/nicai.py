
from numpy import *
import numpy as np
import os
import os.path
maxn = 300

arr3 = np.random.randint(0, 100, size = [maxn, maxn])

for i in range(maxn):
    for j in range(maxn):
    	arr3[i][j] = 1

fileHandle = open('1.txt', 'w')
fileHandle.write(arr3)

#print(arr3)