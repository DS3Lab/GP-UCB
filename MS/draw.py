import random
import numpy as np
from matplotlib import pylab as plt



with_prior=[]
for line in open("ucb_accuracy3.txt",'r'):
	with_prior.append(line)
without_prior=[]
for line in open("ucb_accuracy4.txt",'r'):
	without_prior.append(line)

ei_with_prior=[]
for line in open("ei_accuracy3.txt",'r'):
	ei_with_prior.append(line)
print ei_with_prior
ei_without_prior=[]
for line in open("ei_accuracy4.txt",'r'):
	ei_without_prior.append(line)

latest=[]
for line in open("latest_first_with.txt",'r'):
	latest.append(line)
most_cited=[]
for line in open("cited_first_with.txt",'r'):
	most_cited.append(line)
test=[]
for line in open("test_second.txt",'r'):
	test.append(line)

latest_network_accuracy=[]

size= [0,1,2,3,4,5,6,7,8]

for i in range (9):
	plt.style.use('ggplot')
	fig, ax1 = plt.subplots()
	ax1.set_xlabel('# trials')
	ax1.set_ylabel('Current Best Accuracy')
	tmp_test = test[i].strip("\n").split("\t")
	a_with_prior = with_prior[i].strip(" \n").split(" ")
	a_without_prior = without_prior[i].strip(" \n").split(" ")
	a_ei_with_prior = ei_with_prior[i].strip(" \n").split(" ")
	print a_ei_with_prior
	a_ei_without_prior = ei_without_prior[i].strip(" \n").split(" ")
	a_latest_first = latest[i].strip(" \n").split(" ")
	a_most_cited = most_cited[i].strip("\n").split(" ")
	print a_most_cited
	r0=[]
	r1=[]

	max0 = 0
	max1 = 0

	a = random.sample([0,1,2,3,4,5,6,7,8],9)
	for aa in a:
		if float(tmp_test[int(aa)]) > max0:
			max0 = float(tmp_test[int(aa)])
		r0.append(max0)
	a = random.sample([0,1,2,3,4,5,6,7,8],9)
	for aa in a:
		if float(tmp_test[int(aa)]) > max1:
			max1 = float(tmp_test[int(aa)])
		r1.append(max1)
	#a = random.sample([0,1,2,3,4,5,6,7,8],9)
	#for aa in a:
	#	if float(tmp_test[int(aa)]) > max2:
	#		max2 = float(tmp_test[int(aa)])
	#	r2.append(max2)
	#a = random.sample([0,1,2,3,4,5,6,7,8],9)
	#for aa in a:
	#	if float(tmp_test[int(aa)]) > max3:
	#		max3 = float(tmp_test[int(aa)])
	#	r3.append(max3)
	#a = random.sample([0,1,2,3,4,5,6,7,8],9)
	#for aa in a:
	#	if float(tmp_test[int(aa)]) > max4:
	#		max4 = float(tmp_test[int(aa)])
	#	r4.append(max4)


##res
#
#a1_0 = [0.06, 0.2045 , 0.341, 0.5322 ]
#a1_1 =[0.06, 0.2036 ,  0.334,  0.5178     ]
#a1_2 =[0.064, 0.2453,    0.358 ,   0.54 ]

#a5_2 = [0.166   ,  0.29 , 0.53]
	plt.plot(size, a_with_prior, 'b',marker='x', label = "GP-UCB")
	#plt.plot(size, a_without_prior, 'r',marker='x', label = "GP-UCB (without prior)")
	plt.plot(size, a_ei_with_prior, 'r--',marker='.', label = "EI")
	#plt.plot(size, a_ei_without_prior, 'c--',marker='.', label = "GP-EI (without prior)")
	#plt.plot(size, a_latest_first, 'y--', marker='.', label = "Latest network first")
	#plt.plot(size, a_most_cited, 'b--', marker='.', label = "Most cited network first")



	#plt.scatter(size, r0, c = 'c', s = 100, marker='.', label = "Random0")
	#plt.scatter(size, r1, c = 'b', s = 100, marker='.', label = "Random1")
	#plt.scatter(size, r2, c = 'r', s = 200, marker='x', label = "Random2")
	#plt.scatter(size, r3, c = 'y', s = 200, marker='x', label = "Random3")
	#plt.scatter(size, r4, c = 'b', s = 200, marker='x', label = "Random4")


	ax1.legend(loc=4)
	
	if i == 0:
		plt.axis([0,8,0.52,0.78])
	elif i == 1:
		plt.axis([0,8,0.02,0.06])
	elif i == 2:
		plt.axis([0,8,0.03,0.15])
	elif i == 3:
		plt.axis([0,8,0.18,0.32])
	elif i == 4:
		plt.axis([0,8,0.25,0.38])
	elif i == 5:
		plt.axis([0,8,0.38,0.57])
	elif i == 6:
		plt.axis([0,8,0.45,0.68])
	elif i == 7:
		plt.axis([0,8,0.55,0.74])
	elif i == 8:
		plt.axis([0,8,0.5,0.67])
	
	if i == 0:
		plt.title("Model selection (accuracy)[Imagenet]")
		plt.savefig("/users/serena/desktop/with/ImageNet")
	elif i == 1:
		plt.title("Model selection (accuracy)[Sculpture6k]")
		plt.savefig("/users/serena/desktop/with/Sculpture6k")
	elif i == 2:
		plt.title("Model selection (accuracy)[CUB-200]")
		plt.savefig("/users/serena/desktop/with/CUB-200")
	elif i == 3:
		plt.title("Model selection (accuracy)[MIT-67]")
		plt.savefig("/users/serena/desktop/with/MIT-67")
	elif i == 4:
		plt.title("Model selection (accuracy)[voc2012]")
		plt.savefig("/users/serena/desktop/with/VOC2012")
	elif i == 5:
		plt.title("Model selection (accuracy)[Caltech101]")
		plt.savefig("/users/serena/desktop/with/Caltech-101")
	elif i == 6:
		plt.title("Model selection (accuracy)[Oxford5k]")
		plt.savefig("/users/serena/desktop/with/Oxford5k")
	elif i == 7:
		plt.title("Model selection (accuracy)[Oxford-102]")
		plt.savefig("/users/serena/desktop/with/Oxford-102")
	elif i == 8:
		plt.title("Model selection (accuracy)[Cifar100]")
		plt.savefig("/users/serena/desktop/with/Cifar100")
	











