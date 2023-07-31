

#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h >
#include <WiFiManager.h>
 
void setup()
{
  Serial.begin(115200);
  //Hacer parpadeo de led o que se prenda en algun color (Led RGB)
  // Creamos una instancia de la clase WiFiManager
  AsyncWiFiManager wifiManager(&server, &dns);
  //192.168.4.1 default ip 
  
  // Descomentar para resetear configuración
  //wifiManager.resetSettings();
 
  // Cremos AP y portal cautivo
  wifiManager.setSTAStaticIPConfig(IPAddress(192,168,0,10), IPAddress(192,168,0,1), IPAddress(255,255,255,0));
  wifiManager.autoConnect("ESP8266Temp", "bocaboca");
  Serial.println("Ya estás conectado");

  //Apagar led 

}
 
void loop() {}
