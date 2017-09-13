#define FULL_PUMP_RATE 10.0/10.85 //unit is mL/s, need to be calibrated for different functions of code
#define CTR_PIN 10 // Control the transistor to turn on/off the pump
#define Pump_Time(pump_amount) ((pump_amount*1000.0)/(FULL_PUMP_RATE))
/*Alternate formula:
 #define SLOW_VOLUME //The percent of the total required volume that the pump will pump at slower rate to get more accuracy
 #define REDUCED_PUMP_RATE 50 //unit is mL/s
 #define Pump_Time(pump_amount,SLOW_VOLUME) ((1.0-SLOW_VOLUME/100.0)*(pump_amount)/(FULL_PUMP_RATE) + (SLOW_VOLUME/100.0)*pump_amount/(REDUCED_PUMP_RATE))
 */
float test_amount=9.0;//unit is mL

void setup() {
        TCCR1A = 0x23;//configure the TCCR1A register on mode of operation and TOP
        TCCR1B = 0x19; //configure the TCCR1B register on mode of operation and TOP
        OCR1A = 639; // limit by 16 bits, determine the frequency of the output

        pinMode(CTR_PIN, OUTPUT); // enable the PWM output (you now have a PWM signal on digital pin 10)
        //digitalWrite(CTR_PIN, LOW);
        Serial.begin(9600);
}

void loop() {
        static long int start_time=millis();
        static double pump_duration=Pump_Time(test_amount);
        if((millis()-start_time)<pump_duration) {
                OCR1B = 639; // the ratio of OCR1B/OCR1A will set duty cycle
                Serial.println(pump_duration);
                //digitalWrite(CTR_PIN, HIGH);
        }
        else {
                OCR1B = 0;//actually stopped the pumping
                Serial.println("Stopped pumping");
                delay(1000);
        }
}
