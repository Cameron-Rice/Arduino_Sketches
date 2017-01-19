const int onboard = 13;
const int recordButton = 15;
const int inputButton = 16;
const int green_led = 17;

boolean recording = false;
boolean recorded = false;

unsigned long lastInterrupt = 0;

int pos = 0;

int x = 0;

int timer = 0;
boolean steps[5000];

void setup() {

  for(int i = 0; i < 5000; i++){
    steps[i] = false;
  }

  pinMode(onboard, OUTPUT);
  pinMode(recordButton, INPUT);
  pinMode(inputButton, INPUT_PULLUP);
  attachInterrupt(inputButton, input, RISING);
  pinMode(green_led, OUTPUT);

}

void loop() {

  if(digitalRead(recordButton) == HIGH){

    if(recorded == true){
      resetValues();
    }
    

    timer++;
    delay(1000);

    if(timer == 3){
      
      recording = true;
      digitalWrite(onboard, HIGH);
      timer = 0;

      while(recording == true){
       
        pos++;
        delay(1);

        if(pos == 5000){
          recording = false;
          recorded = true;
        }
        
      }
      
    }    
  }
  else{
    digitalWrite(onboard, LOW);
  }

  if(recorded == true){

      digitalWrite(onboard, HIGH);
      delay(500);
      digitalWrite(onboard, LOW);
      delay(500);
      
   }
   else{
      digitalWrite(onboard, LOW);
   }
}

void input(){

  if((millis() - lastInterrupt) > 10){
     
    if(recording == true){
  
      steps[pos] = true;
  
      while(digitalRead(inputButton) == HIGH){
  
        pos++;
        steps[pos] = true;
        delay(1);

        if(pos == 5000){
          recording = false;
          recorded = true;
        }
     
      }
    }

    if(recorded == true){
      playback();
    }

  lastInterrupt = millis();
    
  }
}

void playback(){

  digitalWrite(onboard, HIGH);
  
  for(int i = 0; i < 5000; i++){
    if(steps[i] == true){
      digitalWrite(green_led, HIGH);
      delay(1);
    }
    else if(steps[i] == false){
      digitalWrite(green_led, LOW);
      delay(1);
    }
  }

  digitalWrite(green_led, LOW);
  digitalWrite(onboard, LOW);
  
}

void resetValues(){
  for(int i = 0; i < 5000; i++){
    steps[i] = false;
  }

  recording = false;
  recorded = false;
  pos = 0;
  timer = 0;

  digitalWrite(onboard, HIGH);
  delay(50);
  digitalWrite(onboard, LOW);
  delay(50);
  digitalWrite(onboard, HIGH);
  delay(50);
  digitalWrite(onboard, LOW);
  delay(50);
  digitalWrite(onboard, HIGH);
  delay(50);
  digitalWrite(onboard, LOW);
  delay(50);
  
}

