#!/bin/bash

cd matrix_generator;
make clean;
cd ../fork 
make clean;
cd ../threads;
make clean;
cd ../single;
make clean;
cd ../; 
rm -rf results;
rm -rf samples;
