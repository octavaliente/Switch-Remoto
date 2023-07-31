#include <ESP8266WiFi.h>
#include <Espalexa.h>
Espalexa espAlexa;
////////////////////////////
#define rele 0

const char* ssid = "";
const char* password = "";

void setup() {
  Serial.begin(115200);
  pinMode(rele,OUTPUT); 
  digitalWrite(rele,HIGH); //inicia apagado
  ConectarWifi(); 
  espAlexa.addDevice("RELE", foco);
  espAlexa.begin();
}
///////////////////// VOID LOOP ////////////////////////////////////////////////////
void loop(){
  ConectarWifi();
  espAlexa.loop();
  delay(1);}
   
/////////////////// FUNCION PARA CONECTAR EL WIFI ///////////////////////////////////
void ConectarWifi() {
  if(WiFi.status() != WL_CONNECTED) {
     WiFi.mode(WIFI_STA);
     WiFi.begin(ssid, password);
     Serial.println("");
     Serial.println("Connecting to WiFi");
     while(WiFi.status() != WL_CONNECTED) {
           delay(500);
           Serial.print(".");}
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());}}
/////////////////// FUNCION PARA  LED /////////////////////////////
void foco(uint8_t brillo){
     if(brillo){
      digitalWrite(rele, LOW);}
     else{
      digitalWrite(rele, HIGH);}}   
