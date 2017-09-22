#define BIT(x) (0x01<<(x))//create bit mask
#define bit_set(reg, bit_mask) ((reg)|=(bit_mask))//set a bit to 1
#define bit_clear(reg, bit_mask) ((reg&=~(bit_mask)))//set a bit to 0

#define FULL_PUMP_RATE 10.0/9.3 //unit is mL/s, need to be calibrated for different functions of code
#define CTR_PIN_PUMP_1 2// Control the transistor to turn on/off the pump
#define CTR_PIN_PUMP_2 3
#define CTR_PIN_PUMP_3 4

//change the number below to change the pump amount
#define WATER_AMOUNT 25.0//unit is mL
#define THIOSULFATE_AMOUNT 10.0
#define ACID_AMOUNT 15.0

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
        DDRD=0x1C;// set 2,3,4 to output.
        PORTD=0x00;//turn off everything
        Serial.begin(115200);

        Pump1.initiate_pump(WATER_AMOUNT, CTR_PIN_PUMP_1);
        bit_set(PORTD,BIT(CTR_PIN_PUMP_1));
        Pump2.initiate_pump(THIOSULFATE_AMOUNT, CTR_PIN_PUMP_2);
        bit_set(PORTD,BIT(CTR_PIN_PUMP_2));
        Pump3.initiate_pump(ACID_AMOUNT, CTR_PIN_PUMP_3);
        bit_set(PORTD,BIT(CTR_PIN_PUMP_3));
}

void loop() {
        Pump1.check_pump();
        Pump2.check_pump();
        Pump3.check_pump();
}
