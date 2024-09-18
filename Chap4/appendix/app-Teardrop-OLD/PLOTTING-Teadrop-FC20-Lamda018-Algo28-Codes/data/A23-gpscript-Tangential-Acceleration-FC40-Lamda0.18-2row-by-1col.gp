
## File: Butterfly-Tangential-Acceleration-FC20-Lamda0.18-Algo23.gp
## Date: Wed 27 Sep 2023 10:16:30 PM +08
## wruslan@HPLaptop-01-ub20:~$ 
## Plot as 2 rows BY 1 COLUMN

clear
# set size square
set autoscale
set grid

set xlabel "parameter (u)"
set ylabel "tangential-acceleration (mm/s2)"

# set multiplot layout 2,2 columns
set multiplot layout 2,1 columns

    set xrange [ 0.00 :  + 0.50]
    set yrange [ -60.00 :  +60.00]
	set title "Lamda0.18 Teardrop FC40"
    plot "FC40-data_calc_u_next.txt" using 2:13 with lines lw 2 linecolor black title "tang-accn"

    set xrange [ 0.50 :  + 1.00]
    set yrange [ -60.00 :  +60.00]
	set title "continue Lamda0.18 Teardrop FC40"
    plot "FC40-data_calc_u_next.txt" using 2:13 with lines lw 2 linecolor black title "tang-accn"
    
 
unset multiplot
    
    
    
