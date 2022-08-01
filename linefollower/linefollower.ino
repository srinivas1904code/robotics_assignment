int lefts, rights;
void setup() {
  // put your setup code here, to run once:
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}
void stop(int n) {
  for (int i = 0; i < n; i++) {
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
    delay(10);
  }
}
void left() {
  digitalWrite(10, HIGH);
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
  digitalWrite(13, HIGH);
}
void right() {
  digitalWrite(10, LOW);
  digitalWrite(11, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(13, LOW);
}
void forward() {
  digitalWrite(10, HIGH);
  digitalWrite(11, LOW);
  digitalWrite(12, HIGH);
  digitalWrite(13, LOW);
}
void backward() {
  digitalWrite(10, LOW);
  digitalWrite(11, HIGH);
  digitalWrite(12, LOW);
  digitalWrite(13, HIGH);
}


void loop() {
  // code for line follower
  lefts = analogRead(A0);
  rights = analogRead(A1);
  Serial.println(String(lefts)+"    "+ String(rights));
   if (lefts > 250 && rights > 450) {
    forward();
    delay(10);
    stop(2);
  }
  else if (lefts < 250 && rights > 450) {
    left();
    left();
    delay(20);
    stop(2);
  }
  else if (lefts > 250 && rights < 450) {
    right();
    right();
    delay(20);
    stop(2);
  }
  else {
    stop(5);
  }
}