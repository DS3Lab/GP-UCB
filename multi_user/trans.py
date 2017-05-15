fout = open("out.txt",'w')

for line in open("44.txt"):
	line = line.strip("\n")
	fout.write(str(line)+",")
