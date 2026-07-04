# Module 2 Written Theory Evaluations 

## Q11. IoT Architecture Layers Blueprint [cite: 87]
- **Perception Layer (Sensors/Actuators):** Hardware units picking up data fields from real-world spaces (e.g., DHT11 Temperature Sensor). [cite: 88, 89]
- **Network Layer (Transmission Protocols):** Pathways carrying data to the cloud engines (e.g., Wi-Fi, MQTT). [cite: 88, 89]
- **Processing Layer (Middleware/Analytics):** Servers interpreting incoming databases (e.g., Database brokers, IoT Platforms). [cite: 88, 89]
- **Application Layer (User Interfaces):** The dashboard interface displaying insights (e.g., Smart Phone App UI, Web Dashboard). [cite: 88, 89]

## Q12. Microcontrollers vs. Microprocessors Target Specifications [cite: 90, 91]
- **Microcontroller (MCU - Arduino Uno):** Low speed (16MHz clock rates), very small on-chip storage profile limits (2KB SRAM, 32KB Flash), runs raw compiled metal code without an Operating System. Highly power efficient for single-purpose tasks. [cite: 92]
- **Microprocessor (MPU - Raspberry Pi):** High speed (1.5GHz multi-core processing engines), external RAM/Flash chips up to gigabyte scales, runs a full multi-tasking Operating System (e.g., Linux OS). Consumes substantial power. [cite: 92]

## Q13. Arduino Pin Type Hardware Allocations [cite: 95]
- **Digital Input:** Reads explicit binary high/low states (e.g., Push buttons tracking door access alerts). [cite: 96, 97]
- **Digital Output:** Outputs high/low control voltage rails (e.g., Tripping alert buzzers). [cite: 96, 97]
- **Analog Input:** Converts variable incoming voltage fields between 0-5V to 10-bit numerical scales (e.g., Monitoring analog soil moisture probes). [cite: 96, 97]
- **PWM Output:** Simulates an analog voltage drop via rapid duty cycle switching (e.g., Modulating structural brightness variables on variable display lights). [cite: 96, 97]

## Q19. analogWrite() vs. analogRead() Processing Loops [cite: 134]
- `analogRead()` reads incoming external voltages via the internal 10-bit Analog-to-Digital Converter (ADC), yielding a value from 0 to 1023 (e.g., Reading data arrays off an analog sensor). [cite: 134, 135]
- `analogWrite()` maps output channels via Pulse Width Modulation (PWM), shifting duty cycles from 0 (off) to 255 (fully open) to simulate varying output voltages (e.g., Fading dimming lamps). [cite: 134, 135]

## Q20. Responsive sensory processing using non-blocking alternatives [cite: 136]
Placing long blocking commands like `delay(5000)` halts the CPU core completely during that window[cite: 136]. The microcontroller becomes blind to its environment, missing sensor changes or input transitions during the pause[cite: 136, 137]. 

The non-blocking alternative is using the `millis()` clock[cite: 137]. By tracking elapsed timestamps against current operational cycles, tasks can execute at precise intervals without ever locking the code loop.
