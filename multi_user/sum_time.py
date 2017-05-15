test_time=[]
for line in open("test_time.txt",'r'):
	test_time.append(line)

fout = open("sum_time.txt",'w')

i = 0
for line in open("multi_user8.txt",'r'):
	line = line.split(" ")
	tmp_test = test_time[i]
	tmp_test = tmp_test.split("\t")

	sum_ =0
	for j in range(len(line)):
		sum_ = sum_ + float(tmp_test[int(line[j])-1])
		fout.write(str(sum_) + " ")
	fout.write("\n")
	i = i+1
