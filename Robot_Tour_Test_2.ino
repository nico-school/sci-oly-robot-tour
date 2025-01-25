/*  Arduino DC Motor Control - PWM | H-Bridge | L298N  -  Example 01

    by Dejan Nedelkovski, www.HowToMechatronics.com
*/

#define PWM 9
#define in1 6
#define in2 7
#define PWM2 10
#define in3 11
#define in4 12

static const int ENCA = 2; // YELLOW
static const int ENCB = 3; // WHITE

static const int ENCC = 4; // YELLOW
static const int ENCD = 5; // WHITE

int pos = 0;

template<typename T>
Print& operator<<(Print& printer, T value) {
  printer.print(value);
  return printer;
}

void setup() {
  Serial.begin(9600); // need this in order to print stuff out


  pinMode(PWM, OUTPUT);
  pinMode(PWM2, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  // Set initial rotation direction
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  // Used to measure position later
  attachInterrupt(digitalPinToInterrupt(ENCA), readEncoder1, RISING);
  attachInterrupt(digitalPinToInterrupt(ENCC), readEncoder2, RISING);
}

void readEncoder1() {
  int b = digitalRead(ENCB);
  if (b > 0) {pos++;}
  else {pos--;}
}

void readEncoder2() {
  int b = digitalRead(ENCD);
  if (b > 0) {pos++;}
  else {pos--;}
}

int intensity = 160;

void stop() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);

  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void move(int direction, int length) {
  analogWrite(PWM, intensity); // Send PWM signal to L298N pin
  analogWrite(PWM2, intensity); // Send PWM signal to L298N pin
  if (direction == 1) {
    int goal = pos + length;
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);

    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);

    Serial.println(pos);

    do {delay(1);} while (pos < goal);
    stop();
  }

  if (direction == 0 || direction == -1) {
    int goal = pos - length;
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);

    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);

    Serial.println(pos);
    do {delay(1);} while (pos > goal);
    stop();
  }
}

void turn(int direction, int length) {
  analogWrite(PWM, intensity); // Send PWM signal to L298N pin
  analogWrite(PWM2, intensity); // Send PWM signal to L298N pin

  if (direction == 1) {
    int goal = pos + length;
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);

    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);

    Serial.println(pos);

    delay(length * 6);
    stop();
  }

  if (direction == 0 || direction == -1) {
    int goal = pos - length;
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);

    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);

    Serial.println(pos);
    delay(length * 6);
    stop();
  }
}

void loop() {
  // int potValue = analogRead(A0); // Read potentiometer value?
  int pwmOutput = intensity; // Map the potentiometer value from 0 to 255
  // Serial.print("pwmOutput = ");
  // Serial.print(pwmOutput);
  analogWrite(PWM, pwmOutput); // Send PWM signal to L298N pin
  analogWrite(PWM2, pwmOutput); // Send PWM signal to L298N pin


  move(1, 200);
  delay(2000);
  Serial.println(pos);


  move(0, 200);
  delay(2000);
  Serial.println(pos);

}