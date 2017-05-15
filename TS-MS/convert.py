fout = open("2.txt",'w')
for line in open("prior.txt",'r'):
	line = line.strip("\n")
	line = line.split(" ")
	for i in range(len(line)):
		fout.write(str(line[i]) + "\t")
	fout.write("\n")
