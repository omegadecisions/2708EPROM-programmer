#include <SD.h>

//
// Mode of programmer
// 0 - command wait
// 1 - read chip
// 2 - write chip
int nMode = 0;

int writePin = 4;
int readPin = 5;
uint8_t dataBuffer[1024];


//
// Prepare ports for address bus
//
void init_address_bus() {

  // preare mode for A0-A7 bits
  DDRA = 0xFF;
  PORTA = 0x00;

  // preare A8,A9 bits
  DDRL = 0xFF;
  PORTL = 0x00;
  
}


//
// Prepare port C as data bus
//
void init_data_bus () {
  set_data_bus_to_read();
}


//
// Compare EPROM with bufer
//
bool check_eprom() {
  
  // define result flag
  int res = true;
  int current_byte;
  
  // set EPROM address to maximum value
  int address = 1023;

  // high and low parts of address
  int high_byte, low_byte;

  // prepare control signals to read EPROM
  set_pr_led_off ();
  set_high_voltage_off ();
  set_cs_low ();
  set_pr_low ();
  
  // Set Data Bus to read data
  set_data_bus_to_read();

  int col = 0;

  while (address >= 0 && res == true) {

    high_byte = highByte (address);
    low_byte = lowByte (address);

    // set low addresses of address bus
    PORTA = low_byte;

    // set high addresses of address bus
    PORTL = high_byte;
    
    // prepare control signals to read EPROM
    set_pr_led_off ();
    set_high_voltage_off ();
    set_cs_low ();
    set_pr_low ();

    delay (10);
    
    // read current byte from EPROM
    current_byte = PINC;
    delay (10);

    Serial.print (dataBuffer[address], HEX);
    Serial.print (":");
    Serial.print (current_byte, HEX);
   
    if(current_byte != dataBuffer[address]){
      res = false;
    }
    
    if (col < 8) {
      col = col + 1;
      Serial.print (" ");      
    } else {
      col = 0;
      Serial.print ("\n");      
    }
    
    
    address = address - 1;

  }

  return res;
}


//
// Read file to array
//
bool load_dump () {

  int address = 0;
  
  File fileDump = SD.open("dump.bin");
  if (fileDump) {

    for (address = 0; address < 1024; address++) {
      dataBuffer[address] = fileDump.read();
    }

    fileDump.close();
    return true;
  
  } else {
    Serial.println("No file dump.bin found!!!");
    return false;
  }

}


//
// Print buffer dump to log
//
void print_dump () {
  
  int address = 0;
  int address_row = 0;
  int row = 0;
  int col = 0;

  for (row = 0; row < 64; row++) {
    address_row = (16 * row);
    Serial.print(address_row, HEX);
    Serial.print(": ");
    for (col = 0; col < 16; col++) {
      address = address_row + col;
        Serial.print(dataBuffer[address], HEX);
        Serial.print(" ");
    }

    Serial.print ("\n");
  }
}


//
// Read data dump from EPROM
//
void read_chip() {

  // set EPROM address to maximum value
  int address = 1023;
  int high_byte, low_byte;

  Serial.println("Start reading chip...");  

  // prepare control signals to read EPROM
  set_pr_led_off ();
  set_high_voltage_off ();
  set_cs_low ();
  set_pr_low ();
  
  // Set Data Bus to read data
  set_data_bus_to_read();
  delay(10);
  
  while (address >= 0) {

    high_byte = highByte (address);
    low_byte = lowByte (address);

    // set low addresses of address bus
    PORTA = low_byte;
    delay(5);

    // set high addresses of address bus
    PORTL = high_byte;
    delay(5);

    set_pr_led_off ();
    set_high_voltage_off ();
    set_cs_low ();
    set_pr_low ();

    delay (10);
  
    // read current byte to bufer
    dataBuffer[address] = PINC;
       
    address = address - 1;

  }
}


//
// Write data dump to EPROM
//
void write_chip() {
  
  int internal_cnt;
  int address = 1023;
  int high_byte, low_byte;

  // prepare control signals to write EPROM
  set_pr_led_on ();
  set_high_voltage_off ();
  set_pr_low ();
  set_cs_high ();
  
  // Set Data Bus to write data
  set_data_bus_to_write();


  for (internal_cnt = 12; internal_cnt > 0; internal_cnt--) {   

    address = 1023;

    while (address >= 0) {

      high_byte = highByte (address);
      low_byte = lowByte (address);
  
      // set low addresses of address bus
      PORTA = low_byte;
  
      // set high addresses of address bus
      PORTL = high_byte;
      delay (2);
          
      // prepare control signals to write EPROM
      set_pr_led_on ();
      set_high_voltage_off ();
      set_pr_low ();
      set_cs_high ();
      

      PORTC = dataBuffer[address];
      delay (2);

      //
      // WRITE pulse
      //
      
      // prepare control signals to PULSE
      set_pr_high ();
      set_high_voltage_on ();
      
      delay (1);
      
      set_high_voltage_off ();
      set_pr_low ();

      address = address - 1;     
      
    }
  }

  set_pr_led_off ();
  set_cs_low ();

  // Set Data Bus to read data
  set_data_bus_to_read();

}


//
// Set mode data bus for read data
//
void set_data_bus_to_read () {

  // set mode Port C for read
  DDRC = 0x00;

  // Pull-UP port C
  PORTC = 0xFF;
 
}


//
// Set mode data bus for write data
//
void set_data_bus_to_write () {

  // set mode Port C for write
  DDRC = 0xFF;

}


// Set high-level to CS (PR)
void set_cs_high () {
  digitalWrite(38, LOW);
}


// Set low-level to CS (PR)
void set_cs_low () {
  digitalWrite(38, HIGH);
}


// set high voltage to PR  off
void set_high_voltage_off () {
  digitalWrite(42, LOW);
}


// set high voltage to PR on
void set_high_voltage_on () {
  digitalWrite(42, HIGH);
}


// set low-level to PR
void set_pr_low () {
  digitalWrite(44, HIGH);
}


// set high-level to PR
void set_pr_high () {
  digitalWrite(44, LOW);
}


// PR LED ON
void set_pr_led_on () {
  digitalWrite(46, HIGH);
}


// PR LED OFF
void set_pr_led_off () {
  digitalWrite(46, LOW);
}


//
// System initial set-up
//
void setup() {

  // prepare serial port baud rate for logging
  Serial.begin(9600);
   while (!Serial) {
      delay(10); 
   }

  Serial.println("System init...");

  // Init ports for address bus
  init_address_bus();

  // Init port for data bus
  init_data_bus();

  // prepare port for SD-CARD CS (chip select)
  pinMode(53, OUTPUT);

  // prepare ports for control buttons
  // "WR" button
  pinMode(writePin, INPUT);
  
  // "RD" button
  pinMode(readPin, INPUT);

  // prepare ports for High-level programming control

  // Chip write LED
  pinMode(46, OUTPUT);
  digitalWrite(46, LOW);
   
  // Low-level CS (PE)
  pinMode(38, OUTPUT);
  digitalWrite(38, HIGH);
  delay(1);

  // Low-level on PR
  pinMode(44, OUTPUT);
  digitalWrite(44,HIGH);
  delay(1);

  // High-voltage keys for PR
  pinMode(42, OUTPUT);
  digitalWrite(42, LOW); 
  delay(1);  

  Serial.println("Systed is ready!");
  Serial.println("Waiting command...");  

}


//
// Main system loop
//
void loop() {

  int loop_cnt = 16;
  int check_flag = false;
  
  // check command buttons
  if (digitalRead(4) == LOW && nMode == 0){
      
    delay (50);
    
    if (!SD.begin(53)) {
      nMode = -1;
      Serial.println("Card failed, or not present");
      return;
    }

    Serial.println("Load EPROM dump...");
    
    if (load_dump()) {
      delay(10);

      Serial.println("Print EPROM dump...");
      print_dump();
      Serial.println("\n");
      delay(10);

      Serial.println("Start writing chip...");
          
      for (loop_cnt=16; loop_cnt > 0; loop_cnt--) {
        Serial.print("N = ");  
        Serial.println(loop_cnt);  
        
        Serial.println("Check eprom...");  
        if (!check_eprom()) {
          Serial.println("Checking eprom is incorrect");  
          // set flag incorrect check EPROM
          check_flag = false;
          
        } else {
          Serial.println("Checking eprom is correct");  
          // set flag to correct check eprom
          check_flag = true;
        }

        write_chip();  
        delay (10);
       
      }

      if (check_flag) {
        Serial.println("EPROM write is success");
      } else {
        Serial.println("EPROM write is wrong");
      }
      
    } else {
      nMode = -1;
      Serial.println("Error reading data dump");
      return;
    }
    
    delay (500);
    
  } else if (digitalRead(5) == LOW && nMode == 0) {
    
    delay (50);
    
    read_chip();
    Serial.println("EPROM data is readed");
    print_dump();
    
    delay (500);
  }

  delay(100);
}
