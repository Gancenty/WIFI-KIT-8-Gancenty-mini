## 一：产品简介
WIFI-KIT-8&nbsp;[GitHub首页](https://github.com/HelTecAutomation/Heltec_ESP8266) | [产品官网](https://heltec.org)

## 二：如何使用该项目
### 首先下载该项目
1. 通过Git `Git clone git@github.com:Gancenty/WIFI-KIT-8-Gancenty-mini.git`
2. 直接点击 [DownLoad ZIP](https://github.com/Gancenty/WIFI-KIT-8-Gancenty-mini/archive/master.zip)
### 安装库文件
1. 安装 [ESP8266](https://github.com/esp8266/Arduino) 库
2. 安装[Heltec_ESP8266](https://github.com/HelTecAutomation/Heltec_ESP8266)库
3. 安装 [WifiManager](https://github.com/tzapu/WiFiManager)库
4. 安装 [Time](https://github.com/PaulStoffregen/Time)库
5. 安装 [ArduinoJson](https://github.com/bblanchon/ArduinoJson)库
### 使用Arduino打开 `gancenty/Gancenty.ino` 测试是否编译成功
## 三：代码介绍
`/xbm`文件夹下为bmp位图转换成的c语言数组，用于显示丰富的动画效果 [图片来源](https://icons8.com/animated-icons)

`func.h`一些自定义函数

例：`void wifiicon(int xpos,int ypos,int iwidth,int iheight);`&nbsp;xpos表示在屏幕显示的横轴 ypos表示在屏幕上显示的纵轴 iwidth和iheight是位图长宽，默认为32。

## 四：产品功能
```c
  switch(DisplayType){
    case 1:WeatherTimeDis();break;
    case 2:TimeDis();break;
    case 3:WeatherNowDis();break;
    case 4:TimeCountDis();break;
    case 5:WifiDis();break;
    default:break;
  }
```
1. 显示此时天气，默认更新时间为十分钟`time_t updatetime=10*60;` 
2. 显示此时时间，默认更新时间5分钟`setSyncInterval(300);`
3. 借助`WifiManager`库实现WiFi连接
4. 计时功能`TimeCountDis();`
## 五：如何修改代码
* 自定义天气显示地区`String reqLocation = "BeiJing";  `天气的数据源为 [心知天气](https://www.seniverse.com/) 相关城市名字请查看[心知天气文档](https://cdn.sencdn.com/download/data/thinkpage_cities.zip) 
    
    *注意：由于心知天气免费版只支持全国370余个城市，不确定你所在的地区可以正常加载天气信息*
* 请注册你的心知天气账户，并将你的私钥填写此处 `String reqUserKey = "S0u-8VQ7vWGcXDVf2";`

## 六：最后
本人还是一名学生，相关能力还在增长中，希望有更多大佬能够发起issue来指点一下我。

Email：2539797953@qq.com