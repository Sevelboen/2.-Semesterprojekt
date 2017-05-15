
 
int led1 = 2;
int led2 = 3;
int led3 = 4;
int led4 = 5;
String input = "";

void setup()
{
    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
    pinMode(led3, OUTPUT);
    pinMode(led4, OUTPUT);

    // Start up serial connection
    Serial.begin(9600); // baud rate
    Serial.flush();
    
}

void loop()
{
    
    // Read any serial input
    
    
        input = (char) Serial.read(); // Read in one char at a time
         // Delay for 5 ms so the next char has time to be received
    

    if (input == "1")
    {
      if (digitalRead(led1) == HIGH){
         digitalWrite(led1, LOW);
      }
      else if (digitalRead(led1) == LOW){
         digitalWrite(led1, HIGH);
      }
    }
   else if (input == "2")
   {
       if (digitalRead(led2) == HIGH){
         digitalWrite(led2, LOW);
      }
      else if (digitalRead(led2) == LOW){
         digitalWrite(led2, HIGH);
      }
   }
   else if (input == "3")
   {
       if (digitalRead(led3) == HIGH){
         digitalWrite(led3, LOW);
      }
      else if (digitalRead(led3) == LOW){
         digitalWrite(led3, HIGH);
      }
   }
   else if (input == "4")
   {
       if (digitalRead(led4) == HIGH){
         digitalWrite(led4, LOW);
      }
      else if (digitalRead(led4) == LOW){
         digitalWrite(led4, HIGH);
      }
   }
 }
