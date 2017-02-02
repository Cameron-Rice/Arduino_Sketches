// 2-dimensional array of row pin numbers:
const int row[8] = {
  16, 21, 9, 19, 2, 8, 3, 6
};

// 2-dimensional array of column pin numbers:
const int col[8] = {
  20, 4, 5, 17, 7, 18, 22, 23
};

// 2-dimensional array of pixels:
int pixels[8][8];

unsigned long lastupdate = 0;
int timer = 0;
int speedval = 0;

const int potpin = 14;

void setup() {
  // initialize the I/O pins as outputs
  // iterate over the pins:
  for (int thisPin = 0; thisPin < 8; thisPin++) {
    // initialize the output pins:
    pinMode(col[thisPin], OUTPUT);
    pinMode(row[thisPin], OUTPUT);
    // take the col pins (i.e. the cathodes) high to ensure that
    // the LEDS are off:
    digitalWrite(col[thisPin], HIGH);
  }

  for(int x = 0; x < 8; x++){
    for(int y = 0; y < 8; y++){
      pixels[x][y] = HIGH;
    }
  }

}

void loop() {

  speedval = analogRead(potpin);

  Serial.println(speedval);


  if((millis() - lastupdate) > speedval){
    
    timer++;

    lastupdate = millis();
  }

  if(timer == 0){
    heartBeatUp();
  }
  else if(timer == 1){
    heartBeatDown();
  }
  
  if(timer == 2){
    timer = 0;
  }
  
  refreshMatrix();
  
}

void refreshMatrix(){
  
  for(int x = 0; x < 8; x++){

    digitalWrite(row[x], HIGH);
    
    for(int y = 0; y < 8; y++){

      int currState = pixels[x][y];

      digitalWrite(col[y], currState);

      if(currState == LOW){
        digitalWrite(col[y], HIGH);
      }
    }

   digitalWrite(row[x], LOW);
    
  }
}

void heartBeatUp(){

  pixels[3][1] = LOW;
  pixels[4][1] = LOW;
  pixels[2][2] = LOW;
  pixels[5][2] = LOW;
  pixels[1][3] = LOW;
  pixels[6][3] = LOW;
  pixels[0][4] = LOW;
  pixels[7][4] = LOW;
  pixels[0][5] = LOW;
  pixels[7][5] = LOW;
  pixels[1][6] = LOW;
  pixels[6][6] = LOW;
  pixels[2][6] = LOW;
  pixels[5][6] = LOW;
  pixels[3][5] = LOW;
  pixels[4][5] = LOW;

  pixels[3][2] = HIGH;
  pixels[4][2] = HIGH;
  pixels[2][3] = HIGH;
  pixels[5][3] = HIGH;
  pixels[1][4] = HIGH;
  pixels[1][5] = HIGH;
  pixels[6][5] = HIGH;
  pixels[6][4] = HIGH;
  
}

void heartBeatDown(){
  
  pixels[3][2] = LOW;
  pixels[4][2] = LOW;
  pixels[2][3] = LOW;
  pixels[5][3] = LOW;
  pixels[1][4] = LOW;
  pixels[1][5] = LOW;
  pixels[2][6] = LOW;
  pixels[3][5] = LOW;
  pixels[4][5] = LOW;
  pixels[5][6] = LOW;
  pixels[6][5] = LOW;
  pixels[6][4] = LOW;

  pixels[3][1] = HIGH;
  pixels[4][1] = HIGH;
  pixels[2][2] = HIGH;
  pixels[5][2] = HIGH;
  pixels[1][3] = HIGH;
  pixels[6][3] = HIGH;
  pixels[0][4] = HIGH;
  pixels[7][4] = HIGH;
  pixels[0][5] = HIGH;
  pixels[7][5] = HIGH;
  pixels[1][6] = HIGH;
  pixels[6][6] = HIGH;
  
}




