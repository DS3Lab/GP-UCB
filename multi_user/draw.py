import random
import numpy as np
from matplotlib import pylab as plt

time_ = []
for line in open("test_time.txt",'r'):
	line = line.strip("\n").split("\t")
	time_.append(line)

accu = []
for line in open("test4.txt",'r'):
	line = line.strip("\n").split("\t")
	accu.append(line)
print accu


plt.style.use('ggplot')
fig, ax1 = plt.subplots()
ax1.set_xlabel('time')
ax1.set_ylabel('Current Sum of Accuracy of all users')

max_accu=[0,0,0,0]

x_time=[]
y_accu=[]

sum_time = 0
sum_accu = 0

for line in open("2rr_0132.txt",'r'):
	line = line.strip("\n").split(" ")
	sum_time = sum_time + float(time_[int(line[0])][int(line[1])])
	x_time.append(sum_time)

	if accu[int(line[0])][int(line[1])] > max_accu[int(line[0])]:
		print line[0]+ " " + line[1]
		print accu[int(line[0])][int(line[1])]
		sum_accu = sum_accu - float(max_accu[int(line[0])]) + float(accu[int(line[0])][int(line[1])])
		max_accu[int(line[0])] = accu[int(line[0])][int(line[1])]
	y_accu.append(sum_accu)
plt.semilogx(x_time, y_accu, 'b',marker='.', label = "2-RR-order1")
print "max_accu "+str(max_accu[0])
print "max_accu "+str(max_accu[1])
print "max_accu "+str(max_accu[2])
print "max_accu "+str(max_accu[3])


max_accu=[0,0,0,0]

x_time=[]
y_accu=[]

sum_time = 0
sum_accu = 0

for line in open("2rr_0123.txt",'r'):
	line = line.strip("\n").split(" ")
	sum_time = sum_time + float(time_[int(line[0])][int(line[1])])
	x_time.append(sum_time)

	if accu[int(line[0])][int(line[1])] > max_accu[int(line[0])]:
		print line[0]+ " " + line[1]
		print accu[int(line[0])][int(line[1])]
		sum_accu = sum_accu - float(max_accu[int(line[0])]) + float(accu[int(line[0])][int(line[1])])
		max_accu[int(line[0])] = accu[int(line[0])][int(line[1])]
	y_accu.append(sum_accu)
plt.semilogx(x_time, y_accu, 'c',marker='.', label = "2-RR-order2")
print "max_accu "+str(max_accu[0])
print "max_accu "+str(max_accu[1])
print "max_accu "+str(max_accu[2])
print "max_accu "+str(max_accu[3])

max_accu=[0,0,0,0]

x_time=[]
y_accu=[]

sum_time = 0
sum_accu = 0

for line in open("2rr_0213.txt",'r'):
	line = line.strip("\n").split(" ")
	sum_time = sum_time + float(time_[int(line[0])][int(line[1])])
	x_time.append(sum_time)

	if accu[int(line[0])][int(line[1])] > max_accu[int(line[0])]:
		print line[0]+ " " + line[1]
		print accu[int(line[0])][int(line[1])]
		sum_accu = sum_accu - float(max_accu[int(line[0])]) + float(accu[int(line[0])][int(line[1])])
		max_accu[int(line[0])] = accu[int(line[0])][int(line[1])]
	y_accu.append(sum_accu)
plt.semilogx(x_time, y_accu, 'black',marker='.', label = "2-RR-order3")
print "max_accu "+str(max_accu[0])
print "max_accu "+str(max_accu[1])
print "max_accu "+str(max_accu[2])
print "max_accu "+str(max_accu[3])



max_accu=[0,0,0,0]

x_time=[]
y_accu=[]

sum_time = 0
sum_accu = 0

for line in open("multi_user_666.txt",'r'):
	line = line.strip("\n").split(" ")
	sum_time = sum_time + float(time_[int(line[0])][int(line[1])])
	x_time.append(sum_time)

	if accu[int(line[0])][int(line[1])] > max_accu[int(line[0])]:
		print line[0]+ " " + line[1]
		print accu[int(line[0])][int(line[1])]
		sum_accu = sum_accu - float(max_accu[int(line[0])]) + float(accu[int(line[0])][int(line[1])])
		max_accu[int(line[0])] = accu[int(line[0])][int(line[1])]
	y_accu.append(sum_accu)
print "max_accu "+str(max_accu[0])
print "max_accu "+str(max_accu[1])
print "max_accu "+str(max_accu[2])
print "max_accu "+str(max_accu[3])

plt.semilogx(x_time, y_accu, 'r',marker='x', label = "Most Variance drop")

max_accu=[0,0,0,0]

x_time=[]
y_accu=[]

sum_time = 0
sum_accu = 0

for line in open("random_0.txt",'r'):
	line = line.strip("\n").split(" ")
	sum_time = sum_time + float(time_[int(line[0])][int(line[1])])
	x_time.append(sum_time)

	if accu[int(line[0])][int(line[1])] > max_accu[int(line[0])]:
		print line[0]+ " " + line[1]
		print accu[int(line[0])][int(line[1])]
		sum_accu = sum_accu - float(max_accu[int(line[0])]) + float(accu[int(line[0])][int(line[1])])
		max_accu[int(line[0])] = accu[int(line[0])][int(line[1])]
	y_accu.append(sum_accu)
print "max_accu "+str(max_accu[0])
print "max_accu "+str(max_accu[1])
print "max_accu "+str(max_accu[2])
print "max_accu "+str(max_accu[3])

#plt.plot(x_time, y_accu, 'g',marker='.', label = "Random0")


max_accu=[0,0,0,0]

x_time=[]
y_accu=[]

sum_time = 0
sum_accu = 0

for line in open("multi_user_rr+variance_drop.txt",'r'):
	line = line.strip("\n").split(" ")
	sum_time = sum_time + float(time_[int(line[0])][int(line[1])])
	x_time.append(sum_time)

	if accu[int(line[0])][int(line[1])] > max_accu[int(line[0])]:
		print line[0]+ " " + line[1]
		print accu[int(line[0])][int(line[1])]
		sum_accu = sum_accu - float(max_accu[int(line[0])]) + float(accu[int(line[0])][int(line[1])])
		max_accu[int(line[0])] = accu[int(line[0])][int(line[1])]
	y_accu.append(sum_accu)
print "max_accu "+str(max_accu[0])
print "max_accu "+str(max_accu[1])
print "max_accu "+str(max_accu[2])
print "max_accu "+str(max_accu[3])

plt.semilogx(x_time, y_accu, 'y--',marker='x', label = "RR+Variance drop")


ax1.legend(loc=4)
plt.axis([-1000,25000,0.00,1.0])
plt.title("Multi-user cost-aware model selection")
plt.savefig("/users/serena/desktop/plus_log2")
