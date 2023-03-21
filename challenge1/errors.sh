#!/bin/bash
# A script that launches gnuplot on the file result.dat
#
# you can also launch gnuplot and type the command at the gnuplot prompt
#
# replot "result.dat" u 1:4 w lp lw 2 title "err"

gnuplot -persist <<EOF
set term x11
plot "errors.dat" u 1:2 w lp lw 2 title "err", "errors.dat" u 1:3 w lp lw 2 title "H1","errors.dat" u 1:4 w lp lw 2 title "H2"
pause -1
EOF
