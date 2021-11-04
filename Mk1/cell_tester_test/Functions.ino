void check_array(){
  
  if((time_current - time_prev) >= 57600){
   
   time_total += (time_current-time_prev);
   
   //update capacity variables
   mAh_vals[index] = charge_current*time_total*(60*60/1000);
   
   //Update voltage index 
   v_vals[index] = analogRead(vin_pin);  
    
   index++;
   time_prev = time_current;
  }
}

float get_voltage(){
  return float(((float(analogRead(vin_pin)))/1024)*5);
}

void charge(int x){
  digitalWrite(charge_pin,x);
}

void discharge(bool x){
  if(x == true){
    analogWrite(pwm_pin,pwm_val);  
  } else {
    analogWrite(pwm_pin,0);  
  }
}

void print_vals(){
  
  Serial.print("Current capacity drained: ");
  Serial.print(mAh_vals[index]);
  Serial.print("\n Current voltage is: ");
  //Serial.print((v_vals[index]/1024)*5);
  Serial.print(get_voltage());
  Serial.print("\n Current index: ");
  Serial.print(index);
  Serial.print("\n\n");
 
  }
