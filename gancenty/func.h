void wifiicon(int xpos,int ypos,int iwidth,int iheight);
void sunny(int xpos,int ypos,int iwidth,int iheight);
void cloudy(int xpos,int ypos,int iwidth,int iheight);
void windy(int xpos,int ypos,int iwidth,int iheight);
void lightsnow(int xpos,int ypos,int iwidth,int iheight);
void heavysnow(int xpos,int ypos,int iwidth,int iheight);
void dayhaze(int xpos,int ypos,int iwidth,int iheight);
void nightfog(int xpos,int ypos,int iwidth,int iheight);
void puzzled(int xpos,int ypos,int iwidth,int iheight);
void shower(int xpos,int ypos,int iwidth,int iheight);
void lightrain(int xpos,int ypos,int iwidth,int iheight);
void heavyrainy(int xpos,int ypos,int iwidth,int iheight);
void thunderrain(int xpos,int ypos,int iwidth,int iheight);
void synchronize(int xpos,int ypos,int iwidth,int iheight);
void energy(int xpos,int ypos,int iwidth,int iheight);
/*累死了我啊！！！*/
void screenClean(int xpos,int ypos,int iwidth,int iheight);//用于屏幕清除
void screenCleanA();//用于屏幕清除 Heltec.display->clear();
void drawRectdotI(int xpos,int ypos,int iwidth,int iheight,int density);//绘制内点框
void drawRectdotO(int xpos,int ypos,int iwidth,int iheight,int density);//绘制外点框

void WifiInfo();//搭配wifiicon
void WeatherNowInfo();//天气信息，搭配天气动画使用
void WeatherTimeInfo();//同时显示天气和时间
void SynchronizeInfo(int progress);
void setwifi();

void WeatherNowDis();//天气显示 
void TimeDis();
void WeatherTimeDis();
void SynchronizeDis(int type);
void WifiDis();
void TimeCountDis();

void UpdateWeatherNow();//天气更新

time_t getNtpTime();//获取当前时间
void httpRequest();//现在天气获取函数
