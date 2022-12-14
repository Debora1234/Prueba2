
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ESP_Google_Sheet_Client.h>
#define ON_Board_LED 2  //--> Defining an On Board LED, used for indicators when the process of connecting to a wifi router



//----------------------------------------Conexion wifi
#ifndef STASSID
#define STASSID "Fibertel WiFi886 2.4GHz"; //--> Your wifi name or SSID.
#define STAPSK  "00435054850"; //--> Your wifi password.
#endif

const char* ssid     = STASSID;
const char* password = STAPSK;
//----------------------------------------


//----------------------------------------Host & httpsPort
const char* host = "script.google.com";
const int httpsPort = 443;
WiFiClientSecure client; //--> Create a WiFiClientSecure object.
String GAS_ID = "1_Jcidfgr2d_xDrc-iJ2LMt2rxS1V6fnhoHehwEt4ZkY/edit#gid=0"; //--> spreadsheet script ID





#define PROJECT_ID "AKfycby7Wpg8BCgj7fGGFLWYzAocn5y9K_ELVYeLC4R26qIX1syp71hQLgUg2FJB3RpMFJs"  //gas_id

//Service Account's client email
#define CLIENT_EMAIL "arg.expendedora@gmail.com"

//Service Account's private key
const char PRIVATE_KEY[] PROGMEM = "-----BEGIN PRIVATE KEY-----Expendedora2022-----END PRIVATE KEY-----\n";

//----------------------------------------

bool gsheetSetupReady = false;

bool taskComplete = false;

void setupGsheet();

void tokenStatusCallback(TokenInfo info);





void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(500);


  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  /* Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default,
     would try to act as both a client and an access-point and could cause
     network-issues with your other WiFi-devices on your WiFi-network. */
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
    
  pinMode(ON_Board_LED,OUTPUT); //--> On Board LED port Direction output
  digitalWrite(ON_Board_LED, HIGH); //--> Turn off Led On Board

  //----------------------------------------Wait for connection
  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    //----------------------------------------Make the On Board Flashing LED on the process of connecting to the wifi router.
    digitalWrite(ON_Board_LED, LOW);
    delay(2500);
    digitalWrite(ON_Board_LED, HIGH);
    delay(2500);
    //----------------------------------------
  }
  //----------------------------------------
  digitalWrite(ON_Board_LED, HIGH); //--> Turn off the On Board LED when it is connected to the wifi router.
  Serial.println("");
  Serial.print("Successfully connected to : ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  //----------------------------------------
   // Use HTTPSRedirect class to create a new TLS connection
  

 

}

void loop() {
  //enviar informacióna las hojas de google
  float t, h;
  t=11.12;
  h=10.33;



    if (!gsheetSetupReady)
        setupGsheet();

    bool ready = GSheet.ready();

    if (ready && !taskComplete)
    {

        //Google sheet code here

        taskComplete = true;
    }
// #endif

  
   // sendData(t); //--> Calls the sendData Subroutine
  //----------------------------------------
 
}


//==============================================================================


void setupGsheet()
{
    //Set the callback for Google API access token generation status (for debug only)
    GSheet.setTokenCallback(tokenStatusCallback);

    //Begin the access token generation for Google API authentication
    GSheet.begin(CLIENT_EMAIL, PROJECT_ID, PRIVATE_KEY);

    gsheetSetupReady = true;
}

void tokenStatusCallback(TokenInfo info)
{
    if (info.status == esp_signer_token_status_error)
    {
        Serial.printf("Token info: type = %s, status = %s\n", GSheet.getTokenType(info).c_str(), GSheet.getTokenStatus(info).c_str());
        Serial.printf("Token error: %s\n", GSheet.getTokenError(info).c_str());
    }
    else
    {
        Serial.printf("Token info: type = %s, status = %s\n", GSheet.getTokenType(info).c_str(), GSheet.getTokenStatus(info).c_str());
    }
}
/*
void sendData(float tem) {
  Serial.println("==========");

  //----------------------------------------Connect to Google host
  if (!client.connect(host, httpsPort)) {
    Serial.println("connection failed");
    return;
  }
  //----------------------------------------
  String string_temperature =  String(tem);
  String url = "/macros/s/" + GAS_ID + "temperature" + string_temperature;
  Serial.print("requesting URL: ");
  Serial.println(url);
  
 client.print(String("GET ") + url + " HTTP/1.1\r\n" +
         "Host: " + host + "\r\n" +
         "User-Agent: BuildFailureDetectorESP8266\r\n" +
         "Connection: close\r\n\r\n");


while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("headers received");
      break;
    }
  }
  String line = client.readStringUntil('\n');
  if (line.startsWith("{\"state\":\"success\"")) {
    Serial.println("esp8266/Arduino CI successfull!");
  } else {
    Serial.println("esp8266/Arduino CI has failed");
  }
  Serial.print("reply was : ");
  Serial.println(line);
  Serial.println("closing connection");
  Serial.println("==========");
  Serial.println();
  //----------------------------------------
} 

  */
