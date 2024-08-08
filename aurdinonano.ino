#include <SoftwareSerial.h>

// Initialize SoftwareSerial on pins 2 and 3
SoftwareSerial nodemcu(2, 3);

// Define sensor pins for the four parking slots
int parking_slot1_ir_s = 10;
int parking_slot2_ir_s = 11;
int parking_slot3_ir_s = 12;
int parking_slot4_ir_s = 13;

// Variables to store sensor readings
String sensor1;
String sensor2;
String sensor3;
String sensor4;

// Variable to accumulate the sensor data
String cdata = ""; 

void setup()
{
    Serial.begin(9600);      // Initialize serial communication with PC
    nodemcu.begin(9600);     // Initialize serial communication with NodeMCU

    // Set pin modes for the parking slot sensors
    pinMode(parking_slot1_ir_s, INPUT);
    pinMode(parking_slot2_ir_s, INPUT);
    pinMode(parking_slot3_ir_s, INPUT);
    pinMode(parking_slot4_ir_s, INPUT);
}

void loop()
{
    // Read and process each parking slot sensor
    readSlot(parking_slot1_ir_s, sensor1);
    readSlot(parking_slot2_ir_s, sensor2);
    readSlot(parking_slot3_ir_s, sensor3);
    readSlot(parking_slot4_ir_s, sensor4);

    // Concatenate sensor data and send it via Serial and SoftwareSerial
    cdata = sensor1 + "," + sensor2 + "," + sensor3 + "," + sensor4 + ","; // Add a trailing comma for delimiter
    Serial.println(cdata);
    nodemcu.println(cdata);

    // Wait for 6 seconds before the next reading
    delay(6000);
    
    // Clear the data string for the next cycle
    cdata = "";
}

// Function to read a parking slot
void readSlot(int pin, String &sensor)
{
    if (digitalRead(pin) == LOW)
    {
        sensor = "255";  // Sensor detected
    }
    else
    {
        sensor = "0";    // Sensor not detected
    }
    delay(200); // Debounce delay
}
