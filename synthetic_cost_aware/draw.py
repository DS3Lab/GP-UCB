import random
import numpy as np
from matplotlib import pylab as plt


test_time=[]
for line in open("s_cost.txt",'r'):
	test_time.append(line)


test_accu=[]
for line in open("test.txt",'r'):
	test_accu.append(line.strip("\n"))

gp_ucb=[]
for line in open("plain_ucb.txt",'r'):
	gp_ucb.append(line.strip(" "))

# ei/time
ei=[]
for line in open("ei_result.txt",'r'):
	ei.append(line.strip(" "))

# ei
ei0=[]
for line in open("plain_ei.txt",'r'):
	ei0.append(line.strip(" "))

i = 0
for line in open("ucb_time_result_square.txt",'r'):
	plt.style.use('ggplot')
	fig, ax1 = plt.subplots()
	ax1.set_xlabel('cost (time)')
	ax1.set_ylabel('Current Best Accuracy')

	best_accuracy = 0
	line = line.strip(" \n").split(" ")

	gp_tmp = gp_ucb[i].strip(" \n").split(" ")
	ei_tmp = ei[i].strip(" \n").split(" ")
	ei0_tmp = ei0[i].strip(" \n").split(" ")

	print line
	sum_time = 0
	time_ =[]
	curren_accu=[]
	accu = test_accu[i]
	accu = accu.strip(" \n").split(" ")
	print accu
	t = test_time[i]
	t = t.split(" ")
	for j in range(len(line)):
		index = int(line[j]) - 1
		if (accu[index] > best_accuracy):
			best_accuracy = accu[index]
			curren_accu.append(best_accuracy)
		else:
			curren_accu.append(best_accuracy)
		sum_time = float(sum_time) + float(t[index])
		time_.append(sum_time)
	plt.semilogx(time_, curren_accu, 'b',marker='x', label = "Cost-Aware-GP-UCB")

	best_accuracy = 0
	curren_accu=[]
	sum_time=0
	time_=[]


	for j in range(len(gp_tmp)):
		index = int(gp_tmp[j]) - 1
		if (accu[index] > best_accuracy):
			best_accuracy = accu[index]
			curren_accu.append(best_accuracy)
		else:
			curren_accu.append(best_accuracy)
		sum_time = float(sum_time) + float(t[index])
		time_.append(sum_time)

	plt.semilogx(time_, curren_accu, 'r',marker='x', label = "GP-UCB")

	best_accuracy = 0
	curren_accu=[]
	sum_time=0
	time_=[]


	for j in range(len(ei_tmp)):
		index = int(ei_tmp[j]) - 1
		if (accu[index] > best_accuracy):
			best_accuracy = accu[index]
			curren_accu.append(best_accuracy)
		else:
			curren_accu.append(best_accuracy)
		sum_time = float(sum_time) + float(t[index])
		time_.append(sum_time)

	#plt.semilogx(time_, curren_accu, 'g',marker='.', label = "EI/time")

	best_accuracy = 0
	curren_accu=[]
	sum_time=0
	time_=[]


	for j in range(len(ei0_tmp)):
		index = int(ei0_tmp[j]) - 1
		if (accu[index] > best_accuracy):
			best_accuracy = accu[index]
			curren_accu.append(best_accuracy)
		else:
			curren_accu.append(best_accuracy)
		sum_time = float(sum_time) + float(t[index])
		time_.append(sum_time)

	#plt.semilogx(time_, curren_accu, 'y',marker='.', label = "EI")


	ax1.legend(loc=4)

	
	plt.axis([0,300,0.0,0.9])


	if i == 0:
		plt.title("Single User Cost Sensitive Model Selection")
		plt.savefig("/users/serena/desktop/setting2/sq1")
	elif i == 1:
		plt.title("Single User Cost Sensitive Model Selection")
		plt.savefig("/users/serena/desktop/setting2/sq2")
	elif i == 2:
		plt.title("Single User Cost Sensitive Model Selection")
		plt.savefig("/users/serena/desktop/setting2/sq3")
	elif i == 3:
		plt.title("Single User Cost Sensitive Model Selection")
		plt.savefig("/users/serena/desktop/setting2/sq4")
	elif i == 4:
		plt.title("Single User Cost Sensitive Model Selection")
		plt.savefig("/users/serena/desktop/setting2/sq5")

	i = i + 1
