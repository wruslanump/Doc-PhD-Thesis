# File: gpscript-Butterfly-Tangential-Acceleration-4-Lamdas-FC20-Algo23-2row-by-2col.gp 
# wruslan@HPLaptop-01-ub20:~$ date
# Wed 04 Oct 2023 01:07:27 PM +08
 
## Example 1: Plotting 2 curves in one plot with same axis (Left only no color)

clear
## set size square
set autoscale
set grid


## DATA COLUMN DESCRIPTION
## COL[4] = u value
## COL[7] = NAL value Next-Arc-Length
## COL[9] = NCL value Next-Chord-Length


## INDIVIDUAL CURVE 1 CHECK THIS IS FOR NAL ONLY
## set xlabel "parameter u"
## set ylabel "Next-Arc-Length (NAL) mm"
## set xrange [ 0.0 :  + 1.0]   
## set yrange [0.009997 : 0.0100005]  
## plot "data-SkewedAstroid-ArcLength-ChordLength-FC10-Lamda0.18-Algo28-data_01.txt" using 4:7 with lines lc "blue" linewidth 2 title "Next-Arc-Length (NAL)"


## INDIVIDUAL CURVE 2 CHECK THIS IS FOR NCL ONLY
## set xlabel "parameter u"
## set ylabel "Next-Chord-Length (NCL) mm"
## set xrange [ 0.0 :  + 1.0]
## set yrange [ -1E-2 : +2E-2]  
## plot "data-SkewedAstroid-ArcLength-ChordLength-FC10-Lamda0.18-Algo28-data_01.txt" using 4:9 with lines lc "magenta" linewidth 2 title "Next-Chord-Length (NCL)"

## ================================================    
## BEGIN
    
set title "FC10 L0.18 SkewedAstroid"

# USE THE BIGGER RANGE 
set xrange [ 0.0 :  + 1.0]  
set yrange [ -1E-2 : +2E-2]  
## set yrange [0.009997 : 0.0100005]  

set xlabel "parameter u"
set ylabel "NAL and NCL mm"
    
plot   "data-SkewedAstroid-ArcLength-ChordLength-FC10-Lamda0.18-Algo28-data_01.txt" using 4:7  with lines lw 2 title "Next-Arc-Length (NAL)" 
replot "data-SkewedAstroid-ArcLength-ChordLength-FC10-Lamda0.18-Algo28-data_01.txt" using 4:9  with lines lw 2 title "Next-Chord-Length (NCL)" 

## END
## ==============================================
## EXECUTION EXAMPLE
## gnuplot -p gpscript-SkewedAstroid-Tangential-Acceleration-4-Lamdas-FC20-Algo23-2row-by-2col.gp  
    
## FILE SAVE AS pdf FOR CLARITY    
    
