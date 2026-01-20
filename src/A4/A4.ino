#include <SoftwareSerial.h>       // Library for serial communication with ESP-01
SoftwareSerial espSerial(6, 7);   // Connection (Arduino RX: pin 6) to (ESP-01: TX pin)

#define DEBUG true

// WiFi and ThingSpeak settings
String mySSID = "linksys_1";
String myPWD = "";
String myHOST = "api.thingspeak.com";
String myPORT = "80";
String myWriteAPI = "6UKE7N1W16R0TIOC";
String myCHANNEL = "2749755";

// Field names
String fieldRed = "field1";
String fieldOrange = "field2";
String fieldGreen = "field3";

// Traffic light durations
int DELAY_RED = 30000;      // Delay for red light
int DELAY_ORANGE = 20000;   // Delay for orange light
int DELAY_GREEN = 30000;    // Delay for green light

String response;            // Response from the ESP8266
String sendData = "";       // Data to be sent
int sendVal;                // Value to be sent

void setup() 
{    
    Serial.begin(9600);
    espSerial.begin(9600);                                                // In case of error, change espSerial to 9600

    Serial.println("************ ESP-01 Setup ************");
   
    espData("AT+RST", 1000, DEBUG);                                        // Reset ESP-01
    espData("AT+CWMODE=1", 1000, DEBUG);                                   // Mode=1 => client
    espData("AT+CWJAP=\"" + mySSID + "\",\"" + myPWD + "\"", 1000, DEBUG); // Connection to WiFi network
    
    while(!espSerial.find("WIFI GOT IP"))                                  // Wait for connection
    {          
        Serial.print(".");
        delay(1000);
        Serial.print(".");
        delay(1000);
        Serial.print(".");
        delay(1000);
    }
    
    Serial.println("Connected!");
    delay(1000);
    
    Serial.println("***************************************");
}

void loop() 
{
/*
 *  Task Α.4 : Enable traffic light
 */
    Serial.println("************ Task A.4 ************");

    setTrafficLight("RED"); 
    delay(DELAY_RED);
    setFieldValue(fieldRed, myWriteAPI, 0); // Disable red light

    setTrafficLight("GREEN");
    delay(DELAY_GREEN);
    setFieldValue(fieldGreen, myWriteAPI, 0); // Disable green light

    setTrafficLight("ORANGE");
    delay(DELAY_ORANGE);
    setFieldValue(fieldOrange, myWriteAPI, 0); // Disable orange light

    Serial.println("***************************************");
}

// Function to set the traffic light to a specific color
void setTrafficLight(String color) 
{
    String field;
    if (color == "RED") 
    {
        field = fieldRed;
        sendVal = 1;
    }
    else if (color == "ORANGE") 
    {
        field = fieldOrange;
        sendVal = 2;
    }
    else if (color == "GREEN")
    {
        field = fieldGreen;
        sendVal = 3;
    }
    else return;

    setFieldValue(field, myWriteAPI, sendVal); // Update the corresponding field in ThingSpeak
    Serial.println("Traffic Light is set to " +color);
}

// Function to write a value to a field in ThingSpeak
void setFieldValue(String field, String writeAPI, int value) 
{
	// HTTP GET request for writing a value to a field
    sendData = "GET /update?api_key=" + writeAPI + "&" + field + "=" + String(value);
    
	// Start of TCP connection 
	espData("AT+CIPMUX=1", 1000, DEBUG);
    espData("AT+CIPSTART=0,\"TCP\",\"" + myHOST + "\"," + myPORT, 1000, DEBUG);
    espData("AT+CIPSEND=0," + String(sendData.length() + 4), 1000, DEBUG);
    espSerial.find(">");
    espSerial.println(sendData);
    Serial.println("Value to be sent: ");
    Serial.println(value);

	// Termination of TCP connection
    espData("AT+CIPCLOSE=0", 1000, true);
    delay(10000);
}

// Function for sending AT commands to the ESP-01
String espData(String command, const int timeout, boolean debug) 
{
    Serial.print("AT Command ==> ");
    Serial.println(command);

    response = "";
    espSerial.println(command);
    long int time = millis();
    while ((time + timeout) > millis()) 
    {
        while (espSerial.available()) 
        {
            char c = espSerial.read();
            response += c;
        }
    }
    if (debug) 
    {
       // Serial.print(response);
    }

    return response;
}
