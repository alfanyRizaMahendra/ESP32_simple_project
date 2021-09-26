#include <ThingSpeak.h>
#include <WiFi.h>

//Replace your wifi credentials here
const char* ssid     = "MyExtender";
const char* password = "nggonankuikilo";

//change your channel number here (Thinkspeak Channel ID)
unsigned long number = 1518155;
int channel1 = 0;
int channel2 = 1;

//1 and 2 are channel fields. You don't need to change if you are following this tutorial. However, you can modify it according to your application
unsigned int led1 = 1;
unsigned int led2 = 2;


// Pins
static const int led01 = 32;
static const int led02 = 33;

// Setting ESP32 PWM
int freq = 2000;
int resolution = 8;

// replacing delay() function
int previous_time = 0;
const int event = 1000;

WiFiClient  client;

void setup() {
  Serial.begin(115200);
  delay(100);
  
  // pin initialzed
  ledcSetup(channel1, freq, resolution);
  ledcSetup(channel2, freq, resolution);
  ledcAttachPin(led01, channel1);
  ledcAttachPin(led02, channel2);
  
  // We start by connecting to a WiFi network
 
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Netmask: ");
  Serial.println(WiFi.subnetMask());
  Serial.print("Gateway: ");
  Serial.println(WiFi.gatewayIP());
  ThingSpeak.begin(client);
  
  previous_time = millis();
}

void loop() {
  int current_time = millis();
  //get the last data of the fields
  uint8_t led_1 = ThingSpeak.readFloatField(number, led1);
  uint8_t led_2 = ThingSpeak.readFloatField(number, led2);

  if(current_time - previous_time > event)
  {
      ledcWrite(channel1, led_1);
      ledcWrite(channel2, led_2);
      notif(led_1, led_2);
      led_1 = 0;
      led_2 = 0;
      previous_time = millis();  
  }
}

int notif(int inp1, int inp2){
    Serial.print("Led 1's duty cycle : ");
    Serial.println(inp1);       
    Serial.print("Led 2's duty cycle : ");
    Serial.println(inp2);
    Serial.println("");
}
