//used for cleaning the pump by pumping DI water through the system
#define CLEAN_TIME 12000//unit is ms
#define CTR_PIN 10

void setup() {
        TCCR1A = 0x23;//configure the TCCR1A register on mode of operation and TOP
        TCCR1B = 0x19; //configure the TCCR1B register on mode of operation and TOP
        OCR1A = 639; // limit by 16 bits, determine the frequency of the output
        OCR1B = 0;//Ratio of OCR1B/OCR1A will determine duty cycle, 0 means off
        pinMode(CTR_PIN, OUTPUT); // enable the PWM output (you now have a PWM signal on digital pin 10)
        Serial.begin(9600);

}

void loop() {
        static long int start_time=millis();
        if((millis()-start_time)<CLEAN_TIME) {
                OCR1B = 639; // 100% duty cycle
        }
        else{
                OCR1B = 0;
                Serial.println("Done Cleaning");

        }


}
