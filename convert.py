#!/home/julian/Software/anaconda/bin/python
import scipy
import os
import re
import pandas as pd
# Este script larga output.csv, con el formato que buscamos para que lo tome
# el software para graficar, Tableau.

split = {
    'default': 100
}

sizes2 = [(top, l) for top in xrange(1, 100) for l in xrange(2, max(top + 1, 3))]

dataset = []

files = map(lambda x: 'experiments/'+x, os.listdir('experiments'))
#files += map(lambda x: 'tests/'+x, os.listdir('tests'))

for fname in files:
    if fname[-3:] != 'sts':
        continue

    matches = re.match(r"^(experiments|tests)\/test_([1-3])_(.*)?\.sts$", fname)
    method = int(matches.group(2).strip())
    name = matches.group(3).strip()

    with open(fname, 'r') as handle:
        data = handle.read()

    data = data.strip().split('\n')

    for line in data:
        if line.strip() == '':
            continue

        line = line.strip().split('\t\t\t')
        line[1] = line[1].strip().split(',')

        try:
            spl = split[name]
        except:
            spl = split['default']

        line[1] = [line[1][i:i+spl] for i in range(0, len(line[1]), spl)]

        if method == 2:
            for case, measures in enumerate(line[1]):
                (n, l) = sizes2[case]

                measures = sorted(measures)

                # Podo un 10% de las muestras
                measures = measures[10:-10]

                for index, measure in enumerate(measures):
                    output = {
                        'name': name,
                        'method': method,
                        'case': case + 1,
                        'run': index + 1,
                        'N': n,
                        'L': l,
                        'timer': line[0],
                        'value': int(measure),
                    }

                    dataset.append(output)
        else:
            for case, measures in enumerate(line[1]):
                measures = sorted(measures)

                # Podo un 10% de las muestras
                measures = measures[10:-10]

                for index, measure in enumerate(measures):
                    output = {
                        'name': name,
                        'method': method,
                        'case': case + 1,
                        'run': index + 1,
                        'timer': line[0],
                        'value': int(measure),
                    }

                    dataset.append(output)

df = pd.DataFrame(dataset)
df.to_csv('output.csv', index=False)

