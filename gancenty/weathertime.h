void WeatherTimeInfo(){
    screenCleanA();
    String timenow="";
    if(hour()<10){
      timenow+="0";
    }
    timenow+=String(hour());
    timenow+=":";
    if(minute()<10){
      timenow+="0";
    }
    timenow+=String(minute());
    timenow+=":";
    if(second()<10){
      timenow+="0";
    }
    timenow+=String(second());
    drawRectdotO(0,0,90,32,3); 
    Heltec.display->setTextAlignment(TEXT_ALIGN_CENTER_BOTH);
    Heltec.display->setFont(ArialMT_Plain_10);
    Heltec.display->drawString(screencenterX-15,screencenterY-5,timenow); 
    String datenow="";
    if(month()<10){
      datenow+="0";
    }
    datenow+=String(month());
    datenow+='/';
    if(day()<10){
      datenow+="0";
    }
    datenow+=String(day());
    switch(weekday()){
      case 1:datenow+=F(" Sun");break;
      case 2:datenow+=F(" Mon");break;
      case 3:datenow+=F(" Tue");break;
      case 4:datenow+=F(" Wed");break;
      case 5:datenow+=F(" Thu");break;
      case 6:datenow+=F(" Fri");break;
      case 7:datenow+=F(" Sat");break;
      default:datenow+=F(" NULL");
    }
    Heltec.display->setTextAlignment(TEXT_ALIGN_CENTER_BOTH);
    Heltec.display->setFont(ArialMT_Plain_10);
    Heltec.display->drawString(screencenterX+15,screencenterY+5,datenow);
    Heltec.display->display(); 
}
void WeatherTimeDis(){
    int setday=0;
      if(WiFi.status() != WL_CONNECTED){
      WeatherTimeInfo();
      puzzled(95,0,32,32);
      Serial.println(F("No Internet Connect!"));
      Serial.flush();
      return;
    }
    UpdateWeatherNow();
    WeatherTimeInfo();
     if(weathernow=="null"){
        puzzled(95,0,32,32);
        return;
      }//获取不到天气信息
      if(weathercode[setday]==0||weathercode[setday]==1||weathercode[setday]==38){
        sunny(95,0,32,32);
      }
      if(weathercode[setday]==4||weathercode[setday]==5||weathercode[setday]==6||weathercode[setday]==7||weathercode[setday]==8||weathercode[setday]==9){
        cloudy(95,0,32,32);
      }
      if(weathercode[setday]==10){
        shower(95,0,32,32);
      }   
      if(weathercode[setday]==11||weathercode[setday]==12){
        thunderrain(95,0,32,32);
      } 
      if(weathercode[setday]==13||weathercode[setday]==14){
        lightrain(95,0,32,32);
      } 
      if(weathercode[setday]==15||weathercode[setday]==16||weathercode[setday]==17||weathercode[setday]==18){
        heavyrain(95,0,32,32);
      }
      if(weathercode[setday]==19||weathercode[setday]==20||weathercode[setday]==21||weathercode[setday]==22||weathercode[setday]==23){
        lightsnow(95,0,32,32);
      }
      if(weathercode[setday]==24||weathercode[setday]==25||weathercode[setday]==37){
        heavysnow(95,0,32,32);
      }
      if(weathercode[setday]==26||weathercode[setday]==27||weathercode[setday]==28||weathercode[setday]==29||weathercode[setday]==30||weathercode[setday]==31){
        if(hour()>=18){
          nightfog(95,0,32,32);
        }else{
          dayhaze(95,0,32,32);
        }
      }
      if(weathercode[setday]==32||weathercode[setday]==33||weathercode[setday]==34||weathercode[setday]==35||weathercode[setday]==36){
        windy(95,0,32,32);
      }
}
