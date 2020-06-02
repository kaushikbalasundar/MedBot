const int Y_pin = 0; // analog pin connected to X output
const int X_pin = 15; // analog pin connected to X output

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
// Serial.println(analogRead(X_pin));


Serial.println("X: ");
Serial.println(analogRead(X_pin));
Serial.println("Y: ");
Serial.println(analogRead(Y_pin));
delay(1000);



if (analogRead(Y_pin) > 700) {
  Serial.println("Go forward");
  //Paste code for going forward
}
else if (analogRead(Y_pin)<300){
  Serial.println("Go back");
  //Paste code for going back
}

else if (analogRead(X_pin) > 900){
  Serial.println("Turn left");
  //Paste code for turning left
}
else if (analogRead(X_pin)<100){
  Serial.println("Turn Right");
  //Paste code for turning right
}
else
  Serial.println("Stop");
 
}
