import random
import numpy as np
from matplotlib import pylab as plt



ucb=[]
for line in open("ucb_accuracy.txt",'r'):
	ucb.append(line)


ei=[]
for line in open("ei_accuracy_fixed.txt",'r'):
	ei.append(line)
print ei


test=[]
for line in open("test.txt",'r'):
	test.append(line)



size=[]
for i in range(100):
	size.append(i)


for i in range (5):
	plt.style.use('ggplot')
	fig, ax1 = plt.subplots()
	ax1.set_xlabel('# trials')
	ax1.set_ylabel('Current Best Accuracy')
	tmp_test = test[i].strip(" \n").split(" ")
	a_ucb = ucb[i].strip(" \n").split(" ")
	a_ei = ei[i].strip(" \n").split(" ")


	r0=[]
	r1=[]

	max0 = 0
	max1 = 0

	sample_list=[]
	for j in range(100):
		sample_list.append(j)

	a = random.sample(sample_list,100)

	for aa in a:
		if float(tmp_test[int(aa)]) > max0:
			max0 = float(tmp_test[int(aa)])
		r0.append(max0)

	a = random.sample(sample_list,100)
	for aa in a:
		if float(tmp_test[int(aa)]) > max1:
			max1 = float(tmp_test[int(aa)])
		r1.append(max1)

	plt.plot(size, a_ucb, 'b',marker='x', label = "GP-UCB")
	#plt.plot(size, a_without_prior, 'r',marker='x', label = "GP-UCB (without prior)")
	plt.plot(size, a_ei, 'r--',marker='.', label = "EI")
	#plt.plot(size, a_ei_without_prior, 'c--',marker='.', label = "GP-EI (without prior)")
	#plt.plot(size, a_latest_first, 'y--', marker='.', label = "Latest network first")
	#plt.plot(size, a_most_cited, 'b--', marker='.', label = "Most cited network first")



	plt.scatter(size, r0, c = 'y', s = 100, marker='.', label = "Random0")
	plt.scatter(size, r1, c = 'c', s = 100, marker='.', label = "Random1")
	#plt.scatter(size, r2, c = 'r', s = 200, marker='x', label = "Random2")
	#plt.scatter(size, r3, c = 'y', s = 200, marker='x', label = "Random3")
	#plt.scatter(size, r4, c = 'b', s = 200, marker='x', label = "Random4")


	ax1.legend(loc=4)
	
	
	plt.axis([-10,100,0.2,0.9])
#	elif i == 1:
#		plt.axis([0,8,0.02,0.06])
#	elif i == 2:
#		plt.axis([0,8,0.03,0.15])
#	elif i == 3:
#		plt.axis([0,8,0.18,0.32])
#	elif i == 4:
#		plt.axis([0,8,0.25,0.38])
#	elif i == 5:
#		plt.axis([0,8,0.38,0.57])
#	elif i == 6:
#		plt.axis([0,8,0.45,0.68])
#	elif i == 7:
#		plt.axis([0,8,0.55,0.74])
#	elif i == 8:
#		plt.axis([0,8,0.5,0.67])
	print i
	if i == 0:
		plt.title("Single User Model Selection Without Cost")
		print "hello"
		plt.savefig("/users/serena/desktop/setting1/1")
	elif i == 1:
		plt.title("Single User Model Selection Without Cost")
		plt.savefig("/users/serena/desktop/setting1/2")
	elif i == 2:
		plt.title("Single User Model Selection Without Cost")
		plt.savefig("/users/serena/desktop/setting1/3")
	elif i == 3:
		plt.title("Single User Model Selection Without Cost")
		plt.savefig("/users/serena/desktop/setting1/4")
	elif i == 4:
		plt.title("Single User Model Selection Without Cost")
		plt.savefig("/users/serena/desktop/setting1/5")
#	elif i == 5:
#		plt.title("Model selection (accuracy)[Caltech101]")
#		plt.savefig("/users/serena/desktop/with/Caltech-101")
#	elif i == 6:
#		plt.title("Model selection (accuracy)[Oxford5k]")
#		plt.savefig("/users/serena/desktop/with/Oxford5k")
#	elif i == 7:
#		plt.title("Model selection (accuracy)[Oxford-102]")
#		plt.savefig("/users/serena/desktop/with/Oxford-102")
#	elif i == 8:
#		plt.title("Model selection (accuracy)[Cifar100]")
#		plt.savefig("/users/serena/desktop/with/Cifar100")
	











