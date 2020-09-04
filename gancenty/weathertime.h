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
      }//获取不到天气信息
      if(weathercode==0||weathercode==1||weathercode==38){
        sunny(95,0,32,32);
      }
      if(weathercode==4||weathercode==5||weathercode==6||weathercode==7||weathercode==8||weathercode==9){
        cloudy(95,0,32,32);
      }
      if(weathercode==10){
        shower(95,0,32,32);
      }   
      if(weathercode==11||weathercode==12){
        thunderrain(95,0,32,32);
      } 
      if(weathercode==13||weathercode==14){
        lightrain(95,0,32,32);
      } 
      if(weathercode==15||weathercode==16||weathercode==17||weathercode==18){
        heavyrain(95,0,32,32);
      }
      if(weathercode==19||weathercode==20||weathercode==21||weathercode==22||weathercode==23){
        lightsnow(95,0,32,32);
      }
      if(weathercode==24||weathercode==25||weathercode==37){
        heavysnow(95,0,32,32);
      }
      if(weathercode==26||weathercode==27||weathercode==28||weathercode==29||weathercode==30||weathercode==31){
        if(hour()>=18){
          nightfog(95,0,32,32);
        }else{
          dayhaze(95,0,32,32);
        }
      }
      if(weathercode==32||weathercode==33||weathercode==34||weathercode==35||weathercode==36){
        windy(95,0,32,32);
      }
}
