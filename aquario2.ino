#include <LiquidCrystal.h>
 

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
 
void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("TEMP:20 C");
  lcd.setCursor(9,0);
  lcd.print("LUZ:ON ");
  lcd.setCursor(0,1);
  lcd.print("OPERANDO: NORMAL");
}

String comando;
String temperatura="20 C";
String luz="ON ";
String op="NORMAL ";
int valor;

void loop()
{
  if(Serial.available())
  {
    comando = Serial.readStringUntil(';');
    if(comando=="T")
    {
      temperatura = Serial.readStringUntil('C');
      valor = temperatura.toInt();
      if(valor<10 && valor >=0)
      {
        temperatura ="0";
        temperatura+=valor;
        Serial.println("TEMP"+temperatura);
      }
    }
    if(comando=="L")
    {
      luz = Serial.readStringUntil(';');
      Serial.println("LUZ"+luz);
    }
    if(comando=="C")
    {
      op=Serial.readStringUntil(';');
      Serial.println("OPERANDO"+op);
    }
    if(comando=="F")
    {
      op=Serial.readStringUntil(';');
      Serial.println("OPERANDO"+op);
    }
    if(comando=="N")
    {
      op=Serial.readStringUntil(';');
      Serial.println("OPERANDO"+op);
    }
    if(comando=="O")
    {
      op=Serial.readStringUntil(';');
      Serial.println("OPERANDO"+op);
    }
    lcd.setCursor(5,0);
    lcd.print(temperatura);      
    lcd.setCursor(13,0);
    lcd.print(luz);
    lcd.setCursor(9,1);
    lcd.print(op);    
  }
  delay(100);   
}
  

