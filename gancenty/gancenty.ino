#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <Wire.h>  // Only needed for Arduino 1.6.5 and earlier
#include "heltec.h" // alias for `#include "SSD1306Wire.h"`
#include <Arduino.h>
#include<WiFiManager.h>
#include <TimeLib.h>
#include <WiFiUdp.h>
#include<FS.h>

#include "func.h"
#include "variable.h"

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

/*动画函数*/
#include "weatherani.h"//天气动画
#include "wifi.h"//wifi信息显示
#include "syn.h"//同步动画
#include "weathernow.h"//当天天气
#include "weathertime.h"//天气与时间显示
#include "timenow.h"//当前时间
#include "weatherforecast.h"//天气预报
#include "classtabledis.h"//课表显示
#include "timecount.h"//计时器代码
/************************DHT11传感器读取***********************************/
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 14    // Digital pin connected to the DHT sensor 
// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.

// Uncomment the type of sensor in use:
#define DHTTYPE    DHT11     // DHT 11
//#define DHTTYPE    DHT22     // DHT 22 (AM2302)
//#define DHTTYPE    DHT21     // DHT 21 (AM2301)

// See guide for details on sensor wiring and usage:
//   https://learn.adafruit.com/dht/overview

DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;
/**************************************************************************/
void setup() {
  Heltec.begin(true /*DisplayEnable Enable*/, true /*Serial Enable*/);
  dht.begin();//dht11
  Heltec.display->flipScreenVertically();
  Heltec.display->setBrightness(128);
  screenCleanA();
  SPIFFS.begin();//文件操作服务
  WiFiManager wifiConnect;
  delay(100); 
  wifiConnect.setConfigPortalTimeout(240);
  wifiConnect.setConnectTimeout(30);
  WifiDis();
  wifiConnect.autoConnect("Malloc.","20001031");
  
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
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  Serial.println(F("------------------------------------"));
  Serial.println(F("Temperature Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("°C"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("°C"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("°C"));
  Serial.println(F("------------------------------------"));
  // Print humidity sensor details.
  dht.humidity().getSensor(&sensor);
  Serial.println(F("Humidity Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("%"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("%"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("%"));
  Serial.println(F("------------------------------------"));
  // Set delay between sensor readings based on sensor details.
  delayMS = sensor.min_delay / 1000;  
}

void loop(){
  int progress=0;//进度条变量
  String nowstr="";
  if(hour()>=23&&minute()>=30||hour()<6){
    DisplayType=8;
    nightstatus=true;
  }//自动进入夜间模式
  if(digitalRead(0)==LOW&&DisplayType==8){
    nightstatus=!nightstatus;
    delay(50);
    if(hour()>=23&&minute()>=30||hour()<6){//夜间模式时按动显示时间5秒
      for(int i=0;i<5;i++){
        Heltec.display->displayOn();
        Heltec.display->setBrightness(128);
        TimeDis();
        delay(1000);
      } 
    }
  }
  if(digitalRead(0)==LOW&&DisplayType==2){
    pause=!pause;
    delay(100);
    pausetime=now()-(nowpassed+secondpassed);
  }
  while(digitalRead(0)==LOW){
    screenCleanA();
    Heltec.display->drawProgressBar(15,17,98,10,progress);
    delay(10);
    progress+=1;
    if(progress%(100/4)==0){//每次25自动加一
    DisplayType+=1;
    timecount=true;
    pause=true;
    }
    if(progress==100){
       progress=0;
    }
    if(DisplayType==10){
      DisplayType=1;
    }
    switch(DisplayType){
    case 1:nowstr="1.WeatherTimeDis";break;
    case 2:nowstr="2.TimeCountDis";break;
    case 3:nowstr="3.ClassTableDis";break;
    case 4:nowstr="4.WeatherNowDis";break;
    case 5:nowstr="5.Temper&Humidity";break;
    case 6:nowstr="6.TimeDis";break;
    case 7:nowstr="7.WeatherDis";break;
    case 8:nowstr="8.WiFiDis";break;
    case 9:nowstr="9.NightMode";break;
    default:break;
  }  
    Heltec.display->setFont(ArialMT_Plain_10);
    Heltec.display->setTextAlignment(TEXT_ALIGN_CENTER_BOTH); 
    Heltec.display->drawString(64,9,nowstr); 
    Heltec.display->display();
    screenCleanA(); 
  }
  switch(DisplayType){
    case 1:WeatherTimeDis();break;
    case 2:TimeCountDis();break;
    case 3:ClasstableDis(weekday()-1);break;
    case 4:WeatherNowDis();break;
    case 5:TemperHumidityDis();break;
    case 6:TimeDis();break;
    case 7:WeatherForecastDis();break;
    case 8:WifiDis();break;
    case 9:nightmode();break;
    default:break;
  }
 }
void TemperHumidityDis(){
  // Delay between measurements.
  delay(delayMS);
  // Get temperature event and print its value.
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
    tem=0;
  }
  else {
    Serial.print(F("Temperature: "));
    Serial.print(event.temperature);
    Serial.println(F("°C"));  
    tem=event.temperature;
  }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
    hum=0;
  }
  else {
    Serial.print(F("Humidity: "));
    Serial.print(event.relative_humidity);
    Serial.println(F("%"));
    hum=event.relative_humidity;
  }
    screenCleanA(); 
    Heltec.display->setFont(ArialMT_Plain_10);
    Heltec.display->setTextAlignment(TEXT_ALIGN_CENTER_BOTH);
    drawRectdotI(36,0,128-37,32,3);
    Heltec.display->drawString(screencenterX,screencenterY-5,"Temp:"+(String)(tem)+"°C"); 
    Heltec.display->drawString(screencenterX,screencenterY+5,"Humi:"+(String)(hum)+"%");
    Heltec.display->display();
  WeatherAniDis();
}
void nightmode(){
  int statusnow;
  String str;
  if(nightstatus==true){
    str="ON";
    statusnow=100;
  }else{
    str="OFF";
    statusnow=0;
    Heltec.display->setBrightness(128);
    Heltec.display->displayOn();
  }
  if(now()!=prevDisplay||str=="ON"){
    prevDisplay=now();
    screenCleanA();
//  drawRectdotI(0,2,65,28,3);不好看emmm
    Heltec.display->setFont(ArialMT_Plain_10);
    Heltec.display->setTextAlignment(TEXT_ALIGN_CENTER_BOTH); 
    Heltec.display->drawProgressBar(100,10,20,10,statusnow);
    Heltec.display->drawString(32,16,"Status: "+str); 
    Heltec.display->display();
  }
  statusnow=0;
  while(nightstatus){
    delay(100);
    if(statusnow<50){
      statusnow+=1;
      Heltec.display->setBrightness(128-(statusnow*128/50));
    }
    if(digitalRead(0)==LOW){
      delay(50);
      break;
    }
    if(statusnow==50){
      Heltec.display->displayOff();
    }
    if(hour()==6&&minute()==0){
      Heltec.display->setBrightness(128);
      Heltec.display->displayOn();
      DisplayType=1;
      nightstatus=false;
    }//自动退出夜间模式
  }
}
void setwifi(){
  WiFiManager wifiConnect;
  WiFi.disconnect();
  delay(100); 
  wifiConnect.setConfigPortalTimeout(180);
  wifiConnect.setConnectTimeout(30);
  WifiDis();
  wifiConnect.startConfigPortal("Malloc.","20001031");  
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
  String reqRes = "/v3/weather/daily.json?key=" + reqUserKey +
                  + "&location=" + reqLocation + "&language=en&unit=" +
                  reqUnit + "&start=0&days=3";
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
  }
  else {
    Serial.println(" connection failed!");
  }   
  //断开客户端与服务器连接工作
  client.stop(); 
}
 
void parseInfo(WiFiClient client){
  const size_t capacity = JSON_ARRAY_SIZE(1) + JSON_ARRAY_SIZE(3) + JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(6) + 3*JSON_OBJECT_SIZE(14) + 860;
  
  DynamicJsonDocument doc(capacity);
  
  deserializeJson(doc, client);
  
  JsonObject results_0 = doc["results"][0];
  
  JsonArray results_0_daily = results_0["daily"];
  
  JsonObject results_0_daily_0 = results_0_daily[0];
  const char* results_0_daily_0_date = results_0_daily_0["date"]; 
  const char* results_0_daily_0_text_day = results_0_daily_0["text_day"]; 
  const char* results_0_daily_0_code_day = results_0_daily_0["code_day"];
  const char* results_0_daily_0_text_night = results_0_daily_0["text_night"]; 
  const char* results_0_daily_0_code_night = results_0_daily_0["code_night"]; 
  const char* results_0_daily_0_high = results_0_daily_0["high"];
  const char* results_0_daily_0_low = results_0_daily_0["low"]; 
  const char* results_0_daily_0_rainfall = results_0_daily_0["rainfall"];
  const char* results_0_daily_0_precip = results_0_daily_0["precip"]; 
  const char* results_0_daily_0_wind_direction = results_0_daily_0["wind_direction"]; 
  const char* results_0_daily_0_wind_direction_degree = results_0_daily_0["wind_direction_degree"];
  const char* results_0_daily_0_wind_speed = results_0_daily_0["wind_speed"];
  const char* results_0_daily_0_wind_scale = results_0_daily_0["wind_scale"];
  const char* results_0_daily_0_humidity = results_0_daily_0["humidity"];
  
  JsonObject results_0_daily_1 = results_0_daily[1];
  const char* results_0_daily_1_date = results_0_daily_1["date"];
  const char* results_0_daily_1_text_day = results_0_daily_1["text_day"];
  const char* results_0_daily_1_code_day = results_0_daily_1["code_day"];
  const char* results_0_daily_1_text_night = results_0_daily_1["text_night"]; 
  const char* results_0_daily_1_code_night = results_0_daily_1["code_night"]; 
  const char* results_0_daily_1_high = results_0_daily_1["high"];
  const char* results_0_daily_1_low = results_0_daily_1["low"]; 
  const char* results_0_daily_1_rainfall = results_0_daily_1["rainfall"]; 
  const char* results_0_daily_1_precip = results_0_daily_1["precip"]; 
  const char* results_0_daily_1_wind_direction = results_0_daily_1["wind_direction"];
  const char* results_0_daily_1_wind_direction_degree = results_0_daily_1["wind_direction_degree"]; 
  const char* results_0_daily_1_wind_speed = results_0_daily_1["wind_speed"];
  const char* results_0_daily_1_wind_scale = results_0_daily_1["wind_scale"];
  const char* results_0_daily_1_humidity = results_0_daily_1["humidity"]; 
  
  JsonObject results_0_daily_2 = results_0_daily[2];
  const char* results_0_daily_2_date = results_0_daily_2["date"];
  const char* results_0_daily_2_text_day = results_0_daily_2["text_day"];
  const char* results_0_daily_2_code_day = results_0_daily_2["code_day"];
  const char* results_0_daily_2_text_night = results_0_daily_2["text_night"];
  const char* results_0_daily_2_code_night = results_0_daily_2["code_night"];
  const char* results_0_daily_2_high = results_0_daily_2["high"]; 
  const char* results_0_daily_2_low = results_0_daily_2["low"]; 
  const char* results_0_daily_2_rainfall = results_0_daily_2["rainfall"];
  const char* results_0_daily_2_precip = results_0_daily_2["precip"]; 
  const char* results_0_daily_2_wind_direction = results_0_daily_2["wind_direction"]; 
  const char* results_0_daily_2_wind_direction_degree = results_0_daily_2["wind_direction_degree"]; 
  const char* results_0_daily_2_wind_speed = results_0_daily_2["wind_speed"];
  const char* results_0_daily_2_wind_scale = results_0_daily_2["wind_scale"]; 
  const char* results_0_daily_2_humidity = results_0_daily_2["humidity"]; 
  
  const char* results_0_last_update = results_0["last_update"]; 
  
  // 从以上信息中摘选几个通过串口监视器显示
  if(hour()<18){
    weathernow = results_0_daily_0["text_day"].as<String>(); 
    weathercode[0] = results_0_daily_0["code_day"].as<int>(); 
  }else{
    weathernow = results_0_daily_0["text_night"].as<String>(); 
    weathercode[0] = results_0_daily_0["code_night"].as<int>(); 
  }
  weathercode[1] = results_0_daily_1["code_day"].as<int>();
  weathercode[2] = results_0_daily_2["code_day"].as<int>();
  weatherOnlineUpdate= results_0["last_update"].as<String>();
  tempnow=String(results_0_daily_0["low"].as<int>())+"-"+String(results_0_daily_0["high"].as<int>());


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
