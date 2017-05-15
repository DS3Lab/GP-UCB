str1 = 'plain_ucb.txt'
str2 = 'test.txt'
fout1 = open("ucb_accuracy.txt",'w')

#------------------------------

b=[]
for line in open(str2):
	line = line.strip(" \n").split(" ")
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
	for i in range(100):
		id_ = int(line[i]) - 1
		print data_id,i,id_
		accu = accu_list[id_].strip('\n')
		if accu > max_accuracy:
			max_accuracy = accu
		fout1.write(str(max_accuracy)+" ")
	data_id = data_id + 1
	fout1.write("\n")
fout1.close()

str1 = 'plain_ei_fixed.txt'
str2 = 'test.txt'
fout1 = open("ei_accuracy_fixed.txt",'w')

#------------------------------

b=[]
for line in open(str2):
	line = line.strip(" \n").split(" ")
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
	for i in range(100):
		id_ = int(line[i]) - 1
		print data_id,i,id_
		accu = accu_list[id_].strip('\n')
		if accu > max_accuracy:
			max_accuracy = accu
		fout1.write(str(max_accuracy)+" ")
	data_id = data_id + 1
	fout1.write("\n")
fout1.close()
