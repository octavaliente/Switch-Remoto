#include <FS.h>
#include <ESP8266WiFi.h>  //Incluimos librerías
#include <DNSServer.h>
#include <ESPAsyncWiFiManager.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

//Configurar una dirección IP Estática
//IPAddress ip(192,168,0,10);     
//IPAddress gateway(192,168,0,1);   
//IPAddress subnet(255,255,255,0);

const int Rele_Pin = 0; //Pin donde estará la señal al rele
const int Led_Pin = 2;

String Estado_Rele; //Variable String para mandar el estado del rele a nuestra página web

AsyncWebServer server(80); //Puerto TCP
DNSServer dns;

String processor(const String& var) //Función Processor para regresar valores a página Web
{
  if(var == "ESTADO_RELE")
    {
     if(digitalRead(Rele_Pin)==1)
     {
      Estado_Rele= "Encendido";
     }
     else
     {
      Estado_Rele = "Apagado";
     }
    
    } 
    return Estado_Rele;
}

void setup(){
  // Iniciamos comunicación Serial y ponemos el pin del rele como salida
  Serial.begin(115200);
  pinMode(Rele_Pin, OUTPUT);
  pinMode(Led_Pin, OUTPUT);
  digitalWrite(Led_Pin, HIGH);
  AsyncWiFiManager wifiManager(&server, &dns);
  
  wifiManager.setSTAStaticIPConfig(IPAddress(192,168,0,10), IPAddress(192,168,0,1), IPAddress(255,255,255,0));
  wifiManager.autoConnect("ESP8266Temp", "bocaboca");
  
  //Iniciamos el sistema Flash
  if(!SPIFFS.begin()){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }
  
  WiFi.mode(WIFI_STA);
  // Conectamos a WiFi Modo estación con dirección IP estática
  /*WiFi.mode(WIFI_STA);
  WiFi.config(ip, gateway, subnet);
  WiFi.begin(ssid, password);

  //Mientras se conecta a la red que se imprima conectando a WiFi
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a WiFi..");
  }
  //Imprimimos IP en el monitor serial
  Serial.println(WiFi.localIP());
  */
  //A partir de aqui vamos a resolver las solicitudes del cliente

  // Cuando ingresen a nuestra página
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  
  // Cuando nuestro archivo Html solicite el archivo Css
  server.on("/estilos.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/estilos.css", "text/css");
  });
  
  // Cuando pulsemos el botón de encendido
  server.on("/RELE=ON", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(Rele_Pin, HIGH);    
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  
  // Cuando pulsemos el botón de apagado
  server.on("/RELE=OFF", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(Rele_Pin, LOW);    
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  
  //Iniciamos servidor
  digitalWrite(Led_Pin, LOW);
  server.begin();
}
void loop() {
//No se usará debido a la librería del servidor web asíncrono
}
