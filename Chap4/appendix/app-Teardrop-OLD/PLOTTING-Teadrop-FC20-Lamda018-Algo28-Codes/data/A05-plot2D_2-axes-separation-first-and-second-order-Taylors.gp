
## FILE: plot3D_01_data_curve_cposition_xpos_ypos_u.gp

clear
set size square
set autoscale
set grid

set xlabel "parameter (u)"
set ylabel "second-order-Taylors-approx(u)"



## TWO CURVES IN ONE PLOT HAHAHA
## ================================================    
## BEGIN
    
set title "Plot2D curve (u) vs first-order vs second-order-Taylors-approx(u)"

set xrange [ 0.0 :  + 1.0]   
set yrange [0.00001 : 0.00034]  

set x2range [ 0.0 :  + 1.0]  
set y2range [0.00001 : 0.00038]  

set ytics 0.00005 nomirror tc lt 1
set ylabel "first-order Taylors approx"

set y2tics 0.00005   nomirror tc lt 2
set y2label "second-order Taylors approx"
    
## plot "FC10-data_calc_u_next.txt" using 2:5 axes x1y1 with lines lt 1 lw 2 title "first-order" ,  "FC10-data_calc_u_next.txt" using 2:6 axes x2y2 with lines lt 2 lw 2 title "second-order" 
plot "FC20-data_calc_u_next.txt" using 2:5 axes x1y1 with lines lt 1 lw 2 title "first-order" ,  "FC20-data_calc_u_next.txt" using 2:6 axes x2y2 with lines lt 2 lw 2 title "second-order" 
## plot "FC30-data_calc_u_next.txt" using 2:5 axes x1y1 with lines lt 1 lw 2 title "first-order" ,  "FC30-data_calc_u_next.txt" using 2:6 axes x2y2 with lines lt 2 lw 2 title "second-order" 
## plot "FC40-data_calc_u_next.txt" using 2:5 axes x1y1 with lines lt 1 lw 2 title "first-order" ,  "FC40-data_calc_u_next.txt" using 2:6 axes x2y2 with lines lt 2 lw 2 title "second-order" 


## END
## ==============================================

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
