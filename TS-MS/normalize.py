fout = open("time_normalized.txt",'w')

for line in open("time.txt",'r'):
	line = line.strip(" \n").strip(" ").split("\t")
	print line
	for i in range(len(line)):

		line[i] = float(line[i])*1.0/2250.0

		fout.write(str(line[i])+" ")
	fout.write("\n")