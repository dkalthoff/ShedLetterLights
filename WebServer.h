#ifndef WebServer_h
#define WebServer_h

#include <ArduinoHttpServer.h>
#include "LightsService.h"
#include "WebContent.h"

WiFiServer wifiServer(80);

class WebServer
{
  private:
    /**
       Process the http request to determine the pattern to set
    */
    void processRequest(WiFiClient &wifiClient)
    {
      // Connected to client. Allocate and initialize StreamHttpRequest object.
      ArduinoHttpServer::StreamHttpRequest<1024> httpRequest(wifiClient);

      if (httpRequest.readRequest())
      {
        String uri = httpRequest.getResource().toString();
        uri.toLowerCase();

        debugln("Uri: " + uri);

        switch (httpRequest.getMethod())
        {
          case ArduinoHttpServer::Method::Get:
            handleGet(uri, wifiClient);
            break;
          case ArduinoHttpServer::Method::Post:
            handlePost(uri, httpRequest.getBody(), wifiClient);
            break;
          default:
            debugln("Http Method not supported");
            break;
        }
      }
    }

    /**
       Handle the GET http request
    */
    void handleGet(const String &uri, WiFiClient &wifiClient)
    {
      debugln("Http Method is GET");
      debugln("Determine lights pattern from uri: " + uri);

      if (uri == "/")
      {
        sendResponse(wifiClient, webContent.defaultPage);
        debugln("Return default page in response");
      }
      else if (uri == "/contentpage/menu")
      {
        sendResponse(wifiClient, webContent.contentPage_Menu);
      }
      else if (uri == "/contentpage/scenes")
      {
        sendResponse(wifiClient, webContent.contentPage_Scenes);
      }
      else if (uri == "/contentpage/static")
      {
        sendResponse(wifiClient, webContent.contentPage_Static);
      }
      else if (uri == "/contentpage/pulse")
      {
        sendResponse(wifiClient, webContent.contentPage_Pulse);
      }
      else if (uri == "/contentpage/segments")
      {
        sendResponse(wifiClient, webContent.contentPage_Segments);
      }
      else if (uri == "/contentpage/random")
      {
        sendResponse(wifiClient, webContent.contentPage_Random);
      }
      else if (uri == "/scripts/defaultpage.js")
      {
        sendResponse(wifiClient, webContent.defaultPage_JS);
      }
      else
      {
        ArduinoHttpServer::StreamHttpErrorReply httpErrorReply(wifiClient, "text/html");
        httpErrorReply.send("Lights pattern not supported");
      }
    }

    /**
       Handle POST http request
    */
    void handlePost(const String &uri, String body, WiFiClient &wifiClient)
    {
      debugln("Http Method is POST");
      debugln("Request Body:");
      debugln(body);
      debugln();

      body.replace("=%23", "=");
      debugln("Body after removal of encoded #: " + body);

      LightsConfiguration lightsConfiguration;

      if (uri == "/api/scenes")
      {
        lightsConfiguration.lightsPattern = scenes;
        lightsConfiguration.scenesType = (scenesTypeEnum)body.substring(body.indexOf('=') + 1, body.length()).toInt();
        
      }
      else if (uri == "/api/selectedstatic")
      {
        lightsConfiguration.lightsPattern = selectedStatic;
        char hexColor[7];
        body.substring(body.indexOf('=') + 1, body.length()).toCharArray(hexColor, body.length());
        strcpy(lightsConfiguration.colors[0], hexColor);
      }
      else
      {
        ArduinoHttpServer::StreamHttpErrorReply httpErrorReply(wifiClient, "text/html");
        httpErrorReply.send("Lights pattern not supported");
        return;
      }

      lightsService.setLightsPattern(lightsConfiguration);
      sendSuccesfulResponse(wifiClient);
    }

    /*
      Convert hex String ("FF0000") into byte values in rgbColors array
    */
    void setRGBValues(String hexColorAsString, uint8_t rgbColors[])
    {
      debugln("Hex color: " + hexColorAsString);

      // convert it to integer
      int hexColorAsNumber = (int)strtol( &hexColorAsString[0], NULL, 16);

      // Split them up into r, g, b values
      rgbColors[RED] = hexColorAsNumber >> 16;
      rgbColors[GREEN] = hexColorAsNumber >> 8 & 0xFF;
      rgbColors[BLUE] = hexColorAsNumber & 0xFF;

      debug("Red:"); debug(rgbColors[RED]);
      debug(" Green:"); debug(rgbColors[GREEN]);
      debug(" Blue:"); debugln(rgbColors[BLUE]);
    }

    void sendResponse(WiFiClient &wifiClient, const String &data)
    {
      ArduinoHttpServer::StreamHttpReply httpReply(wifiClient, "text/html");
      httpReply.send(data);
      debugln("Sent: " + data);
    }

    void sendSuccesfulResponse(WiFiClient &wifiClient)
    {
      wifiClient.println("HTTP/1.1 204 No Content");
      wifiClient.println("Content-type:text/html");
      wifiClient.println("Content-Length: 0");
      wifiClient.println("Connection: close");
      wifiClient.println();
  
      // The HTTP response ends with another blank line:
      wifiClient.println();
    }

  public:
    void startHttpListener()
    {
      wifiServer.begin();
      debugln("Web Server Started");
    }

    void listenForHttpRequest()
    {
      WiFiClient wifiClient( wifiServer.available() ); // listen for incoming clients

      if (wifiClient.connected())
      {
        debugln("");
        debugln("Http Request Received ------->");
        
        processRequest(wifiClient);
        wifiClient.stop();
        
        debugln("<------- Http Response Sent");
        debugln("");
      }
    }
};

WebServer webServer;

#endif
