#!/bin/bash

cd matrix_generator;
make clean;
cd ../mpi
make clean;
cd ../single;
make clean;
cd ../;
rm -rf results;
rm -rf samples;
