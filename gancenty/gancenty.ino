#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <Wire.h>  // Only needed for Arduino 1.6.5 and earlier
#include "heltec.h" // alias for `#include "SSD1306Wire.h"`
#include <Arduino.h>
#include<WiFiManager.h>
#include <TimeLib.h>
#include <WiFiUdp.h>

#include "func.h"

#include "./xbm/wifigif.h"
#include "./xbm/cloudy.h"//阴天 晴晚间多云 晴晚间大部多云
#include "./xbm/sunny.h"//晴天（白天晚上）
#include "./xbm/heavyrain.h"//大雨 暴雨 大暴雨 特大暴雨 
#include "./xbm/shower.h"//阵雨
#include "./xbm/lightrain.h"//小雨 中雨
#include "./xbm/thunderrain.h"//雷阵雨 雷阵雨带有冰雹
#include "./xbm/lightsnow.h"//冻雨 雨夹雪 阵雪 小雪 中雪
#include "./xbm/heavysnow.h"//大雪 暴雪
#include "./xbm/windy.h"//风 大风 飓风 热带风暴 龙卷风
#include "./xbm/nightfog.h"//浮尘 扬沙 沙尘暴 强沙尘暴 雾 霾
#include "./xbm/dayhaze.h"//同上
#include "./xbm/puzzled.h"
#include "./xbm/Synchronize.h"
#include "./xbm/energy.h"

/*天气服务配置信息*/
const char* host = "api.seniverse.com";     // 将要连接的服务器地址  
const int httpPort = 80;                    // 将要连接的服务器端口      
 
// 心知天气HTTP请求所需信息
String reqUserKey = "S0u-8VQ7vWGcXDVf2";   // 私钥
String reqLocation = "Jian";            // 城市
String reqUnit = "c"; 

time_t prevDisplay = 0;//初始时间
unsigned int localPort = 8888;
WiFiUDP Udp;//用于向ntp服务器发送数据包端口
static const char ntpServerName[] = "ntp1.aliyun.com";//时间NTP服务器
const int timeZone = 8; //时区设置

int animationfps=40;//动画30帧
int refreshtime=1000/animationfps;

String weathernow="";//现在天气情况
String tempnow="";//现在温度情况
int weathercode=0;//现在天气代码
String weatherOnlineUpdate="";//网络天气更新时间
time_t lastupdate=0;//最后更新时间
time_t updatetime=10*60;//更新延迟 十分钟
int DisplayType=1;
bool timecount=true;

int xpos=0;
int ypos=0;
int iwidth=0;
int iheight=0;
int16_t screencenterX=0;
int16_t screencenterY=0;

/*动画函数*/
#include "weatherani.h"
#include "wifi.h"
#include "syn.h"
#include "weathernow.h"
#include "weathertime.h"
#include "timenow.h"

void setup() {
  Heltec.begin(true /*DisplayEnable Enable*/, true /*Serial Enable*/);
  Heltec.display->flipScreenVertically();
  Heltec.display->setBrightness(128);
  screenCleanA();
  WiFiManager wifiConnect;
  delay(100); 
  WifiDis();
  wifiConnect.autoConnect("Malloc.","20001031");//WIFI默认密码
  pinMode(0,INPUT_PULLUP);
  screenCleanA();
  Udp.begin(localPort);
  for(int i=0;i<3;i++){
  SynchronizeDis(1);
  if(i==2){
    setSyncProvider(getNtpTime);//Update time
    setSyncInterval(300);//同步时间单位s
    delay(100);
  }
  }
  for(int i=0;i<3;i++){
  SynchronizeDis(2);
  if(i==2){
    UpdateWeatherNow();//Update Weather
    delay(100);
  }
  }
  screenCleanA();
}
void loop(){
  if(digitalRead(0)==LOW){
    delay(1000);
    screenCleanA();
    DisplayType+=1;
    timecount=true;
    if(DisplayType==6){
      DisplayType=1;
    }
  }
  switch(DisplayType){
    case 1:WeatherTimeDis();break;
    case 2:TimeDis();break;
    case 3:WeatherNowDis();break;
    case 4:TimeCountDis();break;
    case 5:WifiDis();break;
    default:break;
  }
 }
int nowpassed=0;
void TimeCountDis(){
    screenCleanA();
    if(timecount){
      nowpassed=now();
      timecount=false;
    }
    Heltec.display->setTextAlignment(TEXT_ALIGN_CENTER_BOTH);
    Heltec.display->setFont(ArialMT_Plain_16);
    String timenow="";
    int secondpassed=now()-nowpassed;
    int hournow=secondpassed/3600;
    int minutenow=(secondpassed-hournow*3600)/60;
    int secondnow=secondpassed%60;
    if(hournow<10){
      timenow+="0";
    }
    timenow+=String(hournow);
    timenow+=":";
    if(minutenow<10){
      timenow+="0";
    }
    timenow+=String(minutenow);
    timenow+=":";
    if(secondnow<10){
      timenow+="0";
    }
    timenow+=String(secondnow);
    drawRectdotI(0,0,90,32,3); 
    Heltec.display->drawString(screencenterX,screencenterY,timenow); 
    Heltec.display->display();
    energy(95,0,32,32);    
}
void UpdateWeatherNow(){
  if(now()-lastupdate>updatetime){
        httpRequest();
        Serial.println("LastUpdate="+String(lastupdate));
        Serial.println("Now="+String(now()));
        Serial.println("OnlineUpdate="+weatherOnlineUpdate);
        Serial.println(F(""));
        Serial.flush();
        lastupdate=now();
      }else{
        Serial.println("LastUpdate="+String(lastupdate));
        Serial.println("Now="+String(now()));
        Serial.println("LeftUpdate="+String(updatetime-now()+lastupdate));
        Serial.println("OnlineUpdate="+weatherOnlineUpdate);
        Serial.println(F("")); 
        Serial.flush();    
      }
}

void drawRectdotI(int xpos,int ypos,int iwidth,int iheight,int density){
    screencenterX=xpos+iwidth/2;
    screencenterY=ypos+iheight/2;
    for(int i=xpos+2;i<xpos+iwidth-2;i+=density){
      Heltec.display->setPixel(i, ypos+2);
    }
    for(int i=xpos+2;i<xpos+iwidth-2;i+=density){
      Heltec.display->setPixel(i, ypos+iheight-3);
    }
    for(int i=ypos+2;i<ypos+iheight-2;i+=density){
      Heltec.display->setPixel(xpos+2, i);
    }
    for(int i=ypos+2;i<ypos+iheight-2;i+=density){
      Heltec.display->setPixel(xpos+iwidth-3, i);
    }
    Heltec.display->drawRect(xpos,ypos,iwidth,iheight);
    Heltec.display->display();
}
void drawRectdotO(int xpos,int ypos,int iwidth,int iheight,int density){
    screencenterX=xpos+iwidth/2;
    screencenterY=ypos+iheight/2;
    for(int i=xpos;i<xpos+iwidth;i+=density){
      Heltec.display->setPixel(i, ypos);
    }
    for(int i=xpos;i<xpos+iwidth;i+=density){
      Heltec.display->setPixel(i, ypos+iheight-1);
    }
    for(int i=ypos;i<ypos+iheight;i+=density){
      Heltec.display->setPixel(xpos, i);
    }
    for(int i=ypos;i<ypos+iheight;i+=density){
      Heltec.display->setPixel(xpos+iwidth-1, i);
    }
    Heltec.display->drawRect(xpos+2,ypos+2,iwidth-4,iheight-4);
    Heltec.display->display();
}

void screenClean(int xpos,int ypos,int iwidth,int iheight){  
  for(int i=xpos;i<xpos+iwidth;i++){
    for(int j=ypos;j<ypos+iheight;j++){
      Heltec.display->setColor(BLACK);
      Heltec.display->setPixel(i,j);  
    }
  }
  Heltec.display->display();
  Heltec.display->setColor(WHITE);
}
void screenCleanA(){
 Heltec.display->clear();  
}

void httpRequest(){
  WiFiClient client;
  String reqRes = "/v3/weather/now.json?key=" + reqUserKey +
                  + "&location=" + reqLocation + 
                  "&language=en&unit=" +reqUnit;
  // 建立http请求信息
  String httpRequest = String("GET ") + reqRes + " HTTP/1.1\r\n" + 
                              "Host: " + host + "\r\n" + 
                              "Connection: close\r\n\r\n";
  Serial.println(""); 
  Serial.print("Connecting to "); Serial.print(host);
 
  // 尝试连接服务器
  if (client.connect(host, 80)){
    Serial.println(" Success!");
 
    // 向服务器发送http请求信息
    client.print(httpRequest);
    Serial.println("Sending request: ");
    Serial.println(httpRequest);  
 
    // 获取并显示服务器响应状态行 
    String status_response = client.readStringUntil('\n');
    Serial.print("status_response: ");
    Serial.println(status_response);
 
    // 使用find跳过HTTP响应头
    if (client.find("\r\n\r\n")) {
      Serial.println("Found Header End. Start Parsing.");
    }
    
    // 利用ArduinoJson库解析心知天气响应信息
    parseInfo(client); 
  } else {
    Serial.println(" connection failed!");
  }   
  //断开客户端与服务器连接工作
  client.stop(); 
}
 
// 利用ArduinoJson库解析心知天气响应信息
void parseInfo(WiFiClient client){
  const size_t capacity = JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(1) + 2*JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(6) + 230;
  DynamicJsonDocument doc(capacity);
  
  deserializeJson(doc, client);
  
  JsonObject results_0 = doc["results"][0];
  
  JsonObject results_0_now = results_0["now"];
  const char* results_0_now_text = results_0_now["text"]; // "Sunny"
  const char* results_0_now_code = results_0_now["code"]; // "0"
  const char* results_0_now_temperature = results_0_now["temperature"]; // "32"
  
  const char* results_0_last_update = results_0["last_update"]; // "2020-06-02T14:40:00+08:00" 
 
  // 通过串口监视器显示以上信息
  String results_0_now_text_str = results_0_now["text"].as<String>(); 
  int results_0_now_code_int = results_0_now["code"].as<int>(); 
  int results_0_now_temperature_int = results_0_now["temperature"].as<int>(); 
  
  String results_0_last_update_str = results_0["last_update"].as<String>();   
  /*-------------显示天气要用到的-----------------*/
  weathernow=results_0_now_text_str;
  weathercode=results_0_now_code_int;
  tempnow=String(results_0_now_temperature_int);
  weatherOnlineUpdate=results_0_last_update_str;
  /*--------------------------------------------*/
  Serial.println(F("======Weahter Now======="));
  Serial.print(F("Weather Now: "));
  Serial.print(results_0_now_text_str);
  Serial.print(F(" "));
  Serial.println(results_0_now_code_int);
  Serial.print(F("Temperature: "));
  Serial.println(results_0_now_temperature_int);
  Serial.print(F("Last Update: "));
  Serial.println(results_0_last_update_str);
  Serial.println(F("========================"));
}
/*---------------------------------NTP code--------------------------*/
const int NTP_PACKET_SIZE = 48; // NTP time is in the first 48 bytes of message
byte packetBuffer[NTP_PACKET_SIZE]; //buffer to hold incoming & outgoing packets

time_t getNtpTime()
{
  IPAddress ntpServerIP; // NTP server's ip address

  while (Udp.parsePacket() > 0) ; // discard any previously received packets
  Serial.println("Transmit NTP Request");
  // get a random server from the pool
  WiFi.hostByName(ntpServerName, ntpServerIP);
  Serial.print(ntpServerName);
  Serial.print(": ");
  Serial.println(ntpServerIP);
  sendNTPpacket(ntpServerIP);
  uint32_t beginWait = millis();
  while (millis() - beginWait < 1500) {
    int size = Udp.parsePacket();
    if (size >= NTP_PACKET_SIZE) {
      Serial.println("Receive NTP Response");
      Udp.read(packetBuffer, NTP_PACKET_SIZE);  // read packet into the buffer
      unsigned long secsSince1900;
      // convert four bytes starting at location 40 to a long integer
      secsSince1900 =  (unsigned long)packetBuffer[40] << 24;
      secsSince1900 |= (unsigned long)packetBuffer[41] << 16;
      secsSince1900 |= (unsigned long)packetBuffer[42] << 8;
      secsSince1900 |= (unsigned long)packetBuffer[43];
      return secsSince1900 - 2208988800UL + timeZone * SECS_PER_HOUR;
    }
  }
  Serial.println("No NTP Response :-(");
  return 0; // return 0 if unable to get the time
}

// send an NTP request to the time server at the given address
void sendNTPpacket(IPAddress &address)
{
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12] = 49;
  packetBuffer[13] = 0x4E;
  packetBuffer[14] = 49;
  packetBuffer[15] = 52;
  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  Udp.beginPacket(address, 123); //NTP requests are to port 123
  Udp.write(packetBuffer, NTP_PACKET_SIZE);
  Udp.endPacket();
}
