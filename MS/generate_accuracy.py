import sys


str1 = 'ucb_with_prior_without_googlenet.txt'
str2 = 'test_without_googlenet.txt'
fout1 = open("ucb_accuracy1.txt",'w')



str3 = 'ucb_without_prior_without_googlenet.txt'
str4 = 'test_without_googlenet.txt'
fout2 = open("ucb_accuracy2.txt",'w')


str5 = 'ucb_with_prior_with_googlenet.txt'
str6 = 'test_second.txt'
fout3 = open("ucb_accuracy3.txt",'w')

str7 = 'ucb_without_prior_with_googlenet.txt'
str8 = 'test_second.txt'
fout4 = open("ucb_accuracy4.txt",'w')

#------------------------------

b=[]
for line in open(str2):
	line = line.split("\t")
	a=[]
	for i in range(0, len(line)):
		a.append(line[i])
		print a
	b.append(a)


data_id = 0
for line in open(str1):
	max_accuracy = 0
	accu_list = b[data_id]
	line = line.split(" ")
	for i in range(8):
		id_ = int(line[i]) - 1
		print data_id,i,id_
		accu = accu_list[id_].strip('\n')
		if accu > max_accuracy:
			max_accuracy = accu
		fout1.write(str(max_accuracy)+" ")
	data_id = data_id + 1
	fout1.write("\n")

#---------------------

b=[]
for line in open(str4):
	line = line.split("\t")
	a=[]
	for i in range(0, len(line)):
		a.append(line[i])
		print a
	b.append(a)


data_id = 0
for line in open(str3):
	max_accuracy = 0
	accu_list = b[data_id]
	line = line.split(" ")
	for i in range(8):
		id_ = int(line[i]) - 1
		print data_id,i,id_
		accu = accu_list[id_].strip('\n')
		if accu > max_accuracy:
			max_accuracy = accu
		fout2.write(str(max_accuracy)+" ")
	data_id = data_id + 1
	fout2.write("\n")

	#-----------------

b=[]
for line in open(str6):
	line = line.split("\t")
	a=[]
	for i in range(0, len(line)):
		a.append(line[i])
		print a
	b.append(a)


data_id = 0
for line in open(str5):
	max_accuracy = 0
	accu_list = b[data_id]
	line = line.split(" ")
	for i in range(9):
		id_ = int(line[i]) - 1
		print data_id,i,id_
		accu = accu_list[id_].strip('\n')
		if accu > max_accuracy:
			max_accuracy = accu
		fout3.write(str(max_accuracy)+" ")
	data_id = data_id + 1
	fout3.write("\n")


#---------------------------------

b=[]
for line in open(str8):
	line = line.split("\t")
	a=[]
	for i in range(0, len(line)):
		a.append(line[i])
		print a
	b.append(a)


data_id = 0
for line in open(str7):
	max_accuracy = 0
	accu_list = b[data_id]
	line = line.split(" ")
	for i in range(9):
		id_ = int(line[i]) - 1
		print data_id,i,id_
		accu = accu_list[id_].strip('\n')
		if accu > max_accuracy:
			max_accuracy = accu
		fout4.write(str(max_accuracy)+" ")
	data_id = data_id + 1
	fout4.write("\n")



