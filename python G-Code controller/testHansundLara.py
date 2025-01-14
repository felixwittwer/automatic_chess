import serial
import time

# Konfiguration der seriellen Schnittstelle
arduino_port = 'COMB3'  # Ersetze dies durch den richtigen Port für dein Arduino
baud_rate = 115200

# Öffnen der seriellen Verbindung zum Arduino
arduino = serial.Serial(arduino_port, baud_rate)
time.sleep(2)  # Warte, bis die Verbindung hergestellt ist

# G-Code-Befehle
gcode_commands = [
   
]

# Senden der G-Code-Befehle an den Arduino
for command in gcode_commands:
    print(f'Sending: {command}')
    arduino.write((command + '\n').encode())  # Sende den G-Code-Befehl
    time.sleep(1)  # Warte eine Sekunde zwischen den Befehlen

# Warten auf Benutzereingabe, um das Programm zu beenden
input("Drücke <Enter>, um das Programm zu beenden.")

# Schließen der seriellen Verbindung
arduino.close()
