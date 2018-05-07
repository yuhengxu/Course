from numpy import *
import numpy as np
import datetime

start = datetime.datetime.now()

arr1 = np.random.randint(0, 100, size = [1000, 1000])
arr2 = np.random.randint(0, 100, size = [1000, 1000])
arr3 = np.dot(arr1, arr2)
print(arr3)

end = datetime.datetime.now()
print("调用numpy的运行时间", end - start)