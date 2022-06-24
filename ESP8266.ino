#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <time.h>
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");
char  arr[6];
//const char* ssid = "Shiba shopee";
//const char* password = "abcefghhh";
//const char* ssid = "iPhone 12";
//const char* password = "concactihon";
const char* ssid = "86 Cafe and Milktea";
const char* password = "@cmnm86cf";

int timezone = 7 * 3600;
int dst = 0;
String weekDays[7]={"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};


void setup() 
{
  Serial.begin(9600);
  Serial.println();
  Serial.print("Wifi connecting to ");
  Serial.println( ssid );
  WiFi.begin(ssid,password);
  
  while( WiFi.status() != WL_CONNECTED ){
      delay(500);
      Serial.print(".");        
  }
  
  Serial.println("Wifi Connected Success!");
  Serial.print("NodeMCU IP Address : ");
  Serial.println(WiFi.localIP() );

  configTime(timezone, dst, "pool.ntp.org","time.nist.gov");
  Serial.println("\nWaiting for Internet time");

  while(!time(nullptr)){
     Serial.print("*");
     delay(1000);
  }
  Serial.println("\nTime response....OK");   
}

void Send_Data()
{ 
  time_t now = time(nullptr);
  struct tm* p_tm = localtime(&now);
  String weekDay = weekDays[timeClient.getDay()]; 
  sprintf(arr, "%02d%02d%04d%02d%02d%02d%s",p_tm->tm_mday,p_tm->tm_mon + 1,p_tm->tm_year + 1900,p_tm->tm_hour, p_tm->tm_min, p_tm->tm_sec,weekDay);
  //Serial.println(arr);
}

void loop()
{
  Send_Data();
  while (Serial.available())
  {
    char in = (char)Serial.read();
    if (in == 'u')//in la gui
    {
      Serial.print('y');
      delay(100);
      Serial.println(arr);
    }
  }
  Serial.print('s');
  delay(100);
}
