
## File: Butterfly-Tangential-Acceleration-FC20-Lamda0.18-Algo23.gp
## Date: Wed 27 Sep 2023 10:16:30 PM +08
## wruslan@HPLaptop-01-ub20:~$ 
## Plot as 2 rows BY 1 COLUMN

clear
# set size square
set autoscale
set grid

set xlabel "parameter u"
set ylabel "tang-acceleration (mm/s2)"


# set multiplot layout 2,2 columns
set multiplot layout 2,1 columns

    set xrange [ 0.25 :  + 0.35]
    set yrange [ -60.00 :  +60.00]
    set title "Lamda = 0.18 SnaHyp FC20 Part1/2 "
    plot "SNAHYP-data-Lamda-018-FC20-U-vs-Tang-Accn.txt" using 2:13 with lines linecolor black title "tang-accn"

    set xrange [ 0.650 :  + 0.75]
    set yrange [ -60.00 :  +60.00]
    set title "continue Lamda = 0.18 SnaHyp FC20 Part 2/2"
    plot "SNAHYP-data-Lamda-018-FC20-U-vs-Tang-Accn.txt" using 2:13 with lines linecolor black title "tang-accn"
    
 
unset multiplot
    
    
    
