
#ifdef ESP32



void ble_scaner() {
 /* const IPAddress remote_ip(192, 168, 0, 23);
  const IPAddress esp_ip(192, 168, 0, 97);
  if (millis() - timing_ble_scaner > 5000) { // Вместо 10000 подставьте нужное вам значение паузы
    if (WiFi.localIP() != esp_ip)
    {
      Serial.print("WiFi connected ERROOOOOOOR ");
      Serial.println(WiFi.localIP());
    }

    Serial.print("Pinging ip ");
    Serial.println(remote_ip);

    if (Ping.ping(remote_ip))
    {
      Serial.println("Success!! ");
      //flag_key_verifed=0;

      BLEDevice::init("");
      pBLEScan = BLEDevice::getScan(); //create new scan
      pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
      pBLEScan->setActiveScan(true); //active scan uses more power, but get results faster
      pBLEScan->setInterval(100);
      pBLEScan->setWindow(99);  // less or equal setInterval value

      // put your main code here, to run repeatedly:
      BLEScanResults foundDevices = pBLEScan->start(scanTime, false);
      Serial.print("Devices found: ");
      Serial.println(foundDevices.getCount());
      Serial.println("Scan done!");
      pBLEScan->clearResults();


    }



    else
    {
      Serial.println("ERROR :( ");
      flag_key_verifed++;
    }


    Serial.println(flag_key_verifed);
    timing_ble_scaner = millis();
  }

*/

}


 void Bluetooth_scan() {
  BLEScanResults foundDevices = pBLEScan->start(SCAN_TIME);

  int count = foundDevices.getCount();
  for (int i = 0; i < count; i++)
  {
    BLEAdvertisedDevice d = foundDevices.getDevice(i);
deviceAddress = d.getAddress().toString().c_str();
    if (deviceAddress == "D2:C8:5B:F9:92:13") {
      check = true;
      count_stable =0;
       
      char deviceBuffer[100]; //это для чего
      deviceName = d.getName().c_str();
      deviceAddress = d.getAddress().toString().c_str();
      deviceRSSI = d.getRSSI();

      sprintf(deviceBuffer, "Name: %s| Address: %s| RSSI: %d\n", deviceName.c_str(), deviceAddress.c_str(), deviceRSSI);
      Serial.print(deviceBuffer);

      if (deviceAddress == "D2:C8:5B:F9:92:13" && deviceRSSI > -80)
      {
        digitalWrite(LED_ONBOARD, HIGH); // Turn on LED
      }
      else
      {
        digitalWrite(LED_ONBOARD, LOW); // Turn off LED
        Serial.println("OFF");
      }
      //---------------------------------------------------------Check if not found Mi Band-------------------------------------
    }else if(i == count-1 && check == false){
      count_stable +=1;
      if(count_stable ==20){ // set limit to reset counter
        count_stable =0;
      }
      Serial.println(count_stable);
      if(count_stable == 4){ //set quantity of scan cycle for accept missing Mi Band
      digitalWrite(LED_ONBOARD, LOW); 
        Serial.println("Not Found");
      }
    }
      check = false;
      //---------------------------------------------------------------------------------------------------------------------------
  }
  pBLEScan->clearResults();
}



#endif
