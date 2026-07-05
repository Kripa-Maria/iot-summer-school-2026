# Module 2 Written Theory Evaluations

## Q11. IoT Architecture Layers Blueprint
* **Perception Layer:** DHT11 Sensor (Collects physical temperature and humidity metrics)
* **Network Layer:** Wi-Fi Gateway (Transmits collected data packets securely over wireless protocols)
* **Processing Layer:** Cloud Broker (Parses incoming streams and executes data storage logic)
* **Application Layer:** Web UI (Displays visual graphs and analytics dashboards to the end-user)

---

## Q12. Microcontrollers vs. Microprocessors Target Specifications
Below is the verified target specification comparison matrix evaluating the differences between microcontrollers (like the Arduino Uno) and microprocessors (like the Raspberry Pi):

![Q12 MCU vs MPU Specification Matrix](../week2/schematics/mcu_vs_mpu.jpg)

---

## Q19. analogWrite() vs. analogRead() and PWM Analysis
* **Functional Distinction:** `analogRead()` utilizes a 10-bit ADC to sample continuous input voltages (0-5V) across a 0-1023 integer range. `analogWrite()` outputs an 8-bit duty cycle square wave (0-255) to simulate a variable voltage using digital switching.
* **PWM Mechanics:** Pulse Width Modulation rapidly alternates output states at fixed frequencies. Adjusting the high-state duty-cycle width alters the average effective power delivered to components.
* **IoT Application Matrix:**
  * `analogRead()`: Mapping structural environmental telemetry values from an analog Soil Moisture sensor node into cloud databases.
  * `analogWrite()`: Adjusting lighting arrays on smart home fixtures from values received via cloud dashboard sliders.

---

## Q20. Microcontroller Runtime Lifecycle and Non-Blocking Architectures
* **Function Routines:** `setup()` handles single-pass system configurations on boot. `loop()` maintains continuous execution of core program operations.
* **Thread Blocking Complications:** Long `delay()` sequences trap the program counter inside empty execution loops. Sensor read tasks are blocked, resulting in significant polling latency and missed real-time physical triggers.
* **Non-Blocking Architecture:** Utilizing `millis()` tracking to establish state flags. Program cycles verify elapsed delta timings against target milestones, executing timed events while keeping the loop running with zero processing delays.
