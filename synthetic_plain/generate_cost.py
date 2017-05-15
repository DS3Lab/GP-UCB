# generate cost
import random
import numpy as np

fout3 = open("cost.txt",'w')
cost=np.random.rand(100)*2
print cost


# nmake sure that the mean of the cost is 1

for i in range(len(cost)):
	fout3.write(str(cost[i])+" ")