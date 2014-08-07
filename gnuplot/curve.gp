#!/bin/bash

gnuplot << EOF
unset key
set term eps enhanced color solid  lw 2 font  'Helvetica,8'
set output '$1.eps'
set title "$1"
set ylabel "amplitude"
set xlabel "y"
set xrange [0:$2]
set palette gray
plot "$1.dat" using $3 with linespoints pt 3 ps 0.1 lc rgb "#000000"
EOF
epstopdf $1.eps
rm $1.eps
okular $1.pdf
