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
      nowpassed+=pausetime;//过去时候的暂停时间加上暂停时间
      secondpassed=now()-nowpassed;//过去的秒数
      pausetime=0;//暂停时间归零
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