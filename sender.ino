// Libraries used for the arduino code for the wireless receiver to work
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// Declaring each of the variables for the program
RF24 radio(9, 10); 
const byte address[6] = "00001"; //Address so that the two NRF24L01 wireless modules know who each other are
int pir_pin = 2; // Declaring that the PIR is connected to digital Pin 2
boolean pir_state = 0; // Sets the default state of the PIR to 0 (off/not detecting anything)


void setup() 
{
  pinMode(pir_pin, INPUT); // Declares that the PIR is an input
  radio.begin(); //Setup functions for the NRF24L01 wireless module     
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN); 
  radio.stopListening();
  Serial.println("System active");  
}


void loop()
{
  pir_state = digitalRead(pir_pin); //Reads the current state of the PIR (if it is activated or not)
  if(pir_state == HIGH){ //If the PIR is triggered then excecute this function
    const char text[] = "PIR State is HIGH";
    radio.write(&text, sizeof(text)); //Sends the "text" data to the other wireless module              
  }
  else{ //else if the pir is not triggered then excecute this function
    const char text[] = "PIR State is LOW";
    radio.write(&text, sizeof(text)); //Sends the "text" data to the other wireless module
  }
  radio.write(&pir_state, sizeof(pir_state)); //Sends the "pir_state" data to the other wireless module
  delay(200);
}
