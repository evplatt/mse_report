set title "Measured Delay Times with Outliers" font 'Arial-Bold'

set offset 0,0,.5,.5
set autoscale fix
set xlabel "Trial" font 'Arial'
set ylabel "% of Max Time" font 'Arial'

stats 'memtest_results.dat' using 1 prefix 'A'
stats 'test_result.dat' using 1 prefix 'B'

plot 'memtest_results.dat' using ((($1-A_min)/(A_max-A_min))*100) with points title "Simple Write Access" pointtype 7 lt rgb "blue", \
	'test_result.dat' using ((($1-B_min)/(B_max-B_min))*100) with points title "GPIO Round Trip" pointtype 7 lt rgb "red"
