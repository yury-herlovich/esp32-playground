#include <WiFi.h>
#include <blink.h>
#include "SPIFFS.h"
#include "pubsub.h"

// Set web server port number to 80
WiFiServer server(80);

// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

unsigned long currentTime = millis();
unsigned long previousTime = 0;

// Variable to store the HTTP request
String header;

// web page content
String webPageContent;

// Function declaration
String loadWebPage();
String processTemplate(String page, bool ledStatus);

void startHttpServer() {
  Serial.println("Starting HTTP server");

  server.begin();

  Serial.println("Client connected");

  // load web page
  webPageContent = loadWebPage();
}

void listenConnections() {
  WiFiClient client = server.available();

  if (client) {
    currentTime = millis();
    previousTime = currentTime;

    Serial.println("new http request");

    String currentLine = "";

    while (client.connected() && currentTime - previousTime <= timeoutTime) {  // loop while the client's connected
      currentTime = millis();

      if (client.available()) {
        char c = client.read();  // read char by char HTTP request
        Serial.write(c);
        header += c;

        if (c == '\n') {
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            if (header.indexOf("GET /blink") >= 0) {
              Serial.println("Blink request");

              blink(100, 3);
            }

            if (header.indexOf("GET /on") >= 0) {
              Serial.println("ON request");
              ledOn();
              publishMessage("LED ON");
            }

            if (header.indexOf("GET /off") >= 0) {
              Serial.println("OFF request");
              ledOff();
              publishMessage("LED OFF");
            }

            String pageContent = processTemplate(webPageContent, ledStatus());
            client.println(pageContent);

            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
      }
    }

    // Clear the header variable
    header = "";

    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}

String loadWebPage() {
  File file = SPIFFS.open("/page.html", "r");
  String webPage = "";

  if(!file){
    Serial.println("Failed to open file for reading");
  }

  while(file.available()){
    webPage += (char)file.read();
  }

  file.close();

  return webPage;
}

String processTemplate(String page, bool ledStatus) {
  page.replace("{{LED_STATUS}}", ledStatus ? "Turn OFF" : "Turn ON");
  page.replace("{{LED_STATUS_CLASS}}", ledStatus ? "on" : "off");
  page.replace("{{LED_STATUS_NEXT}}", ledStatus ? "off" : "on");

  return page;
}
