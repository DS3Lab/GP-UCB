import random
import numpy as np
import math

# matrix: 10*100

prior=[]

fout = open("prior2.txt",'w')

# a is the mean-array of 100 algorithms, the algorithms are correlated with each other in the way that 
# every result got after applying the 100 algorithms is a draw from a Gaussian distribution (0.5, sqrt(0.025))
# let the mean of every algorithm satisfies a Gaussian distribution (0.5, sqrt(0.025))
mean = 0.5
variance = 0.025
sd = math.sqrt(variance)
a = np.random.normal(mean,sd,100) 
print a


# let every column be a Gaussian distribution with the same \sigma
for i in a:
	b = np.random.normal(i, 0.01, 10)
	for j in b:
		prior.append(j)

sampling_noise = 0.05 * variance
mark = 0
for i in range(len(prior)):
	fout.write(str(prior[i] + sampling_noise)+" ")
	mark = mark + 1
	if mark % 100 == 0:
		fout.write("\n")


# generate 10 test data, following the same Gaussian distribution
fout2 = open("test2.txt",'w')
test=[]
for i in a:
	b = np.random.normal(i, 0.01, 10)
	for j in b:
		test.append(j)

sampling_noise = 0.05 * variance

mark = 0
for i in range(len(test)):
	fout2.write(str(test[i] + sampling_noise)+" ")
	mark = mark + 1
	if mark % 100 == 0:
		fout2.write("\n")


