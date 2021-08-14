# Artekit WaveTooEasy - Library for Arduino

This is a library for interfacing your Arduino with a [*WaveTooEasy* board](https://www.artekit.eu/products/devboards/wavetooeasy/) using serial communication.

[![](https://www.artekit.eu/resources/doc/wavetooeasy/wavetooeasy-manual.jpg)](https://www.artekit.eu/products/devboards/wavetooeasy/)

## Installation

Download the zip file from this page (green button at upper-right corner) and copy it into your libraries folder, or click on the *Sketch* menu in the Arduino IDE, then *Include Library* and *Add .ZIP Library*. Select the ZIP file you have downloaded.

## Connections

Refer to the [WaveTooEasy manual](https://www.artekit.eu/doc/guides/wavetooeasy/) for instructions on how to connect the WaveTooEasy to an Arduino using the Serial port.

## Usage

1) Add the `WaveTooEasy.h` file to you sketch, like this:

    ```cpp
    #include <WaveTooEasy.h>
    ```

2) Instantiate an Artekit_WaveTooEasy class. Optionally you can specify the Serial port you want to use, for example `Serial`, `Serial2`, etc., and the baudrate if different from 115200 (the default baudrate).

    ```cpp
    Artekit_WaveTooEasy WaveTooEasy();
    ```

    Example specifying Serial object and baudrate:

    ```cpp
    Artekit_WaveTooEasy WaveTooEasy(Serial1, 57600);
    ```

3) In your `setup()` function, call `begin()`.

    ```cpp
    void setup()
    {
        // Initialization
        WaveTooEasy.begin();
    }
    ```

4) After calling `begin()`, you can use any of the WaveTooEasy functions to play audio:

    ```cpp
    void setup()
    {
        // Initialization
        WaveTooEasy.begin();

        // Play a WAV file on channel 5
        WaveTooEasy.playFile("my_audio_file.wav", 5, PLAY_MODE_NORMAL);
    }

    void loop()
    {
        // Play beep on channel 2 every second
        WaveTooEasy.playFile("beep.wav", 2, PLAY_MODE_NORMAL);
        delay(1000);
    }
    ```

## Functions

### `uint8_t hello()`

Use this function to poll for a connected *WaveTooEasy* board. Useful to check if the communication is working as it should.

---

### `uint8_t getVersion(uint8_t* major, uint8_t* minor, uint8_t* fix)`

Asks for the *WaveTooEasy* software version.

#### Parameters

`major`, `minor` and `fix` are three pointers to numbers representing the *WaveToEasy* version in [Semantic Versioning 2.0.0](https://semver.org/) format.

#### Example

```cpp
uint8_t major, minor, fix;

WaveTooEasy.getVersion(&major, &minor, &fix);
```

---

### `uint8_t playFile(char* file, uint8_t channel, uint8_t mode)`

Plays a file on a give channel.

#### Parameters

`file` is a null-terminated string containing the full path of the file to play.

`channel` is the channel number (from 1 to 10).

`mode` can be `PLAY_MODE_NORMAL` for normal playback or `PLAY_MODE_LOOP` for looped playback.

#### Example

```cpp
// Play beep.wav on channel 2
WaveTooEasy.playFile("beep.wav", 2, PLAY_MODE_NORMAL);
```

---

### `uint8_t playChannel(uint8_t channel, uint8_t mode)`

Plays the file that corresponds to a given channel. This channel<->file mapping is configured in the configuration file. Refer to [WaveTooEasy documentation] to learn how to map a file to a channel. In case there is no file mapped to a channel, *WaveTooEasy* will try to play the `[channel].wav` file, where `channel` is the number you provide to this function.

#### Parameters

`channel` is the channel number (from 1 to 10).

`mode` can be `PLAY_MODE_NORMAL` for normal playback or `PLAY_MODE_LOOP` for looped playback.

#### Example

```cpp
// Play whatever file is mapped to channel 1
WaveTooEasy.playChannel(1, PLAY_MODE_NORMAL);
```

---

### `uint8_t stopChannel(uint8_t channel)`

Stops the playback on a given chanel.

#### Parameters

`channel` is the channel number (from 1 to 10).

#### Example

```cpp
// Stop playback on channel 1
WaveTooEasy.stopChannel(1);
```

---

### `uint8_t stopAll()`

Stops the playback on all the channels.

#### Example

```cpp
WaveTooEasy.stopAll();
```

---

### `uint8_t pauseChannel(uint8_t channel)`

Pauses the playback on a given channel.

#### Parameters

`channel` is the channel number (from 1 to 10).

#### Example

```cpp
// Play beep.wav on channel 2
WaveTooEasy.playFile("beep.wav", 2, PLAY_MODE_NORMAL);

// Wait one second
delay(1000);

// Pause playback of channel 2
WaveTooEasy.pauseChannel(2);
```

---

### `uint8_t pauseAll()`

Pauses the playback on all the channels.

#### Example

```cpp
// Play beep.wav on channel 2
WaveTooEasy.playFile("beep.wav", 2, PLAY_MODE_NORMAL);

// Play music.wav on channel 3
WaveTooEasy.playFile("music.wav", 3, PLAY_MODE_LOOP);

// Wait one second
delay(1000);

// Pause all
WaveTooEasy.pauseAll();
```

---

### `uint8_t resumeChannel(uint8_t channel)`

Resumes a paused channel.

#### Parameters

`channel` is the channel number (from 1 to 10).

#### Example

```cpp
// Play beep.wav on channel 2
WaveTooEasy.playFile("beep.wav", 2, PLAY_MODE_NORMAL);

// Wait one second
delay(1000);

// Pause playback of channel 2
WaveTooEasy.pauseChannel(2);

// Wait one second
delay(1000);

// Resume playback on channel 2
WaveTooEasy.resumeChannel(2);
```

---

### `uint8_t resumeAll()`

Resumes all the channels that were put in pause with the `pauseChannel()` or the `pauseAll()` functions.

#### Example

```cpp
// Play beep.wav on channel 2
WaveTooEasy.playFile("beep.wav", 2, PLAY_MODE_NORMAL);

// Play music.wav on channel 3
WaveTooEasy.playFile("music.wav", 3, PLAY_MODE_LOOP);

// Wait one second
delay(1000);

// Pause all
WaveTooEasy.pauseAll();

// Wait one second
delay(1000);

// Resume all
WaveTooEasy.resumeAll();
```

---

### `uint8_t getAllChannelsStatus(WTE_CHANNELS_STATUS* channels)`

Retrieve the status code for all the channels.

#### Parameters

`channels` is a pointer to an struct of type `WTE_CHANNELS_STATUS`, defined in the following way:

```cpp
typedef struct wteChannelsStatus
{
	uint8_t channel1;
	uint8_t channel2;
	uint8_t channel3;
	uint8_t channel4;
	uint8_t channel5;
	uint8_t channel6;
	uint8_t channel7;
	uint8_t channel8;
	uint8_t channel9;
	uint8_t channel10;
} WTE_CHANNELS_STATUS;
```

#### Example

```cpp
WTE_CHANNELS_STATUS status;

// Retrieve the status code for all the channels
WaveTooEasy.getAllChannelsStatus(&status);

// Check if channel 5 AND 6 are playing a file, otherwise make
// them play their corresponding WAV files.
if (status.channel5 == STATUS_STOPPED && status.channel6 == STATUS_STOPPED)
{
    WaveTooEasy.playChannel(5, PLAY_MODE_NORMAL);
    WaveTooEasy.playChannel(6, PLAY_MODE_NORMAL);
}
```

---

### `uint8_t getChannelStatus(uint8_t channel, uint8_t* status)`

Retrieves the status code for a given channel.

#### Parameters

`channel` is the channel number (from 1 to 10).

`status` is a pointer to the status code.

#### Example

```cpp
uint8_t status;

// Retrieve the status code for channel 7
WaveTooEasy.getChannelStatus(7, &status);

// Check if channel 7 is paused. If so, resume it.
if (status == STATUS_PAUSED)
    WaveTooEasy.resumeChannel(7);
```

---

### `uint8_t getChannelVolume(uint8_t channel, float* volume)`

Gets the base volume for a given channel.

#### Parameters

`channel` is the channel number (from 1 to 10).

`volume` is a pointer a floating point variable that will receive the volume value. It's a floating point value between 0 and 2. 0 it's the lowest value and means no audio output. 1 is the default volume.

#### Example

```cpp
float volume;

// Retrieve the volume of channel 2
WaveTooEasy.getChannelVolume(2, &volume);
```

---

### `uint8_t setChannelVolume(uint8_t channel, float volume)`

Sets the volume of a given channel.

#### Parameters

`channel` is the channel number (from 1 to 10).

`volume` It's a floating point value greater or equal than 0. 0 it's the lowest value and means no audio output. 1 is the default volume.

#### Example

```cpp
// Set the channel 1 volume to the half (0.5)
WaveTooEasy.setChannelVolume(1, 0.5f);
```

---

### `uint8_t setSpeakersVolume(float volume)`

Sets the volume of the speakers.

#### Parameters

`volume` is a floating point number representing the speakers volume in dB, ranging from -53 dB up to 24 dB. The default value is 0.

You can use any dB value, but know that the *WaveToEasy* amplifier (the Texas Instruments LM49450) can only accept a predefined set of values for the speakers. In case you want to know, these values are:

`
-53, -42, -34.5, -28.5, -24, -21, -18, -15, -12, -9, -7.5, -6, -4.5, -3, -1.5, 0, 1.5, 3, 4.5, 6, 7.5, 9, 10.5, 12, 13.5, 15, 16.5, 18, 19.5, 21, 22.5, 24
`

*WaveTooEasy* will pick the next lower available value. This means that if you pass 5dB to this function, the resulting volume would be 4.5dB.

#### Example

```cpp
// Set the speakers volume to -3 dB
WaveTooEasy.setSpeakersVolume(-3.0f);
```

---

### `uint8_t setHeadphoneVolume(float volume)`

Set the volume of the headphone output.

#### Parameters

`volume` is a floating point number representing the headphone volume in dB, ranging from -59 dB up to 18 dB. The default value is 0.

You can use any dB value, but know that the *WaveToEasy* amplifier (the Texas Instruments LM49450) can only accept a predefined set of values for the headphone. In case you want to know, these values are:

`
-59, -48, -40.5, -34.5, -30, -27, -24, -21, -18, -15, -13.5, -12, -10.5, -9, -7.5, -6, -4.5, -3, -1.5, 0, 1.5, 3, 4.5, 6, 7.5, 9, 10.5, 12, 13.5, 15, 16.5, 18
`

*WaveTooEasy* will pick the next lower available value. This means that if you pass 5dB to this function, the resulting volume would be 4.5dB.

#### Example

```cpp
// Set the headphone volume to -3 dB
WaveTooEasy.setHeadphoneVolume(-3.0f);
```

---

### `uint8_t getSpeakersVolume(float* volume)`

Retrieves the current volume of the speakers.

#### Parameters

`volume` is a pointer to a floating point number that will receive the current speakers volume.

#### Example

```cpp
float volume;

// Get the speakers volume
WaveTooEasy.getSpeakersVolume(&volume);
```

---

### `uint8_t getHeadphoneVolume(float* volume)`

Retrieves the current headphone volume.

#### Parameters

`volume` is a pointer to a floating point number that will receive the current headphone volume.

#### Example

```cpp
float volume;

// Get the headphone volume
WaveTooEasy.getHeadphoneVolume(&volume);
```

## Status codes

These are the status codes returned by the `getAllChannelsStatus()` and `getChannelStatus()` functions:

* `STATUS_STOPPED`
* `STATUS_PLAYING`
* `STATUS_PAUSED`

## Error codes

All the function returns `ERROR_NONE` on success. Otherwise it returns an error code like the following:

* `ERROR_PLAYING`: the file cannot be found, or cannot be played because an error occurred (for example, the WAV file has a sampling rate different than the one in the configuration file).

* `ERROR_INVALID_FILE_LENGTH`: the filename passed to the `playFile()` function is too long.

* `ERROR_INVALID_CHANNEL`: the channel number is invalid.

* `ERROR_INVALID_MODE`: the playback mode used in the `playFile()` or `playChannel()` function is invalid.

* `ERROR_NOT_PAUSED`: returned when `pauseChannel()` is called on an already paused channel.

* `ERROR_NOT_PLAYING`: returned when `pauseChannel()` and `stopChannel()` are called on a channel that is not currently playing.

* `ERROR_PARAM`: there is an error with some or all of the parameters supplied.

* `ERROR_RX_TIMEOUT`: *WaveTooEasy* is not responding to commands.
