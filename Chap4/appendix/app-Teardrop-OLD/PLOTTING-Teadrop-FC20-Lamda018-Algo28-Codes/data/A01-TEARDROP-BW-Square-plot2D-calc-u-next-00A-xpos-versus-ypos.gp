
## File: plot2D-calc-u-next-00A-xpos-versus-ypos.gp

clear
set size square
set autoscale
set grid

set xlabel "x-position"
set ylabel "y-position"
set title  "Plot 2D (x,y) parametric curve (square view)"

## set title  "plot2D-calc-u-next-00A-xpos-versus-ypos.gp"

# COMMENT RANGES FOR DEFAULT
set xrange [ -40.0 : +40.0]
set yrange [ -40.0 : +40.0]

## PLOT CHECK
plot   "FC20-data_calc_u_next.txt" using 8:9 with lines linecolor black linewidth 2 title "(x,y) points"

# DATA COLUMNS INDEX = COLUMN NUMBER
# rtime[1] 
# u[2] 
# u_next[3] 
# t_interpol[4] 
# first_order[5] 
# second_order[6] 
# diff[7] 
# pos_x[8]
# pos_y[9]
# pos_r[10] 
# eps[11]
# rho[12] 
# curr_tang_accn[13] 
# curr_frate[14] 
# frate_limit[15] 
# x_frate[16] 
# y_frate17]

# DTStamp_FHdata_calc_u_next 2022-06-23 12:23:39 179309410 

# EXECUTION
# gnuplot -p plot2D_calc_u_next_00_u_versus_u_next.gp


