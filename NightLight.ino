// 

#define MOVAVGSIZE 64

int holder[MOVAVGSIZE];
int i;
int divider;

void setup() {
  Serial.begin(9600);

  pinMode(A0, INPUT);
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);

  digitalWrite(6, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);

}

void loop() {
  divider = 0;
  for (i = 0; i < MOVAVGSIZE; i++){
    holder[i] = analogRead(A0);
    divider = divider + holder[i];
    //Serial.print("Holder ");
    //Serial.print(i);
    //Serial.print(": ");
    //Serial.println(holder[i]);
  }

  divider = divider/MOVAVGSIZE;

  //Serial.print("Divider: ");
  //Serial.println(divider);
  
  analogWrite(6, 255);
  analogWrite(9, 255);
  analogWrite(10, 255);
  analogWrite(11, 255);

  delay(5000);

}
