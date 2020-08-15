static AsyncClient * aClient = NULL;

void runAsyncClient(const char* server, const char* command, int async_on) {
  cmd = command;
  s = server;
  async= async_on;
  
  if (aClient) //client already exists
    return;

  aClient = new AsyncClient();
  if (!aClient) //could not allocate client
    return;

  aClient->onError([](void * arg, AsyncClient * client, int error) {
    Serial.println("Connect error");
    aClient = NULL;
    delete client;
  }, NULL);

  aClient->onConnect([](void * arg, AsyncClient * client) {
    Serial.println("Connected");
    aClient->onError(NULL, NULL);


    client->onDisconnect([](void * arg, AsyncClient * c) {
      Serial.println("Disconnected");
      aClient = NULL;
      delete c;
    }, NULL);

 /*   client->onData([](void * arg, AsyncClient * c, void * data, size_t len) {
 //ОБРАБОТКА ОТВЕТА
      char aux_response[len];
      uint8_t *d = (uint8_t *)data;

      for (size_t i = 0; i < len; i++) {
        aux_response[i] = d[i];
      }
      _lastServerResponse += String(aux_response);

      Serial.print(_lastServerResponse);
      //_lastServerResponse="";


      input_lamp(_lastServerResponse);
      _lastServerResponse = "";

Serial.print(async);
      if (async == 3) {
        if (dataPartt[3] == "off")
        {
          c->write(set_bg_start_cf);
          c->write(set_scene6500_100);

        }
        if (dataPartt[3] == "on")
        {

          c->write(set_power_off);
        }
      }
      
      if (async == 4) {
        if (dataPartt[4] == "0")
        {
          c->write(set_bg_start_cf);
          c->write(set_scene_moon100);

        }
        if (dataPartt[4] == "1")
        {

          c->write(set_scene6500_1);
        }
      }

     // c->stop();// ЧТОБЫ СРАЗУ ДИСКОНЕКНУТЬСЯ 



    }, NULL);*/

    //send the request

    //    if (async == true)
    {
      Serial.println("runAsyncClient");
      client->write(cmd);
client->stop();
client = NULL;delete client;
    }
    
  }, NULL);

  if (!aClient->connect(server, 55443)) {
    Serial.println("Connect Fail");
    AsyncClient * client = aClient;
    aClient = NULL;
    delete client;
  }

}
void runClient(const char* server, const char* command, int dual)
{ // getclient.stop(); //очистка  избежания краша скеча
  // getclient.flush();
  Serial.println("runClient");
  getclient.connect(server, 55443);
  //getclient.setTimeout(2);
  Serial.println("1");

  getclient.print(command);  Serial.println("2");
  if (dual == 1) input_lamp(getclient.readStringUntil('\r\n')); Serial.println("3");
  getclient.stop();
  getclient.flush();

}
