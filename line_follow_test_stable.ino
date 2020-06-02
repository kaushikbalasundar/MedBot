

int IR1 = 17; //white 
int IR2 = 16; //black
int IR3 = 18; //white

const int Y_pin = 0; // analog pin connected to Y output
const int X_pin = 1; // analog pin connected to X output
int i =0;

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
  char room_nums[4];
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
  motor1.begin();
  motor2.begin();
  Serial.println("Press 0 for manual and A for autonomous");
  int i = 0;  
}


void loop(){
 char mode = keypad.getKey();
  if (mode == '0'){
    manual = 1;
    Serial.println("Mode is: ");
    Serial.println(manual);
  }
  else if (mode == 'A'){
    manual = 0;
    Serial.println("Mode is: ");
    Serial.println(manual);
  }
     
     
    while (manual == 1){

      char mode = keypad.getKey(); 
    if (mode == 'A'){
        Serial.println("changing to autonomous");
        manual = 0;
      }
  
  // put your main code here, to run repeatedly:
if (analogRead(Y_pin) < 10){
      Serial.println("Forward");
      motor1.rotate(60,CCW);
      motor2.rotate(60, CW);
    }
    
    else if (analogRead(Y_pin)>1000){
      Serial.println("Backwards");
      motor1.rotate(60,CW);
      motor2.rotate(60,CCW);
    }
    else if (analogRead(X_pin) < 10){
      Serial.println("Left");
      
      motor1.rotate(60, CCW);
    }
    else if (analogRead(X_pin)>1000){
      Serial.println("Right");
      
      motor2.rotate(60, CW);
       
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
        manual = 1;
      }
    /*
    motor2.rotate(60, CW);
    motor1.rotate(100, CCW);
    delay(2000);
    motor1.stop();
    motor2.stop();
   */

    if (digitalRead(15) == LOW && digitalRead(17) == LOW){ //FORWARD
      
      motor1.rotate(30,CCW);// run motor with 100% speed in CW direction
      motor2.rotate(30, CW);
    }

    
    else if (digitalRead(15) == HIGH && digitalRead(16) == LOW && digitalRead(17) == LOW){
      motor2.rotate(30, CW);
      motor1.stop();
      //.rotate(50,CW);
    }

    else if (digitalRead(15) == HIGH && digitalRead(16) == HIGH && digitalRead(17) == LOW){
      motor2.rotate(30, CW);
      motor1.stop();
    }
    else if (digitalRead(15) == LOW && digitalRead(16) == LOW && digitalRead(17) == HIGH){
      motor1.rotate(30,CCW);
      motor2.stop();
      //motor2.rotate(20, CCW);
}
    else if (digitalRead(15) == LOW && digitalRead(16) == HIGH && digitalRead(17) == HIGH){
      motor1.rotate(30, CCW);
      motor2.stop();
      
      // motor2.rotate(50, CCW);
      //motor2.rotate(25, CCW);
}

    else if (digitalRead(15) == HIGH && digitalRead(16) == HIGH && digitalRead(17) == HIGH ){
      
      motor1.stop();
      motor2.stop();}


    else if (digitalRead(15) == LOW && digitalRead(16) == LOW && digitalRead(17) == LOW ){
      motor1.stop();
      motor2.stop();
       // motor1.rotate(20,CW);// run motor with 100% speed in CW direction
      // motor2.rotate(20, CCW);
      
    }
}
}

       
