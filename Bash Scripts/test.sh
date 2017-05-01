#!/bin/bash
read string
./Serial $string;
./Parallel1 $string;
./Parallel2_2T $string;
./Parallel2_4T $string;

