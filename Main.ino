
// #include <Servo_ESP32.h>
 
 
// Motor A
 
int enA = 5;
int in1 = 17;
int in2 = 16;
 
// Motor B
 
int enB = 2;
int in3 = 4;
int in4 = 0;

// Motor C
int in5 = 19;
int in6 = 18;

// Servo arm; 
// Servo_ESP32 myservo; 
//Buzzer
int buzzer = 23;

//Gas sensor 
int gas = 12 ;

//servo
int servo = 21;

//IR line tracking sensors 
int R_S = 10;
int L_S = 11;
// flang IR
int flang_IR = 34 ;



void setup()
 
{
 
  // Set all the motor control pins to outputs
 
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(in5, OUTPUT);
  pinMode(in6, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(R_S, INPUT);
  pinMode(L_S, INPUT);
  pinMode(flang_IR, INPUT);
  pinMode(servo, OUTPUT);
  // myservo.attach(33);  // attaches the servo on pin 9 to the servo object

}
 


void movment_stop(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  }


void movment_forward(){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  }

void movment_backward(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  }


void movment_left(){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  }


void movment_right(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);  
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  }


void scissor_lift_down(){
  digitalWrite(in5, LOW);
  digitalWrite(in6, HIGH);  
  }

void scissor_lift_up(){
  digitalWrite(in5, HIGH);
  digitalWrite(in6, LOW);  
  }

void buzz(){
digitalWrite(buzzer, HIGH);
delay(500);
digitalWrite(buzzer, LOW);
delay(500);
}


// void arm180(){
  
//   myservo.write(180); 
//   }
// void arm0(){
  
// myservo.write(0); 
//   }

void lineTrack(){

if((digitalRead(R_S) == 0)&&(digitalRead(L_S) == 0)){movment_forward();} 

if((digitalRead(R_S) == 1)&&(digitalRead(L_S) == 0)){movment_right();} 

if((digitalRead(R_S) == 0)&&(digitalRead(L_S) == 1)){movment_left();} 

if((digitalRead(R_S) == 1)&&(digitalRead(L_S) == 1)){movment_stop();} 


}
  

void avoid_flang(){

if(digitalRead(flang_IR) == 1){


}


}  
void loop()
 
{


}
