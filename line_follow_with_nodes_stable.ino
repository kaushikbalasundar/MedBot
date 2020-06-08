int IR1 = 17; //white 
int IR2 = 16; //black
int IR3 = 18; //white
int buzzer = 20;
int ultr_ride = 21;
const int Y_pin = 0; // analog pin connected to Y output
const int X_pin = 15; // analog pin connected to X output
int i =0;
int j=0;
int k=0;
int node = 0;
int deliver = 0;
int room = 0;
String room_nums[4];
String input;
String str_node;
const int trigPin = 39;
const int echoPin = 41;
int incrementer = 0;
// defines variables
long duration;
int distance;

#include <RobojaxBTS7960.h>
#include <Keypad.h>

//BTS7960 motor driver 1 
#define RPWM 3 // define pin 3 for RPWM pin (output)
#define R_EN 4 // define pin 2 for R_EN pin (input)
#define R_IS 5 // define pin 5 for R_IS pin (output)

#define LPWM 6 // define pin 6 for LPWM pin (output)
#define L_EN 7 // define pin 7 for L_EN pin (input)
#define L_IS 8 // define pin 8 for L_IS pin (output)

//BTS7960 motor driver 2 
#define RPWM1 9 // define pin 3 for RPWM pin (output)
#define R_EN1 10 // define pin 2 for R_EN pin (input)
#define R_IS1 11 // define pin 5 for R_IS pin (output)

#define LPWM1 12 // define pin 6 for LPWM pin (output)
#define L_EN1 13 // define pin 7 for L_EN pin (input)
#define L_IS1 14 // define pin 8 for L_IS pin (output)

// general purpose for BTS7960 

#define CW 1 //do not change
#define CCW 0 //do not change
#define debug 1 //change to 0 to hide serial monitor debugging information or set to 1 to view

RobojaxBTS7960 motor1(R_EN,RPWM,R_IS, L_EN,LPWM,L_IS,debug);
RobojaxBTS7960 motor2(R_EN1,RPWM1,R_IS1, L_EN1,LPWM1,L_IS1,debug);


const byte ROWS = 4; //four rows
  const byte COLS = 4; //three columns

  char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {23, 25, 27, 29}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {31,33,35,37}; //connect to the column pinouts of the keypad


Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
int manual = 5;

void setup() {
  // BTS7960 Motor Control Code by Robojax.com 20190622
  Serial.begin(9600);// setup Serial Monitor to display information
  pinMode(IR1,INPUT); 
  pinMode(IR2,INPUT);
  pinMode(IR3,INPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(21, OUTPUT);
  motor1.begin();
  motor2.begin();
  Serial.println("Press 0 for manual and A for autonomous");
  int i = 0;  
  pinMode(buzzer, OUTPUT);
}


void loop(){
  
  
 char mode = keypad.getKey();
  if (mode == '0'){
    manual = 1;
   
  }
  else if (mode == 'A'){
    manual = 0;
    tone(buzzer, 10); // Send 1KHz sound signal...
    delay(1000);
    noTone(buzzer); // Send 1KHz sound signal...
    delay(1000);

  }
     
     
    while (manual == 1){
      

      char mode = keypad.getKey(); 
    if (mode == 'A'){
        Serial.println("changing to autonomous");
        tone(buzzer, 10); // Send 1KHz sound signal...
        delay(1000);
        noTone(buzzer); // Send 1KHz sound signal...
        delay(1000);
        manual = 0;
      }
  
  // put your main code here, to run repeatedly:
if (analogRead(Y_pin) > 700){
      Serial.println("Forward");
      motor1.rotate(35,CCW);
      motor2.rotate(35, CW);
    }
    
    else if (analogRead(Y_pin)<400){
      Serial.println("Backwards");
      motor1.rotate(35,CW);
      motor2.rotate(35,CCW);
    }
    else if (analogRead(X_pin) > 900){
      Serial.println("Left");
      
      motor1.rotate(35, CCW);
      motor2.stop();
    }
    else if (analogRead(X_pin)< 100){
      Serial.println("Right");
      
      motor2.rotate(35, CW);
      motor1.stop();
       
    }
    
        else{
      motor1.stop();
      motor2.stop();

}

    }
while (manual == 0){ 

    char mode = keypad.getKey(); 
    if (mode == '0'){
        Serial.println("changing to manual");
        tone(buzzer, 10); // Send 1KHz sound signal...
        delay(1000);
        noTone(buzzer); // Send 1KHz sound signal...
        delay(1000);
        manual = 1;
      }

while (room < 5){
    char key = keypad.getKey();
    if (key){
    if (key == '#'){
      Serial.println("Exiting");
      deliver = 0;
      break;
    }
    if (key == '*'){
      room = 0;

      Serial.println("Resetting");
      continue;
    }

 if (key == 'D'){
      incrementer = 1;
    }
       
    input += key;
    if (incrementer == 1){
    int str_length = input.length();
    input.remove(str_length-1, 1);
    room_nums[room] = input;
    //input[0] = '\0'; //clearing string after input 
    input = "";
    incrementer = 0;
     
    room += 1;
    }
    

    tone(buzzer, 1000); // Send 1KHz sound signal...
    delay(300);
    noTone(buzzer); // Send 1KHz sound signal...
    delay(300);
    
    }
      
           
  }


    if (digitalRead(15) == LOW && digitalRead(17) == LOW){ //FORWARD
      
      motor1.rotate(30,CCW);// run motor with 100% speed in CW direction
      motor2.rotate(30, CW);
    }

    
    else if (digitalRead(15) == HIGH && digitalRead(16) == LOW && digitalRead(17) == LOW){
           
      motor1.stop();
      motor2.rotate(30, CW);
        
    }

    else if (digitalRead(15) == HIGH && digitalRead(16) == HIGH && digitalRead(17) == LOW){

      motor1.stop();
      motor2.stop();
      delay(100);
      motor1.stop();
      motor2.rotate(30, CW);
      delay(200);
      
    }
    else if (digitalRead(15) == LOW && digitalRead(16) == LOW && digitalRead(17) == HIGH){
      motor2.stop();
      motor1.rotate(30,CCW);
 
}
    else if (digitalRead(15) == LOW && digitalRead(16) == HIGH && digitalRead(17) == HIGH){
      motor1.stop();
      motor2.stop();
      delay(500);
      motor1.rotate(30,CCW);
      motor2.stop();
      
}



    else if (digitalRead(15) == HIGH && digitalRead(16) == HIGH && digitalRead(17) == HIGH ){

      Serial.println("node encountered");
      node +=1;
      str_node = String(node);
      for (j = 0; j<5;j ++){
        if (room_nums[j] == str_node){
        deliver = 1; 
        }
        else{
        deliver = 0;
      }
 
// Prints the distance on the Serial Monitor
      while (deliver == 1){
        Serial.println("Stopping");
        motor1.stop();
        motor2.stop();

        digitalWrite(trigPin, LOW);
        delayMicroseconds(2);
        // Sets the trigPin on HIGH state for 10 micro seconds
        digitalWrite(trigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPin, LOW);
        // Reads the echoPin, returns the sound wave travel time in microseconds
        duration = pulseIn(echoPin, HIGH);
        // Calculating the distance
        distance = duration*0.034/2;

        if(distance<10)
        {
           motor1.rotate(30,CCW);
           motor2.rotate(30, CW);
           delay(800);
           motor1.stop();
           motor2.stop();
           delay(500);
           tone(buzzer, 1000); // Send 1KHz sound signal...
           delay(300);
           noTone(buzzer); // Send 1KHz sound signal...
           deliver = 0;
        } 
      else
           deliver = 1;    
        }
      }
    }

else if (digitalRead(15) == LOW && digitalRead(16) == LOW && digitalRead(17) == LOW ){
      
      motor1.stop();
      motor2.stop();

      
    }
}
}
