# Q4/Q5: Versioned Potentiometer-Controlled LED Blink System

## Project Description
This project demonstrates basic embedded system engineering principles using an Arduino Uno. It features an LED that adjusts its flashing speed dynamically based on the analog input read from a 10kΩ potentiometer. The system also outputs tracking metrics over a serial interface connection for diagnostic monitoring.

---

## 🛠️ Hardware Required
* **1x** Arduino Uno R3 Development Board
* **1x** Breadboard
* **1x** Red LED
* **1x** 220Ω Resistor (Current-limiting)
* **1x** 10kΩ Potentiometer (Analog Input)
* Solid-core hookup jumper wires

---

## 🔌 Circuit Diagram Description
The connections are wired securely onto the prototyping board using a shared common power scheme:
* **LED Loop:** The positive **Anode** leg of the LED connects directly to Arduino **Digital Pin 13**. The negative **Cathode** leg connects to one side of the **220Ω Resistor**, while the opposite side of the resistor plugs into the common **GND** rail.
* **Potentiometer Loop:** The left terminal terminal connects to the **5V** rail. The central wiper pin interfaces directly with Arduino **Analog Input A0**. The right terminal terminal connects to the common **GND** rail.

---

## 🚀 How to Upload and Run the Code

### Option A: Using the Tinkercad Simulator
1. Open your Tinkercad Circuit workspace canvas.
2. Arrange the hardware components according to the *Circuit Diagram Description* above.
3. Open the **Code** panel tray in the upper right, switch the dropdown from Blocks to **Text**, and paste the contents of `Versioned LED Controller.ino`.
4. Press the green **Start Simulation** button.
5. Click on the **Serial Monitor** at the bottom of the code box to see live data output.

### Option B: Using Physical Hardware (Arduino IDE)
1. Mount your components safely onto your physical breadboard and plug in the jumper connections.
2. Connect your Arduino Uno to your PC using a standard blue USB Type-B interface cable.
3. Open the **Arduino IDE** and copy-paste the project code.
4. Go to **Tools -> Board** and select `Arduino Uno`. Go to **Tools -> Port** and select your active COM port.
5. Click the **Upload** arrow icon button in the top menu bar.
6. Open the **Serial Monitor** tool (`Ctrl + Shift + M`) and set the baud rate to **9600** to observe the logs.

---

## 📊 Expected Output
* **Hardware Visuals:** The Red LED flashes continuously. Turning the potentiometer knob completely clockwise slows the blink cycle down to 2-second intervals, while turning it counter-clockwise speeds it up to a rapid 100ms flash sequence.
* **Serial Monitor Log Stream:** The terminal updates continuously, outputting the incrementing metrics on a new line:
    ```text
    Blink count: 1
    Blink count: 2
    Blink count: 3
    ```

---

## 🔍 Troubleshooting Tips
* **1. The LED Remains Off But Simulation Runs:** Check the orientation of your LED. Current can only flow from the positive Anode (bent leg) to the negative Cathode (straight leg). If it is reversed, the circuit will stay dark.
* **2. Turning the Potentiometer Has No Effect on Speed:** Double-check that the middle wiper pin of your potentiometer is firmly connected to **A0** instead of power or ground, and verify your `map()` function bounds in the source code.
* **3. Serial Monitor Displays Garbled Characters or Question Marks:** Ensure that the baud rate selection dropdown in the bottom right corner of your Serial Monitor window matches exactly **9600 baud**, corresponding to the `Serial.begin(9600)` declaration.
