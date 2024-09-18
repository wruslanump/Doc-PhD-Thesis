
## FILE: plot3D_01_data_curve_cposition_xpos_ypos_u.gp

clear
set size square
set autoscale
set grid

set xlabel "parameter (u)"
set ylabel "Difference (1st - 2nd) Taylors Approx(u)"

set title "Plot2D Difference First-Order minus Second-Order Taylors Approximation"
set xrange [ 0.0 :  + 1.0]  
## set yrange [* : *] 

## plot "FC10-data_calc_u_next.txt" using 2:7 with lines linecolor black linewidth 2 title "difference (1st - 2nd)" 
plot "FC20-data_calc_u_next.txt" using 2:7 with lines linecolor black linewidth 2 title "difference (1st - 2nd)" 
## plot "FC30-data_calc_u_next.txt" using 2:7 with lines linecolor black linewidth 2 title "difference (1st - 2nd)" 
## plot "Fc40-data_calc_u_next.txt" using 2:7 with lines linecolor black linewidth 2 title "difference (1st - 2nd)" 

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
# eps[11] chord-error
# rho[12] radius of curvature 
# curr_tang_accn[13] 
# curr_frate[14] 
# frate_limit[15] 
# x_frate[16] 
# y_frate[17] 
# frate_command[18], 
# diff_frate[19]

# ALHAN DULILLAH 3 TIMES.
