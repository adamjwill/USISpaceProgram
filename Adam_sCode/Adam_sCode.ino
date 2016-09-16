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
    1_2: Changed packet structure to followoing:

        Packet 1:         Packet 2:         Packet 3:
        packet counter    packet counter    packet counter    
        temp_px           soloar_px         plasma_V
        temp_nx           solar_nx          plasma_I
        temp_py           solar_py          gps_long
        temp_ny           solar-ny          gps_lat
        temp_pz           battery_V         gps_alt
        temp_nz           mag_x             hour
        temp_C            mag_y             minute
        temp_P            mag_z             blank
        
*/

int addr = 0;       //address for EEPROM
byte packet= 0;     //counter for addressing of sent packages
byte temp_raw;      //adc value for temp sensors
float temp_V [8];   //voltage variables for temp sensors
float temp[8];      //variable for final temperature
int tmux[4];        //temp MUX control variables

byte solar_raw;     //adc value for solar cells
float solar[4];     //voltage variable for solar cells
byte battery_raw;   //adc value for battery
float battery;      //variable for storing battery
byte fake_magx;     //variables for simulating magnetometer data
byte fake_magy;
byte fake_magz;

byte fake_probe_V;  //variable for simulating plasma probe data
byte fake_probe_I;  //variable for simulating plasma probe data
byte fake_gps_lat;  //variable for simulating gps latitude
byte fake_gps_long;  //variable for simulating gps longitude
byte fake_gps_alt;  //variable for simulating gps altitude

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
  if (packet <2) Serial.print(B0);     // these if statements are just for printing leading zeroes on binary outputs, just to make it look better when it prints
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
  for (int j=0; j<8; j++) {
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
    if (temp_raw/4 <2) Serial.print(B0);    // these if statements are just for printing leading zeroes on binary outputs, just to make it look better when it prints
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

if (packet <2) Serial.print(B0);     // these if statements are just for printing leading zeroes on binary outputs, just to make it look better when it prints
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

packet++;
  if (packet==256)  //resets packet counter to 0 so that packet number always fits within one byte
  {
    packet = 0;
  }
  Serial.println("");
  
  for (int h=0; h<4; h++) {
  solar_raw = analogRead(1)/4;  //reads ADC value and converts to a single byte
  solar[h] = solar_raw*(5.0/255.0); // converts raw ADC value to voltage
  if (solar_raw/4 <2) Serial.print(B0);   // these if statements are just for printing leading zeroes on binary outputs, just to make it look better when it prints
  if (solar_raw/4 <4) Serial.print(B0);
  if (solar_raw/4 <8) Serial.print(B0);
  if (solar_raw/4 <16) Serial.print(B0);
  if (solar_raw/4 <32) Serial.print(B0);
  if (solar_raw/4 <64) Serial.print(B0);
  if (solar_raw/4 <128) Serial.print(B0);
  if (solar_raw/4 <256) Serial.print(B0);
  Serial.print(solar_raw/4, BIN); // displays byte in binary followed by byte description
  Serial.print("\t");
  Serial.print("Solar");
  Serial.print("\t");
  if (h==0) Serial.print("PosX");
  if (h==1) Serial.print("NegX");
  if (h==2) Serial.print("PosY");
  if (h==3) Serial.print("NegY");
  Serial.print("\t");
  Serial.print(":");
  Serial.print("\t");
  Serial.println(solar[h]);
  EEPROM.write(addr, solar);
  addr++;
  delay(dly);
  }

  battery_raw = analogRead(1)/4;  //reads ADC value and converts to a single byte
  battery = battery_raw*(5.0/255.0); // converts raw ADC value to voltage
  if (battery_raw/4 <2) Serial.print(B0);   // these if statements are just for printing leading zeroes on binary outputs, just to make it look better when it prints
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

fake_magx = random(255);
  if (fake_magx <2) Serial.print(B0);   // these if statements are just for printing leading zeroes on binary outputs, just to make it look better when it prints
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
  if (fake_magy <2) Serial.print(B0);   // these if statements are just for printing leading zeroes on binary outputs, just to make it look better when it prints
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
  if (fake_magz <2) Serial.print(B0);   // these if statements are just for printing leading zeroes on binary outputs, just to make it look better when it prints
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

  if (packet <2) Serial.print(B0);     // these if statements are just for printing leading zeroes on binary outputs, just to make it look better when it prints
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

  packet++;
  if (packet==256)  //resets packet counter to 0 so that packet number always fits within one byte
  {
    packet = 0;
  }
  Serial.println("");
  
  fake_probe_V = random(255);               // creates a random byte just to fill in packet
  if (fake_probe_V <2) Serial.print(B0);    // these if statements are just for printing leading zeroes on binary outputs, just to make it look better when it prints
  if (fake_probe_V <4) Serial.print(B0);
  if (fake_probe_V <8) Serial.print(B0);
  if (fake_probe_V <16) Serial.print(B0);
  if (fake_probe_V <32) Serial.print(B0);
  if (fake_probe_V <64) Serial.print(B0);
  if (fake_probe_V <128) Serial.print(B0);
  if (fake_probe_V <256) Serial.print(B0);
  Serial.print(fake_probe_V, BIN); // displays byte in binary followed by byte description
  Serial.print("\t");
  Serial.print("Plasma Probe Voltage:");
  Serial.print("\t");
  Serial.println(fake_probe_V);    
  EEPROM.write(addr, fake_probe_V);
  addr++;
  delay(dly);

  fake_probe_I = random(255);               // creates a random byte just to fill in packet
  if (fake_probe_I <2) Serial.print(B0);    // these if statements are just for printing leading zeroes on binary outputs, just to make it look better when it prints
  if (fake_probe_I <4) Serial.print(B0);
  if (fake_probe_I <8) Serial.print(B0);
  if (fake_probe_I <16) Serial.print(B0);
  if (fake_probe_I <32) Serial.print(B0);
  if (fake_probe_I <64) Serial.print(B0);
  if (fake_probe_I <128) Serial.print(B0);
  if (fake_probe_I <256) Serial.print(B0);
  Serial.print(fake_probe_I, BIN); // displays byte in binary followed by byte description
  Serial.print("\t");
  Serial.print("Plasma Probe Current:");
  Serial.print("\t");
  Serial.println(fake_probe_I);    
  EEPROM.write(addr, fake_probe_I);
  addr++;
  delay(dly);
  
  fake_gps_lat = random(255);
  if (fake_gps_lat <2) Serial.print(B0);   // these if statements are just for printing leading zeroes on binary outputs, just to make it look better when it prints
  if (fake_gps_lat <4) Serial.print(B0);
  if (fake_gps_lat <8) Serial.print(B0);
  if (fake_gps_lat <16) Serial.print(B0);
  if (fake_gps_lat <32) Serial.print(B0);
  if (fake_gps_lat <64) Serial.print(B0);
  if (fake_gps_lat <128) Serial.print(B0);
  if (fake_gps_lat <256) Serial.print(B0);
  Serial.print(fake_gps_lat, BIN); // displays byte in binary followed by byte description
  Serial.print("\t");
  Serial.print("GPS Latitude:");
  Serial.print("\t");
  Serial.println(fake_gps_lat);    
  EEPROM.write(addr, fake_gps_lat);
  addr++;  
  delay(dly);

  fake_gps_long = random(255);
  if (fake_gps_long <2) Serial.print(B0);   // these if statements are just for printing leading zeroes on binary outputs, just to make it look better when it prints
  if (fake_gps_long <4) Serial.print(B0);
  if (fake_gps_long <8) Serial.print(B0);
  if (fake_gps_long <16) Serial.print(B0);
  if (fake_gps_long <32) Serial.print(B0);
  if (fake_gps_long <64) Serial.print(B0);
  if (fake_gps_long <128) Serial.print(B0);
  if (fake_gps_long <256) Serial.print(B0);  
  Serial.print(fake_gps_long, BIN); // displays byte in binary followed by byte description
  Serial.print("\t");
  Serial.print("GPS Latitude:");
  Serial.print("\t");
  Serial.println(fake_gps_long);    
  EEPROM.write(addr, fake_gps_long);
  addr++;  
  delay(dly);

  fake_gps_alt = random(255);
  if (fake_gps_alt <2) Serial.print(B0);   // these if statements are just for printing leading zeroes on binary outputs, just to make it look better when it prints
  if (fake_gps_alt <4) Serial.print(B0);
  if (fake_gps_alt <8) Serial.print(B0);
  if (fake_gps_alt <16) Serial.print(B0);
  if (fake_gps_alt <32) Serial.print(B0);
  if (fake_gps_alt <64) Serial.print(B0);
  if (fake_gps_alt <128) Serial.print(B0);
  if (fake_gps_alt <256) Serial.print(B0);
  Serial.print(fake_gps_alt, BIN); // displays byte in binary followed by byte description
  Serial.print("\t");
  Serial.print("GPS Altitude:");
  Serial.print("\t");
  Serial.println(fake_gps_alt);    
  EEPROM.write(addr, fake_gps_alt);
  addr++;  
  delay(dly);   

  Serial.print("Hour:");
  Serial.print("\t");
  Serial.println(""); 

  Serial.print("Minute:");
  Serial.print("\t");
  Serial.println(""); 

  Serial.println("00000000");

  if (packet <2) Serial.print(B0);     // these if statements are just for printing leading zeroes on binary outputs, just to make it look better when it prints
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

  packet++;
  if (packet==256)  //resets packet counter to 0 so that packet number always fits within one byte
  {
    packet = 0;
  }
  Serial.println("");
}
