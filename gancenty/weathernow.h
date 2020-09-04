void WeatherNowInfo(){
    screenCleanA();
    Heltec.display->setFont(ArialMT_Plain_10);
    Heltec.display->setTextAlignment(TEXT_ALIGN_CENTER_BOTH);
    drawRectdotO(36,0,128-37,32,3);
    Heltec.display->drawString(screencenterX,screencenterY-5,weathernow); 
    Heltec.display->drawString(screencenterX,screencenterY+5,"Temp:"+tempnow+"°C");
    Heltec.display->display();
}
void WeatherNowDis(){
    int setday=0;
    if(WiFi.status() != WL_CONNECTED){
      WeatherNowInfo();
      puzzled(0,0,32,32);
      Serial.println(F("No Internet Connect!"));
      Serial.flush();
      return;
    }
    UpdateWeatherNow();
    WeatherNowInfo();
    if(weathernow=="null"){
      puzzled(0,0,32,32);
    }//获取不到天气信息
    if(weathercode[setday]==0||weathercode[setday]==1||weathercode[setday]==38){
      sunny(0,0,32,32);
    }
    if(weathercode[setday]==4||weathercode[setday]==5||weathercode[setday]==6||weathercode[setday]==7||weathercode[setday]==8||weathercode[setday]==9){
      cloudy(0,0,32,32);
    }
    if(weathercode[setday]==10){
      shower(0,0,32,32);
    }   
    if(weathercode[setday]==11||weathercode[setday]==12){
      thunderrain(0,0,32,32);
    } 
    if(weathercode[setday]==13||weathercode[setday]==14){
      lightrain(0,0,32,32);
    } 
    if(weathercode[setday]==15||weathercode[setday]==16||weathercode[setday]==17||weathercode[setday]==18){
      heavyrain(0,0,32,32);
    }
    if(weathercode[setday]==19||weathercode[setday]==20||weathercode[setday]==21||weathercode[setday]==22||weathercode[setday]==23){
      lightsnow(0,0,32,32);
    }
    if(weathercode[setday]==24||weathercode[setday]==25||weathercode[setday]==37){
      heavysnow(0,0,32,32);
    }
    if(weathercode[setday]==26||weathercode[setday]==27||weathercode[setday]==28||weathercode[setday]==29||weathercode[setday]==30||weathercode[setday]==31){
      if(hour()>=18){
        nightfog(0,0,32,32);
      }else{
        dayhaze(0,0,32,32);
      }
    }
    if(weathercode[setday]==32||weathercode[setday]==33||weathercode[setday]==34||weathercode[setday]==35||weathercode[setday]==36){
      windy(0,0,32,32);
    }
}
