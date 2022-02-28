// Libraries used for the arduino code for the NRF24L01 wireless receiver to work
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// Declaring each of the variables for the program
RF24 radio(9, 10);
const byte address[6] = "00001"; //Address so that the two NRF24L01 wireless modules know who each other are
boolean pir_state = 0; // Sets the default state of the PIR to 0 (off/not detecting anything)
int fan_pin = 3; //Declaring that the fan is connected to digital pin 3



void setup() 
{
pinMode(6, OUTPUT);
Serial.begin(9600); //Setting baud rate for the system to 9600
radio.begin(); //Setup functions for the NRF24L01 wireless module   
radio.openReadingPipe(0, address); 
radio.setPALevel(RF24_PA_MIN);       
radio.startListening();              
}



void loop(){
  if (radio.available()){ //If the system is active do this
    char text[32] = "";                 
    radio.read(&text, sizeof(text)); //Read the "text" data that has been received from the other NRF24L01 wirless module
    radio.read(&pir_state, sizeof(pir_state)); //Read the "pir_state" data that has been received from the other NRF24L01 wirless module
    if(pir_state == HIGH){ //If the PIR is triggered then excecute this statement
      digitalWrite(6, HIGH); //Set Pin 6 to HIGH/ON
      Serial.println(text);
    }
    else{ //else if the pir is not triggered then excecute this statement
      digitalWrite(6, LOW); //Set Pin 6 to LOW/OFF
      Serial.println(text);
    }
  }
  delay(100);
}
