/******************************************************************************
 * Author: Kripa Maria
 * Date: July 2026
 * Program: IIT Jammu Summer School 2026
 * Description: Progressive IoT speed-modulated system using potentiometer A0 
 * input and active loop counting log output over standard UART lines.
 *****************************************************************************/

int loopAccumulator = 0;
const int controlWiperPin = A0; 

void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // Read potentiometer to control blink speed (0-1023 ms dynamic delay)
  int dynamicDelayRate = analogRead(controlWiperPin); 

  digitalWrite(13, HIGH);
  delay(dynamicDelayRate);
  digitalWrite(13, LOW);
  delay(dynamicDelayRate);
  
  // Increment and log data to Serial Monitor
  loopAccumulator++;
  Serial.print("Blink count: ");
  Serial.println(loopAccumulator);
}
