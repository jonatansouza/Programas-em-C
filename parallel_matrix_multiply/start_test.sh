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
  for ((i=500; i <= 2000; i=i+500));
         do
           ./matrix_generator/main samples/matrix$i $i $i
         done;
fi

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
for ((i=500; i <= 2000; i=i+500));
       do
         echo "matriz $i $i"
         { time ./single/main samples/matrix$i samples/matrix$i ;}   &>> results/single/$i.out

       done;

echo "****************************";

for ((i=2; i <= 8; i=i+1));
       do
         for ((j=500; j <= 2000; j=j+500));
                do
                  echo "matriz $j $j com $i Processos"
                  { time ./fork/main samples/matrix$j samples/matrix$j "$i" ;} &>> results/fork/${j}_${i}.out
            done
       done

 echo "****************************";
for ((i=2; i <= 8; i=i+1));
    do
        for ((j=500; j <= 2000; j=j+500));
               do
                   echo "matriz $j $j com $i Threads"
                   { time ./threads/main samples/matrix$j samples/matrix$j "$i"  ;}  &>> results/threads/${j}_${i}.out
              done
done
