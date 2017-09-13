#define FULL_PUMP_RATE 100 //unit is mL/s
#define CTR_PIN 10 // Control the transistor to turn on/off the pump
#define Pump_Time(pump_amount) ((pump_amount)/(FULL_PUMP_RATE))
/*Alternate formula:
 #define SLOW_VOLUME //The percent of the total required volume that the pump will pump at slower rate to get more accuracy
 #define REDUCED_PUMP_RATE 50 //unit is mL/s
 #define Pump_Time(pump_amount,SLOW_VOLUME) ((1.0-SLOW_VOLUME/100.0)*(pump_amount)/(FULL_PUMP_RATE) + (SLOW_VOLUME/100.0)*pump_amount/(REDUCED_PUMP_RATE))
 */
int test_amount=20.0;//unit is mL

void setup() {
        TCCR1A = 0x23;//configure the TCCR1A register on mode of operation and TOP
        TCCR1B = 0x19; //configure the TCCR1B register on mode of operation and TOP
        OCR1A = 639; // limit by 16 bits, determine the frequency of the output

        pinMode(CTR_PIN, OUTPUT); // enable the PWM output (you now have a PWM signal on digital pin 10)
        Serial.begin(9600);
}

void loop() {
        static long int start_time=millis();
        if((millis()-start_time)<Pump_Time(test_amount)) {
                OCR1B = 639; // the ratio of OCR1B/OCR1A will set duty cycle
        }
        else {
                digitalWrite(CTR_PIN, LOW);
                Serial.println("Stopped pumping");
                delay(1000);
        }
}
