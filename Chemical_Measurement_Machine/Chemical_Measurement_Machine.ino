#define PUMP_RATE 100 //unit is mL/s
#define CTR_PIN 5 // Control the transistor to turn on/off the pump
#define Pump_Time(PUMP_RATE,pump_amount) ((pump_amount)/(PUMP_RATE))

int test_amount=20;//unit is mL
void setup() {
        Serial.begin(9600);
        pinMode(CTR_PIN, OUTPUT);
}

void loop() {
        static long int start_time=millis();
        if(millis()-start_time<Pump_Time(PUMP_RATE,test_amount)) {
                digitalWrite(CTR_PIN, HIGH);
                Serial.println("Still pumping");
        }
        else {
                digitalWrite(CTR_PIN, LOW);
                Serial.println("Stopped pumping");
                delay(1000);
        }
}
