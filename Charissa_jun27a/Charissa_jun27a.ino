#include "arduino_secrets.h"
#include "thingProperties.h"

#define emx 19
#define led1 2
bool flagEmx;

void pisca(int vezes)
{
    for(int i = 0; i < vezes; i++)
    {
      digitalWrite(led1,1);
      delay(500);
      digitalWrite(led1,0);
      delay(500);
    }
}

void setup() {
  Serial.begin(9600);
  delay(1500); 
  initProperties();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();


 
  pinMode(emx, INPUT_PULLUP);
  pinMode(led1, OUTPUT);
  printf("ola\n");
 pisca(3);
  
}

void loop() {
  ArduinoCloud.update();
  flagEmx = digitalRead(emx);
  
  if(flagEmx == LOW || botao == 1)
  {
    for(int i = 0; i < 3; i++){
      led = 1;
      ArduinoCloud.update();
      digitalWrite(led1,1);
      delay(500);
      printf("emergencia\n");
      led = 0;
      ArduinoCloud.update();
      digitalWrite(led1,0);
      delay(500);
    }
  }
  
}
/*
void onTempChange()  {
  // Add your code here to act upon Temp change
}

void onLedChange()  {
  // Add your code here to act upon Led change
}


void onBotaoChange()  {
  // Add your code here to act upon Botao change
}*/
