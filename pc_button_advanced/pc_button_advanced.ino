
#ifdef ESP32
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESP32Ping.h>
#include <Arduino.h>
#include <sstream>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
TaskHandle_t Task1;
TaskHandle_t Task2;
int key = 0;
String Bluetooth_device_mac;
int Bluetooth_device_rssi;
#define LED_ONBOARD   22
#define SCAN_TIME       1  // seconds
#define INTERVAL_TIME   200   // (mSecs)
#define WINDOW_TIME     100   // less or equal setInterval value
BLEScan* pBLEScan;
String deviceName;
String deviceAddress;
int16_t deviceRSSI;
uint16_t countDevice;
boolean check;
int count_stable = 0;

#else
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#endif


#include <ESPAsyncWebServer.h>
#include "OneButton.h" // Setup a new OneButton on pin A1.
OneButton button1(0, true); // 0 тут номер пина esp, для моих плат это кнопка Flash


WiFiClient client;
WiFiClient getclient;
WiFiClient clientt;
WiFiClient clienttt;

// Replace with your network credentials
const char* ssid = ""; //Enter SSID
const char* password = ""; //Enter Password



int l = 0;
String _lastServerResponse = "";
const char* cron_get = "{\"id\":1,\"method\":\"cron_get\",\"params\":[0]}\r\n";//cron_get
const char* power_and_active_mode = "{\"id\":1,\"method\":\"get_prop\",\"params\":[\"power\", \"active_mode\"]}\r\n"; //лампа включена? лампа в р'ежиме луны?
const char* ct_and_power_and_active_mode = "{\"id\":1,\"method\":\"get_prop\",\"params\":[\"power\", \"active_mode\",\"ct\"]}\r\n"; //цветовая температура//Color temperature. Range 1700 ~ 6500(k)
const char* power_bright = "{\"id\":1,\"method\":\"get_prop\",\"params\":[\"power\", \"bright\"]}\r\n";


const char*   set_toggle = "{\"id\":1,\"method\":\"toggle\",\"params\":[]}\r\n"; // Function for toggle the lightactive_mode
const char*   set_power_on = "{\"id\": 1,\"method\":\"set_power\",\"params\":[\"on\",\"smooth\",1500]}\r\n";    //включение
const char*   set_power_off = "{\"id\": 1,\"method\":\"set_power\",\"params\":[\"off\",\"smooth\",1500]}\r\n";
const char*   set_bright100 = "{\"id\":1,\"method\":\"set_bright\",\"params\":[100, \"smooth\", 500]}\r\n";
const char*   set_scene6500_100 = "{\"id\": 1, \"method\": \"set_scene\", \"params\": [\"ct\", 6500, 100]}\r\n";
const char*  set_scene6500_1 = "{\"id\": 1, \"method\": \"set_scene\", \"params\": [\"ct\", 6500, 1]}\r\n";
const char*   set_scene_moon1 = "{\"id\":1,\"method\":\"set_scene\", \"params\": [\"nightlight\", 1]}\r\n";  //луна
const char*   set_scene_moon100 = "{\"id\":1,\"method\":\"set_scene\", \"params\": [\"nightlight\", 100]}\r\n";
const char*  set_bg_start_cf = "{\"id\":1,\"method\":\"bg_start_cf\",\"params\":[0,0,\"10000,1,255,100,10000,1,65280,100,10000,1,16711680,100\"]}\r\n";


const char*   set_bright100_smooth = "{\"id\":1,\"method\":\"set_bright\",\"params\":[1, \"smooth\", 2000]}\r\n";
const char*   set_bright0_smooth = "{\"id\":1,\"method\":\"set_bright\",\"params\":[0, \"smooth\", 2000]}\r\n";

String dataPartt[20]; //для input_lamp
bool result = false; // для проверки выполнения команды лампой
const char*  cmd;
const char* s;
int  async;
bool flag_client_connect = false;



String bg_power = "{\"id\":1,\"Method\":\"props\",\"Params\":[\"bg_power\":\"on\"]}\r\n";


String textt = "{\"id\":1,\"method\":\"get_prop\",\"params\":[\"power\", \"not_exist\", \"bright\"]}\r\n";
String texttt = "{\"id\":1,\"method\":\"get_prop\",\"params\":[\"power\", \"name\"]}\r\n";
unsigned long timing;
unsigned long timingg;

unsigned long timing_ble_scaner;
int flag_key_verifed = 0;

int  t = 0;

const char* H0 = "192.168.0.85"; // YLXD50YL
const char* H1 = "192.168.0.128"; //e27
const char* H2 = "192.168.0.226"; //bslamp
int port = 55443; // Lights port
String HTMLpage = "";
int LED = 0;
int i = 0;

const int output = 2;

// HTML web page
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
  <head>
    <title>ESP Pushbutton Web Server</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <style>
      body { font-family: Arial; text-align: center; margin:0px auto; padding-top: 30px;}
      .button {
        padding: 10px 20px;
        font-size: 24px;
        text-align: center;
        outline: none;
        color: #fff;
        background-color: #2f4468;
        border: none;
        border-radius: 5px;
        box-shadow: 0 6px #999;
        cursor: pointer;
        -webkit-touch-callout: none;
        -webkit-user-select: none;
        -khtml-user-select: none;
        -moz-user-select: none;
        -ms-user-select: none;
        user-select: none;
        -webkit-tap-highlight-color: rgba(0,0,0,0);
      }  
      .button:hover {background-color: #1f2e45}
      .button:active {
        background-color: #1f2e45;
        box-shadow: 0 4px #666;
        transform: translateY(2px);
      }
    </style>
  </head>
  <body>
    <h1>ESP Pushbutton Web Server</h1>
    <button class="button" onmousedown="toggleCheckbox('on');" ontouchstart="toggleCheckbox('on');" onmouseup="toggleCheckbox('off');" ontouchend="toggleCheckbox('off');">LED PUSHBUTTON</button>
   <a href="lamp_max"><button>lamp_max</button></a>
   <a href="off"><button>off</button></a>
   <a href="on"><button>on</button></a>
   <script>
   
   function toggleCheckbox(x) {
     var xhr = new XMLHttpRequest();
     xhr.open("GET", "/" + x, true);
     xhr.send();
   }
  </script>
  </body>
</html>)rawliteral";

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

AsyncWebServer server(80);

#ifdef ESP32
class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
    void onResult(BLEAdvertisedDevice advertisedDevice) {
      /* unComment when you want to see devices found */
      Serial.printf("Found device: %s \n", advertisedDevice.toString().c_str());
    }
};
#endif

void setup() {
  Serial.begin(115200);
  //create a task that will be executed in the Task2code() function, with priority 1 and executed on core 1

  //  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("WiFi Failed! RECONNECT!!");
    WiFi.begin(ssid, password);

    return;
  }
  Serial.println();
  Serial.print("ESP IP Address: http://");
  Serial.println(WiFi.localIP());

#ifdef ESP32
  BLEDevice::init("");
  pBLEScan = BLEDevice::getScan();
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true); //active scan uses more power, but get results faster
  pBLEScan->setInterval(INTERVAL_TIME); // Set the interval to scan (mSecs)
  pBLEScan->setWindow(WINDOW_TIME);  // less or equal setInterval value

  pinMode(output, OUTPUT);
  digitalWrite(output, LOW);
  xTaskCreatePinnedToCore(
    Task2code,   /* Task function. */
    "Task2",     /* name of task. */
    10000,       /* Stack size of task */
    NULL,        /* parameter of the task */
    1,           /* priority of the task */
    &Task2,      /* Task handle to keep track of created task */
    1);          /* pin task to core 1 */
  delay(500);
#else


#endif


  button1.attachClick(click1);
  button1.attachDoubleClick(doubleclick1);
  button1.attachLongPressStart(longPressStart1);
  button1.attachLongPressStop(longPressStop1);
  button1.attachDuringLongPress(longPress1);



  // Send web page to client
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/html", index_html);
  });

  // Receive an HTTP GET request
  server.on("/on", HTTP_GET, [] (AsyncWebServerRequest * request) {
    digitalWrite(output, HIGH);
    request->send_P(200, "text/html", index_html);
    Serial.printf("test");
  });

  // Receive an HTTP GET request
  server.on("/off", HTTP_GET, [] (AsyncWebServerRequest * request) {
    digitalWrite(output, LOW);
    request->send_P(200, "text/html", index_html);
    Serial.printf("off");
  });

  // Receive an HTTP GET request
  server.on("/lamp_max", HTTP_GET, [] (AsyncWebServerRequest * request) {
    digitalWrite(output, HIGH);
    request->send_P(200, "text/html", index_html);
    Serial.println("web lamp_max");
    web_button();
  });
  server.onNotFound(notFound);
  server.begin();
}

void loop() {
#ifdef ESP32
#else
  button1.tick();

#endif
  //set_bright100_smooth runAsyncClient(H1, set_scene_moon100, 1);


  if (millis() - timingg > 5000) { //
    timingg = millis();
    //Serial.println ("5 seconds");
    t = 0 ;

  }
  //ble_scaner();
  // auto_moon();
  //OnDemandConfig();SendInfo();
  //Bluetooth_scan();



}

void auto_moon() {
  if (millis() - timing > 5000) { // Вместо 10000 подставьте нужное вам значение паузы

    client.connect(H0, port);
    client.print(ct_and_power_and_active_mode); //лампа включена и включен режим дневного освещения
    //String  ct  = client.readStringUntil('{\"id\":1,\"result\":[\"\"]}');
    input_lamp(client.readStringUntil('{\"id\":1,\"result\":[\"\"]}'));   //client.readStringUntil('{\"id\":1,\"result\":[\"\"]}')
    client.stop();

    //Serial.println(ct);
    //Serial.println(ct.length());

    //Serial.println(ct.substring(19, 23));



    if (dataPartt[5].toInt() <= 2800 and dataPartt[3] == "on" and dataPartt[4] == "0") //лампа включена и включен режим дневного освещения и температура меньше 3000к
    {
      Serial.println("t< 2800, вкл луну");

      runAsyncClient(H0, set_scene_moon100, 1);




    }
    /*      if (ct.substring(19, 23).toInt() < 2800)
          {
            client.connect(H0, port);
            client.print(moon);
            ct  = client.readStringUntil(' ');
            Serial.write(ct);
            client.stop();
          }*/
    timing = millis();


  }



}
void writeInfo() {
  // Use WiFiClient class to create TCP connections
  //digitalWrite(led, LOW);
  // Serial.println("1");
  WiFiClient client;
  client.connect(H0, port);
  client.print(power_and_active_mode);
  { //Serial.println("2");
    String  RX  = client.readStringUntil('{/"id/":1,/"result/":[/"off/",/"/"]}');
    client.stop();
    Serial.println(RX);
    Serial.println(RX.length());
    //if (RX.length() == 27)
    {



      client.connect(H0, port);
      client.print(set_scene_moon100);
      //input_lamp(); //client.readStringUntil('{\"id\":1,\"result\":[\"\"]}')
      client.stop();
      WiFiClient clientt;
      clientt.connect(H1, port);
      clientt.print(set_toggle);
      //input_lamp(); //client.readStringUntil('{\"id\":1,\"result\":[\"\"]}')
      clientt.stop();




    }
    //else
    {
      /*Serial.println("было ВЫКЛЮЧЕНО, ВКЛЮЧАЮ");
        client.connect(H0, port);
        client.print(moon100);
        client.stop();*/
    }


    //char RX = client.read();
    ///if (RX==a)

    // Serial.println(RX.indexOf('/"off/"'));// Шлём в UART
    //Serial.println(strncmp(RX, "off", 3))
    {
      //if (strtok(RX, " ") && new_bulb)
      {
        //if (strcmp(strtok(nullptr, " "), "off"));
        // Serial.printf("Bulb power: %s\n", new_bulb->GetPower() ? "on" : "off");
      }
    }

  }
  client.stop();

}
