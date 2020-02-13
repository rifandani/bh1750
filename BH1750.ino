/*
 * Pencahayaan (lux)  |   Permukaan diterangi oleh
 * 0.0001             |   Malam tanpa bulan, langit mendung saat malam (Bintang)
 * 0.002              |   Langit malam tanpa bulan yang cerah dengan pijaran udara
 * 0.05–0.36          |   Bulan purnama di langit malam yang cerah
 * 3.4                |   Batas antara kegelapan saat senja di pemukiman di bawah langit yang cerah
 * 20-50              |   Tempat umum, dengan lingkungan yang gelap
 * 50                 |   Penerangan ruang tamu keluarga (Australia, 1998)
 * 80                 |   Gedung kantor lorong/Toilet pencahayaan
 * 100                |   Mendung yang sangat gelap di malam hari
 * 320-500            |   Penerangan kantor
 * 400                |   Matahari Terbit atau matahari terbenam pada hari yang cerah.
 * 1000               |   Hari mendung; Pencahayaan di TV studio
 * 10,000–25,000      |   Siang hari (tidak terkena matahari langsung)
 * 32,000–100,000     |   Terik Sinar matahari langsung
*/

#define _TOOLOW                       25
#define _LOW                          50
#define _HIGH                         500
#define _TOOHIGH                      750
#define LEVEL_TOOLOW                  "Too low"
#define LEVEL_LOW                     "Low"
#define LEVEL_OPTIMAL                 "Ideal"
#define LEVEL_HIGH                    "High"
#define LEVEL_TOOHIGH                 "Too high"

#include <Wire.h>
#include <BH1750.h>
BH1750 ukurLuxCahaya (0x5C);          //connect ADDR ke 3.3V, defaultnya 0x23

uint16_t lux        = 250;
int      luxLevel   = 3;
String   luxMessage = LEVEL_OPTIMAL;

void setup(){
  Serial.begin(115200);

  // Initialize the I2C bus (BH1750 library doesn't do this automatically)
  Wire.begin();

  ukurLuxCahaya.begin();
  Serial.println(F("BH1750 mulai"));
}

void loop() {
  lux = ukurLuxCahaya.readLightLevel();

  if ( lux <= _TOOLOW ) {
    luxLevel = 1;
    luxMessage = LEVEL_TOOLOW;
  } else if ( lux > _TOOLOW && lux <= _LOW ) {
    luxLevel = 2;
    luxMessage = LEVEL_LOW;
  } else if ( lux > _LOW && lux <= _HIGH ) {
    luxLevel = 3;
    luxMessage = LEVEL_OPTIMAL;
  } else if ( lux > _HIGH && lux < _TOOHIGH ) {
    luxLevel = 4;
    luxMessage = LEVEL_HIGH;
  } else {
    luxLevel = 5;
    luxMessage = LEVEL_TOOHIGH;
  }
  
  Serial.print("Light: "); 
  Serial.print(lux);
  Serial.print(" lx, level: ");
  Serial.print(luxLevel);
  Serial.print(" , quality: ");
  Serial.println(luxMessage);
  delay(1000);
}
