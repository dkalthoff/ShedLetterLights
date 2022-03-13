#ifndef NetworkServices_h
#define NetworkServices_h

#include <ArduinoHttpServer.h>
#include <WiFi101.h>
#include "ArduinoSecrets.h"
#include "LightsConstants.h"

class NetworkServices
{
  private:  
    void printWifiData()
    {
      debugln("**************************");
      // print your board's IP address:
      IPAddress ip = WiFi.localIP();
      debug("IP Address: ");
      debugln(ip);

      // print your MAC address:
      byte mac[6];
      WiFi.macAddress(mac);
      char macBuf[18]; // 12 digits, 5 colons, and a '\0' at the end
      macAddrToString(mac, macBuf);
      debug("MAC address: ");
      debugln(macBuf);

      // print your subnet mask:
      IPAddress subnet = WiFi.subnetMask();
      debug("NetMask: ");
      debugln(subnet);

      // print your gateway address:
      IPAddress gateway = WiFi.gatewayIP();
      debug("Gateway: ");
      debugln(gateway);
      debugln("**************************");
    }

    void printCurrentNet()
    {
      debugln("**************************");

      // print the SSID of the network you're attached to:
      debug("SSID: ");
      debugln(WiFi.SSID());

      // print the received signal strength:
      long rssi = WiFi.RSSI();
      debug("signal strength (RSSI):");
      debugln(rssi);

      debugln("**************************");
    }

    void checkFirmwareVersion()
    {
      debug("Current WiFi Firmware Version is ");
      debugln(WiFi.firmwareVersion());
    }

    void macAddrToString(byte *mac, char *str) {
      for (int i = 0; i < 6; i++)
      {
        byte digit;
        digit = (*mac >> 8) & 0xF;
        *str++ = (digit < 10 ? '0' : 'A' - 10) + digit;
        digit = (*mac) & 0xF;
        *str++ = (digit < 10 ? '0' : 'A' - 10) + digit;
        *str++ = ':';
        mac ++;
      }
      // replace the final colon with a nul terminator
      str[-1] = '\0';
    }

  public:
    void connect()
    {
      // check for the WiFi module:
      if (WiFi.status() == WL_NO_SHIELD)
      {
        debugln("No WiFi module found. Unable to connect.");
        // don't continue
        while (true);
      }

      checkFirmwareVersion();

      debug("Attempting to connect to SSID: ");
      debugln(arduinoSecrets.WIFI_SSID);
      
      WiFi.begin(const_cast<char*>(arduinoSecrets.WIFI_SSID), arduinoSecrets.WIFI_SSID_PASSWORD);
      while (WiFi.status() != WL_CONNECTED)
      {
        delay(500);
        debug("WiFi Status: ");
        debugln(WiFi.status());
      }

      debugln("Connected to the network");
      printCurrentNet();
      debugln("");
      printWifiData();
      debugln("");
    }

    bool isConnected()
    {
      return WiFi.status() == WL_CONNECTED;
    }

};

NetworkServices networkServices;

#endif
