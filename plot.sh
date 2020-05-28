#!/bin/bash

obs_file=$1

gnuplot -persist <<-EOFMarker

    set terminal png size 800, 600

    set output "kalman_filter_results_xhat.png"
    set title "Estimated state xhat"
    set xlabel "Observations"
    set ylabel "xhat"
    set grid
    plot -0.37727 title "true value" linewidth 5 linecolor rgb "gray", \
         "${obs_file}" using 1:3 with lines title "" linecolor 1 linewidth 2, \
         "${obs_file}" using 1:3:4 with yerrorbars linecolor 2 pointtype 7 pointsize 1 title "xhat"

    set output "kalman_filter_results_gain.png"
    set title "Estimated Kalman gain K"
    set ylabel "K"
    plot "${obs_file}" using 1:2 with lines linecolor 1 linewidth 2 title "K", \
         "${obs_file}" using 1:2 pointtype 7 title "" \


EOFMarker