#include <AltSoftSerial.h>
#include <WaveTooEasy.h>

// We use AltSoftSerial to emulate a serial port on pins 8 and 9
// because we want to use Arduino UNO serial port on USB to show
// some messages.
AltSoftSerial altSerial; // RX 8 - TX 9

// Initialize Artekit WaveTooEasy class, and we tell it to use
// altSerial to communicate with the WaveTooEasy board.
Artekit_WaveTooEasy WaveTooEasy(altSerial);

// This function plays a file on a given channel (from 1 to 10).
// It returns true on success or false on failure, and it prints
// a message.
bool playFile(char* file, uint8_t channel)
{
    if (channel > 10)
    {
        Serial.println("Wrong channel number");
        return false;
    }

    // Play the 'file' audio file on a given 'channel'
    if (!WaveTooEasy.playFile(file, channel, 0))
    {
        Serial.print("Error playing file ");
        Serial.println(file);
        return false;
    } else {
        Serial.print("Playing file ");
        Serial.println(file);
    }

    return true;
}

void setup() {

    // Initialize the altSerial
    altSerial.begin(9600);

    // Initialize Serial for printing messages
    Serial.begin(9600);

    // Initialize the WaveTooEasy library
    WaveTooEasy.begin();

    Serial.println("Started");
    
    if (WaveTooEasy.hello())
    {
        playFile("1.wav", 1);
        playFile("2.wav", 2);
        playFile("3.wav", 3);
        playFile("4.wav", 4);
        playFile("5.wav", 5);
        playFile("6.wav", 6);
        playFile("7.wav", 7);
        playFile("8.wav", 8);
        playFile("9.wav", 9);
        playFile("10.wav", 10);
    } else {
         Serial.println("WaveTooEasy is not responding");
    }
}

void loop() {

}
