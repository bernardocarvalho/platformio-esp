#include <Arduino.h>
#include <WiFi.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 13
#define BUILTIN_LED 2
//const int ledPin = 2;

// WiFi credentials.
char * WIFI_SSID = "TP-LINK_EE791A";
const char * WIFI_PASS = "Margarida";

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

// arrays to hold device addresses
DeviceAddress insideThermometer, outsideThermometer;

void wifi_connect(void) {
	// Connect to Wifi.
	Serial.println();
	Serial.println();
	Serial.print("Connecting to ");
	Serial.println(WIFI_SSID);

	// Set WiFi to station mode and disconnect from an AP if it was previously connected
	//	WiFi.mode(WIFI_STA);
	//	WiFi.disconnect();
	delay(100);

	WiFi.begin(WIFI_SSID, WIFI_PASS);
	Serial.println("Connecting...");

	while (WiFi.status() != WL_CONNECTED) {
		// Check to see if connecting failed.
		// This is due to incorrect credentials
		if (WiFi.status() == WL_CONNECT_FAILED) {
			Serial.println("Failed to connect to WIFI. Please verify credentials: ");
			Serial.println();
			Serial.print("SSID: ");
			Serial.println(WIFI_SSID);
			Serial.print("Password: ");
			Serial.println(WIFI_PASS);
			Serial.println();
		}
		delay(2000);
	}

	Serial.println("");
	Serial.println("WiFi connected");
	Serial.println("IP address: ");
	Serial.println(WiFi.localIP());

	Serial.println("Hello World, I'm connected to the internets!!");
}


void setup()
{
	pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
	Serial.begin(115200);
	// Giving it a little time because the serial monitor doesn't
	// immediately attach. Want the firmware that's running to
	// appear on each upload.
	delay(5000);

	Serial.println();
	Serial.println("Running Firmware.");
	// Start up the library
	wifi_connect();
	sensors.begin();

	// locate devices on the bus
	Serial.print("Found ");
	Serial.print(sensors.getDeviceCount(), DEC);
	Serial.println(" devices.");
	//Serial.println("Hello World, I'm connected to the internets!!");
}

void loop()
{
	//    delay(2000);
	Serial.println("Hello World");
	digitalWrite (BUILTIN_LED, HIGH);	// turn on the LED
	delay(500);	// wait for half a second or 500 milliseconds
	digitalWrite (BUILTIN_LED, LOW);	// turn off the LED
	delay(500);	// wait for half a second or 500 milliseconds
}
