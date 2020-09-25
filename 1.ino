//Libraries
#include <DallasTemperature.h>
#include <OneWire.h>
#include <Adafruit_NeoPixel.h>
#include <LiquidCrystal_I2C.h>

//Definitions
#if defined(ARDUINO) && ARDUINO >= 100
#define printByte(args)  write(args);
#else
#define printByte(args)  print(args,BYTE);
#endif

#define tempPin 7 

//Declarations
char mode = "C";
int tempVal = 20;
int tempC, tempF;

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
Adafruit_NeoPixel neopixel(8, 13, NEO_GRB + NEO_KHZ800);

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)

OneWire oneWire(tempPin);

 

// Pass our oneWire reference to Dallas Temperature. 

DallasTemperature sensors(&oneWire);

void pinDirs()
{
  pinMode(tempPin, OUTPUT);
 // pinMode();  
}

void setup()
{
  pinDirs();

  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
  
  neopixel.begin();
  sensors.begin();
  
  neopixel.clear();
  //String tempstr = String(tempVal);
  lcd.print("Loading...");
  for(int i=0; i<8; i++)
  {
    neopixel.setPixelColor(i,neopixel.Color(10*i*2,150,150));
    neopixel.show();
    delay(500);
  }
}

void loop()
{
  sensors.requestTemperatures(); 
  float t = sensors.getTempCByIndex(0);
  lcd.setCursor(0,1);
  Serial.println(t);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(t);
  lcd.print("C");
  lcd.setCursor(0,1);
  //lcd.print((value * 9)/5 + 32); //turning the celsius into fahrehait
  //lcd.print("F");
  delay(50);
}
