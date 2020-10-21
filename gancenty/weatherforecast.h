void WeatherForecastDis(){
  UpdateWeatherNow();
  int delaytime=0;
  if(now() >= prevDisplay){
    prevDisplay=now()+10*60;
    delaytime=500;
  }  
  Heltec.display->setTextAlignment(TEXT_ALIGN_CENTER_BOTH);
  Heltec.display->setFont(ArialMT_Plain_10);
  for(int setday=0;setday<3;setday++){
    if(digitalRead(0)==LOW){
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
