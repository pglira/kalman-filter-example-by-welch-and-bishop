#!/bin/bash

obs_file=$1

gnuplot -persist <<-EOFMarker
    set terminal png size 800, 600
    set output "kalman_filter_results.png"
    set title "Kalman filter results"
    set xlabel "Observations"
    set ylabel "Status estimate"
    set grid
    plot "${obs_file}" using 1:3 with lines title "", \
    "${obs_file}" using 1:3:4 with yerrorbars pointtype 7 pointsize 1 title "xhat"
EOFMarker