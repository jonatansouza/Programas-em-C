#!/bin/bash

cd matrix_generator;
make;
cd ../fork;
make;
cd ../threads;
make;
cd ../single;
make;
cd ../;

if [ ! -d samples ]; then
  mkdir -p samples;
fi


for ((i=200; i <= 3200; i=i*2));
       do
         ./matrix_generator/main samples/matrix$i $i $i
       done;

if [ ! -d results/fork ]; then
  mkdir -p results/fork;
fi

if [ ! -d results/threads ]; then
  mkdir -p results/threads;
fi

if [ ! -d results/single ]; then
  mkdir -p results/single;
fi
echo "single"
echo "matriz 200 200"
./single/main samples/matrix200 samples/matrix200 >> results/single/result200.out
echo "matriz 400 400"
./single/main samples/matrix400 samples/matrix400  >> results/single/result400.out
echo "matriz 800 800"
./single/main samples/matrix800 samples/matrix800  >> results/single/result800.out
echo "matriz 1600 1600"
./single/main samples/matrix1600 samples/matrix1600  >> results/single/result1600.out
echo "matriz 3200 3200"
./single/main samples/matrix3200 samples/matrix3200  >> results/single/result3200.out

echo "****************************";

for ((i=2; i <= 4; i=i+1));
       do

          echo "$i Processos"
          echo "matriz 200 200"
          ./fork/main samples/matrix200 samples/matrix200 $i >> results/fork/result200_$i.out
          echo "matriz 400 400"
          ./fork/main samples/matrix400 samples/matrix400 $i >> results/fork/result400_$i.out
          echo "matriz 800 800"
          ./fork/main samples/matrix800 samples/matrix800 $i >> results/fork/result800_$i.out
          echo "matriz 1600 1600"
          ./fork/main samples/matrix1600 samples/matrix1600 $i >> results/fork/result1600_$i.out
          echo "matriz 3200 3200"
          ./fork/main samples/matrix3200 samples/matrix3200 $i >> results/fork/result3200_$i.out

          echo "****************************";
          echo "$i Threads"

          echo "matriz 200 200"
          ./threads/main samples/matrix200 samples/matrix200 $i >> results/threads/result200_$i.out
          echo "matriz 400 400"
          ./threads/main samples/matrix400 samples/matrix400 $i >> results/threads/result400_$i.out
          echo "matriz 800 800"
          ./threads/main samples/matrix800 samples/matrix800 $i >> results/threads/result800_$i.out
          echo "matriz 1600 1600"
          ./threads/main samples/matrix1600 samples/matrix1600 $i >> results/threads/result1600_$i.out
          echo "matriz 3200 3200"
          ./threads/main samples/matrix3200 samples/matrix3200 $i >> results/threads/result3200_$i.out

          echo "****************************";
       done
