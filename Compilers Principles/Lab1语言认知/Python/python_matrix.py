from numpy import *
import numpy as np
import datetime
maxn = 300
start = datetime.datetime.now()

arr1 = np.random.randint(0, 100, size = [maxn, maxn])
arr2 = np.random.randint(0, 100, size = [maxn, maxn])
arr3 = np.random.randint(0, 100, size = [maxn, maxn])

for i in range(maxn):
    for j in range(maxn):
        for k in range(maxn):
        	arr3[i][j] += arr1[i][k] * arr2[k][j]

#print(arr3)

end = datetime.datetime.now()
print("python的运行时间：", end - start)