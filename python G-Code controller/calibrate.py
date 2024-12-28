import serial

ser = serial.Serial('COM8', 115200)

# ser.write(b'G1 X10 F200')
ser.write(b'G91 X-1.0 F200')

# set origin
# ser.write(b'G92 X0 Y0 Z0')

# Close the serial port
ser.close()