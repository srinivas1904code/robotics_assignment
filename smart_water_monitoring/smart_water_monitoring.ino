#include<SoftwareSerial.h>
byte statusled = 13;
byte interuptpin = 0;//interrupt pin as pin2
byte sensorpin = 2;
float calibrfact = 4.5;// outputs 4.5 pulses per second for 1 lit/min
volatile byte pulsecount;
float flowrate;
unsigned int flowMl;
unsigned long totalMl;
unsigned long oldTime;
SoftwareSerial esp8266(3,5);
#define SSID "Rasp"
#define PASS "123456789"


String sendAT(String command,const int timeout){
  String response = "";
  esp8266.print(command);
  long int time = millis();
  while(millis()-time<timeout){
    while(esp8266.available()){
      char c = esp8266.read();
      response = response+c;
      
    }
  }
  Serial.print(response);
  return response;
}


void connectWifi(){
  sendAT("AT\r\n",1000);
  sendAT("AT+CWMODE=1\r\n",2000); //station mode
  sendAT("AT+CWJAP=\""SSID"\",\""PASS"\"\r\n",1000);
  while(!esp8266.find("OK")){
  }
  sendAT("AT+CIFSR\r\n",1000);
  sendAT("AT+CIPMUX=0\r\n",1000);//restricting connections to 1
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  esp8266.begin(9600);
  sendAT("AT+RST\r\n",2000);
  connectWifi();
  pinMode(statusled,OUTPUT);
  digitalWrite(statusled,HIGH);
  pinMode(sensorpin,INPUT);
  digitalWrite(sensorpin,HIGH);
  pulsecount = 0;
  flowrate = 0.0;
  flowMl = 0;
  totalMl = 0;
  oldTime = 0;
 attachInterrupt(interuptpin,pulsecounter,FALLING); //hall sensor connected to pin2 and configured to trigger on a Falling change 
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned int frac;
  if((millis()-oldTime)>1000){
    detachInterrupt(interuptpin);// disables the interrupt after 1 second
    flowrate = ((1000.0/(millis()-oldTime))*pulsecount)/calibrfact;
    oldTime = millis();
    flowMl = (flowrate*1000)/60;
    totalMl = totalMl + flowMl;
    Serial.print("Flow rate:");
    Serial.print(int(flowrate));
    Serial.print(". ");
    frac = (flowrate-int(flowrate))*10;
    Serial.print(frac,DEC);// prints the fractional part of the vehicle
    Serial.print("L/min  ");
    Serial.print("current liquid flowing");
    Serial.print(flowMl);
    Serial.print("ml/sec  ");
    Serial.print("cummulative flow:");
    Serial.print(totalMl);
    Serial.println("ml");
    pulsecount = 0; //resseting for countingagain
    attachInterrupt(interuptpin,pulsecounter,FALLING);
  }
  String F = String(frac);
  String FM = String(flowMl);
  String TM = String(totalMl);
  updateTS(F,FM,TM);
}


void updateTS(String F,String FM,String TM){
  Serial.print(" ");
  sendAT("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80\r\n",1000);
  delay(2000);
  String cmdlen;
  String cmd = "GET /update?key=X8JQ90DPRIMDXTRN&field1="+F+"&field2="+FM+"&field3="+TM+"\r\n;";
  cmdlen = cmd.length();
  sendAT("AT+CIPSEND="+cmdlen+"\r\n",2000);
  esp8266.print(cmd);
  sendAT("AT+CIPCLOSE\r\n",2000);
  Serial.print("");
}

void pulsecounter(){
  pulsecount++;
}
