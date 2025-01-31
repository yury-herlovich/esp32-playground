#include <WiFi.h>
#include <blink.h>
#include "SPIFFS.h"
#include "pubsub.h"
#include <ArduinoJson.h>

// Set web server port number to 80
WiFiServer server(80);

// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

unsigned long currentTime = millis();
unsigned long previousTime = 0;

// web page content
String webPageContent;

// Function declaration
String loadFile(String path);
String loadWebPage();
String processTemplate(String page, bool ledStatus);
void blinkHandler(WiFiClient client);
void switchHandler(WiFiClient client);
void colorHandler(WiFiClient client, String body);
bool servFiles(WiFiClient client, String path);

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

    // array of strings to store the header
    String header = "";
    String body = "";
    String currentLine = "";
    int contentLength = 0;

    while (client.connected() && currentTime - previousTime <= timeoutTime) {  // loop while the client's connected
      currentTime = millis();

      if (client.available()) {
        char c = client.read();  // read char by char HTTP request
        Serial.write(c);

        if (c == '\n') {
          // if current line is empty, you got two newline characters in a row
          if (currentLine.length() == 0) {
            if (contentLength > 0) {
              Serial.println("Content length: " + String(contentLength));

              // read the body
              while (client.available() && body.length() < contentLength) {
                body += (char)client.read();
              }

              Serial.println("Body: " + body);
            }

            break;
          } else {
            // store only first line as header (method + url)
            if (header.length() == 0) {
              header = currentLine;
            }

            if (currentLine.startsWith("Content-Length: ")) {
              contentLength = currentLine.substring(16).toInt();
            }

            currentLine = "";
          }
        } else if (c == '\r') {
          continue;
        } else {
          currentLine += c;
        }
      }
    }

    String method = header.substring(0, header.indexOf(" "));
    String url = header.substring(method.length() + 1, header.indexOf(" ", method.length() + 1));

    Serial.println("Method: " + method);
    Serial.println("URL: \"" + url + "\"");

    if (method == "GET") {
      if (url == "/") {
        client.println("HTTP/1.1 200 OK");
        client.println("Content-type:text/html");
        client.println("Connection: close");
        client.println();

        String pageContent = processTemplate(webPageContent, ledStatus());
        client.println(pageContent);
      } else {
        bool isFile = servFiles(client, url);

        if (!isFile) {
          client.println("HTTP/1.1 404 Not Found");
          client.println("Content-type:text/html");
          client.println("Connection: close");
          client.println();

          client.println("404 Not Found");
        }
      }
    } else if (method == "POST") {
      if (url == "/blink") {
        blinkHandler(client);
      } else if (url == "/switch") {
        switchHandler(client);
      } else if (url == "/color") {
        colorHandler(client, body);
      } else {
        client.println("HTTP/1.1 404 Not Found");
        client.println("Content-type:text/html");
        client.println("Connection: close");
        client.println();

        client.println("404 Not Found");
      }
    }

    // Clear the header variable
    header = "";
    currentLine = "";

    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}

void blinkHandler(WiFiClient client) {
  Serial.println("Blink request");

  client.println("HTTP/1.1 200 OK");
  client.println("Content-type:application/json");
  client.println("Connection: close");
  client.println();

  blink(100, 3);
}

void switchHandler(WiFiClient client) {
  Serial.println("Switch led request");

  client.println("HTTP/1.1 200 OK");
  client.println("Content-type:application/json");
  client.println("Connection: close");
  client.println();

  if (ledStatus()) {
    ledOff();
    publishMessage("LED OFF");
  } else {
    ledOn();
    publishMessage("LED ON");
  }

  String response = "{\"ledStatus\": \"" + String(ledStatus() ? "ON" : "OFF") + "\"}";
  client.println(response);
}

void colorHandler(WiFiClient client, String body) {
  Serial.println("Color request");

  JsonDocument doc;
  deserializeJson(doc, body);

  Serial.println("Color: " + doc.as<String>());

  setColor(doc["r"], doc["g"], doc["b"]);

  client.println("HTTP/1.1 200 OK");
  client.println("Content-type:application/json");
  client.println("Connection: close");
  client.println();

  String response = "{\"status\": \"OK\"}";
  client.println(response);
}

bool servFiles(WiFiClient client, String path) {
  if (path == "") {
    return false;
  }

  String fileContent = loadFile(path);

  if (fileContent == "") {
    return false;
  }

  client.println("HTTP/1.1 200 OK");

  if (path.indexOf(".css") > 0) {
    client.println("Content-type:text/css");
  } else if (path.indexOf(".js") > 0) {
    client.println("Content-type:application/javascript");
  } else {
    client.println("Content-type:text/html");
  }

  client.println("Connection: close");
  client.println();

  client.println(fileContent);

  return true;
}

String loadFile(String path) {
  File file = SPIFFS.open(path, "r");
  String fileContent = "";

  if(!file){
    Serial.println("Failed to open " + path + " file for reading");
  }

  while(file.available()){
    fileContent += (char)file.read();
  }

  file.close();

  return fileContent;
}

String loadWebPage() {
  return loadFile("/page.html");
}

String processTemplate(String page, bool ledStatus) {
  page.replace("{{LED_STATUS}}", ledStatus ? "Turn OFF" : "Turn ON");
  page.replace("{{LED_STATUS_CLASS}}", ledStatus ? "on" : "off");
  page.replace("{{LED_STATUS_NEXT}}", ledStatus ? "off" : "on");

  return page;
}
