fout = open("scaled_time.txt",'w')

for line in open("time.txt",'r'):
	line = line.strip("\n").strip("\t").strip(" ").split("\t")
	sum_ = 0
	for i in range(len(line)):
		sum_ = sum_ + float(line[i])
	factor = sum_ * 1.0/9
	for i in range(len(line)):
		line[i] = float(line[i])*1.0/factor
		fout.write(str(line[i])+" ")
	fout.write("\n")
