## Example 1: Plotting of a few curves using the multiplot command.

clear
set size square
set autoscale
set grid

set xlabel "parameter u"
set ylabel "tang-acceleration (mm/s2)"

set xrange [ 0 :  + 1.0]
set yrange [ -40 : +40]

## set title "Butterfly curve acceleration safety factor lamda"

set multiplot layout 2,2 columns
    
    set title "Lamda 0.10 FC20 Algo23 Butterfly"
    plot "Butterfly-FC20-Lamda0.10-Algo23-data_calc_u_next.txt" using 2:13 with lines linecolor black title "tang-accn"
    
    set title "Lamda 0.18 FC20 Algo23 Butterfly"
    plot "Butterfly-FC20-Lamda0.18-Algo23-data_calc_u_next.txt" using 2:13 with lines linecolor black title "tang-accn"
    
    set title "Lamda 0.20 FC20 Algo23 Butterfly"
    plot "Butterfly-FC20-Lamda0.20-Algo23-data_calc_u_next.txt" using 2:13 with lines linecolor black title "tang-accn"
    
    set title "Lamda 0.50 FC20 Algo23 Butterfly"
    plot "Butterfly-FC20-Lamda0.50-Algo23-data_calc_u_next.txt" using 2:13 with lines linecolor black title "tang-accn"

unset multiplot
    
    
    
