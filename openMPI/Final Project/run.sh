#!/bin/bash
        for i in `seq 1 209`;
        do
                mpirun -np $i ./programFoundry >> results.txt
        done    
