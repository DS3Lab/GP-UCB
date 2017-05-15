fout = open("cost2.txt",'w')

l=[]
for line in open("cost.txt",'r'):
	line = line.strip(" \n").split(" ")
	for i in range(len(line)):
		l.append(line[i])
for i in l:
	fout.write(str(float(i)*50)+" ")
fout.write("\n")


for i in l:
	fout.write(str(float(i)*100)+" ")
fout.write("\n")

for i in l:
	fout.write(str(float(i)*150)+" ")
fout.write("\n")

for i in l:
	fout.write(str(float(i)*200)+" ")
fout.write("\n")

for i in l:
	fout.write(str(float(i)*250)+" ")
fout.write("\n")
