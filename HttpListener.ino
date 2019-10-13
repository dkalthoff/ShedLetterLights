#include <ArduinoHttpServer.h>

WiFiServer wifiServer(80);

void startHttpListener()
{
    wifiServer.begin();
    Serial.println("Http Listener Started");
}

void listenForHttpRequest()
{
  WiFiClient wifiClient = wifiServer.available();   // listen for incoming clients

  if (wifiClient.connected()) 
  {
    Serial.print("Http Request Received at ");
    printDateTime();
    processRequest(wifiClient);
    wifiClient.stop();
  }
  else
  {
      setLightsPattern(currentLightsPattern);
  } 
}

/**
 * Process the http request to determine the pattern to set
 */
void processRequest(WiFiClient wifiClient)
{
  // Connected to client. Allocate and initialize StreamHttpRequest object.
  ArduinoHttpServer::StreamHttpRequest<1024> httpRequest(wifiClient);
  
  if (httpRequest.readRequest())
  {
    Serial.print("Uri: ");
    Serial.println(httpRequest.getResource().toString());
    
    ArduinoHttpServer::MethodEnum method = httpRequest.getMethod();
    String uri = httpRequest.getResource().toString();
    uri.toLowerCase();
    
    switch (method)
    {
      case ArduinoHttpServer::MethodEnum::MethodGet:
        handleGet(uri, wifiClient);
        break;
      case ArduinoHttpServer::MethodEnum::MethodPost:
        handlePost(uri, httpRequest.getBody(), wifiClient);
        break;
      default:
        Serial.println("Http Method not supported");
        break;
    }
  }
}

/**
 * Handle the GET http request
 */
void handleGet(String uri, WiFiClient wifiClient)
{
  Serial.println("Http Method is GET");
  Serial.println("Determine lights pattern from uri: " + uri);
  
  bool foundUriSupport = true;
    
  if(uri == "/")
  {
    foundUriSupport = true; // return default page in response
  }
  else if (uri == "/originallightsdemo") 
  {
    currentLightsPattern = originalLightsDemo;
  }
  else if (uri == "/whitepulse")
  {
    currentLightsPattern = whitePulse;
  }
  else if (uri == "/randompulse")
  {
    currentLightsPattern = randomPulse;
  }
  else if(uri == "/lightspowerstatus/on")
  {
    lightAreOn = true;
  }
  else if(uri == "/lightspowerstatus/off")
  {
    lightAreOn = false;
  }
  else if(uri == "/shouldoverridesunset/on")
  {
    shouldOverrideSunset = true;
  }
  else if(uri == "/shouldoverridesunset/off")
  {
    shouldOverrideSunset = false;
  }
  else
  {
    foundUriSupport = false;
  }
  
  if(foundUriSupport)
    buildDefaultPageResponse(wifiClient);
  else
    buildResourceNotFoundResponse(wifiClient);
  
  setLightsPattern(currentLightsPattern);
  printCurrentLightPattern(currentLightsPattern);
}

/**
 * Handle POST http request
 */
void handlePost(String uri, String body, WiFiClient wifiClient)
{
  Serial.println("Http Method is POST");
  Serial.println("Request Body:");
  Serial.println(body);
  Serial.println();

  bool foundUriSupport = true;
  body.replace("=%23", "=");
  Serial.println("Body after removal of encoded #: " + body);
  if(uri == "/selectedpulse")
  {
    String hexColorAsString = body.substring(body.indexOf('=') + 1, body.length());    
    byte rgbColors[3];
    setRGBValues(hexColorAsString, rgbColors);

    selectedPulseRed = rgbColors[0];
    selectedPulseGreen = rgbColors[1];
    selectedPulseBlue = rgbColors[2];
    selectedPulseColor = "#" + hexColorAsString;
    
    currentLightsPattern = selectedPulse;
  }
  else if(uri == "/selectedstatic")
  {
    String hexColorAsString = body.substring(body.indexOf('=') + 1, body.length());    
    byte rgbColors[3];
    setRGBValues(hexColorAsString, rgbColors);

    selectedStaticRed = rgbColors[0];
    selectedStaticGreen = rgbColors[1];
    selectedStaticBlue = rgbColors[2];
    selectedStaticColor = "#" + hexColorAsString;
    
    currentLightsPattern = selectedStatic;
  }
  else if(uri == "/selectedsegments")
  {
    byte rgbColors[3];
    
    //selectedColor1
    int startIndex = body.indexOf("selectedColor1=") + 15;
    int endIndex = startIndex + 6;
    String hexColorAsString = body.substring(startIndex, endIndex);
    setRGBValues(hexColorAsString, rgbColors);
    
    selectedSegmentsRed1 = rgbColors[0];
    selectedSegmentsGreen1 = rgbColors[1];
    selectedSegmentsBlue1 = rgbColors[2];
    selectedSegmentsColor1 = "#" + hexColorAsString;
    
    //selectedColor2
    startIndex = body.indexOf("selectedColor2=") + 15;
    endIndex = startIndex + 6;
    hexColorAsString = body.substring(startIndex, endIndex);
    setRGBValues(hexColorAsString, rgbColors);

    selectedSegmentsRed2 = rgbColors[0];
    selectedSegmentsGreen2 = rgbColors[1];
    selectedSegmentsBlue2 = rgbColors[2];
    selectedSegmentsColor2 = "#" + hexColorAsString;

    //selectedColor3
    startIndex = body.indexOf("selectedColor3=") + 15;
    endIndex = startIndex + 6;
    hexColorAsString = body.substring(startIndex, endIndex);
    setRGBValues(hexColorAsString, rgbColors);

    selectedSegmentsRed3 = rgbColors[0];
    selectedSegmentsGreen3 = rgbColors[1];
    selectedSegmentsBlue3 = rgbColors[2];
    selectedSegmentsColor3 = "#" + hexColorAsString;
    
    currentLightsPattern = selectedSegments;
  }
  else
  {
    foundUriSupport = false;
  }
  
  if(foundUriSupport)
    buildDefaultPageResponse(wifiClient);
  else
    buildResourceNotFoundResponse(wifiClient);
  
  setLightsPattern(currentLightsPattern);
  printCurrentLightPattern(currentLightsPattern);
}

/*
 * Convert hex String ("FF0000") into byte values in rgbColors array
 */
void setRGBValues(String hexColorAsString, byte rgbColors[])
{
  Serial.println("selectedPulse Hex color: " + hexColorAsString);
  
  // convert it to integer
  int hexColorAsNumber = (int)strtol( &hexColorAsString[0], NULL, 16);
  
  // Split them up into r, g, b values
  rgbColors[0] = hexColorAsNumber >> 16;
  rgbColors[1] = hexColorAsNumber >> 8 & 0xFF;
  rgbColors[2] = hexColorAsNumber & 0xFF;

  Serial.print("Red:");
  Serial.print(rgbColors[0]);
  Serial.print(" Green:");
  Serial.print(rgbColors[1]);
  Serial.print(" Blue:");
  Serial.println(rgbColors[2]);
}

void buildDefaultPageResponse(WiFiClient wifiClient)
{
  String header = "HTTP/1.1 200 OK"
                  "Content-type:text/html"
                  "Connection: close";
                  
  String body = "<html lang=\"en\">"
                "<head>"
                "<title>Shed Letter Lights</title>"
                "</head>"
                "<body>"
                  "<a href=\"/\">Home</a><br/><br/>"
                  
                  "<h4>Light Patterns:</h4>"
                    "<a href=\"/originallightsdemo\">Original Lights Demo</a> - full color spectrum with different actions<br>"
                    "<a href=\"/whitepulse\">White Pulse</a><br>"
                    "<a href=\"/randompulse\">Random Pulse</a><br>"
                    "<form action=\"/selectedpulse\" method=\"post\">Choose pulse color: <input name=\"selectedColor\" type=\"color\" value=\"" + selectedPulseColor + "\"> <input type=\"submit\" value=\"Submit\"></form><br/>"
                    "<form action=\"/selectedstatic\" method=\"post\">Choose static color: <input name=\"selectedColor\" type=\"color\" value=\"" + selectedStaticColor + "\"> <input type=\"submit\" value=\"Submit\"></form><br/>"
                    "<form action=\"/selectedsegments\" method=\"post\">"
                      "Choose segment colors: "
                      "<input name=\"selectedColor1\" type=\"color\" value=\"" + selectedSegmentsColor1 + "\"> "
                      "<input name=\"selectedColor2\" type=\"color\" value=\"" + selectedSegmentsColor2 + "\"> "
                      "<input name=\"selectedColor3\" type=\"color\" value=\"" + selectedSegmentsColor3 + "\"> "
                      "<input type=\"submit\" value=\"Submit\">"
                    "</form><br/>"
                    
                  "<h4>System Status</h4>"
                    "Date/time: " + getDateTimeAsString() + "</br><br/>"
                    "Sunrise: " + getSunriseAsString() + "<br/>"
                    "Sunset: " + getSunsetAsString() + ": " + getOverrideSunsetHtml() + "<br/><br/>"
                    "Lights are: " + getLightsPowerStatusHtml() + "<br/>"
                    "Current Lights Pattern: " + getCurrentLightPatternAsString(currentLightsPattern) + ""
                "</body>"
                "<html>";

  wifiClient.println(header);
  wifiClient.println(); // The HTTP response header ends with a blank line
  wifiClient.println(body);
  wifiClient.println(); // The HTTP response ends with another blank line
  
  Serial.println("Send Http Response with default html content");  
}

String getOverrideSunsetHtml()
{
  if(shouldOverrideSunset)
    return "Set to turn on now <a href=\"/shouldOverrideSunset/off\">Turn on after sunset</a>";
  else
    return "Set to turn on after sunset <a href=\"/shouldOverrideSunset/on\">Turn on now</a>"; 
}

String getLightsPowerStatusHtml()
{
  if(lightAreOn) 
    return "On <a href=\"/lightspowerstatus/off\">Turn Off</a>";
  else
    return "Off <a href=\"/lightspowerstatus/on\">Turn On</a>"; 
}

void buildResourceNotFoundResponse(WiFiClient wifiClient)
{
    wifiClient.println("HTTP/1.1 404 NOT FOUND");
    wifiClient.println("Content-type:text/html");
    wifiClient.println();

    // The HTTP response ends with another blank line:
    wifiClient.println();
}
