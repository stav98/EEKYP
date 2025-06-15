//Κάνει software Reset τον AVR
void(* resetFunc)(void) = 0;

void ReadSensors()
 {
  //------------ Διάβασε τιμή 1ου Θερμομέτρου εδάφους ------------------------
  float new_Tground1 = ground_temp1.getTempCByIndex(0);
  if (new_Tground1 == -127) //Αν υπάρχει CRC Error
     {
      Serial.println(F("Failed to read from probe 1 !"));
      Tground1_str = "Err";
     }
  else
     {
      Tground1 = new_Tground1;
      Tground1_S += Tground1; //Άθροισμα για υπολογισμό MO κάθε 5 λεπτά
      if (Tground1 > max_Tground1)
          max_Tground1 = Tground1;
      Tground1_str = String(Tground1).substring(0,4);
      //Serial.println(Tground1_str); //Debug 
     }
  ground_temp1.requestTemperatures();

  //------------ Διάβασε τιμή 2ου Θερμομέτρου εδάφους ------------------------
  float new_Tground2 = ground_temp2.getTempCByIndex(0);
  if (new_Tground2 == -127) //Αν υπάρχει CRC Error
     {
      Serial.println(F("Failed to read from probe 2 !"));
      Tground2_str = "Err";
     }
  else
     {
      Tground2 = new_Tground2;
      Tground2_S += Tground2; //Άθροισμα για υπολογισμό MO κάθε 5 λεπτά
      if (Tground2 > max_Tground2)
          max_Tground2 = Tground2;
      Tground2_str = String(Tground2).substring(0,4);
      //Serial.println(Tground2_str); //Debug 
     }
  ground_temp2.requestTemperatures();
 }

 float fmap(unsigned int x, unsigned int min, unsigned int max, unsigned int o_min, unsigned int o_max)
 {
  //if (x < min) x = min;
  float y = (float)(x - min) * (o_max - o_min) / (float)(max - min) + o_min;
  if (min > max)
     {
      if (x < max) x = max;
      y = (float)(min - x) * (o_max - o_min) / (float)(min - max) + o_min;
     }
  return y;
 }