#include <ArduinoJson.h>
#include "FS.h"
#include <LittleFS.h>

bool saveConfig() {
  StaticJsonDocument<200> doc;
  doc["ssid"] = "Fibertel WiFi681 2.4GHz";
  doc["Password"] = "00522344416";

  File configFile = LittleFS.open("/config.json", "w");
  if (!configFile) {
    Serial.println("Failed to open config file for writing");
    return false;
  }

  serializeJson(doc, configFile);
  return true;
}
