#include <WiFi101.h>

// Status
int status = WL_IDLE_STATUS;

// WiFi parameters
const char ssid[] = "Heated Shed Software";
//const char ssid[] = "07112002";
//const char pwd[] = "kalthoff";

void connectToWiFi()
{
  // Connect to WiFi
  while (status != WL_CONNECTED) 
  {
    status = WiFi.begin(ssid);

    // Wait 10 seconds for connection:
    delay(10000);
  }
  
  Serial.print("WiFi connected: ");
  Serial.println(ssid);

  // Print the IP address
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  Serial.println();
}
