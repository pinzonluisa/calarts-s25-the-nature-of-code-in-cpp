//  sensor.cpp
//  Reads and parses serial data from Adafruit Circuit Playground Bluefruit
//  Expected string format: "Sensor, x , y , a1 , a2 , a3 , a4 , end"

#include "sensor.hpp"

//--------------------------------------------------------------
sensor::sensor(){
	// Initialize all values to zero before any data arrives
	// In C++, uninitialized variables contain garbage values (whatever
	// was in that memory before) — always initialize explicitly
	//
	// Note: 0.0f vs 0.0
	// In C++, a plain decimal like 0.0 is a "double" by default —
	// a 64-bit high-precision number. A float is 32-bit.
	// Writing 0.0f tells the compiler explicitly: "this is a float, not a double"
	// Since x and y are declared as float, we match the type with 0.0f
	// For creative coding and graphics, float precision is always enough
	x  = 0.0f;
	y  = 0.0f;
	a1 = 0;
	a2 = 0;
	a3 = 0;
	a4 = 0;

	// Empty string to start — we haven't received any characters yet
	buffer = "";
}

//--------------------------------------------------------------
void sensor::setup(string portName, int baudRate){
	// Open the serial connection at the specified baud rate
	// Baud rate = communication speed in bits per second
	// Both sides must agree on the same rate or data comes out as gibberish
	// Our Circuit Playground Python code sends at 9600 — confirmed via TouchDesigner
	serial.setup(portName, baudRate);

	// ofLogNotice prints to the OF console so you can confirm the port opened
	ofLogNotice("sensor") << "Serial opened on " << portName << " at " << baudRate << " baud";
}

//--------------------------------------------------------------
void sensor::update(){
	// serial.available() returns how many bytes are waiting in the serial buffer
	// We loop and read everything that has arrived this frame — not just one byte
	// This is important: at 9600 baud, data trickles in slowly relative to your
	// frame rate, so we drain the whole buffer each frame
	while (serial.available() > 0) {

		// Read exactly one character from the serial port
		char c = serial.readByte();

		if (c == '\n') {
			// '\n' is the newline character — Python's print() always adds one at the end
			// When we see '\n' we know the buffer holds a complete message
			// Time to parse it!
			parseLine(buffer);
			buffer = ""; // Reset buffer for the next incoming line

		} else if (c != '\r') {
			// '\r' is a carriage return — some systems (Windows) send \r\n instead of just \n
			// We ignore '\r' and only keep real data characters
			// Everything else gets appended to the buffer
			buffer += c;
		}
	}
}

//--------------------------------------------------------------
void sensor::parseLine(string line){
	// ofSplitString cuts a string into pieces at every comma
	// Input:  "Sensor, 1.23 , -4.56 , 1 , 0 , 0 , 0 , end"
	// Result: ["Sensor", " 1.23 ", " -4.56 ", " 1 ", " 0 ", " 0 ", " 0 ", " end"]
	// Note the spaces around each value — we'll handle those with ofTrim below
	vector<string> parts = ofSplitString(line, ",");

	// Safety check — if fewer than 8 parts, the message is incomplete or corrupted
	// We just return and wait for the next good message
	// This mirrors the TouchDesigner check: if len(splitString) < 8: return
	if (parts.size() < 8) return;

	// ofTrim removes leading and trailing whitespace from a string
	// " Sensor " → "Sensor"    " end " → "end"
	// We need this because ofSplitString leaves spaces in from the original string
	string identifier = ofTrim(parts[0]);
	string verifier   = ofTrim(parts[7]);

	// Validate the message — must start with "Sensor" and end with "end"
	// If either check fails, we discard the message
	// This guards against partial reads, corrupted data, or random noise on the line
	// Same logic as TouchDesigner: if identifier == "Sensor" and verifier == "end"
	if (identifier != "Sensor" || verifier != "end") return;

	// ofToFloat converts a string to a float
	// Everything over serial is text — "1.23" is the characters '1' '.' '2' '3'
	// ofToFloat does the conversion so we can do math with it
	// ofTrim first removes any leftover whitespace before converting
	float rawX = ofToFloat(ofTrim(parts[1]));
	float rawY = ofToFloat(ofTrim(parts[2]));

	// ofToInt does the same but gives us an integer
	// Touch values are always 0 or 1 so int is the right type
	a1 = ofToInt(ofTrim(parts[3]));
	a2 = ofToInt(ofTrim(parts[4]));
	a3 = ofToInt(ofTrim(parts[5]));
	a4 = ofToInt(ofTrim(parts[6]));

	// --- Low-pass filter + Quantization ---
	// Two-stage noise reduction for the accelerometer:
	//
	// Stage 1 — Low-pass filter
	// Blends the new reading with the previous value to smooth out jitter
	// Formula: filtered = alpha * newValue + (1 - alpha) * oldValue
	//
	// alpha controls the smoothing strength:
	//   0.01f → extremely smooth, very slow to respond
	//   0.1f  → smooth, good starting point
	//   0.5f  → faster response, less smoothing
	//   0.9f  → barely filtered, nearly raw data
	float alpha = 0.1f;
	float filteredX = alpha * rawX + (1.0f - alpha) * x;
	float filteredY = alpha * rawY + (1.0f - alpha) * y;

	// Stage 2 — Quantization
	// Snaps the filtered value to the nearest multiple of step
	// This eliminates the tiny in-between jitter that survives the low-pass
	// With step = 0.2f: 1.23 → 1.2, 0.91 → 1.0, -3.67 → -3.6
	// Larger step = chunkier/more stepped movement
	// Smaller step = finer resolution
	float step = 0.2f;
	x = round(filteredX / step) * step;
	y = round(filteredY / step) * step;
}
