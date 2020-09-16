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
String reqLocation = "Nanchang";            // 城市
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
int weathercode[3]={0,0,0};//现在天气代码
String weatherOnlineUpdate="";//网络天气更新时间

time_t lastupdate=0;//最后更新时间
time_t updatetime=10*60;//更新延迟 十分钟
#define CLASSTABLE "/classtable.txt"//课表文件目录

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
}
int DisplayType=1;//显示模块
bool timecount=true;//计时开启
bool clearOnce=true;//forecast清屏
int nowpassed=0;//过去开始计时时候的now()
int secondpassed=0;//过去的时间
int pausetime=0;//暂停时间
bool pause=false;//计时器暂停
void loop(){
  int progress=0;//进度条变量
  String nowstr="";
  if(digitalRead(0)==LOW&&DisplayType==2){
    pause=!pause;
    delay(100);
    pausetime=now()-(nowpassed+secondpassed);
  }
  while(digitalRead(0)==LOW){
    screenCleanA();
    Heltec.display->drawProgressBar(15,17,98,10,progress);
    delay(10);
    progress+=2;
    
    if(progress==100){
    DisplayType+=1;
    timecount=true;
    pause=false;
    clearOnce=true;
    progress=0;
    if(DisplayType==8){
      DisplayType=1;
    }
    }
    
    switch(DisplayType){
    case 1:nowstr="1.WeatherTimeDis";break;
    case 2:nowstr="2.TimeCountDis";break;
    case 3:nowstr="3.ClassTableDis";break;
    case 4:nowstr="4.WeatherNowDis";break;
    case 5:nowstr="5.TimeDis";break;
    case 6:nowstr="6.WeatherDis";break;
    case 7:nowstr="7.WiFiDis";break;
    default:break;
  }  
    Heltec.display->setFont(ArialMT_Plain_10);
    Heltec.display->setTextAlignment(TEXT_ALIGN_CENTER_BOTH); 
    Heltec.display->drawString(64,9,nowstr); 
    Heltec.display->display();
  }
  switch(DisplayType){
    case 1:WeatherTimeDis();break;
    case 2:TimeCountDis();break;
    case 3:ClasstableDis(weekday()-1);break;
    case 4:WeatherNowDis();break;
    case 5:TimeDis();break;
    case 6:WeatherForecastDis();break;
    case 7:WifiDis();break;
    default:break;
  }
 }
void ClasstableDis(int classday){
    screenCleanA();
    if(!juagefile()){
      return;
    }
    Heltec.display->setFont(ArialMT_Plain_10);
    Heltec.display->setTextAlignment(TEXT_ALIGN_CENTER_BOTH); 
    if(classday==0){
    classday=7;//调整到星期日的课表
    }
    String COURSE;//课程名字
    String COURSETI;//上课时间
    String COURSERO;//上课地点
    File datetable=SPIFFS.open(CLASSTABLE,"r");//打开CLASSTABLE课表   
    while(datetable.available()){
    datetable.readStringUntil('\r\n');//跳过注释部分
    for(int i=0;i<classday;i++){
       datetable.readStringUntil('?');
       datetable.readStringUntil('/');
    }//选择第几天的课表
    bool judge=true;
    int j=0;
   if(hour()>=22&&hour()<=24&&judge){     
    datetable.readStringUntil('?');
    datetable.readStringUntil('/');
    Serial.println(F("跳过三次"));
    } 
   if(hour()>=12&&hour()<=18&&judge){  
    j=1;
    datetable.readStringUntil('/');
    datetable.readStringUntil('/');
    Serial.println(F("跳过一次"));
    judge=false;
    }
   if(hour()>=18&&hour()<=22&&judge){
    j=2;
    datetable.readStringUntil('/');
    datetable.readStringUntil('/');
    datetable.readStringUntil('/');
    datetable.readStringUntil('/');
    Serial.println(F("跳过二次"));
    judge=false;
    }
    screenCleanA();
    drawRectdotI(0,0,128,32,3);
    for(int i=0;i<2;i++){
    //循环两次把课表两节课显示出来
    //LIKE  /高数T08001000C1105F01-16/线代T10201150C1106F01-15/TCF/TCF/TCF/TCF/
    COURSE=datetable.readStringUntil('T');//COURSE
    delay(10);
    if(COURSE==""){
      COURSE=F("^_^");
      }
    COURSETI=datetable.readStringUntil('C');//时间
    delay(10);
    if(COURSETI==""){
      COURSETI=F("00:00-00:00");
      }
    COURSERO=datetable.readStringUntil('/');//教室 
    delay(10);
    if(COURSERO==""){
      COURSERO=F("0000");
      }
      int xpos,ypos;
      switch(i){
        case 0:xpos=screencenterX;ypos=screencenterY-6;break;
        case 1:xpos=screencenterX;ypos=screencenterY+6;break;
        default:xpos=0;ypos=0;break;
      }
      String title=COURSE+"  "+COURSERO+"  "+COURSETI;
      Heltec.display->drawString(xpos-48,ypos,COURSE); 
      Heltec.display->drawString(xpos-18,ypos,COURSERO); 
      Heltec.display->drawString(xpos+28,ypos,COURSETI); 
    }
      Heltec.display->display();
      datetable.close();
   }
   int i=0;
   while(digitalRead(0)!=LOW){
      delay(500);
      i++;
      if(i==120){
        break;
      }
   }
 }
bool juagefile(){
    bool a=true;
    while(!SPIFFS.exists(CLASSTABLE)){  
      //判断是否存在classtable文件
        Heltec.display->setFont(ArialMT_Plain_16);
        Heltec.display->setTextAlignment(TEXT_ALIGN_CENTER_BOTH); 
        Heltec.display->drawString(64,16,"Oh No!"); 
        Heltec.display->display();
        a=false;
        break;
      }
  return a;//判断是否有课表 返回值 bool
}
void WeatherForecastDis(){
  int delaytime=500;
  if(clearOnce){
    screenCleanA();
    clearOnce=false;    
  }else{
    delaytime=0;
  }
  Heltec.display->setTextAlignment(TEXT_ALIGN_CENTER_BOTH);
  Heltec.display->setFont(ArialMT_Plain_10);
  for(int setday=0;setday<3;setday++){
    if(digitalRead(0)==LOW){
      clearOnce=true;
      break;
    }//退出显示天气预报
    switch(setday){
      case 0:xpos=0;ypos=0;break;
      case 1:xpos=48;ypos=0;Heltec.display->drawString(40,15,"<>");Heltec.display->display();delay(delaytime);break;
      case 2:xpos=96;ypos=0;Heltec.display->drawString(88,15,"<>");Heltec.display->display();delay(delaytime);break;
      default:break;
    }
    if(weathernow=="null"){
      puzzled(xpos,ypos,32,32);
      continue;
    }//获取不到天气信息
    if(weathercode[setday]==0||weathercode[setday]==1||weathercode[setday]==38){
      sunny(xpos,ypos,32,32);
    }
    if(weathercode[setday]==4||weathercode[setday]==5||weathercode[setday]==6||weathercode[setday]==7||weathercode[setday]==8||weathercode[setday]==9){
      cloudy(xpos,ypos,32,32);
    }
    if(weathercode[setday]==10){
      shower(xpos,ypos,32,32);
    }   
    if(weathercode[setday]==11||weathercode[setday]==12){
      thunderrain(xpos,ypos,32,32);
    } 
    if(weathercode[setday]==13||weathercode[setday]==14){
      lightrain(xpos,ypos,32,32);
    } 
    if(weathercode[setday]==15||weathercode[setday]==16||weathercode[setday]==17||weathercode[setday]==18){
      heavyrain(xpos,ypos,32,32);
    }
    if(weathercode[setday]==19||weathercode[setday]==20||weathercode[setday]==21||weathercode[setday]==22||weathercode[setday]==23){
      lightsnow(xpos,ypos,32,32);
    }
    if(weathercode[setday]==24||weathercode[setday]==25||weathercode[setday]==37){
      heavysnow(xpos,ypos,32,32);
    }
    if(weathercode[setday]==26||weathercode[setday]==27||weathercode[setday]==28||weathercode[setday]==29||weathercode[setday]==30||weathercode[setday]==31){
      if(hour()>=18){
        nightfog(xpos,ypos,32,32);
      }else{
        dayhaze(xpos,ypos,32,32);
      }
    }
    if(weathercode[setday]==32||weathercode[setday]==33||weathercode[setday]==34||weathercode[setday]==35||weathercode[setday]==36){
      windy(xpos,ypos,32,32);
    }
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

void TimeCountDis(){  
    if(timecount){
      nowpassed=now();
      timecount=false;
      pausetime=0;
      }
    if(!pause){
      screenCleanA();
      Heltec.display->setTextAlignment(TEXT_ALIGN_CENTER_BOTH);
      Heltec.display->setFont(ArialMT_Plain_16);
      String timenow="";
      nowpassed+=pausetime;
      secondpassed=now()-nowpassed;
      pausetime=0;
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
   }else{
      screenCleanA();
      Heltec.display->setTextAlignment(TEXT_ALIGN_CENTER_BOTH);
      Heltec.display->setFont(ArialMT_Plain_16);
      String timenow="";
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
      Heltec.display->drawXbm(95, 0, 32, 32, energy27);
      Heltec.display->display();  
      delay(500);
      pausetime=now()-(nowpassed+secondpassed);
  }
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
