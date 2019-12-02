//  Variables
int PulseSensorPurplePin = 0;        // Pulse Sensor PURPLE WIRE connected to ANALOG PIN 0
int LED13 = 13;   //  The on-board Arduion LED

unsigned long beatRecordedatMs[4] = {0,0,0,0} ;
int Signal;                // holds the incoming raw data. Signal value can range from 0-1024
int Threshold = 450;            // Determine which Signal to "count as a beat", and which to ingore.
int wasBeat = 0;
// The SetUp Function:
void setup() {
  pinMode(LED13,OUTPUT);         // pin that will blink to your heartbeat!
   Serial.begin(9600);         // Set's up Serial Communication at certain speed.

}

// The Main Loop Function
void loop() {

  Signal = analogRead(PulseSensorPurplePin);  // Read the PulseSensor's value.
                                              // Assign this value to the "Signal" variable.

   //Serial.println(Signal);                    // Send the Signal value to Serial Plotter.


   if(Signal > Threshold){// If the signal is above "550", then "turn-on" Arduino's on-Board LED.
     digitalWrite(LED13,HIGH);
     wasBeat = 1;
   } else {
    if(wasBeat == 1)
    {
      beatRecordedatMs[3] = beatRecordedatMs[2] ;
      beatRecordedatMs[2] = beatRecordedatMs[1] ;
      beatRecordedatMs[1] = beatRecordedatMs[0] ;
      beatRecordedatMs[0] = millis() ;
      int elapsedTimeof4Pulses = beatRecordedatMs[0] - beatRecordedatMs[3] ;
      float pulseRateBeatsPerMinute =  60000 / ( elapsedTimeof4Pulses / 3.0 ) ;
      Serial.println(pulseRateBeatsPerMinute);
      wasBeat = 0;
    }
     digitalWrite(LED13,LOW);                //  Else, the sigal must be below "550", so "turn-off" this LED.
   }


delay(10);


}

