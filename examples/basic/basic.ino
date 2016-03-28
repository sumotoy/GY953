/*
 * Quick n dirty example of GY-953.
 * The library use an interrupt handled internally.
 */
#include <GY953.h>
#include <SPI.h>

bool justStarted = true;

GY953 mag = GY953(10, 2);

void setup() {
  Serial.begin(115200);
  long unsigned debug_start = millis ();
  while (!Serial && ((millis () - debug_start) <= 5000));
  mag.begin();
  //mag.changeRefreshRate(200);
  Serial.println("started");
}

void loop() {
  if (mag.update()) {
    int data[3];
    if (justStarted) {
      justStarted = false;
      byte data2[4];
      byte data3[3];
      memset(data,0,3);
      memset(data2,0,4);
      memset(data3,0,3);
      mag.readAccuracy(data2);
      Serial.println("\nAccuracy");
      Serial.print("ACC:");   //0..3 (less...more accurate)
      Serial.print(data2[0]);
      Serial.print(" | GYR:");//0..3 (less...more accurate)
      Serial.print(data2[1]);
      Serial.print(" | MAG:");//0..3 (less...more accurate)
      Serial.print(data2[2]);
      Serial.print(" | Freq:");//3:50Hz - 4:100Hz - 5:200Hz
      Serial.print(data2[3]);

      mag.readRange(data3);
      Serial.println("\nRange");
      Serial.print("ACC:");   //0---------------+-2g
      Serial.print(data3[0]);
      Serial.print(" | GYR:");//3---------------+-2000dps/s
      Serial.print(data3[1]);
      Serial.print(" | MAG:");//1:---------16bit
      Serial.print(data3[2]);
    } else {
      mag.getRPY(data);
      /*
        Natively, range is:
        Roll:
        Pitch:
        Yaw:
      */
 
      Serial.println();
      Serial.print("Roll:");
      Serial.print(data[0]);
      Serial.print(" | Pitch:");
      Serial.print(data[1]);
      Serial.print(" | Yaw:");
      Serial.print(data[2]);

    }

  }

}