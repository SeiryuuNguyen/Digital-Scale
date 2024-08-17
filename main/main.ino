#include <HX711_ADC.h>
#include <LiquidCrystal_I2C.h>

const int HX711_dt = 2;
const int HX711_sck =3;
HX711_ADC LoadCell(HX711_dt ,HX711_sck);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() 
{
  lcd.init(); 
  lcd.backlight(); 
  lcd.setCursor(0, 0); 
  lcd.print("  DIGITAL SCALE "); 
  lcd.setCursor(0, 1);
  lcd.print("Waitting...");

  LoadCell.begin();    
  LoadCell.start(2000); 
  LoadCell.setCalFactor(1045.2672); 
  LoadCell.tare(); 
  
  lcd.setCursor(0, 1);
  lcd.print("Done");
}

void loop() 
{
  bool newDataReady;
  if(LoadCell.update())
  {
    newDataReady=true;
  }
  if(newDataReady == true)
  {
    if(millis()%500==0)
    {
      float weight = LoadCell.getData();
      lcd.setCursor(0, 1);
      lcd.print("WEIGHT(g):");
      lcd.print(weight);
      newDataReady = false;
    }
  }
}
