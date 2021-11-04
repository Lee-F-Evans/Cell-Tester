#define pwm_pin 9
#define vin_pin 6
#define charge_pin 7

// enter charge current in mA
#define charge_current 500

// Value used to set the PWM output for a resistance of 0.65ohm
int pwm_val = ((float(charge_current)/1000)*0.7/5)*255;

// Arrays used to hold charge and discharge data
byte v_vals[500];
int mAh_vals[500];

// Index used to track the filling of above arrays
int index = 0;

// Variables to track the total time of charging
int time_prev = 0;
int time_current = 0;
int time_total = 0;

byte temp_state = 0;


void setup() {
//Setup inputs and outputs
pinMode(pwm_pin,OUTPUT);
pinMode(charge_pin,OUTPUT);
pinMode(vin_pin, INPUT);

//Print some stats before starting
Serial.begin(115200);
Serial.print("Discharge current set to:");
Serial.print(charge_current);
Serial.print("\nBattery voltage at:");
Serial.print(get_voltage());
Serial.print("\n--------------------\n");

//Set device to neutral state
digitalWrite(charge_pin,LOW);
analogWrite(pwm_pin,0);

//temp delay to give time to bail on boot
delay(5000);
}

void loop() {
  print_vals();

    Serial.print("\n **DISCHARGING**\n");
    time_current = millis();
    check_array();
    //discharge(true);
    delay(3000);
    charge(HIGH);
}



void store(){
  if(get_voltage()<= 3.6 && temp_state == 0){
    charge(HIGH);
    Serial.print("\n**CHARGING**\n");
  }else if(get_voltage()>= 3.55 && temp_state == 0){
    temp_state = 1;
    charge(LOW);
    
    memset(v_vals,0,sizeof(v_vals));
    memset(mAh_vals,0,sizeof(mAh_vals));
    
    delay(3000);
  }else if(get_voltage() >= 2.8 && temp_state == 1){
    Serial.print("\n **DISCHARGING**\n");
    time_current = millis();
    check_array();
    discharge(true);
  }else if(get_voltage()<= 3.0 && temp_state == 1){
    temp_state = 0;
    discharge(false);
    delay(3000);
  }  
  
}
