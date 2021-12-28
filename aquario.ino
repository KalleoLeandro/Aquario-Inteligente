#include <Servo.h>
#define tmp36 A0
#define ph A1
#define autoluz A2
#define pot A5
//luz
#define light 11
#define botmode 12
#define botliga 18

//nível da água
#define echoPin 9 // Echo Pin
#define trigPin 10 // Trigger Pin
//motor vibração
#define vib 3
//motor limpeza
#define mot1A 7
#define mot1B 6
//motor nível
#define mot2A 5
#define mot2B 4

Servo myservo;
int temp=0;
int modo=0;
int num=0;
int dia;
int nivel=0;
int maxRange=300;
long duration, distance;
int limpeza=7;
int aluz=0;
int bluz=0;
unsigned long tempoanterior = 0;
unsigned long tempoatual=0;
String temperatura;
String luz="ON ";
String f="O;NORMAL";
String funcao;

void setup()
{  
  Serial.begin(9600);
  myservo.attach(8);
  pinMode(2,OUTPUT);
  pinMode(tmp36,INPUT);
  pinMode(ph,INPUT);
  pinMode(vib, OUTPUT);
  pinMode(mot1A,OUTPUT);
  pinMode(mot1B,OUTPUT);
  pinMode(mot2A,OUTPUT);
  pinMode(mot2B,OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(autoluz, INPUT);
  pinMode(13, OUTPUT);
  pinMode(light, OUTPUT);
  pinMode(botmode, INPUT);
  pinMode(botliga, INPUT);
  pinMode(pot, INPUT);
}

void loop()
{  
  myservo.write(0);
  tempoatual = millis();
  if(tempoatual-(86400000*dia)>0)
  {
    dia++;
  }
  temp = map(((analogRead(tmp36) - 20) * 3.04), 0, 1023, -40, 125);
   if(temp<10)
  {    
    digitalWrite(2,HIGH);
  }
  if(temp>25)
  {
    digitalWrite(2,LOW);
  } 
  temperatura = String(temp);
  funcao="T";
  funcao+=";";
  funcao+=temperatura;
  funcao+="C";
  Serial.println(funcao);
  delay(2000);
  if(digitalRead(botmode)==1)
  {
    modo++;
  }
  if(modo%2!=0)
  {
    luz="OFF";
    if(digitalRead(botliga)==1)
    {      
      num++;
      if(num%2==0)
      {
        
        digitalWrite(light,HIGH);
      }
      else
      {        
        digitalWrite(light,LOW);
      }
    }    
  }
  
  else
  {
    luz="ON ";
    /*if(tempoatual-(86400000*dia) >= 64800000 || tempoatual - (86400000*dia) <= 21600000)
    Esse comentário está no código para controlar a luz via horário do dia(sendo possível ajustar no código um intervalo das 20:00 as 06:00 por exemplo)
    {*/   
    	aluz=map(analogRead(autoluz),0,1023,0,255);    
  		bluz=map(analogRead(pot),0,1023,0,100);    
 		if(aluz<bluz)
 		{
  	  	digitalWrite(light,HIGH);      
  		}
    	else
    	{
      	digitalWrite(light,LOW);
    	}    
    /*}
    else
    {
      	digitalWrite(light,LOW);
    }
    */    
  }    
  funcao=("L");
  funcao+=";";
  funcao+=luz;  
  Serial.println(funcao);
  delay(2000);  
  if(tempoatual-tempoanterior>= 30000)
  {
    f="COMIDA ";
    funcao=("C");
    funcao+=";";
    funcao+=f;
  	Serial.println(funcao);
    delay(1000);
    myservo.write(180);
  	delay(3000);
  	myservo.write(0);   
    tempoanterior=tempoatual;
    tempoatual=0;
    delay(2000);
  }
  
  limpeza=map(analogRead(ph),0,1023,0,14);  
  if(limpeza<3 || limpeza >10)
  {  
    f="LIMPEZA";
    funcao=("F");
    funcao+=";";
    funcao+=f;
  	Serial.println(funcao);
    delay(1000);
    digitalWrite(vib,HIGH);
    digitalWrite(mot1A, HIGH);
    digitalWrite(mot1B, LOW);
    delay(2000);
    digitalWrite(vib,LOW);
    digitalWrite(mot1A, LOW);
    digitalWrite(mot1B,HIGH);
    delay(2000);
    limpeza=map(analogRead(ph),0,1023,0,14);  
  	if(limpeza<3 || limpeza >10)
    {
      do
      {
        digitalWrite(vib,HIGH);
        digitalWrite(mot1A, HIGH);
        digitalWrite(mot1B, LOW);
        delay(2000);
        digitalWrite(vib,LOW);
        digitalWrite(mot1A, LOW);
        digitalWrite(mot1B,HIGH);
        limpeza=map(analogRead(ph),0,1023,0,14);
      }while(limpeza<3 || limpeza >10);
    }
    digitalWrite(mot1A, LOW);
    digitalWrite(mot1B, LOW);    
  }
  delay(2000);
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration/58.2;
  if(distance >= maxRange)
  {
    f="  NIVEL";
    funcao=("N");
    funcao+=";";
    funcao+=f;
  	Serial.println(funcao);  		
    delay(1000);
    do
    {
      
      digitalWrite(mot2A, HIGH);
      digitalWrite(mot2B, LOW);
      delay(2000);    
      digitalWrite(mot2A, LOW);
      digitalWrite(mot2B,HIGH);
      delay(2000);
      digitalWrite(mot2A, LOW);
      digitalWrite(mot2B, LOW);
      //releitura
      digitalWrite(trigPin, LOW); 
      delayMicroseconds(2); 
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10); 
      digitalWrite(trigPin, LOW);
      duration = pulseIn(echoPin, HIGH);
      distance = duration/58.2;
    }while(distance >= maxRange);
  }
  f="NORMAL ";
  funcao=("O");
  funcao+=";";
  funcao+=f;
  Serial.println(funcao);
  delay(2000);
}
