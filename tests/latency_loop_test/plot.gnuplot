set title "Round-Trip Time for an Input Connected to an Output" font 'Arial-Bold'

set offset 0,0,.5,.5
set autoscale fix
set xlabel "Trial" font 'Arial'
set ylabel "Time (microseconds)" font 'Arial'

stats 'test_result.dat' using ($1/1000) prefix 'A'

plot 'test_result_no_outliers.dat' using ($1/1000) with points notitle pointtype 7 lt rgb "blue", \
     A_mean title "Mean" lw 2
