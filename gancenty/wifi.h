void WifiInfo(){
  screenCleanA();
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->setTextAlignment(TEXT_ALIGN_CENTER_BOTH);
  drawRectdotO(0,0,90,32,3);
  if(WiFi.status() != WL_CONNECTED){
    Heltec.display->drawString(screencenterX,screencenterY-5,"WIFI AP:"+WiFi.softAPSSID()); 
    Heltec.display->drawString(screencenterX,screencenterY+5,"PSK:"+WiFi.softAPPSK());
  }else{
    Heltec.display->drawString(screencenterX,screencenterY-5,"WIFI:"+WiFi.SSID()); 
    Heltec.display->drawString(screencenterX,screencenterY+5,"PSK:"+WiFi.psk());
  }
  Heltec.display->display(); 
}
void WifiDis(){
  WifiInfo();
  wifiicon(95,0,32,32);
}
void wifiicon(int xpos,int ypos,int iwidth,int iheight){
    screenClean(xpos,ypos,iwidth,iheight);
    Heltec.display->drawXbm(xpos, ypos, iwidth, iheight, wifi00);
    Heltec.display->display();
    delay(refreshtime);
    screenClean(xpos,ypos,iwidth,iheight);
    Heltec.display->drawXbm(xpos, ypos, iwidth, iheight, wifi01);
    Heltec.display->display();
    delay(refreshtime);
    screenClean(xpos,ypos,iwidth,iheight);
    Heltec.display->drawXbm(xpos, ypos, iwidth, iheight, wifi02);
    Heltec.display->display();
    delay(refreshtime);
    screenClean(xpos,ypos,iwidth,iheight);
    Heltec.display->drawXbm(xpos, ypos, iwidth, iheight, wifi03);
    Heltec.display->display();
    delay(refreshtime);
    screenClean(xpos,ypos,iwidth,iheight);
    Heltec.display->drawXbm(xpos, ypos, iwidth, iheight, wifi04);
    Heltec.display->display();
    delay(refreshtime);
    screenClean(xpos,ypos,iwidth,iheight);
    Heltec.display->drawXbm(xpos, ypos, iwidth, iheight, wifi05);
    Heltec.display->display();
    delay(refreshtime);
    screenClean(xpos,ypos,iwidth,iheight);
    Heltec.display->drawXbm(xpos, ypos, iwidth, iheight, wifi06);
    Heltec.display->display();
    delay(refreshtime);
    screenClean(xpos,ypos,iwidth,iheight);
    Heltec.display->drawXbm(xpos, ypos, iwidth, iheight, wifi07);
    Heltec.display->display();
    delay(refreshtime);
    screenClean(xpos,ypos,iwidth,iheight);
    Heltec.display->drawXbm(xpos, ypos, iwidth, iheight, wifi07);
    Heltec.display->display();
    delay(refreshtime);
    screenClean(xpos,ypos,iwidth,iheight);
    Heltec.display->drawXbm(xpos, ypos, iwidth, iheight, wifi08); 
    Heltec.display->display();
    delay(refreshtime);
    screenClean(xpos,ypos,iwidth,iheight);
    Heltec.display->drawXbm(xpos, ypos, iwidth, iheight, wifi09); 
    Heltec.display->display();
    delay(refreshtime);
    screenClean(xpos,ypos,iwidth,iheight);
    Heltec.display->drawXbm(xpos, ypos, iwidth, iheight, wifi10);
    Heltec.display->display();
    delay(refreshtime);
    screenClean(xpos,ypos,iwidth,iheight);
    Heltec.display->drawXbm(xpos, ypos, iwidth, iheight, wifi11);
    Heltec.display->display();
    delay(refreshtime);
    screenClean(xpos,ypos,iwidth,iheight);
    Heltec.display->drawXbm(xpos, ypos, iwidth, iheight, wifi12);
    Heltec.display->display();
    delay(refreshtime);
    screenClean(xpos,ypos,iwidth,iheight);
    Heltec.display->drawXbm(xpos, ypos, iwidth, iheight, wifi13);
    Heltec.display->display();
    delay(refreshtime);
    screenClean(xpos,ypos,iwidth,iheight);
    Heltec.display->drawXbm(xpos, ypos, iwidth, iheight, wifi14);
    Heltec.display->display();
    delay(refreshtime);
    screenClean(xpos,ypos,iwidth,iheight);
    Heltec.display->drawXbm(xpos, ypos, iwidth, iheight, wifi15);
    Heltec.display->display();
    delay(refreshtime);
    screenClean(xpos,ypos,iwidth,iheight);
    Heltec.display->drawXbm(xpos, ypos, iwidth, iheight, wifi16);
    Heltec.display->display();
    delay(refreshtime);
    screenClean(xpos,ypos,iwidth,iheight);
    Heltec.display->drawXbm(xpos, ypos, iwidth, iheight, wifi17);  
    Heltec.display->display();
    delay(refreshtime);
    screenClean(xpos,ypos,iwidth,iheight);
    Heltec.display->drawXbm(xpos, ypos, iwidth, iheight, wifi18);
    Heltec.display->display();
    delay(refreshtime);
    screenClean(xpos,ypos,iwidth,iheight);
    Heltec.display->drawXbm(xpos, ypos, iwidth, iheight, wifi19);  
    Heltec.display->display();
    delay(refreshtime);
    screenClean(xpos,ypos,iwidth,iheight);
    Heltec.display->drawXbm(xpos, ypos, iwidth, iheight, wifi20);    
    Heltec.display->display();
    delay(refreshtime);
    screenClean(xpos,ypos,iwidth,iheight);
    Heltec.display->drawXbm(xpos, ypos, iwidth, iheight, wifi21);
    Heltec.display->display();
    delay(refreshtime);
    screenClean(xpos,ypos,iwidth,iheight);
    Heltec.display->drawXbm(xpos, ypos, iwidth, iheight, wifi22);  
    Heltec.display->display();
    delay(refreshtime);
    screenClean(xpos,ypos,iwidth,iheight);
    Heltec.display->drawXbm(xpos, ypos, iwidth, iheight, wifi23); 
    Heltec.display->display();
    delay(refreshtime);
    screenClean(xpos,ypos,iwidth,iheight);
    Heltec.display->drawXbm(xpos, ypos, iwidth, iheight, wifi24);
    Heltec.display->display();
    delay(refreshtime);    
    screenClean(xpos,ypos,iwidth,iheight);
    Heltec.display->drawXbm(xpos, ypos, iwidth, iheight, wifi25);
    Heltec.display->display();
    delay(refreshtime);
    screenClean(xpos,ypos,iwidth,iheight);
    Heltec.display->drawXbm(xpos, ypos, iwidth, iheight, wifi26);
    Heltec.display->display();
    delay(refreshtime);
    screenClean(xpos,ypos,iwidth,iheight);
    Heltec.display->drawXbm(xpos, ypos, iwidth, iheight, wifi27);
    Heltec.display->display();
    delay(refreshtime);
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
