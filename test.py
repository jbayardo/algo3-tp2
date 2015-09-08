#!/usr/bin/env python
import os
import re

files = map(lambda x: 'tests/'+x, os.listdir('tests'))

for fname in files:
    if fname[-2:] != 'in':
        continue

    if not os.path.isfile(fname[:-2] + 'expected'):
        print "Falta archivo de salida expected para " + fname
        continue

    matches = re.match(r"^tests\/test_([1-3])_(.*)\.in$", fname)

    method = matches.group(1).strip()
    outf = fname[:-2] + 'out'

    os.system('./algo3_tp2 {method} {fname} {outf}'.format(method=method, fname=fname, outf=outf))

    with open(outf, 'r') as handle:
        output = handle.read().strip()

    output = [x.strip() for x in output.split('\n') if x.strip() != '']

    with open(fname[:-2] + 'expected', 'r') as handle:
        expected = handle.read().strip()

    expected = [x.strip() for x in expected.split('\n') if x.strip() != '']

    fail = 0
    for index, lines in enumerate(zip(output, expected)):
        (line1, line2) = lines

        if line1 != line2:
            fail = 1
            print "Failure at index ", fname, ":", index, ": ", line1, line2
    if fail == 0:
        print "GOOOOD ", fname