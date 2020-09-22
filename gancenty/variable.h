
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

int DisplayType=1;//显示模块
bool timecount=true;//计时开启
bool clearOnce=true;//forecast清屏一次
int nowpassed=0;//过去开始计时时候的now()
int secondpassed=0;//过去的时间
int pausetime=0;//暂停时间
bool pause=false;//计时器暂停