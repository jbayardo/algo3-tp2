#!/bin/bash
make clean;
make all;
echo "Generando casos de prueba";
pypy generate.py;
echo "Testeando cosas";
words=( random best worst )
for (( i = 1; i < 4; i++ ))
do
    for w in "${words[@]}"
    do
        echo $i $w
        algo3_tp2 ${i} experiments/test_${i}_complejidad_${w}.in experiments/test_${i}_complejidad_${w}.out 100
    done
done
cd experiments
git add *.sts
git commit -m "Agrego nuevos resultados"
git push
cd ..