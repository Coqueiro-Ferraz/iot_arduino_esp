#include <Wire.h>
#include <Adafruit_BMP085.h>
#include <dht.h>
#include "arduino_secrets.h"
#include "thingProperties.h"

#define emx 19
#define led1 2

#define MAX_DUTY 2000
#define MIN_DUTY 500

int senoide[30] = {90,109,127,143,157,168,
                  176,180,180,176,168,157,
                  143,127,109,90,71,53,37,
                  23,12,4,0,0,4,12,23,37,
                  53,71};

//#define pinoDHT11 ADC2_CH0
bool flagEmx;
const int pinoServo = 18;
const int pinoDHT11 = 4; 
String medido;
int count = 0;
dht DHT; 
Adafruit_BMP085 bmp;

void moveServo(int angulo)
{
    // código do teste do servo motor
    int i;
    int duty = (angulo / 180.0) * (MAX_DUTY - MIN_DUTY) + MIN_DUTY;
    for (i = 0; i < 2; i++)
    {
        digitalWrite(pinoServo, 1);
        delayMicroseconds(duty);
        digitalWrite(pinoServo, 0);
        delayMicroseconds(20000 - duty);
    }
    // fim do teste do servo motor
}



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

void servoSeno()
{
  for(int i = 0; i<30; i++)
  {
    moveServo(senoide[i]);
    //delay(10);
  }
}

void barom()
{  
    Serial.print("Temperatura: "); //Imprime O Texto No Monitor Serial
    temp = bmp.readTemperature();
    ArduinoCloud.update();
    
    Serial.print(bmp.readTemperature()); //Imprime No Monitor Serial A Temperatura
    Serial.println(" *C (Grau Celsius)"); //Imprime O Texto No Monitor Serial
        
    Serial.print("Pressão: "); //Imprime O Texto No Monitor Serial
    Serial.print(bmp.readPressure()); //Imprime No Monitor Serial A Pressão
    Serial.println(" Pa (Pascal)"); //Imprime O Texto No Monitor Serial
     
    Serial.print("Altitude: "); //Imprime O Texto No Monitor Serial
    Serial.print(bmp.readAltitude()); //Imprime No Monitor Serial A Altitude APROXIMADA
    Serial.println(" m (Metros)"); //Imprime O Texto No Monitor Serial
    
    Serial.print("Pressão a nível do mar (calculada): "); //IMPRIME O TEXTO NO MONITOR SERIAL
    Serial.print(bmp.readSealevelPressure()); //Imprime No Monitor Serial A Pressão A Nível Do Mar
    Serial.println(" Pa (Pascal)"); //Imprime O Texto No Monitor Serial

    Serial.print("Altitude real: "); //Imprime O Texto No Monitor Serial
    Serial.print(bmp.readAltitude(101500)); //Imprime No Monitor Serial A Altitude Real
    Serial.println(" m (Metros)"); //Imprime O Texto No Monitor Serial
     
    Serial.println("-----------------------------------"); //Imprime Uma Linha No Monitor Serial
    delay(2000); //Intervalo De 2 Segundos
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
  pinMode(pinoServo, OUTPUT);
  printf("ola\n");
  moveServo(0);
  pisca(3);
  
  /*if (!bmp.begin()){
    Serial.println("Sensor BMP180 não foi identificado! Verifique as conexões."); 
  }*/
   
}

void loop() {
  
  //medido = DHT.Humidity;
  if(count == 50)
  {
    count = 0;
    DHT.read11(pinoDHT11);

    Serial.print("H: "); 
    Serial.print(DHT.humidity);
    Serial.print("% / T: "); 
    Serial.print(DHT.temperature,0);
    Serial.print("°C\n"); 
    temp = DHT.temperature;
    umid = DHT.humidity;

  //  barom();
    ArduinoCloud.update();
  }
  else
  {
    count++;
  }
  ArduinoCloud.update();
  flagEmx = digitalRead(emx);
  moveServo(servo); 
  if(flagEmx == LOW || botao == 1)
  {
    for(int i = 0; i < 3; i++){
      /*led = 1;
      ArduinoCloud.update();
      digitalWrite(led1,1);
      moveServo(180);
      delay(500);
      printf("emergencia\n");
      led = 0;
      ArduinoCloud.update();
      digitalWrite(led1,0);
      moveServo(0);
      delay(500);*/
      servoSeno();
    }
  }
  delay(10);
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
