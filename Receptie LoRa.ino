#include <SPI.h>    
#include <LoRa.h>  
#include <LiquidCrystal_I2C.h> 

LiquidCrystal_I2C lcd(0x27, 16, 2); 
int x = 0;                         
int y = 0;                         
String inString = "";    
String MyMessage = ""; 
void Reset()
{
   lcd.clear();  
   x = 0;        
   y = 0;        
}
String Decodare(String morseCode)
{
    String alphabet;    
    
    
  
    if (morseCode == ".-") {
        alphabet = "A";
    } else if (morseCode == "-...") {
        alphabet = "B";
    } else if (morseCode == "-.-.") {
        alphabet = "C";
    } else if (morseCode == "-..") {
        alphabet = "D";
    } else if (morseCode == ".") {
        alphabet = "E";
    } else if (morseCode == "..-.") {
        alphabet = "F";
    } else if (morseCode == "--.") {
        alphabet = "G";
    } else if (morseCode == "....") {
        alphabet = "H";
    } else if (morseCode == "..") {
        alphabet = "I";
    } else if (morseCode == ".---") {
        alphabet = "J";
    } else if (morseCode == "-.-") {
        alphabet = "K";
    } else if (morseCode == ".-..") {
        alphabet = "L";
    } else if (morseCode == "--") {
        alphabet = "M";
    } else if (morseCode == "-.") {
        alphabet = "N";
    } else if (morseCode == "---") {
        alphabet = "O";
    } else if (morseCode == ".--.") {
        alphabet = "P";
    } else if (morseCode == "--.-") {
        alphabet = "Q";
    } else if (morseCode == ".-.") {
        alphabet = "R";
    } else if (morseCode == "...") {
        alphabet = "S";
    } else if (morseCode == "-") {
        alphabet = "T";
    } else if (morseCode == "..-") {
        alphabet = "U";
    } else if (morseCode == "...-") {
        alphabet = "V";
    } else if (morseCode == ".--") {
        alphabet = "W";
    } else if (morseCode == "-..-") {
        alphabet = "X";
    } else if (morseCode == "-.--") {
        alphabet = "Y";
    } else if (morseCode == "--..") {
        alphabet = "Z";
    }
 
    else if (morseCode == "-----") {
        alphabet = "0";
    } else if (morseCode == ".----") {
        alphabet = "1";
    } else if (morseCode == "..---") {
        alphabet = "2";
    } else if (morseCode == "...--") {
        alphabet = "3";
    } else if (morseCode == "....-") {
        alphabet = "4";
    } else if (morseCode == ".....") {
        alphabet = "5";
    } else if (morseCode == "-....") {
        alphabet = "6";
    } else if (morseCode == "--...") {
        alphabet = "7";
    } else if (morseCode == "---..") {
        alphabet = "8";
    } else if (morseCode == "----.") {
        alphabet = "9";
    }
    
    else if (morseCode == "C") {
        Reset();
        alphabet = "CLEAR";
    } else if (morseCode == "S") {
        alphabet = " ";
    } else if (morseCode == "COM. NU FUNCT.") {
        Reset();
        alphabet = "COM. NU FUNCT.";
    } else {
        alphabet = "";
    }

    return alphabet;
} 
void setup() {
  pinMode(3,OUTPUT); 
  Serial.begin(9600); 
  lcd.init();           
    lcd.backlight();     
  while (!Serial);
  Serial.println("LoRa Receiver");
  if (!LoRa.begin(433E6))
 { 
    Serial.println("Starting LoRa failed!"); 
    
  }
 
}
 void loop() {   
  digitalWrite(3,false); 
  int packetSize = LoRa.parsePacket(); 
  if (packetSize) { 
    digitalWrite(3,true); 
    while (LoRa.available())
    {
      int inChar = LoRa.read();
      inString += (char)inChar;
      MyMessage = inString;       
    }
    inString = "";     
    LoRa.packetRssi();  
    String control;
    MyMessage=Decodare(MyMessage); 
    control=MyMessage;
     Serial.println(MyMessage);    
     lcd.setCursor(x, y);
     if (control == "CLEAR") {
            MyMessage = "";
           
        } else {
            x++;  
        }
        if (x >= 16) {
            if (y == 0) {
                y++;   
                x = 0;  
            } else {
                Reset();  
            }
        }
         lcd.print(MyMessage);  
      delay(1000);
      digitalWrite(3,false);     
  } 
} 
