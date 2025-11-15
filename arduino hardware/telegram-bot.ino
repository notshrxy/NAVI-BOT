#include <WiFi.h>
#include <ArduinoJson.h>
#include <WiFiClientSecure.h>

char wifi_ssid[] = "teacher";
char wifi_pass[] = "87654321";

//Replace with any Telegram Bot APIs of your choice for Customization
String telegrambotToken = "PLACE_A_CUSTOM_TELEGRAM_BOT_API_KEY_HERE";
String telegrambotChatID = "6441251341";

//Forefront API Key - Free and Open Sourced ChatBot Model
String forefrontKey = "sk-o5R5GbIrBtgmnwHVWXnngqxMcbavjSF9";  // ForeFront API Key

// ForeFront Chat
String role = "You are a helpful assistant.";
String model = "gpt-3.5-turbo"; // or other supported models
String historical_messages = "";

// Image generator --> image:your prompt
String imageSize = "256x256"; // 256x256, 512x512 , 1024x1024

// [Keep all your existing WiFi and Telegram functions unchanged]
// initWiFi(), telegrambot_getUpdates(), sendMessageToTelegram_custom(), 
// sendImageToTelegram_custom(), urlencode() remain the same

String forefront_chat(String message) { 
  WiFiClientSecure client_tcp;
  client_tcp.setInsecure();

  message.replace("\"","'");
  
  // ForeFront API requires messages in a specific format
  String request = "{\"model\":\"" + model + "\",\"messages\":[";
  
  if (historical_messages.length() == 0) {
    // First message includes the system role
    request += "{\"role\":\"system\",\"content\":\"" + role + "\"},";
  } else {
    request += historical_messages + ",";
  }
  
  request += "{\"role\":\"user\",\"content\":\"" + message + "\"}]}";

  if (client_tcp.connect("api.forefront.ai", 443)) {
    client_tcp.println("POST /v1/chat/completions HTTP/1.1");
    client_tcp.println("Connection: close"); 
    client_tcp.println("Host: api.forefront.ai");
    client_tcp.println("Authorization: Bearer " + forefrontKey);
    client_tcp.println("Content-Type: application/json; charset=utf-8");
    client_tcp.println("Content-Length: " + String(request.length()));
    client_tcp.println();
    client_tcp.print(request);
    
    String getResponse="", Feedback="";
    boolean state = false;
    int waitTime = 20000;   // timeout 20 seconds
    long startTime = millis();
    
    while ((startTime + waitTime) > millis()) {
      Serial.print(".");
      delay(100);      
      while (client_tcp.available()) {
          char c = client_tcp.read();
          if (state) 
            getResponse += String(c);
          if (c == '\n')
            Feedback = "";
          else if (c != '\r')
            Feedback += String(c);
            
          // Look for the start of the content in ForeFront's response
          if (Feedback.indexOf("\"content\":\"") != -1)
            state = true;
            
          if (getResponse.indexOf("\"}") != -1 && state) {
            state = false;
            getResponse = getResponse.substring(0, getResponse.length()-2);
          }
          
          startTime = millis();
       }
       
       if (getResponse.length() > 0) {
          client_tcp.stop();
          // Update conversation history
          historical_messages += (historical_messages.length() > 0 ? "," : "") + 
                               "{\"role\":\"user\",\"content\":\"" + message + "\"}," +
                               "{\"role\":\"assistant\",\"content\":\"" + getResponse + "\"}";
          Serial.println("");
          return getResponse;
       }
    }
    
    client_tcp.stop();
    Serial.println(Feedback);
    return "error";
  }
  else {
    return "Connection failed";
  }
}

String forefront_image(String prompt) { 
  WiFiClientSecure client_tcp;
  client_tcp.setInsecure();

  prompt.replace("\"","'");
  String request = "{\"prompt\":\"" + prompt + "\",\"size\":\"" + imageSize + "\"}";

  if (client_tcp.connect("api.forefront.ai", 443)) {
    client_tcp.println("POST /v1/images/generations HTTP/1.1");
    client_tcp.println("Connection: close"); 
    client_tcp.println("Host: api.forefront.ai");
    client_tcp.println("Authorization: Bearer " + forefrontKey);
    client_tcp.println("Content-Type: application/json; charset=utf-8");
    client_tcp.println("Content-Length: " + String(request.length()));
    client_tcp.println();
    client_tcp.print(request);
    
    String getResponse="", Feedback="";
    boolean state = false;
    int waitTime = 20000;   // timeout 20 seconds
    long startTime = millis();
    
    while ((startTime + waitTime) > millis()) {
      Serial.print(".");
      delay(100);      
      while (client_tcp.available()) {
          char c = client_tcp.read();
          if (String(c) == "\"" && state)
            break;           
          if (state)
            getResponse += String(c);
          if (c == '\n')
            Feedback = "";
          else if (c != '\r')
            Feedback += String(c);
          // Look for URL in ForeFront's response
          if (Feedback.indexOf("\"url\":\"") != -1)
            state = true;             
          startTime = millis();
       }
       if (getResponse.length() > 0) {
          client_tcp.stop();
          Serial.println("");
          return getResponse;
       }
    }
    
    client_tcp.stop();
    Serial.println(Feedback);
    return "error";
  }
  else {
    return "Connection failed";
  }
}

void forefront_chat_reset() {
  historical_messages = "";
}

void setup() {
  Serial.begin(115200);
  initWiFi();
}

void loop() {
  String message = telegrambot_getUpdates(telegrambotToken);
  if (message != "" && message != "/start" && message != "null") {
    String response = "";
    if (message.indexOf("image:") != -1) {
      String prompt = message.substring(6);
      response = forefront_image(prompt);
      sendImageToTelegram_custom(telegrambotToken, telegrambotChatID, prompt, response);
    }
    else {
      response = forefront_chat(message);
      sendMessageToTelegram_custom(telegrambotToken, telegrambotChatID, response, "");
    }
  }
  delay(100);
}
