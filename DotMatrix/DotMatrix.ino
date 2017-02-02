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
unsigned long lastinterrupt = 0;
int timer = 0; //anim timer
int speedval = 0; // speed of anim

int animtype = 2; // 0 = shrinking, 1 = growing, 2 = pulsing;
bool updown = true;

int sqsizelow = 1; //1-4, 4 = smallest, 1 = largest.
int sqsizehigh = 6; //6-3, 3 = smaller, 6 = largest.

const int potpin = 14; //potentiometer pin
const int buttonpin = 13;

void setup() {

  pinMode(buttonpin, INPUT_PULLUP);
  attachInterrupt(buttonpin, switchmode, RISING);
    
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

    if(animtype == 0){

      sqsizelow++;
      sqsizehigh--;

      if(sqsizelow == 5 && sqsizehigh == 2){
        //updown = false;
        sqsizelow = 1;
        sqsizehigh = 6;
      }
      
    }
    else if(animtype == 1){
      
      sqsizelow--;
      sqsizehigh++;

      if(sqsizelow == 0 && sqsizehigh == 7){
        //updown = false;
        sqsizelow = 4;
        sqsizehigh = 3;
      }
    }
    else if(animtype == 2){

      if(updown){
        sqsizelow++;
        sqsizehigh--;

        if(sqsizelow == 5 && sqsizehigh == 2){
          sqsizelow--;
          sqsizehigh++;
          updown = false;
        }
        
      }
      else{
        sqsizelow--;
        sqsizehigh++;

        if(sqsizelow == 0 && sqsizehigh == 7){
          sqsizelow++;
          sqsizehigh--;
          updown = true;
        }
      }
      
    }

    lastupdate = millis();
  }

  square();
  
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

void square(){

  for(int i = 0; i < 8; i++){
    for(int j = 0; j < 8; j++){

      pixels[i][j] = HIGH;
      
    }
  }

  for(int x = sqsizelow - 1; x < sqsizehigh + 2; x++){
    for(int y = sqsizelow - 1; y < sqsizehigh + 2; y++){
      pixels[x][y] = LOW;

      if(x >= sqsizelow && x <= sqsizehigh && y >= sqsizelow && y <= sqsizehigh){
        pixels[x][y] = HIGH;
      }      
    }
  }
  
}

void switchmode(){

  if((millis() - lastinterrupt) > 100){

    animtype++;

    if(animtype == 3){
      animtype = 0;
    }
    
    lastinterrupt = millis();
        
  }
  
}




