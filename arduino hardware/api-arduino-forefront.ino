#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// Wifi Credentials
const char* ssid = "YOUR_ARDUINO_WIFI_SSID";
const char* password = "WIFI_PASSWORD";

// Forefront API Key and endpoint
const char* apiKey = "MODEL_API_KEY_HERE";  
const char* endpoint = "USE_A_FOREFRONT_OR_ANY_OPEN_SOURCED_CHATBOT_ENDPOINT_HERE"; 

WiFiClientSecure client;  

void setup() {
    Serial.begin(115200);
    
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi...");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConnected to WiFi!");

    client.setInsecure();  // Ignore SSL verification (ESP32)

    sendForefrontRequest();
}

void loop() {}

void sendForefrontRequest() {
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        http.begin(client, endpoint);
        http.addHeader("Content-Type", "application/json");
        http.addHeader("Authorization", String("Bearer sk-o5R5GbIrBtgmnwHVWXnngqxMcbavjSF9"));  

        String jsonPayload = R"({
            "model": "Phi-2",  
            "messages": [
                {"role": "system", "content": "You are a helpful assistant."},
                {"role": "user", "content": "What is 2+2? Just give me the number."}
            ],
            "temperature": 1.0,
            "max_tokens": 50
        })";

        int httpResponseCode = http.POST(jsonPayload);
        
        if (httpResponseCode > 0) {
            String response = http.getString();
            Serial.println("Response:");
            Serial.println(response);
            
            // Optional: Parse the JSON response
            DynamicJsonDocument doc(1024);
            deserializeJson(doc, response);
            const char* answer = doc["choices"][0]["message"]["content"];
            Serial.println("Answer from model:");
            Serial.println(answer);

        } else {
            Serial.print("HTTP request failed, error code: ");
            Serial.println(httpResponseCode);
        }

        http.end();
    } else {
        Serial.println("WiFi not connected!");
    }
}
