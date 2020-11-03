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
      delay(100); 
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
void energy(int xpos,int ypos,int iwidth,int iheight){
    screenClean(xpos,ypos,iwidth,iheight);
    Heltec.display->drawXbm(xpos, ypos, iwidth, iheight, energy00);
    
    Heltec.display->display();
    delay(refreshtime);
    screenClean(xpos,ypos,iwidth,iheight);
    Heltec.display->drawXbm(xpos, ypos, iwidth, iheight, energy01);
    
    Heltec.display->display();
    delay(refreshtime);
    screenClean(xpos,ypos,iwidth,iheight);
    Heltec.display->drawXbm(xpos, ypos, iwidth, iheight, energy02);
    
    Heltec.display->display();
    delay(refreshtime);
    screenClean(xpos,ypos,iwidth,iheight);
    Heltec.display->drawXbm(xpos, ypos, iwidth, iheight, energy03);
    
    Heltec.display->display();
    delay(refreshtime);
    screenClean(xpos,ypos,iwidth,iheight);
    Heltec.display->drawXbm(xpos, ypos, iwidth, iheight, energy04);
    
    Heltec.display->display();
    delay(refreshtime);
    screenClean(xpos,ypos,iwidth,iheight);
    Heltec.display->drawXbm(xpos, ypos, iwidth, iheight, energy05);
    
    Heltec.display->display();
    delay(refreshtime);
    screenClean(xpos,ypos,iwidth,iheight);
    Heltec.display->drawXbm(xpos, ypos, iwidth, iheight, energy06);
    
    Heltec.display->display();
    delay(refreshtime);
    screenClean(xpos,ypos,iwidth,iheight);
    Heltec.display->drawXbm(xpos, ypos, iwidth, iheight, energy07);
    
    Heltec.display->display();
    delay(refreshtime);
    screenClean(xpos,ypos,iwidth,iheight);
    Heltec.display->drawXbm(xpos, ypos, iwidth, iheight, energy08);
    
    Heltec.display->display();
    delay(refreshtime);
    screenClean(xpos,ypos,iwidth,iheight);
    Heltec.display->drawXbm(xpos, ypos, iwidth, iheight, energy09);
    
    Heltec.display->display();
    delay(refreshtime);
    screenClean(xpos,ypos,iwidth,iheight);
    Heltec.display->drawXbm(xpos, ypos, iwidth, iheight, energy10);
    
    Heltec.display->display();
    delay(refreshtime);
    screenClean(xpos,ypos,iwidth,iheight);
    Heltec.display->drawXbm(xpos, ypos, iwidth, iheight, energy11);
    
    Heltec.display->display();
    delay(refreshtime);
    screenClean(xpos,ypos,iwidth,iheight);
    Heltec.display->drawXbm(xpos, ypos, iwidth, iheight, energy12);
    
    Heltec.display->display();
    delay(refreshtime);
    screenClean(xpos,ypos,iwidth,iheight);
    Heltec.display->drawXbm(xpos, ypos, iwidth, iheight, energy13);
    
    Heltec.display->display();
    delay(refreshtime);
    screenClean(xpos,ypos,iwidth,iheight);
    Heltec.display->drawXbm(xpos, ypos, iwidth, iheight, energy14);
    
    Heltec.display->display();
    delay(refreshtime);
    screenClean(xpos,ypos,iwidth,iheight);
    Heltec.display->drawXbm(xpos, ypos, iwidth, iheight, energy15);
    
    Heltec.display->display();
    delay(refreshtime);
    screenClean(xpos,ypos,iwidth,iheight);
    Heltec.display->drawXbm(xpos, ypos, iwidth, iheight, energy16);
    
    Heltec.display->display();
    delay(refreshtime);
    screenClean(xpos,ypos,iwidth,iheight);
    Heltec.display->drawXbm(xpos, ypos, iwidth, iheight, energy17);
    
    Heltec.display->display();
    delay(refreshtime);
    screenClean(xpos,ypos,iwidth,iheight);
    Heltec.display->drawXbm(xpos, ypos, iwidth, iheight, energy18);
    
    Heltec.display->display();
    delay(refreshtime);
    screenClean(xpos,ypos,iwidth,iheight);
    Heltec.display->drawXbm(xpos, ypos, iwidth, iheight, energy19);
    
    Heltec.display->display();
    delay(refreshtime);
    screenClean(xpos,ypos,iwidth,iheight);
    Heltec.display->drawXbm(xpos, ypos, iwidth, iheight, energy20);
    
    Heltec.display->display();
    delay(refreshtime);
    screenClean(xpos,ypos,iwidth,iheight);
    Heltec.display->drawXbm(xpos, ypos, iwidth, iheight, energy21);
    
    Heltec.display->display();
    delay(refreshtime);
    screenClean(xpos,ypos,iwidth,iheight);
    Heltec.display->drawXbm(xpos, ypos, iwidth, iheight, energy22);
    
    Heltec.display->display();
    delay(refreshtime);
    screenClean(xpos,ypos,iwidth,iheight);
    Heltec.display->drawXbm(xpos, ypos, iwidth, iheight, energy23);
    
    Heltec.display->display();
    delay(refreshtime);
    screenClean(xpos,ypos,iwidth,iheight);
    Heltec.display->drawXbm(xpos, ypos, iwidth, iheight, energy24);
    
    Heltec.display->display();
    delay(refreshtime);    
    screenClean(xpos,ypos,iwidth,iheight);
    Heltec.display->drawXbm(xpos, ypos, iwidth, iheight, energy25);
    
    Heltec.display->display();
    delay(refreshtime);
    screenClean(xpos,ypos,iwidth,iheight);
    Heltec.display->drawXbm(xpos, ypos, iwidth, iheight, energy26);
    
    Heltec.display->display();
    delay(refreshtime);
    screenClean(xpos,ypos,iwidth,iheight);
    Heltec.display->drawXbm(xpos, ypos, iwidth, iheight, energy27);
    
    Heltec.display->display();
    delay(refreshtime);
}
