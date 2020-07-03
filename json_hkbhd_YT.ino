/*
{
"menu": {
  "id": 1234,
  "value": "File",
  "popup": {
    "number": 56,
    "menu_item": ["A",42,3.14]
  }
}
}
*/  


#include <ArduinoJson.h>
String json;

void setup() {
 Serial.begin(115200);
 Serial.println();
 create_json();
 delay(3000);
 Serial.println();
 parse_json(json);

}

void loop() {


}

void create_json()
{
     StaticJsonDocument<500> doc;
   JsonObject root = doc.to<JsonObject>();
  JsonObject menu= root["menu"].to<JsonObject>();
  menu["id"]=1234;
  menu["value"]="File";
  JsonObject popup= menu["popup"].to<JsonObject>();
  popup["number"]=56;
  JsonArray array = popup["menu_item"].to<JsonArray>();
  array.add("A");
  array.add(42);
  array.add(3.14);
   serializeJsonPretty(doc, Serial);
   serializeJsonPretty(doc, json);
}

void parse_json(String json)
{
  StaticJsonDocument<200> doc;
  DeserializationError error = deserializeJson(doc, json);
  if (error) {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.c_str());
      }
  JsonObject root = doc["menu"];
  int id = root["id"];
  String value = root["value"];
  JsonObject popup = root["popup"];
  int number = popup["number"];
  JsonArray menu_item = popup["menu_item"].as<JsonArray>();
  Serial.print("id = ");
  Serial.println(id);
  Serial.print("value = ");
  Serial.println(value);
  Serial.print("number = ");
  Serial.println(number);
  for(JsonVariant v : menu_item) {
      Serial.println(v.as<String>());
  }

  
}
