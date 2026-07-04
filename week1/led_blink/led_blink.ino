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
  int dynamicDelayRate = analogRead(controlWiperPin); 

  digitalWrite(13, HIGH);
  delay(dynamicDelayRate);
  digitalWrite(13, LOW);
  delay(dynamicDelayRate);
  
  loopAccumulator++;
  Serial.print("Blink count: ");
  Serial.println(loopAccumulator);
}
