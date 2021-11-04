


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// ARDUINO BATTERY CAPACITY TESTER
//Version-2.0
//by deba168,INDIA // The code is taken from Hesam Moshiri ( https://www.pcbway.com/blog/technology/Battery_capacity_measurement_using_Arduino.html )
//Dated : 20/10/2019
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

const float Low_BAT_level = 3.0;
//Current steps with a 3R load (R7)
const int Current [] = {0,110,210,300,390,490,580,680,770,870,960,1000};
const byte PWM_Pin = 9;
const int BAT_Pin = A0;
int PWM_Value = 0;
unsigned long Capacity = 0;
int ADC_Value = 0;
float Vcc = 5.04 ; // Voltage of Arduino 5V pin ( Mesured by Multimeter )
float BAT_Voltage = 0;
float sample =0;
byte Hour = 0, Minute = 0, Second = 0;
bool calc = false, Done = false;

void setup () {
//
Serial.begin(9600);
pinMode(PWM_Pin, OUTPUT);
analogWrite(PWM_Pin, PWM_Value);

Serial.print("Open Green Energy");
Serial.print("\n");
delay(2000);
}

//************************* End of Setup function *******************************

void loop() {

  timerInterrupt(); 

}

//************************* End of Loop function *******************************

void timerInterrupt(){
  PWM_Value = 0;
  analogWrite(PWM_Pin,PWM_Value);
  calc = true;
  while (Done == false)  {
     Second ++;
    if (Second == 60)  {
      Second = 0;
      Minute ++;      
    }
    if (Minute == 60)  {
      Minute = 0;
      Hour ++;
    }

 //************ Measuring Battery Voltage ***********
  
  for(int i=0;i< 100;i++)
  {
   Serial.print("\n"); 
   Serial.print(analogRead(BAT_Pin));
   Serial.print("\n");
   sample=sample+float(analogRead(BAT_Pin)); //read the Battery voltage 
   delay (2);
  }
  sample=sample/100; 
  BAT_Voltage = sample * Vcc/ 1024.0; 
 
  //*********************************************

    
    Serial.print(String(Hour) + ":" + String(Minute) + ":" + String(Second));
    Serial.print("\n");
    Serial.print("Disch Curr: ");   
    Serial.print("\n");
    Serial.print(String(Current[PWM_Value / 5])+"mA");
    Serial.print("\n");
    Serial.print("Bat Volt:" + String(BAT_Voltage)+"V" );
    Serial.print("\n");



    Capacity =  (Hour * 3600) + (Minute * 60) + Second;
    Capacity = (Capacity * Current[PWM_Value / 5]) / 3600;
    Serial.print("Capacity:" + String(Capacity) + "mAh");
    Serial.print("\n");

    
    if (BAT_Voltage < Low_BAT_level)
    {
      Capacity =  (Hour * 3600) + (Minute * 60) + Second;
      Capacity = (Capacity * Current[PWM_Value / 5]) / 3600;
    
      Serial.print("Capacity:");
      Serial.print("\n");
      Serial.print(String(Capacity) + "mAh");
      Serial.print("\n");
      Done = true;
      PWM_Value = 0;
      analogWrite(PWM_Pin, PWM_Value);
    }
      delay(1000);
  } 
   
}




  






  
