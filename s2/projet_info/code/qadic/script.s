#!/bin/bash

gcc -c qadic/*.c $1
gcc -o main *.o -lgmp -lflint
rm *.o
