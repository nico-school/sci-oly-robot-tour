int encoderA = 9;
int input1 = 2;
int input2 = 3;
int encoderB = 10;
int input3 = 4;
int input4 = 5;
int ENCA = 6;  //encoder inputs on the arduino being defined
int ENCB = 7;
int ENCC = 11;
int ENCD = 12;


static const int heartbeat = 13;
static const int wheelA = true;
static const int wheelB = true;

template<typename T>
Print& operator<<(Print& printer, T value) {
  printer.print(value);
  return printer;
}

void moveForward(int speed, int time) {
  digitalWrite(input1, HIGH); 
  digitalWrite(input2, LOW);
  digitalWrite(encoderA, speed);
  digitalWrite(input3, HIGH);
  digitalWrite(input4, LOW);
  digitalWrite(encoderB, speed);
  delay(time);
}
void moveBackward(int speed, int time) {
  digitalWrite(input1, LOW); 
  digitalWrite(input2, HIGH);
  digitalWrite(encoderA, speed);
  digitalWrite(input3, LOW);
  digitalWrite(input4, HIGH);
  digitalWrite(encoderB, speed);
  delay(time);
}
void stop(int time) {
  moveForward(0, time);
}
void moveCircle(int speed, int time) {
  digitalWrite(input1, LOW);
  digitalWrite(input2, HIGH);
  digitalWrite(encoderA, speed);
  digitalWrite(input3, HIGH);
  digitalWrite(input4, LOW);
  digitalWrite(encoderB, speed);
  delay(time);
}

void setup() {
  Serial.begin(9600);
  pinMode(heartbeat, OUTPUT);

  // put your setup code here, to run once:
  pinMode(encoderA, OUTPUT);
  pinMode(input1, OUTPUT);
  pinMode(input2, OUTPUT);
  pinMode(encoderB, OUTPUT);
  pinMode(input3, OUTPUT);
  pinMode(input4, OUTPUT);

  pinMode(ENCA, INPUT); //experimenting with having the magnetic encoders as inputs
  pinMode(ENCB, INPUT);
  pinMode(ENCC, INPUT);
  pinMode(ENCD, INPUT);

  moveForward(50, 500);

  stop(1000);

  moveBackward(50, 500);

  stop(1000);
  
}
void loop() {

  int a = digitalRead(ENCA);  //reading encoder input and
  int b = digitalRead(ENCB);
  Serial << "a*b = " << a*b << ", b*5 = " << b*5;
  Serial.println();

}
