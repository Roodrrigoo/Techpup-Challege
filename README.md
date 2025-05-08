# TechPup Hugvest - Arduino Interface

## Project Overview
This project implements an Arduino-based interface for the TechPup Hugvest prototype, enabling manual testing of key hardware features before app integration. The system includes Bluetooth connectivity, LED control, vibration simulation (using a servo motor), pulse sensing (PPG), and respiratory monitoring (sound sensor).

## Features
- **Bluetooth Control**: Connect via HC-05 module to control the system remotely using the RemoteXY mobile app.
- **LED Indicator**: Toggle an LED on/off through the app.
- **Vibration Simulation**: Servo motor mimics vibration feedback when activated.
- **Pulse Monitoring**: PPG sensor measures heart rate and displays raw data on a live graph.
- **Respiration Monitoring**: Sound sensor captures breathing patterns and displays smoothed data on a gauge.
- **User-Friendly**: Designed for accessibility, even for non-technical users.

## Hardware Components
| Component | Quantity | Notes |
|-----------|----------|-------|
| Arduino Mega 2560 | 1 | Required for multiple serial connections |
| HC-05 Bluetooth Module | 1 | For wireless communication |
| PPG Pulse Sensor | 1 | Measures heart rate (connected to A0) |
| RQ-S001 Sound Sensor | 1 | Measures respiration (connected to A1) |
| MG90S Servo Motor | 1 | Simulates vibration (connected to pin 4) |
| LED | 1 | Visual indicator (with 220Ω resistor, connected to pin 5) |
| Breadboard & Jumper Wires | As needed | For easy wiring |

## Software Requirements
- **Arduino IDE** ([Download here](https://www.arduino.cc/en/software))
- **RemoteXY Library** (Install via Arduino Library Manager)
- **PulseSensor Playground Library** (Install via Arduino Library Manager)
- **RemoteXY Mobile App** ([Android](https://play.google.com/store/apps/details?id=com.remotexy) / [iOS](https://apps.apple.com/app/remotexy/id1541119765))

## Setup Instructions
1. **Install Arduino IDE**: Download and install the latest version from the official website.
2. **Install Libraries**: 
   - Open Arduino IDE, go to `Tools > Manage Libraries`, and install:
     - `RemoteXY` by Evgeny Shishatskiy
     - `PulseSensor Playground` by Joel Murphy
3. **Upload Code**: 
   - Copy the provided [Arduino code](#) (or clone this repository) and upload it to your Arduino Mega.
   - Ensure the correct board (`Arduino Mega or Mega 2560`) and port are selected.
4. **Hardware Connections**: 
   - Follow the wiring table in the [documentation](#) or the schematic below (if available).
5. **Pair Bluetooth**: 
   - Power the HC-05 module and pair it with your smartphone (default PIN: `1234`).
6. **Test the System**: 
   - Open the RemoteXY app, connect to the HC-05 module, and interact with the interface.

## How It Works
- **Button Press**: Turns on the LED and activates the servo (vibration simulation).
- **Pulse Sensor**: Reads raw heart rate data and updates the live graph every 3 seconds.
- **Respiration Sensor**: Averages sound levels to reduce noise and displays results on a gauge.

## Troubleshooting
| Issue | Solution |
|-------|----------|
| Bluetooth not connecting | Check power and baud rate (9600). Use Android for better compatibility. |
| LED not lighting up | Verify wiring, resistor, and LED polarity. |
| Servo not moving | Ensure signal wire is connected to pin 4 and power is sufficient. |
| Pulse graph not updating | Confirm sensor placement and connections (A0). |
| Upload fails | Disconnect Bluetooth RX/TX pins before uploading. |

## Credits
Developed by **Rodrigo Fernando Rivera Olea** as part of the TechPup Hugvest prototype.  
Libraries used: [RemoteXY](http://remotexy.com/), [PulseSensor Playground](https://github.com/WorldFamousElectronics/PulseSensorPlayground).

## License
This project is open-source under the **GNU Lesser General Public License (LGPL-2.1)**.  
For details, see the [LICENSE](#) file.

---
**Note**: For a detailed guide, refer to the [full documentation](#) (PDF included in the repository).
