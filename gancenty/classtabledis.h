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
        Heltec.display->drawString(64,16,"Fallin all in you !"); 
        Heltec.display->display();
        a=false;
        break;
      }
  return a;//判断是否有课表 返回值 bool
}
