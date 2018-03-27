int incomingByte = 0;   // for incoming serial data
int speed = 0;
// Clockwise and counter-clockwise definitions.
// Depending on how you wired your motors, you may need to swap.
#define FORWARD  0
#define REVERSE 1

// Motor definitions to make life easier:
#define MOTOR_A 0
#define MOTOR_B 1

// Pin Assignments //
//Default pins:
#define DIRA 12 // Direction control for motor A
#define PWMA 3  // PWM control (speed) for motor A
#define DIRB 13 // Direction control for motor B
#define PWMB 11 // PWM control (speed) for motor B

void setup() {
    setupArdumoto();
    Serial.begin(115200);
    
    Serial1.begin(9600);
    if(Serial1){
      Serial.println("Serial1 is ready to be used");
    }
    
    if(Serial){
      Serial.println("Serial is ready to be used");
    }
    
    Serial.println(F("Adafruit Bluefruit App Controller Example"));
    Serial.println(F("-----------------------------------------"));
}

void loop() {
  
        // send data only when you receive data: 
       int availableBytes = Serial1.available();
          
       if (availableBytes > 0) {
          Serial.println("--------------------------------------------");         
          Serial.print("I received this many bytes: ");
          Serial.println(availableBytes);
          byte receiveBuffer [availableBytes];
          
          for(int i=0; i < availableBytes; i++){
            receiveBuffer[i] = Serial1.read();
          }
          
          String receivedString = String((char*)receiveBuffer);
          receivedString.trim();
          receivedString = receivedString.substring(0, availableBytes);
          
          Serial.println(receivedString);
          
          String directionCommand = String(strtok(&receivedString[0], ":"));
          Serial.println(directionCommand);
          String speedCommand = strtok(NULL, ":");
          Serial.println(speedCommand);
          speed = speedCommand.toInt();
          if(directionCommand.equalsIgnoreCase("B")){
            Serial.println("MOVING : BACK");
            moveBackward();
          }
          else if(directionCommand.equalsIgnoreCase("L")){
            Serial.println("MOVING : LEFT");
            moveLeft();
          }
          else if(directionCommand.equalsIgnoreCase("R")){
            Serial.println("MOVING : RIGHT");
            moveRight();
          }
          else if(directionCommand.equalsIgnoreCase("F")){
            Serial.println("MOVING : FORWARD");
            moveForward();
          }
          else if(directionCommand.equalsIgnoreCase("S")){
            Serial.println("MOVING : STOPPING");
            stopMotors();
          }
          Serial.print("--------------------------------------------");           
        }
}

void moveLeft(){   
  driveArdumoto(MOTOR_A, FORWARD, speed);
  driveArdumoto(MOTOR_B, REVERSE, speed);
}

void moveRight(){ 
  driveArdumoto(MOTOR_A, REVERSE, speed);
  driveArdumoto(MOTOR_B, FORWARD, speed);
}
void moveForward(){
  driveArdumoto(MOTOR_A, FORWARD, speed);
  driveArdumoto(MOTOR_B, FORWARD, speed);
}
void moveBackward() {
  driveArdumoto(MOTOR_A, REVERSE, speed);
  driveArdumoto(MOTOR_B, REVERSE, speed);  
}
void stopMotors(){
  stopArdumoto(MOTOR_A);
  stopArdumoto(MOTOR_B);
}
// setupArdumoto initialize all pins
void setupArdumoto()
{
  // All pins should be setup as outputs:
  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(DIRA, OUTPUT);
  pinMode(DIRB, OUTPUT);

  // Initialize all pins as low:
  digitalWrite(PWMA, LOW);
  digitalWrite(PWMB, LOW);
  digitalWrite(DIRA, LOW);
  digitalWrite(DIRB, LOW);
}

// driveArdumoto drives 'motor' in 'dir' direction at 'spd' speed
void driveArdumoto(byte motor, byte dir, byte spd)
{
  Serial.println((String)motor);
  Serial.println((String)dir);
  Serial.println((String)spd);
  
  if (motor == MOTOR_A)
  {
    digitalWrite(DIRA, dir);
    analogWrite(PWMA, spd);
  }
  else if (motor == MOTOR_B)
  {
    digitalWrite(DIRB, dir);
    analogWrite(PWMB, spd);
  }  
}

// stopArdumoto makes a motor stop
void stopArdumoto(byte motor)
{
  driveArdumoto(motor, 0, 0);
}

