#include "arduino_secrets.h"
#include "thingProperties.h"
//#include "arduino_secrets.h"

const int trigPin = D11;
const int echoPin = D12;
const int led = D13;

//define sound speed in cm/uS
#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701

long duration;
float distanceCm;
float distanceInch;
int contagem = 0;
float maximo = 40;


void pisca(int vezes)
{
  for (int i = 0; i< vezes; i++){
    digitalWrite(led,1);
    delay(300);
    digitalWrite(led,0);
    delay(300);
  }
}

void setup() {
  Serial.begin(9600); //INICIALIZA A PORTA SERIAL
  delay(1500); 
  initProperties();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
  pinMode(echoPin, INPUT); //DEFINE O PINO COMO ENTRADA (RECEBE)
  pinMode(trigPin, OUTPUT); //DEFINE O PINO COMO SAIDA (ENVIA)

  pinMode(led,OUTPUT);
  pisca(3);
}



void loop() {
  //ArduinoCloud.update();
  /* // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance
  distanceCm = duration * SOUND_SPEED/2;
  
  // Convert to inches
  distanceInch = distanceCm * CM_TO_INCH;
  
  // Prints the distance in the Serial Monitor
  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);
  Serial.print("Distance (inch): ");
  Serial.println(distanceInch);
  */
  if(contagem >= 1)
  {
    contagem = 0;
    leDistancia();
    nivel = ((maximo-distanceCm)*100)/maximo;
    if(nivel >= 80)
    {
      lixocheio = 0;
    }
    else
    {
      lixocheio = 1;
    }
    ArduinoCloud.update();
  }
  else
  {
    contagem++;
  }
  delay(1000);
  
}

void leDistancia()
{
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

    
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance
  distanceCm = duration * SOUND_SPEED/2;

  Serial.print("Distancia (cm): ");
  Serial.println(distanceCm);
}
