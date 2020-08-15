// This function will be called when the button1 was pressed 1 time (and no 2. button press followed).

void click1() {
  Serial.println("Button 1 click.");
  //web_button();
//if (flag_client_connect=0)
//flag_client_connect=day_or_off();
/////////////////day_or_off();
////runAsyncClient(H0,power_and_active_mode, 3);
runAsyncClient(H0,set_toggle, 0);




//runClient(H0,set_toggle, 0);




/*input_lamp(_lastServerResponse);
        _lastServerResponse=""; 
        if (dataPartt[3] == "off")
  {
    runAsyncClient(H0,set_power_off, 1);
   
    
  }
   if (dataPartt[3] == "on")
  {
    
 runAsyncClient(H0,set_power_on, 1);
  }
*/


} 


// This function will be called when the button1 was pressed 2 times in a short timeframe.
void doubleclick1() {
  Serial.println("Button 1 doubleclick.");
runAsyncClient(H1,set_toggle, 0);






  
  /*  Serial.println("runClient");
        getclient.connect(H0, 55443);
      //getclient.setTimeout(2); 
      Serial.println("1");

      getclient.print(set_bg_start_cf);  Serial.println("2");
      getclient.read();
      getclient.print(set_scene_moon100);
      getclient.stop();
      getclient.flush();
  */
} // doubleclick1


// This function will be called once, when the button1 is pressed for a long time.
void longPressStart1() {
  Serial.println("Button 1 longPress start");
  //runClient(H1, set_toggle, 0);
} // longPressStart1


// This function will be called often, while the button1 is pressed for a long time.
void longPress1() {
  //Serial.println("Button 1 longPress...");
  l++; Serial.println(l);
 //runAsyncClient(H0, set_bg_start_cf, 0);
  if (l==100)runAsyncClient(H0,set_bg_start_cf, 0);
    if (l==3000)runAsyncClient(H0,set_scene_moon100, 0);
    if (l==7000)runAsyncClient(H0,set_scene6500_1, 0);
    if (l==9000)runAsyncClient(H0,set_scene6500_100, 0);
} // longPress1


// This function will be called once, when the button1 is released after beeing pressed for a long time.
void longPressStop1() {
  Serial.println("Button 1 longPress stop");
    //runAsyncClient(H1,set_toggle, 0);
    l =0;
} // longPressStop1



#ifdef ESP32
void Task2code( void * pvParameters ) {
  Serial.print("Task2 running on core ");
  Serial.println(xPortGetCoreID());

  for (;;) {
    button1.tick();
//Bluetooth_scan();
    //button1.tick();
  }
}
#endif
void day_or_off()
{ 
///AsyncClient day_or_off;//day_or_off
///if (day_or_off.connect(H0, 55443)==true )
{

 
//runClient(H0, power_and_active_mode, 1);
//runClient(H0, set_bg_start_cf, 0);
    Serial.println("runClient");
        getclient.connect(H0, 55443);
      //getclient.setTimeout(2); 
      Serial.println("1");

      getclient.print(power_and_active_mode);  Serial.println("2");
      input_lamp(getclient.readStringUntil('\r\n'));Serial.println("3");
      //getclient.print(set_scene_moon100);


//while(flag_client_connect=1)
  Serial.println("УСЛОВИЕ ");
 if (dataPartt[3] == "off")
  {
    //runClient(H0, set_power_off);
    getclient.print(set_scene6500_100);
    //runClient(H0, set_scene6500_100, 0);
    
  }
  if (dataPartt[3] == "on")
  {
    getclient.print(set_power_off);
    //runClient(H0, set_power_off, 0);
  }
        getclient.stop();
      getclient.flush();
client.stop();
clear_dataPartt();///по идее можно поместить в loop
 /// day_or_off.stop();
      ///day_or_off = NULL;
       
}

}

void toggle()
{ 
AsyncClient toggle;//off_or_all_off
if (toggle.connect(H0, 55443)==true ){
 runClient(H0, power_and_active_mode, 1);
  


 if (dataPartt[3] == "off")
  {
    
    runClient(H2, set_power_off, 0);
    
  }
   if (dataPartt[3] == "on")
  {
    
    runClient(H0, set_power_off, 0);
    runClient(H2, set_power_off, 0);
  }
  
client.stop();
clear_dataPartt();///по идее можно поместить в loop
  toggle.stop();
      toggle = NULL;
       
}

}
