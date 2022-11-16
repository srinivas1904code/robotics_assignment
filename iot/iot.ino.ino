#include<SoftwareSerial.h>
#include<dht.h>
dht DHT;
String temp,hum;
SoftwareSerial esp8266(3,5);
#define SSID "Rasp"
#define PASS "123456789"
String sendAT(String command, const int timeout)
{
  String response = "";
  esp8266.print(command);
  long int time = millis();
  while((time+timeout) > millis())
  {
    while(esp8266.available()){
      char c = esp8266.read();
      response = response+c;
    }
    }
    Serial.print(response);
    return response;
  }

  void setup(){
    Serial.begin(9600);
    esp8266.begin(9600);
    Serial.println("weather monitor");
    sendAT("AT+RST\r\n",2000);
    sendAT("AT\r\n",1000);
    sendAT("AT+CWMODE=1\r\n",2000);
    sendAT("AT+CWJAP=\""SSID"\",\""PASS"\"\r\n",2000);
    while(!esp8266.find("OK")){
      
    }
    sendAT("AT+CIFSR\r\n",1000);
    sendAT("AT+CIPMUX=0\r\n",1000); //restrict it to one connection
    
  }
  void loop(){
    int tempdata = DHT.read11(6);
    Serial.print("temperature: ");
    Serial.print(DHT.temperature);
    Serial.print("\t");
    Serial.print("humidity: ");
    Serial.print(DHT.humidity);
    temp = DHT.temperature;
    delay(2000);
    hum = DHT.humidity;
    updateTS(temp,hum);
    delay(3000);  
  }



  void updateTS(String t,String h){
    Serial.print("");
    sendAT("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80\r\n",1000);
    delay(2000);
    String cmdlen;
    String cmd = "GET /update?api_key=4S3Y2SPASY95O81Y&field1="+h+"&field2="+t+"\r\n";
    cmdlen = cmd.length();
    sendAT("AT+CIPSEND="+cmdlen+"\r\n",2000);
    esp8266.print(cmd);
    Serial.print("");
    sendAT("AT+CLIPCLOSE\r\n",2000);//closes the tcp connection
    delay(2000);
  }
