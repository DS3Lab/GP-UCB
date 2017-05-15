has=[]
fout=open("l.txt",'w')
for line in open("multi_user_rr+variance_drop.txt",'r'):
	line = line.strip("\n").split(" ")
	if (line[0] == '1'):
		has.append(int(line[1]))
		print has
for i in range(100):
	if i not in has:
		fout.write(str(1)+" "+str(i)+"\n")
