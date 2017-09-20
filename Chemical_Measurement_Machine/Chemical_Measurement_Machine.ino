#define BIT(x) (0x01<<(x))//create bit mask
#define bit_set(reg, bit_mask) ((reg)|=(bit_mask))//set a bit to 1
#define bit_clear(reg, bit_mask) ((reg&=~(bit_mask)))//set a bit to 0

#define FULL_PUMP_RATE 10.0/10.85 //unit is mL/s, need to be calibrated for different functions of code
#define CTR_PIN_PUMP_1 2// Control the transistor to turn on/off the pump
#define CTR_PIN_PUMP_2 3
#define CTR_PIN_PUMP_3 4

#define pump1_amount 25.0//unit is mL
#define pump2_amount 10.0
#define pump3_amount 15.0
//change the number below to change the pump amount
class Pump {
public:
float pump_amount;// amount to pump in mL
unsigned int pump_ID;//2,3, or 4


void initiate_pump(unsigned amount, unsigned pin_ID){
        start_time=millis();
        pump_amount=amount;
        pump_ID=pin_ID;
        pump_time=((pump_amount*1000.0)/(FULL_PUMP_RATE));
}
void check_pump(){
        (millis()-start_time<pump_time) ?  : bit_clear(PORTD,BIT(pump_ID));
}

private:
unsigned long start_time;
unsigned long pump_time;
};

Pump Pump1;
Pump Pump2;
Pump Pump3;

void setup() {
        DDRD=0x0E;// set 2,3,4 to output.
        PORTD=0x00;//turn off everything
        Serial.begin(115200);

        Pump1.initiate_pump(pump1_amount, CTR_PIN_PUMP_1);
        bit_set(PORTD,BIT(CTR_PIN_PUMP_1));
        Pump2.initiate_pump(pump2_amount, CTR_PIN_PUMP_2);
        bit_set(PORTD,BIT(CTR_PIN_PUMP_2));
        Pump3.initiate_pump(pump3_amount, CTR_PIN_PUMP_3);
        bit_set(PORTD,BIT(CTR_PIN_PUMP_3));
}

void loop() {
        Pump1.check_pump();
        Pump2.check_pump();
        Pump3.check_pump();
}
