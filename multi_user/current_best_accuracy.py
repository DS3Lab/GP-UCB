test_accu = []
for line in open("test8.txt",'r'):
	test_accu.append(line)
fout = open("current_best_accuracy.txt",'w')

i = 0
for line in open("multi_user8.txt",'r'):
	tmp_accu = test_accu[i]
	tmp_accu = tmp_accu.split("\t")
	max_accu = 0
	line = line.strip(" \n").split(" ")
	for j in range(len(line)):
		accu = float(tmp_accu[int(line[j]) - 1])
		if accu > max_accu:
			max_accu = accu
		fout.write(str(max_accu) + " ")
	fout.write("\n")
	i = i + 1