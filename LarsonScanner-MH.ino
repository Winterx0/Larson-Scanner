/*
I followed this tutorial and made some adjustments to the pins in order to get my design working properly.
I ran into issues with the original source code so I deleted some original parameters. 
I was also having some issues with the clockpin as when it is plugged into the arduino UNO the simulation stoped.
I changed the pin location on the arduino and it corrected this problem.
Overall the tutorial was a success to getting this project built. I will upload the schematic design that I found to work.
https://www.instructables.com/DIY-Larson-Scanner/
*/
int datapin = 13;
int clockpin = 8;
int latchpin = 12;
// We'll also declare a global variable for the data we're
// sending to the shift register:
byte data = 0;
void setup()
{
  // Set the three SPI pins to be outputs:
  pinMode(datapin, OUTPUT);
  pinMode(clockpin, OUTPUT);  
  pinMode(latchpin, OUTPUT);
}
void loop()
{
  int index;
  int delayTime = 100; // time (milliseconds) to pause between LEDs
                       // make this smaller for faster switching
  // step through the LEDs, from 0 to 7
  for(index = 0; index <= 7; index++)
  {
    shiftWrite(index, HIGH);    // turn LED on
    delay(delayTime);       // pause to slow down the sequence
    shiftWrite(index, LOW); // turn LED off
  }
  // step through the LEDs, from 7 to 0
  for(index = 7; index >= 0; index--)
  {
    shiftWrite(index, HIGH);    // turn LED on
    delay(delayTime);       // pause to slow down the sequence
    shiftWrite(index, LOW); // turn LED off
  }
  
}
void shiftWrite(int desiredPin, boolean desiredState)
{
  // First we'll alter the global variable "data," changing the
  // desired bit to 1 or 0:
  bitWrite(data,desiredPin,desiredState);
  // Now we'll actually send that data to the shift register.
  // The shiftOut() function does all the hard work of
  // manipulating the data and clock pins to move the data
  // into the shift register:
  shiftOut(datapin, clockpin, MSBFIRST, data);
  // Once the data is in the shift register, we still need to
  // make it appear at the outputs. We'll toggle the state of
  // the latchPin, which will signal the shift register to "latch"
  // the data to the outputs. (Latch activates on the high-to
  // -low transition).
  digitalWrite(latchpin, HIGH);
  digitalWrite(latchpin, LOW);
}
