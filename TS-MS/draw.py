import random
import numpy as np
from matplotlib import pylab as plt


test_time=[]
for line in open("test_time.txt",'r'):
	test_time.append(line)

test_accu=[]
for line in open("test.txt",'r'):
	test_accu.append(line.strip("\n"))

gp_ucb=[]
for line in open("gp-ucb.txt",'r'):
	gp_ucb.append(line.strip(" "))

ei=[]
for line in open("ei_predict.txt",'r'):
	ei.append(line.strip(" "))

ei0=[]
for line in open("ei0.txt",'r'):
	ei0.append(line.strip(" "))

i = 0
for line in open("predict.txt",'r'):
	plt.style.use('ggplot')
	fig, ax1 = plt.subplots()
	ax1.set_xlabel('time')
	ax1.set_ylabel('Current Best Accuracy')

	best_accuracy = 0
	line = line.strip(" \n").split(" ")

	gp_tmp = gp_ucb[i].split(" ")
	ei_tmp = ei[i].split(" ")
	ei0_tmp = ei0[i].split(" ")

	print line
	sum_time = 0
	time_ =[]
	curren_accu=[]
	accu = test_accu[i]
	accu = accu.split("\t")
	print accu
	t = test_time[i]
	t = t.split("\t")
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

	plt.semilogx(time_, curren_accu, 'g',marker='.', label = "EI/time")

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

	plt.semilogx(time_, curren_accu, 'y',marker='.', label = "EI")

	ax1.legend(loc=4)

	if i == 0:
		plt.axis([-1000,9000,0.02,0.06])
	elif i == 1:
		plt.axis([-1000,9000,0.03,0.15])
	elif i == 2:
		plt.axis([-1000,9000,0.18,0.32])
	elif i == 3:
		plt.axis([-1000,9000,0.25,0.38])
	elif i == 4:
		plt.axis([-1000,9000,0.38,0.57])
	elif i == 5:
		plt.axis([-1000,9000,0.45,0.68])
	elif i == 6:
		plt.axis([-1000,9000,0.55,0.74])
	elif i == 7:
		plt.axis([-1000,9000,0.5,0.67])

	if i == 0:
		plt.title("Cost Sensitive Model Selection [Sculpture6k]")
		plt.savefig("/users/serena/desktop/cost3/Sculpture6k")
	elif i == 1:
		plt.title("Cost Sensitive Model Selection [CUB-200]")
		plt.savefig("/users/serena/desktop/cost3/CUB-200")
	elif i == 2:
		plt.title("Cost Sensitive Model Selection [MIT-67]")
		plt.savefig("/users/serena/desktop/cost3/MIT-67")
	elif i == 3:
		plt.title("Cost Sensitive Model Selection [voc2012]")
		plt.savefig("/users/serena/desktop/cost3/VOC2012")
	elif i == 4:
		plt.title("Cost Sensitive Model Selection [Caltech101]")
		plt.savefig("/users/serena/desktop/cost3/Caltech-101")
	elif i == 5:
		plt.title("Cost Sensitive Model Selection [Oxford5k]")
		plt.savefig("/users/serena/desktop/cost3/Oxford5k")
	elif i == 6:
		plt.title("Cost Sensitive Model Selection [Oxford-102]")
		plt.savefig("/users/serena/desktop/cost3/Oxford-102")
	elif i == 7:
		plt.title("Cost Sensitive Model Selection [Cifar100]")
		plt.savefig("/users/serena/desktop/cost3/Cifar100")

	i = i + 1
