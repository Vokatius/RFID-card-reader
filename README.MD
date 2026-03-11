# RFID Card Reader

## How to run
1. Install VS Code and the PlatformIO extension.
2. Open this project folder in VS Code.
3. Connect your ESP32, RFID-RC522, and LCD1602A to your PC and wire them as expected by the code in `src/main.cpp`.
4. Build and upload the project from PlatformIO.

## Project purpose
This project is a simple RFID scanner built for the ESP32.
It will eventually allow you to register users, update their information, delete existing entries, and assign each user to a specific RFID chip.

More than that, this project is my first more serious attempt to get into embedded and low-level development. 
Since this is the first time I'm developing a project using C++, the projects main goal is to broadly understand how C++ works, aswell as figuring out how to work closer to the hardware, and understanding how a real-world application comes together on a microcontroller.
