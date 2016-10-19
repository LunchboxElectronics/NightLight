/*
    Night Light: uses an Arduino Uno with a photoresistor and some Lego-compatible 
    LEDs to smoothly fade in or out lights
    
    CC BY-SA Teddy Lowe, October 2016
    Lunchbox Electronics
    http://www.lunchboxelectronics.com/
*/

// Changeable stuff
#define MOVAVGSIZE 64
#define LOWBOUND 80
#define HIGHBOUND 250

int holder[MOVAVGSIZE];
int i;
unsigned int divider;
int analog;

// Limiting function
float limit(float input){
  if(input >= HIGHBOUND){                                 // If it is above the light range, switch off
    return 0;
  }else if(input <= LOWBOUND){                            // If it is below the light range, turn on full
    return 255;
  }else{
    float slope = -255/(HIGHBOUND - LOWBOUND);            // Calculate slope between points
    float output = slope*input + (255 - slope*LOWBOUND);  // Draw a straight line between the input and the acceptable range
    return output;
  }
}

void setup() {
  // Set up serial
  Serial.begin(115200);

  // Set up pins
  pinMode(A0, INPUT);
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);

  // Set all pins low
  digitalWrite(6, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);

  // Zero out the holder array
  for (i = 0; i < MOVAVGSIZE; i++){
    holder[i] = 0;
  }
  
}

void loop() {

  // Implement the moving average
  divider = 0;                            // divider to 0 so we don't make any mistakes
  for (i = 0; i < MOVAVGSIZE-1; i++){     // for every part of the holder array EXCEPT the last value...
    holder[i] = holder[i+1];              // make it equal to the one above it
    divider = divider + holder[i];        // then add to the divider
    //Serial.print("holder[");
    //Serial.print(i);
    //Serial.print("]: ");
    //Serial.println(holder[i]);
  }
  
  holder[MOVAVGSIZE-1] = analogRead(A0);  // The last one gets the analogRead value, for a nice fade effect
  
  divider = (divider + holder[MOVAVGSIZE-1])/MOVAVGSIZE;  // Then add the last one and take the average by dividing

  analog = limit((float) divider);  // The analogRead function only takes inputs from 0 to 255 so we need to map it within that range
  
  analogWrite(6, analog);
  analogWrite(9, analog);
  analogWrite(10, analog);
  analogWrite(11, analog);

  //Serial.print("analogRead: ");
  //Serial.println(holder[MOVAVGSIZE-1]);
  Serial.print("Divider: ");
  Serial.println(divider);
  //Serial.print("Analog: ");
  //Serial.println(analog);
}
