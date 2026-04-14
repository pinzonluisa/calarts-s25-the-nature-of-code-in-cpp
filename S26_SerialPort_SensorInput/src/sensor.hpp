//  sensor.hpp
//  Reads and parses serial data from Adafruit Circuit Playground Bluefruit
//  Expected string format: "Sensor, x , y , a1 , a2 , a3 , a4 , end"
//
//  This class is designed to be reusable — it just reads and stores sensor values.
//  Any mapping, scaling, or application logic belongs in ofApp, not here.

#pragma once
#include "ofMain.h"

class sensor {
public:
	sensor();

	// Opens the serial port
	// portName: e.g. "/dev/tty.usbmodem2101" on Mac, "COM3" on Windows
	// baudRate: must match what the Circuit Playground is sending at — 9600 in our case
	// To find your port: run "ls /dev/tty.*" in Terminal before and after plugging in
	void setup(string portName, int baudRate = 9600);

	// Call this every frame in ofApp::update()
	// Reads incoming bytes and parses complete lines
	void update();

	// Accelerometer values in m/s²
	// Range is roughly -9.8 to 9.8 (gravity)
	// These are smoothed with a low-pass filter inside parseLine()
	float x;
	float y;

	// Capacitive touch values — either 0 (not touched) or 1 (touched)
	int a1;
	int a2;
	int a3;
	int a4;

private:
	ofSerial serial;

	// Accumulates incoming characters until a full line is received
	// Serial data arrives one character at a time — the buffer holds them
	// until we see '\n' which marks the end of a complete message
	string buffer;

	// Called internally when a complete line is in the buffer
	void parseLine(string line);
};
