# Potentiometer Controlled LED Blink

## Hardware Required
* Arduino UNO board (1x)
* Breadboard (1x)
* Red LED (1x)
* 220-ohm resistor (1x)
* 10k-ohm Potentiometer (1x)
* Jumper wires

## Circuit Diagram Description
The anode (long leg) of the LED connects to Arduino Digital Pin 13 through a 220-ohm current-limiting resistor, while the cathode attaches to Ground (GND). The potentiometer’s outer pins link to 5V and GND, and its center wiper pin connects directly to Analog Input Pin A0.

## How to Upload Code
1. Install the Arduino IDE on your computer.
2. Connect the Arduino UNO via a USB cable.
3. Open `led_blink.ino` in the IDE.
4. Go to **Tools > Board** and select **Arduino UNO**.
5. Go to **Tools > Port** and pick your active COM port.
6. Click the **Upload** arrow button.

## Expected Output
The LED flashes at a rate corresponding directly to the physical adjustment of the potentiometer knob. Concurrently, the Arduino Serial Monitor (set to 9600 baud) continuously logs the cumulative tracking counts of the execution loops.

## Troubleshooting Tips
1. **LED Not Blinking:** Check if the LED is inserted backwards; the longer leg must link to Pin 13.
2. **Serial Monitor Blank:** Verify that the communication baud rate in the bottom right corner is matching 9600.
3. **No Speed Variance:** Double check that the potentiometer center wiper pin is nested in A0 and not a digital pin.
