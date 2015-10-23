import fileinput

extend = ['Excercise 1 Generate Matrix Timer', 'Excercise 2 Generate Graph Timer', 'Excercise 3 Generate Graph Timer']

for line in fileinput.input():
	line = line.strip().split('\t\t\t')

	if line[0].strip() in extend:
		line[1] = ','.join([','.join([x.strip() for y in range(100)]) for x in line[1].split(',')])

	print '{0}\t\t\t{1}'.format(line[0].strip(),line[1].strip())