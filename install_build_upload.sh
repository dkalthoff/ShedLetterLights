#!/bin/bash

# If you get something like: "bash: ./_install_build_upload: Permission denied"
# Run:
# chmod 755 _install_build_upload
# "755" will give us read, write, and execute permission

# Set the arduino-cli install location for libraries in the config:
# directories:
#  data: /home/dkalthoff/snap/arduino/current/.arduino15
#  downloads: /home/dkalthoff/.arduino15/staging
#  user: /home/dkalthoff/snap/arduino/current/Arduino
#
# arduino-cli config dump --verbose

echo "Install external libraries"
arduino-cli lib install "ArduinoHttpServer"
arduino-cli lib install "WiFi101"
arduino-cli lib install "FastLED"
arduino-cli lib install "FlashStorage"

echo
echo "Install board"
arduino-cli core install "arduino:samd"

echo
echo "Verify and compile..."
arduino-cli compile --fqbn arduino:samd:mkr1000

#echo
#echo "Get available boards"
#arduino-cli board list
#echo "*** Connect the microcontroller. Get the port and fqbn values above ***"

# echo
# echo "Upload binaries to the board..."
# arduino-cli upload --port /dev/ttyACM0 --fqbn arduino:samd:nano_33_iot
