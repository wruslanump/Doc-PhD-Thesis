# File: gpscript-Butterfly-Tangential-Acceleration-4-Lamdas-FC20-Algo23-2row-by-2col.gp 
# wruslan@HPLaptop-01-ub20:~$ date
# Wed 04 Oct 2023 01:07:27 PM +08
 
## Example 1: Plotting 2 curves in one plot with different axes (Left maroon and right green)

clear
## set size square
set autoscale
set grid


## DATA COLUMN DESCRIPTION
## COL[4] = u value
## COL[7] = NAL value Next-Arc-Length
## COL[9] = NCL value Next-Chord-Length

## CURGVE 1 =========================================
## INDIVIDUAL CURVE 1 CHECK THIS IS FOR NAL ONLY
## set xlabel "parameter u"
## set ylabel "Next-Arc-Length (NAL) mm"
## set xrange [ 0.0 :  + 1.0] 
 
## TRICK: COMMENT LINE BELOW TO FIND OUT Y-RANGE, THEN set yrange [:] hahaha   
## set yrange [0.01995 : 0.02005]  
## plot "data_01.txt" using 4:7 with lines lc "blue" linewidth 2 title "Next-Arc-Length (NAL)"

## CURVE 2 ==========================================
## INDIVIDUAL CURVE 2 CHECK THIS IS FOR NCL ONLY
## set xlabel "parameter u"
## set ylabel "Next-Chord-Length (NCL) mm"
## set xrange [ 0.0 :  + 1.0]

## TRICK COMMENT LINE BELOWE TO FIND OUT Y-RANGE   
## set yrange [ 0.019997500 : 0.019997509 ]  
## plot "data_01.txt" using 4:9 with lines lc "magenta" linewidth 2 title "Next-Chord-Length (NCL)"

## ================================================    
## BEGIN
    
## set title "Chord-error below error tolerance 1E-6"

## set xtics 0.1 nomirror 

## set xrange [ 0.0 :  + 1.0]   
## set yrange [0.015 : 0.030]


## set x2range [ 0.0 :  + 1.0]  
## set y2range [ 0.015 : 0.025]  


set ytics 0.0025 nomirror tc lt 1
set ylabel "Next-Arc-Length (NAL) mm"

set y2tics 0.0025   nomirror tc lt 2
set y2label "Next-Chord-Length (NCL) mm"
    
plot   "data_01.txt" using 4:7 axes x1y1 with lines lt 1 lw 2 title "Next-Arc-Length (NAL)" ,  "data_01.txt" using 4:9 axes x2y2 with lines lt 2 lw 2 title "Next-Chord-Length (NCL)" 

## END
## ==============================================
## EXECUTION EXAMPLE
## gnuplot -p gpscript-SkewedAstroid-Tangential-Acceleration-4-Lamdas-FC20-Algo23-2row-by-2col.gp  
    
## FILE SAVE AS pdf FOR CLARITY    
    
