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
void SynchronizeInfo(int progress);//1为time  2为weather
void setwifi();//设置wifi
bool juagefile();//判断文件是否存在

void WeatherNowDis();//天气显示 
void TimeDis();//大屏时间显示
void WeatherTimeDis();//天气和时间和日期显示
void SynchronizeDis(int type);//1为时间同步，2为天气同步
void WeatherForecastDis();//天气预报
void WifiDis();//显示wifi信息
void TimeCountDis();//计时器
void ClasstableDis(int classday);//课表显示

void UpdateWeatherNow();//天气更新

time_t getNtpTime();//获取当前时间
void httpRequest();//现在天气获取函数
