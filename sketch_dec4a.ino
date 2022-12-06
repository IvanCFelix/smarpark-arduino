#include <Arduino.h>
#if defined(ESP32)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif
#include <Firebase_ESP_Client.h>
//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"


#define WIFI_SSID "f(x)=(3x*^2 + 2y)"
#define WIFI_PASSWORD "?*maincra123*?"
#define API_KEY "AIzaSyCX1AYANAMaXVUxpjCaYLcTS4lHC_x1LMs"

// Insert RTDB URLefine the RTDB URL */
#define DATABASE_URL "https://smartpark-286d6-default-rtdb.firebaseio.com"

FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
int count = 0;
bool signupOK = false;


#define PIN_TRIG D7
#define PIN_ECHO D8

float tiempo;
float distancia;

#define TRIG_LOTE_DOS D5
#define ECHO_LOTE_DOS D6

float tiempo2;
float distancia_lote2;
void setup() {
  Serial.begin(9600);

  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  pinMode(TRIG_LOTE_DOS, OUTPUT);
  pinMode(ECHO_LOTE_DOS, INPUT);


  connectWifi();
 
}

void loop() {
  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0)) {
    sendDataPrevMillis = millis();
    // Write an Int number on the database path test/int
    if (Firebase.RTDB.setInt(&fbdo, "test/int", count)) {
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    } else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
  }
  digitalWrite(PIN_TRIG, HIGH);  //generamos Trigger (disparo) de 10us
  delayMicroseconds(4);
  digitalWrite(PIN_TRIG, LOW);  //para generar un pulso limpio ponemos a LOW 4us

  tiempo = pulseIn(PIN_ECHO, HIGH);
  distancia = tiempo / 58.3;

  if (distancia <= 15) {
    String outstring = "SI hay un vehiculo en lote 1: " + String(distancia);
    Serial.println(outstring);
  }


  delay(200);

  digitalWrite(TRIG_LOTE_DOS, HIGH);  //generamos Trigger (disparo) de 10us
  delayMicroseconds(4);
  digitalWrite(TRIG_LOTE_DOS, LOW);  //para generar un pulso limpio ponemos a LOW 4us

  tiempo2 = pulseIn(ECHO_LOTE_DOS, HIGH);
  distancia_lote2 = tiempo2 / 58.3;

  if (distancia_lote2 <= 15) {
    String outstring = "SI hay un vehiculo en lote 2: " + String(distancia_lote2);
    Serial.println(outstring);
  }

  delay(100);
}

void connectWifi() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  connectToFirebase();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
}


 void connectToFirebase(){
 config.api_key = API_KEY;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Sign up */
  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("ok");
    signupOK = true;
  } else {
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }
  config.token_status_callback = tokenStatusCallback;  //see addons/TokenHelper.h

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
 }