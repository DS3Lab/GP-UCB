fout = open("reverse_cost.txt",'w')

for line in open('test.txt','r'):
	line = line.strip(" \n").split(" ")
	for i in range(len(line)):
		a = 1.0 / float(line[i])
		fout.write(str(a)+" ")
	fout.write('\n')
fout.close()


fout2 = open("r_cost.txt",'w')
for line in open("reverse_cost.txt",'r'):
	line = line.strip(" \n").split(" ")
	sum_ = 0
	for i in range(len(line)):
		sum_ = sum_ + float(line[i])
	average = sum_ * 1.0 / len(line)
	for i in range(len(line)):
		fout2.write(str(float(line[i]) / average)+" ")
	fout2.write("\n")
fout2.close()

