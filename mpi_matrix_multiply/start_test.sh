#!/bin/bash

MATRIX_INI_SIZE=500
MATRIX_INI_INC=500
MATRIX_INI_FINAL=1000

PROCESS_INI=2
PROCESS_INI_INC=1
PROCESS_INI_FINAL=4


cd matrix_generator;
make;
cd ../mpi;
make;
cd ../single;
make;
cd ../;

if [ ! -d samples ]; then
  mkdir -p samples;
  echo "****************************";
  for ((i="$MATRIX_INI_SIZE"; i <= "$MATRIX_INI_FINAL"; i=i+"$MATRIX_INI_INC"));
         do
           ./matrix_generator/main samples/matrix$i $i $i
         done
fi

if [ ! -d results/mpi ]; then
  mkdir -p results/mpi;
fi

if [ ! -d results/single ]; then
  mkdir -p results/single;
fi
echo "****************************";
echo "single"
for ((i="$MATRIX_INI_SIZE"; i <= "$MATRIX_INI_FINAL"; i=i+"$MATRIX_INI_INC"));
       do
         echo "matriz $i $i"
          { time ./single/main samples/matrix$i samples/matrix$i ;}   &>> results/single/$i.out
       done;
echo "****************************";
echo "MPI"

for ((i="$PROCESS_INI"; i <= "$PROCESS_INI_FINAL"; i=i+"$PROCESS_INI_INC"));
       do
         for ((j="$MATRIX_INI_SIZE"; j <= "$MATRIX_INI_FINAL"; j=j+"$MATRIX_INI_INC"));
                 do
                  echo "matriz $j $j com $i Processos"
                  { time mpirun -np "$i" ./mpi/main samples/matrix$j samples/matrix$j  ;}  &>> results/mpi/${j}_${i}.out
            done
done
