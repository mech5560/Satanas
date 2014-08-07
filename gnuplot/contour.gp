#!/bin/bash

gnuplot << EOF
unset key
set term eps enhanced color solid  lw 2 font  'Helvetica,12'
set size ratio -1
set output '$1.eps'
set title "$1"
set contour base
set xrange[0:$2]
set yrange[0:$3]
unset surface
set view map
set palette gray
splot "$1.dat" matrix with linespoints pt 3 ps 0.1 palette gray
EOF
epstopdf $1.eps
rm $1.eps
okular $1.pdf
