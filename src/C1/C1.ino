#include <SoftwareSerial.h>       // Library for serial communication with ESP-01
SoftwareSerial espSerial(6, 7);   // Connection (Arduino RX: pin 6) to (ESP-01: TX pin)

#define DEBUG true

// WiFi and ThingSpeak settings
String mySSID = "linksys_1";
String myPWD = "";
String myHOST = "api.thingspeak.com";
String myPORT = "80";
String myWriteAPI = "6UKE7N1W16R0TIOC";
String myReadAPI = "MCX66QIC4S1OR75T"; // [NEW 1.] Read API of our ThingSpeak channel
String myCHANNEL = "2749755";

// Field names
String fieldRed = "field1";
String fieldOrange = "field2";
String fieldGreen = "field3";
String fieldAlert = "field8";

// Traffic light durations
int DELAY_RED = 30000;      // Delay for red light
int DELAY_ORANGE = 20000;   // Delay for orange light
int DELAY_GREEN = 30000;    // Delay for green light

String response;            // Response from the ESP8266
String sendData = "";       // Data to be sent
int sendVal;                // Value to be sent

String res_feeds = "";                  // [NEW 2.] Response from ThingSpeak
int ret_Len;                            // [NEW 3.] Length of the response
int pos;                                // [NEW 4.] Position of the field
unsigned int delayVal = 15000;          // [NEW 5.] Delay value
String messager;                        // [NEW 6.] Message to be sent
String x01;                             // [NEW 7.] Value of the alert field (field8)

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

/*
 *  Task Β : Send the value 0 to the field8 channel which controls the operation of the traffic light
 */
    Serial.println("************ Task B ************");
    
    setFieldValue(fieldAlert, myWriteAPI, 0);
    Serial.println("ALERT Field set to 0.");
    
    Serial.println("***************************************");

/*
 *  Task C.1: Read the value contained in the field8 channel which controls the operation of the traffic light
 */
    Serial.println("************ Task C.1 ************");
        
    x01 = getFieldValue(fieldAlert); // Read value of the field8 field
    Serial.println("Value of ALERT field:" +x01);

    if (x01.equals("1"))
    {
        Serial.println("ALERT: Traffic Light out of order, setting the ORANGE signal.");
        setTrafficLight("ORANGE");
    }
  
    Serial.println("***************************************");

    ret_Len = 0; 
    x01 = "";
    pos = 0;   
    res_feeds = "";
    delay(delayVal);
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

// [NEW 11.] Function to read the value of a field in ThingSpeak
String getFieldValue(String field) 
{
	// HTTP GET request for reading the feed of the channel
    messager = "GET /channels/" + myCHANNEL + "/feeds.json?api_key=" + myReadAPI + "&results=1";
    
	// Start of TCP connection
	espData("AT+CIPMUX=1", 1000, DEBUG);
    espData("AT+CIPSTART=0,\"TCP\",\"" + myHOST + "\"," + myPORT, 1000, DEBUG);
    espData("AT+CIPSTO=10", 1000, DEBUG);
    espData("AT+CIPSEND=0,"+ String(messager.length() + 4), 1000, DEBUG);
    espSerial.find(">"); 
    espSerial.println(messager);
    Serial.println("Starting to read...");
	
	// Termination of TCP connection
    espData("AT+CIPCLOSE=0", 1000, DEBUG);
    delay(1000);
	
	// Read the response of the GET request, so we can extract the value of field8 from the feeds.JSON of the channel
    Serial.println(response);
    ret_Len = response.length();
      
    pos = response.indexOf("[");
    res_feeds = response.substring(pos, ret_Len);
    Serial.print(res_feeds);
    pos = res_feeds.indexOf(field);

    return res_feeds.substring(pos+9, pos+10);
}

// Function to send AT commands to the ESP-01
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
