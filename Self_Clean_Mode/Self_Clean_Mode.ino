//used for cleaning the pump by pumping DI water through the system
#define CLEAN_TIME 20000//unit is ms

void setup() {
        CCR1A = 0x23;//configure the TCCR1A register on mode of operation and TOP
        TCCR1B = 0x19; //configure the TCCR1B register on mode of operation and TOP
        OCR1A = 639; // limit by 16 bits, determine the frequency of the output

        pinMode(CTR_PIN, OUTPUT); // enable the PWM output (you now have a PWM signal on digital pin 10)
        Serial.begin(9600);

}

void loop() {
        static long int start_time;
        if((millis()-start_time)<CLEAN_TIME) {
                OCR1B = 639; // the ratio of OCR1B/OCR1A will set duty cycle
        }
        else{
                digitalWrite(CTR_PIN, LOW);
                Serial.println("Done Cleaning");
                delay(1000);
        }


}
