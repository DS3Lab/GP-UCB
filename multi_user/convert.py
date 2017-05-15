fout = open("test44.txt",'w')

#fout2 = open("test_time2.txt",'w')

for line in open("test4.txt",'r'):
	line = line.strip("\n").split("\t")
	for i in range(len(line)):
		fout.write(str(line[i]) + " ")
	fout.write("\n")

#for line in open("test_time.txt",'r'):
#	line = line.strip("\n").split("\t")
#	for i in range(len(line)):
#		fout2.write(str(line[i]) + " ")
#	fout2.write("\n")