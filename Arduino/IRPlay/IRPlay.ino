#define IRledPin 13
#define NumIRsignals 96



int IRsignalSRC[] = {
  22, 194,
  24, 84,
  24, 84,
  24, 82,
  26, 82,
  26, 190,
  24, 192,
  24, 84,
  24, 84,
  24, 192,
  24, 82,
  26, 82,
  26, 82,
  26, 190,
  22, 86,
  22, 4722,
  20, 196,
  26, 82,
  22, 86,
  22, 86,
  22, 86,
  22, 86,
  22, 86,
  22, 192,
  24, 192,
  24, 84,
  22, 194,
  22, 194,
  26, 190,
  24, 84,
  24, 194,
  22, 4504,
  26, 190,
  24, 84,
  24, 84,
  24, 86,
  22, 86,
  20, 196,
  20, 194,
  22, 86,
  22, 86,
  22, 194,
  22, 86,
  22, 86,
  22, 86,
  22, 194,
  22, 86,
  20, 0};

int IRsignalVU[] = {
  24, 192,
  24, 84,
  24, 86,
  22, 86,
  22, 86,
  20, 86,
  22, 86,
  22, 194,
  22, 86,
  22, 194,
  22, 86,
  22, 86,
  22, 86,
  22, 194,
  22, 84,
  22, 4828,
  26, 194,
  22, 84,
  24, 84,
  24, 84,
  22, 86,
  22, 194,
  22, 194,
  22, 86,
  22, 194,
  22, 86,
  22, 194,
  20, 196,
  20, 196,
  20, 86,
  22, 194,
  22, 4396,
  24, 192,
  24, 86,
  22, 86,
  22, 86,
  22, 86,
  22, 86,
  20, 86,
  22, 194,
  22, 86,
  22, 194,
  22, 86,
  22, 86,
  22, 86,
  22, 194,
  22, 86,
  22, 4830,
  22, 194,
  22, 86,
  22, 84,
  24, 84,
  22, 86,
  22, 194,
  22, 194,
  22, 86,
  22, 194,
  22, 86,
  22, 194,
  20, 196,
  20, 196,
  20, 88,
  20, 194,
  22, 0};

int IRsignalVD[] = {
  24, 190,
  24, 84,
  24, 86,
  22, 86,
  22, 86,
  22, 194,
  22, 86,
  22, 194,
  22, 86,
  22, 194,
  20, 86,
  22, 86,
  22, 86,
  22, 194,
  22, 86,
  22, 4720,
  24, 192,
  24, 86,
  22, 86,
  22, 86,
  22, 86,
  22, 86,
  22, 192,
  22, 86,
  22, 194,
  22, 86,
  22, 194,
  22, 194,
  22, 194,
  22, 86,
  20, 196,
  20, 4506,
  24, 190,
  26, 86,
  20, 88,
  20, 86,
  22, 86,
  22, 194,
  22, 86,
  22, 194,
  22, 86,
  22, 194,
  22, 86,
  20, 86,
  22, 86,
  22, 194,
  22, 86,
  22, 0};

int IRsignalON[] = {
  22, 194,
  26, 82,
  26, 82,
  24, 84,
  24, 84,
  24, 84,
  24, 190,
  26, 190,
  26, 82,
  26, 190,
  26, 82,
  26, 82,
  24, 84,
  24, 192,
  22, 86,
  22, 4722,
  20, 196,
  22, 86,
  22, 86,
  22, 86,
  22, 84,
  24, 192,
  24, 84,
  22, 86,
  22, 194,
  22, 86,
  22, 194,
  22, 194,
  24, 190,
  26, 82,
  26, 192,
  24, 4504,
  24, 190,
  26, 82,
  26, 82,
  26, 84,
  22, 86,
  22, 86,
  22, 194,
  22, 194,
  22, 86,
  22, 194,
  22, 86,
  22, 86,
  22, 84,
  22, 194,
  22, 86,
  22, 0};

void setup(void) {
  digitalWrite(IRledPin, LOW);   
  Serial.begin(9600);      
}

void loop() {
  char data[6];
  int index = 0;

  delay(1000); 

  while (Serial.available() > 0) {          
    if (index < 5) {                          
      data[index] = Serial.read();           
      index++;                              
    }
  }
  
  data[5]='\0'; 
  
  if (strcmp(data, "POWER") == 0){                
    Serial.println("SENDING SIGNAL!");
    for (int i = 0; i < NumIRsignals; i+=2) {         
      pulseIR(IRsignalON[i]*10);              
      delayMicroseconds(IRsignalON[i+1]*10);  
    }
  } else if (strcmp(data, "SOURC") == 0){                
    Serial.println("SENDING SIGNAL!");
    for (int i = 0; i < NumIRsignals; i+=2) {         
      pulseIR(IRsignalSRC[i]*10);             
      delayMicroseconds(IRsignalSRC[i+1]*10); 
    }
  } else if (strcmp(data, "VOLDN") == 0){                
    Serial.println("SENDING SIGNAL!");
    for (int i = 0; i < NumIRsignals; i+=2) {         
      pulseIR(IRsignalSRC[i]*10);             
      delayMicroseconds(IRsignalVD[i+1]*10);  
    }
  }else if (strcmp(data, "VOLUP") == 0){                
    Serial.println("SENDING SIGNAL!");
    for (int i = 0; i < NumIRsignals; i+=2) {         
      pulseIR(IRsignalSRC[i]*10);              
      delayMicroseconds(IRsignalVU[i+1]*10);  
    }
  }
}
void pulseIR(long microsecs) {
  cli(); 
 
  while (microsecs > 0) {
   digitalWrite(IRledPin, HIGH); 
   delayMicroseconds(10);        
   digitalWrite(IRledPin, LOW);   
   delayMicroseconds(10);        
   microsecs -= 26;
  }
  sei(); 
}

