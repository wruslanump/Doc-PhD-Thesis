
## FILE: plot3D_01_data_curve_cposition_xpos_ypos_u.gp

clear
set size square
set autoscale
set grid

set xlabel "position-x(u) mm"
set ylabel "position-y(u) mm"
set zlabel "(u)"
set title "Plot3D position, position-x(u) vs position-y(u) vs (u)"

## 3D-PLOT TEARDROP CHECK

splot "data_curve_cposition.txt" using 4:5:3 with lines linecolor black linewidth 2 title "u-direction" 

# DATA COLUMNS INDEX = COLUMN NUMBER
# step_u(1),   
# u_next(2)
# u(3),           
# cpos_x(4),       
# cpos_y(5),      
# cpos_magn(6),  
# cpos_x_uvect(7),   
# cpos_y_uvect(8), 
# cpos_theta_rad[9], 
# cpos_theta_deg[10], 
# cpos_epsilon[11], 
# cpos_rho[12] 

