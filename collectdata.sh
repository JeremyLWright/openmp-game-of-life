#!/bin/bash
export OMP_NUM_THREADS=6
echo -n "" > outputFile.m
echo -n "single_6 = [" >> outputFile.m
for i in {1..10}
do
    ./run-life 1000 1K.dat 5 0 >> outputFile.m
done
echo "];" >> outputFile.m

echo -n "rows_6 = [" >> outputFile.m
for i in {1..10}
do
    ./run-life 1000 1K.dat 5 1 >> outputFile.m
done
echo "];" >> outputFile.m

echo -n "col_6 = [" >> outputFile.m
for i in {1..10}
do
    ./run-life 1000 1K.dat 5 2 >> outputFile.m
done
echo "];" >> outputFile.m

echo -n "full_6 = [" >> outputFile.m
for i in {1..10}
do
    ./run-life 1000 1K.dat 5 3 >> outputFile.m
done
echo "];" >> outputFile.m
export OMP_NUM_THREADS=12
echo -n "single_12 = [" >> outputFile.m
for i in {1..10}
do
    ./run-life 1000 1K.dat 5 0 >> outputFile.m
done
echo "];" >> outputFile.m

echo -n "rows_12 = [" >> outputFile.m
for i in {1..10}
do
    ./run-life 1000 1K.dat 5 1 >> outputFile.m
done
echo "];" >> outputFile.m

echo -n "col_12 = [" >> outputFile.m
for i in {1..10}
do
    ./run-life 1000 1K.dat 5 2 >> outputFile.m
done
echo "];" >> outputFile.m

echo -n "full_12 = [" >> outputFile.m
for i in {1..10}
do
    ./run-life 1000 1K.dat 5 3 >> outputFile.m
done
echo "];" >> outputFile.m

export OMP_NUM_THREADS=24
echo -n "single_24 = [" >> outputFile.m
for i in {1..10}
do
    ./run-life 1000 1K.dat 5 0 >> outputFile.m
done
echo "];" >> outputFile.m

echo -n "rows_24 = [" >> outputFile.m
for i in {1..10}
do
    ./run-life 1000 1K.dat 5 1 >> outputFile.m
done
echo "];" >> outputFile.m

echo -n "col_24 = [" >> outputFile.m
for i in {1..10}
do
    ./run-life 1000 1K.dat 5 2 >> outputFile.m
done
echo "];" >> outputFile.m

echo -n "full_24 = [" >> outputFile.m
for i in {1..10}
do
    ./run-life 1000 1K.dat 5 3 >> outputFile.m
done
echo "];" >> outputFile.m
