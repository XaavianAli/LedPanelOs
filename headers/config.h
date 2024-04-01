/*
 * Misc Config Variables and functions
 */

#ifndef CONFIG_H
#define CONFIG_H

struct conf {
  bool wifi_en;
  char wifi_ssid[50];
  char wifi_pswd[50];
};

conf sysConf = {
  false,
  "",
  "", 
};

void loadConfig(){
  File file = SD.open("/wifi.json");
  JsonDocument doc;
  DeserializationError error = deserializeJson(doc, file);
  if (error) {
    Serial.println(F("Failed to read file, using default configuration"));
    Serial.println(error.code());
    return;
  }
  sysConf.wifi_en = doc["wifi_en"];
  strlcpy(sysConf.wifi_ssid, doc["wifi_ssid"], sizeof(sysConf.wifi_ssid));
  strlcpy(sysConf.wifi_pswd, doc["wifi_pswd"], sizeof(sysConf.wifi_pswd));
  file.close();
}

#endif
