
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

// Ultrasonic 
int trigPin= 32;
int echoPin= 35;
#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701
long duration;
float distanceCm;


void setup(){
  Serial.begin(9600); // Starts the serial communication
  //Set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(in5, OUTPUT);
  pinMode(in6, OUTPUT);
  pinMode(buzzer, OUTPUT);
  // pinMode(R_S, INPUT);
  // pinMode(L_S, INPUT);
  pinMode(flang_IR, INPUT);
  pinMode(servo, OUTPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

}
 

void movment_stop(){
  analogWrite(enA, 0);
  analogWrite(enB, 0);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  }


void movment_forward(){
  analogWrite(enA, 200);
  analogWrite(enB, 200);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  Serial.println("Robot is moving forward");  // printlns a label
  Serial.println("\t");         // printlns a tab
  }

void movment_backward(){
  analogWrite(enA, 200);
  analogWrite(enB, 200);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  Serial.println("Robot is moving backward");  // printlns a label
  Serial.println("\t");         // printlns a tab
  }


void movment_left(){
  analogWrite(enA, 200);
  analogWrite(enB, 200);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  Serial.println("Robot is moving left");  // printlns a label
  Serial.println("\t");         // printlns a tab
  }


void movment_right(){
  analogWrite(enA, 200);
  analogWrite(enB, 200);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);  
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  Serial.println("Robot is moving right");  // printlns a label
  Serial.println("\t");         // printlns a tab
  }


void scissor_lift_down(){
  digitalWrite(in5, LOW);
  digitalWrite(in6, HIGH); 
  Serial.println("Scissor moving down");  // printlns a label
  Serial.println("\t");         // printlns a tab 
  }

void scissor_lift_up(){
  digitalWrite(in5, HIGH);
  digitalWrite(in6, LOW);  
  Serial.println("Scissor moving up");  // printlns a label
  Serial.println("\t");         // printlns a tab 
  }

void buzz(){

  tone(buzzer, 1000); // Send 1KHz sound signal...
  delay(1000);        // ...for 1 sec
  noTone(buzzer);     // Stop sound...
  delay(1000);        // ...for 1sec
}



void lineTrack(){

if((digitalRead(R_S) == 0)&&(digitalRead(L_S) == 0)){movment_forward();} 

if((digitalRead(R_S) == 1)&&(digitalRead(L_S) == 0)){movment_right();} 

if((digitalRead(R_S) == 0)&&(digitalRead(L_S) == 1)){movment_left();} 

if((digitalRead(R_S) == 1)&&(digitalRead(L_S) == 1)){movment_stop();} 


}
  

// void avoid_flang(){

// if(digitalRead(flang_IR) == 1){


// }

// }

 void ultra(){
// Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance
  distanceCm = duration * SOUND_SPEED/2;
  
    
  // printlns the distance in the Serial Monitor
  Serial.println("Distance (cm): ");
  Serial.println(distanceCm);


if (distanceCm <= 20){
    movment_stop();
    delay(300);
    movment_backward();
    delay(400);
    movment_stop();
    delay(300);

    
  }
  else{
    movment_forward(); 
  }

}


void loop(){
  movment_forward();


}
