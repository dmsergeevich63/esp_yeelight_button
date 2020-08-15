//String ipAdress = "192.168.10.145 ";
//String text = "{\"id\":1,\"result\":[\"2800\"]}";
//String ipAdress = "{\"id\":1,\"result\":[\"off\",\"0\"]}";



void clear_dataPartt(){
    for (int i = 0; i < 20; i++) {
    dataPartt[i] = "";
  }
 
  }

//String dataPartt[20];
void input_lamp(String data)
{
  //result=false;

 clear_dataPartt();

  data.replace(":", "");
  data.replace("[", "");
  data.replace("]", "");
  data.replace("{", "");
  data.replace("}", "");
  char separator = '"';


  // spliting a string and return the part nr index
  // split by separator

  int stringData = 0;        //variable to count data part nr
  //String dataPart = "";
  int index = 0;

  for (int i = 0; i < data.length() - 1; i++) { //Walk through the text one letter at a time

    if (data[i] == separator) {
      //Count the number of times separator character appears in the text
      //Serial.print(dataPartt[stringData]);
      if (dataPartt[stringData] == "," || dataPartt[stringData] == "")
      {
        dataPartt[stringData] = "";
      }
      else
      {
        stringData++;
        index++;
      }

    } else if (stringData == index) {
      //get the text when separator is the rignt one
      dataPartt[stringData].concat(data[i]);


    } else if (stringData > index) { } //return text and stop if the next separator appears - to save CPU-time

  }
  for (int i = 0; i < 20; i++) {
    Serial.print(i); Serial.print("-");
    Serial.print(dataPartt[i]); Serial.print(" ");
  }
    Serial.println();
//if(dataPartt[i]=="Metod"){result=true;Serial.println("result: "+result);}//bool result=false;  и обнулять в начале ф

/*  for (int i = 0; i < 20; i++) {
    if (dataPartt[i] == "power") {
      if (dataPartt[i + 1] == "off") {
        pp_msg->power = 0;
      }
      if (dataPartt[i + 1] == "on") {
        pp_msg->power = 1;
      }
    }
    if (dataPartt[i] == "bright") {
      pp_msg->power = dataPartt[i + 1].toInt();

    }
    if (dataPartt[i] == "ct") {
      pp_msg->power = dataPartt[i + 1].toInt();
    }
    if (dataPartt[i] == "active_mode") {
      Serial.println(dataPartt[i + 1]);
      //Serial.println((String)dataPartt[i + 1]);
      pp_msg->power = dataPartt[i + 1].toInt();
    }
    if (dataPartt[i] == "nl_br") {
      pp_msg->power = dataPartt[i + 1].toInt();
    }
  }* /
  Serial.println();
  /*
    pp_msg->power = (millis() / 1000) % 32768;
    pp_msg->bright = 'x';
    pp_msg->ct = millis() / 10000;

    pp_msg->active_mode = 'x';
    pp_msg->nl_br = millis() / 10000;

  */
  //return (String)index;
}
