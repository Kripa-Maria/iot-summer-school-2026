# Module 3 Written Theory Evaluations

## Q29. Sensor Calibration Framework Analysis
Sensor calibration is the practice of tuning runtime outputs against physical control targets to eliminate analog conversion noise and device component drift.

### Two-Point Calibration Method
1. Dry Point: Read sensor open in air (e.g., Max = 1023).
2. Wet Point: Read sensor fully submerge in water (e.g., Min = 220).
3. Transfer Formula: `Moisture_Pct = map(analogRead(A0), 1023, 220, 0, 100);`

## Q30. The I2C Communication Protocol Schema
The Inter-Integrated Circuit (I2C) standard uses two linesDA (Serial Data) and SCL (Serial Clock)or synchronous, short-distance communications. Peripherals are called selectively by masters broadcasting target 7-bit hardware addresses over the lines.
