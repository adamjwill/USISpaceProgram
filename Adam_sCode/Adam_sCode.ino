#include <EEPROM.h>

/* Code for UNITE CubeSat prototype to be flown on HAB on Oct. 22, 2016
    Prototype will include:
      four AD590 temperature probes routed through a multiplexer
      solar cells with output voltage that will be read by Arduino
      faked data for plasma probe and magnetometer
      data stored in EEPROM to be retrieved after flight

    Printed information is only for testing of prototype and was displayed on serial monitor

    Revisions:
    1_1: Added resistor values for op-amp circuit so temp could be calculated
*/

int addr = 0;       //address for EEPROM
byte packet= 0;     //counter for addressing of sent packages
byte temp_raw;      //adc value for temp sensors
float temp_V [4];   //voltage variables for temp sensors
float temp[4];         //variable for final temperature
int tmux[4];        //temp MUX control variables
byte solar_raw;     //adc value for solar cells
float solar;        //voltage variable for solar cells
byte fake_probe;    //variable for simulating plasma probe data
byte fake_magx;     //variables for simulating magnetometer data
byte fake_magy;
byte fake_magz;
byte battery_raw;   //adc value for battery
float battery;      //variable for storing battery
int dly = 1000;     //variable for setting delay time
int R1 = 993;
int R2 = 997;
int R3 = 10000;

void setup() {
  Serial.begin(9600);
  pinMode(tmux[1],OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (packet <2) Serial.print(B0);
  if (packet <4) Serial.print(B0);
  if (packet <8) Serial.print(B0);
  if (packet <16) Serial.print(B0);
  if (packet <32) Serial.print(B0);
  if (packet <64) Serial.print(B0);
  if (packet <128) Serial.print(B0);
  if (packet <256) Serial.print(B0);
  Serial.print(packet,BIN); //displays byte in binary followed by byte description
  Serial.print("\t");
  Serial.print("Packet:");
  Serial.print("\t");
  Serial.println(packet);

  for (int k=0; k<4; k++) {  //loop which sets all MUX variables to 0
    digitalWrite(tmux[0],LOW);
  }
  for (int j=0; j<4; j++) {
    if (j==1) {
      digitalWrite(tmux[0],HIGH);
    }
    else if (j==2) {
      digitalWrite(tmux[0],LOW);
      digitalWrite(tmux[1],HIGH);
    }
    else if (j==3) {
      digitalWrite(tmux[0],HIGH);
    }
    temp_raw = analogRead(0)/4; // reads ADC value and converts to a single byte
    temp_V[j] = temp_raw*(5.0/255.0); // converts raw ADC value to voltage
    temp[j]=((temp_V[j]*R2/(R2+R3))/R1)*1000000;
    if (temp_raw/4 <2) Serial.print(B0);
    if (temp_raw/4 <4) Serial.print(B0);
    if (temp_raw/4 <8) Serial.print(B0);
    if (temp_raw/4 <16) Serial.print(B0);
    if (temp_raw/4 <32) Serial.print(B0);
    if (temp_raw/4 <64) Serial.print(B0);
    if (temp_raw/4 <128) Serial.print(B0);
    if (temp_raw/4 <256) Serial.print(B0);
    Serial.print(temp_raw/4, BIN); // displays byte in binary followed by byte description
    Serial.print("\t");
    Serial.print("Temp_V");
    Serial.print(j);
    Serial.print(":");
    Serial.print("\t");
    Serial.print(temp_V[j]);
    Serial.print("\t");
    Serial.print(temp[j]);
    Serial.print("K");
    Serial.print("\t");
    Serial.print(temp[j]-273.15);
    Serial.print("C");
    Serial.print("\t");
    Serial.print(((temp[j]-273.15)*(9/5))+32);
    Serial.print("F");
    Serial.println("\t");
    EEPROM.write(addr, temp_V[j]);
    addr++;
    delay(dly);
  }
  solar_raw = analogRead(1)/4;  //reads ADC value and converts to a single byte
  solar = solar_raw*(5.0/255.0); // converts raw ADC value to voltage
  if (solar_raw/4 <2) Serial.print(B0);
  if (solar_raw/4 <4) Serial.print(B0);
  if (solar_raw/4 <8) Serial.print(B0);
  if (solar_raw/4 <16) Serial.print(B0);
  if (solar_raw/4 <32) Serial.print(B0);
  if (solar_raw/4 <64) Serial.print(B0);
  if (solar_raw/4 <128) Serial.print(B0);
  if (solar_raw/4 <256) Serial.print(B0);
  Serial.print(solar_raw/4, BIN); // displays byte in binary followed by byte description
  Serial.print("\t");
  Serial.print("Solar:");
  Serial.print("\t");
  Serial.println(solar);
  EEPROM.write(addr, solar);
  addr++;
  delay(dly);

  fake_probe = random(255);
  if (fake_probe <2) Serial.print(B0);
  if (fake_probe <4) Serial.print(B0);
  if (fake_probe <8) Serial.print(B0);
  if (fake_probe <16) Serial.print(B0);
  if (fake_probe <32) Serial.print(B0);
  if (fake_probe <64) Serial.print(B0);
  if (fake_probe <128) Serial.print(B0);
  if (fake_probe <256) Serial.print(B0);
  Serial.print(fake_probe, BIN); // displays byte in binary followed by byte description
  Serial.print("\t");
  Serial.print("Plasma Probe:");
  Serial.print("\t");
  Serial.println(fake_probe);    
  EEPROM.write(addr, fake_probe);
  addr++;
  delay(dly);
  
  fake_magx = random(255);
  if (fake_magx <2) Serial.print(B0);
  if (fake_magx <4) Serial.print(B0);
  if (fake_magx <8) Serial.print(B0);
  if (fake_magx <16) Serial.print(B0);
  if (fake_magx <32) Serial.print(B0);
  if (fake_magx <64) Serial.print(B0);
  if (fake_magx <128) Serial.print(B0);
  if (fake_magx <256) Serial.print(B0);
  Serial.print(fake_magx, BIN); // displays byte in binary followed by byte description
  Serial.print("\t");
  Serial.print("Mag_X:");
  Serial.print("\t");
  Serial.println(fake_magx);    
  EEPROM.write(addr, fake_magx);
  addr++;  
  delay(dly);

  fake_magy = random(255);
  if (fake_magy <2) Serial.print(B0);
  if (fake_magy <4) Serial.print(B0);
  if (fake_magy <8) Serial.print(B0);
  if (fake_magy <16) Serial.print(B0);
  if (fake_magy <32) Serial.print(B0);
  if (fake_magy <64) Serial.print(B0);
  if (fake_magy <128) Serial.print(B0);
  if (fake_magy <256) Serial.print(B0);  
  Serial.print(fake_magy, BIN); // displays byte in binary followed by byte description
  Serial.print("\t");
  Serial.print("Mag_Y:");
  Serial.print("\t");
  Serial.println(fake_magy);    
  EEPROM.write(addr, fake_magy);
  addr++;  
  delay(dly);

  fake_magz = random(255);
  if (fake_magz <2) Serial.print(B0);
  if (fake_magz <4) Serial.print(B0);
  if (fake_magz <8) Serial.print(B0);
  if (fake_magz <16) Serial.print(B0);
  if (fake_magz <32) Serial.print(B0);
  if (fake_magz <64) Serial.print(B0);
  if (fake_magz <128) Serial.print(B0);
  if (fake_magz <256) Serial.print(B0);
  Serial.print(fake_magz, BIN); // displays byte in binary followed by byte description
  Serial.print("\t");
  Serial.print("Mag_Z:");
  Serial.print("\t");
  Serial.println(fake_magz);    
  EEPROM.write(addr, fake_magz);
  addr++;  
  delay(dly);   
  
  battery_raw = analogRead(1)/4;  //reads ADC value and converts to a single byte
  battery = battery_raw*(5.0/255.0); // converts raw ADC value to voltage
  if (battery_raw/4 <2) Serial.print(B0);
  if (battery_raw/4 <4) Serial.print(B0);
  if (battery_raw/4 <8) Serial.print(B0);
  if (battery_raw/4 <16) Serial.print(B0);
  if (battery_raw/4 <32) Serial.print(B0);
  if (battery_raw/4 <64) Serial.print(B0);
  if (battery_raw/4 <128) Serial.print(B0);
  if (battery_raw/4 <256) Serial.print(B0);
  Serial.print(battery_raw/4, BIN); // displays byte in binary followed by byte description
  Serial.print("\t");
  Serial.print("Battery:");
  Serial.print("\t");
  Serial.println(battery);
  EEPROM.write(addr, battery);
  addr++;
  delay(dly);

  packet++;
  if (packet==256) {
    packet = 0;
  }
  Serial.println("");
}

