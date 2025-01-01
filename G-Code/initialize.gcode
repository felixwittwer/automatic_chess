$H; Homeing
G92 X360 Y390 Z0; set current position
G1 X350 F10000; move -10 on X-axis because of the carrier beeing pysically able to dive furtere than the software should allow
G92 X350 Y390 Z0; set current position actually redundant but in some cases could reduce erorrs
G1 X0 Y0 F10000; move to zero zero aka A1

M3; Turn magnet on
M5; Turn magnet of

M30; End Program