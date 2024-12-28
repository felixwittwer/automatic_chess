import serial
import time

# Set serial port and baudrate (GRBL operates at 115200 baud)
ser = serial.Serial('COM8', 115200)  # Replace with your serial port

# Open a G-Code file (e.g., 'example.gcode')
with open('test.gcode', 'r') as f:
    gcode_lines = f.readlines()

# Send G-Code commands to GRBL
for line in gcode_lines:
    line = line.strip()  # Remove trailing newline characters
    print(f'Sending: {line}')
    ser.write(line.encode() + b'\n')  # Send G-Code line with newline character
    time.sleep(0.1)  # Optional delay between commands
    response = ser.readline().decode().strip()  # Read GRBL response
    print(f': {response}')

# Close serial port
ser.close()