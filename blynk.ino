#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL3RBnqhWrG"
#define BLYNK_TEMPLATE_NAME "Parky"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>


// Auth Token from Blynk
char auth[] = "b1doNSAV-VxKPtMKKRVbGVH1f18TVWCi";

// Your WiFi credentials
// Set password to "" for open networks
char ssid[] = "Rizan's";
char pass[] = "RRRRRRRR";

SimpleTimer timer;

String myString; // Complete message from Arduino, which consists of sensor data
char rdata;      // Received characters

int firstVal, secondVal, thirdVal; // Sensors
int led1, led2, led3, led4, led5, led6;

// This function sends Arduino’s up time every second to Virtual Pin (1).
// In the app, Widget’s reading frequency should be set to PUSH. This means
// that you define how often to send data to the Blynk App.
void myTimerEvent() {
    // You can send any value at any time.
    // Please don’t send more than 10 values per second.
    Blynk.virtualWrite(V1, millis() / 1000);
}

void setup() {
    // Debug console
    Serial.begin(9600);

    // Connect to Blynk
    Blynk.begin(auth, ssid, pass);

    // Setup timers to send sensor values to Blynk
    timer.setInterval(1000L, sensorvalue1);
    timer.setInterval(1500L, sensorvalue2); // Staggered intervals
    timer.setInterval(2000L, sensorvalue3);
    timer.setInterval(2500L, sensorvalue4);
    
}

void loop() {
    if (Serial.available() == 0) {
        Blynk.run();
        timer.run(); // Initiates BlynkTimer
    }

    // Read data from Serial
    while (Serial.available() > 0) {
        rdata = Serial.read();
        myString += rdata; // Append the received character to the string

        // Check for newline character indicating end of message
        if (rdata == '\n') {
            Serial.println(myString);

            // Split the received string by commas
            String l = getValue(myString, ',', 0);
            String m = getValue(myString, ',', 1);
            String n = getValue(myString, ',', 2);
            String o = getValue(myString, ',', 3);
            String p = getValue(myString, ',', 4);
            String q = getValue(myString, ',', 5);

            // Convert string values to integers for LED statuses
            led1 = l.toInt();
            led2 = m.toInt();
            led3 = n.toInt();
            led4 = o.toInt();
            led5 = p.toInt();
            led6 = q.toInt();

            myString = ""; // Reset the string for the next message
        }
    }
}

void sensorvalue1() {
    int sdata = led1;
    Blynk.virtualWrite(V10, sdata);
}

void sensorvalue2() {
    int sdata = led2;
    Blynk.virtualWrite(V11, sdata);
}

void sensorvalue3() {
    int sdata = led3;
    Blynk.virtualWrite(V12, sdata);
}

void sensorvalue4() {
    int sdata = led4;
    Blynk.virtualWrite(V13, sdata);
}


// Function to split the incoming string by a separator
String getValue(String data, char separator, int index) {
    int found = 0;
    int strIndex[] = {0, -1};
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i + 1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
