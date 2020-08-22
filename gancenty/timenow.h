void TimeDis(){
  delay(500);
  screenCleanA();
  if (timeStatus() != timeNotSet) {
  if (now() != prevDisplay) { //update the display only if time has changed
    prevDisplay = now();
    drawRectdotO(0,0,128,32,3);
    Heltec.display->setTextAlignment(TEXT_ALIGN_CENTER_BOTH);
    Heltec.display->setFont(ArialMT_Plain_24);
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
    Heltec.display->drawString(screencenterX,screencenterY,timenow);
    Heltec.display->display();    
      }
    }
}
