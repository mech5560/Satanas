#!/bin/bash
awk '{
       for (f = 1; f <= NF; f++) { a[NR, f] = $f } 
     }
     NF > nf { nf = NF }
     END {
       for (f = 1; f <= nf; f++) {
           for (r = 1; r <= NR; r++) {
               printf a[r, f] (r==NR ? RS : FS)
           }
       }
    }' $1.dat>>$2.dat


gnuplot << EOF
unset key
set term eps enhanced color solid  lw 2 font  'Helvetica,8'
set output '$2.eps'
set title "$2"
set ylabel "amplitude"
set xlabel "X"
set xrange [0:$3]
set palette gray
plot "$2.dat" using $4 with linespoints pt 3 ps 0.1 lc rgb "#000000"
EOF
epstopdf $2.eps
rm $2.eps
okular $2.pdf
