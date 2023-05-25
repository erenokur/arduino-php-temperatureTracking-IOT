#include <DHT.h>
#include <Ethernet.h>
#include <SPI.h>

byte mac[] = {  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
//byte mac[] = { 0x90, 0xA2, 0xDA, 0x0F, 0x2A, 0x8D };
IPAddress ip(192,168,2,2);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress server(192,168,1,102); // 192.168.1.102
EthernetClient client;
char serverName[] = "127.0.0.1";
int serverPort = 80;
//byte server[] = { 127, 0, 0, 1  }; // Server IP

#define DHTPIN 2 // SENSOR PIN
#define DHTTYPE DHT11 // SENSOR TYPE - THE ADAFRUIT LIBRARY OFFERS SUPPORT FOR MORE MODELS
DHT dht(DHTPIN, DHTTYPE);

long previousMillis = 0;
unsigned long currentMillis = 0;
long interval = 250000; // READING INTERVAL

int t = 0;  // TEMPERATURE VAR
int h = 0;  // HUMIDITY VAR
String data;
String apiKeyValue = "tPmAT5Ab3j7F9";
String sensorName = "BME280";
String sensorLocation = "Office";

void setup() { 
  Serial.begin(9600);
  pinMode(4,OUTPUT);
  digitalWrite(4,HIGH);
  //Ethernet.begin(mac, ip, gateway, gateway, subnet);
    if(!Ethernet.begin(mac)) Serial.println(F("failed"));
   else Serial.println(F("ok"));
  Serial.println("ethernet begin : ");
  Serial.println(Ethernet.localIP());
 
  Serial.println("dht begin : ");
  dht.begin(); 
  delay(10000); // GIVE THE SENSOR SOME TIME TO START
  data = "";
}

void loop(){

  currentMillis = millis();
  if(currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;
    h = (int) dht.readHumidity();
    t = (int) dht.readTemperature();
      Serial.println("dht values : temprature =>"+ String(t, DEC) +" humudity =>"+ String(h, DEC));
  }

  data = "api_key=" + apiKeyValue + "&sensor=" + sensorName
                            + "&location=" + sensorLocation + "&value1=" + String(dht.readTemperature())
                            + "&value2=" + String(dht.readHumidity()) + "&value3=" + String(1) + "";
 senddata();
 delay(300000);
}

void senddata()
{  
  if (client.connect(server,80)) { 
    Serial.println("connected");
    client.println("POST /esp-post-data.php HTTP/1.1"); 
    client.println("Host: 192.168.1.102"); // SERVER ADDRESS HERE TOO
    client.println("Connection: close");
    client.println("Content-Type: application/x-www-form-urlencoded"); 
    client.print("Content-Length: "); 
    client.println(data.length()); 
    client.println(); 
    client.print(data); 
    Serial.println("sended : "+ data);
      while(client.connected()) {
      while(client.available()) {
        Serial.write(client.read());
      }
    }
    Serial.println("connectin closed");
  }else
  {
     Serial.write("not connected");
  }
  
  
  /*if (client.connected()) { 
    client.stop();  // DISCONNECT FROM THE SERVER
  }*/

}
