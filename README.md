How to scare trick or treaters with a delayed evil laugh when the door is opened. 

**Items required**
 
* Arduino uno 
* Alarm surface door reed contact sensor 
* 1 x 10K Resistor 
* set of speakers 

**Source code**
[https://github.com/catchcoder/arduino](https://github.com/catchcoder/arduino)

**Connecting it all together**

 1.  Connect the door contact to pin 2 and 5v 
 2. Connect the 10k resistor connected to pin 2 and the other her end to ground 
 3. Connect the speakers (mono) to pin 11 and ground 

**Extra software required:** 

[Sox](http://sox.sourceforge.net) or [Audacity](http://audacity.sourceforge.net/): to convert MP3 to wav 8bit 

You will need to convert the audio file to a wav file first then convert it to 8bit file. Example of using sox to convert a wav file to 8bit wav:    `sox audiodump.wav -c 1 -r 8000 -u -b evillaugh.wav` 

Next we need to convert the 8bit wav file to *c* code. This done by using [Wav2c](https://github.com/olleolleolle/wav2c). Once the audio file converted to *c* replace the code at the bottom of the code arduino source code.

