


void web_button() {
  if (t >= 3) {
    t = 2; ///////////////////
  }
  if (t <= 1) {
    timingg = millis();
  }
  if (t <= 1) {
    t++;
  }

  if (t == 1) {

    


    runAsyncClient(H1, set_scene6500_1,1);




    //input_lamp(clientt.readStringUntil('{\"id\":1,\"result\":[\"\"]}')); //client.readStringUntil('{\"id\":1,\"result\":[\"\"]}')dataa = clientt.readStringUntil('\r');
 
  }
  if (t == 2) {

  }
  Serial.println (t);
}

void lamp_max() {
  /*client.connect(H1, port);
    client.print(power_and_active_mode);
    input_lamp();
    client.stop();*/




  runAsyncClient(H1,set_scene6500_100,1);
  ///  input_lamp(clientt.readStringUntil('{\"id\":1,\"result\":[\"\"]}')); //client.readStringUntil('{\"id\":1,\"result\":[\"\"]}')


  WiFiClient client;
  client.connect(H1, port);
  client.print(power_bright);
  input_lamp(client.readStringUntil('{\"id\":1,\"result\":[\"\"]}'));   //client.readStringUntil('{\"id\":1,\"result\":[\"\"]}')
  client.stop();
  Serial.println("УСЛОВИЕ ");
  if (dataPartt[3] == "on" and dataPartt[4].toInt() == 100)
  {
    Serial.println("проверяю и ");
    //включает nочную лампу
    //  client.connect(H0, port);
    //  client.print(set_scene6500_100);
    //  input_lamp(client.readStringUntil('{\"id\":1,\"result\":[\"\"]}'));
    //  client.stop();

  }


}
