#include <WiFi.h>
#include <HTTPClient.h>

// Replace with your network credentials
const char* ssid = "Rey";
const char* password = "abcd1234";

// Server URL
const char* serverName = "http://your_local_server_ip:5000/sensor";

unsigned long lastTime = 0;
unsigned long timerDelay = 5000;

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  if ((millis() - lastTime) > timerDelay) {
    // Read sensor data
    int sensorValue = analogRead(34); // Change to your sensor pin
    float voltage = sensorValue * (3.3 / 4095.0);
    float temperature = (voltage - 0.5) * 100.0; // Example conversion for a TMP36 sensor

    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;

      // Your domain name with URL path or IP address with path
      http.begin(serverName);

      // Specify content-type header
      http.addHeader("Content-Type", "application/json");

      // Create JSON object
      String httpRequestData = "{\"temperature\":\"" + String(temperature) + "\"}";

      // Send HTTP POST request
      int httpResponseCode = http.POST(httpRequestData);

      if (httpResponseCode > 0) {
        String response = http.getString();
        Serial.println(httpResponseCode); // Print return code
        Serial.println(response);         // Print request answer
      } else {
        Serial.print("Error on sending POST: ");
        Serial.println(httpResponseCode);
      }

      // Free resources
      http.end();
    } else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}
