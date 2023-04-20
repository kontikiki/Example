#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include "secrets.h"
#include "ThingSpeak.h"

#define RXD2 16
#define TXD2 17

char ssid[] = SECRET_SSID;   // your network SSID (name)
char pass[] = SECRET_PASS;   // your network password
int keyIndex = 0;            // your network key Index number (needed only for WEP)
WiFiClient  client;

unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;

uint8_t buff[55];

int pm1 = 0;
int pm25 = 0;
int pm10 = 0;

void setup(void) {

  Serial.begin(9600);
  //Serial1.begin(9600, SERIAL_8N1, RXD2, TXD2);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);

  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);
}

void loop(void) {

  int i = 0;
  while (Serial2.available()) {
    byte num = Serial2.read();
    Serial.write(num);
    buff[i++] = num;
  }

  if ((buff[0] == 0x16 && buff[1] == 0x35)) {
    if (buff[2] == 0x0B) {
      int val = 0;

      val = (buff[3] << 24) + (buff[4] << 16) + (buff[5] << 8)
            + (buff[6]);
      pm1 = val;
      Serial.print("pm1.0 : ");
          Serial.println(pm1);
          
      val = 0;
      val = (buff[7] << 24) + (buff[8] << 16) + (buff[9] << 8)
            + (buff[10]);
      pm25 = val;
      Serial.print("pm2.5 : ");
          Serial.println(pm25);

      val = 0;
      val = (buff[11] << 24) + (buff[12] << 16) + (buff[13] << 8)
            + (buff[14]);
      pm10 = val;
      Serial.print("pm10 : ");
          Serial.println(pm10);
          
    }
    if (WiFi.status() != WL_CONNECTED) {
      Serial.print("Attempting to connect to SSID: ");
      Serial.println(SECRET_SSID);
      while (WiFi.status() != WL_CONNECTED) {
        WiFi.begin(ssid, pass);  // Connect to WPA/WPA2 network. Change this line if using open or WEP network
        Serial.print(".");
        delay(5000);
      }
      Serial.println("\nConnected.");
    }

    // set the fields with the values
    ThingSpeak.setField(1, pm1);
    ThingSpeak.setField(2, pm25);
    ThingSpeak.setField(3, pm10);

    // write to the ThingSpeak channel
    int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
    if (x == 200) {
      Serial.println("Channel update successful.");
    }
    else {
      Serial.println("Problem updating channel. HTTP error code " + String(x));
    }
  }
  memset(buff, 0, sizeof(buff));

}
