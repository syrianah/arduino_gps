// #include <Arduino.h>
// //Barometr:
// #include <Wire.h>
// #include "/Users/wojciechkubiak/Documents/PlatformIO/Projects/arduino_gps/lib/I2C-Sensor-Lib_iLib/src/i2c.h"
// #include "/Users/wojciechkubiak/Documents/PlatformIO/Projects/arduino_gps/lib/I2C-Sensor-Lib_iLib/src/i2c_BMP280.h"
// //Karta pamieci:
// #include <SPI.h>                                         //dodaj bibliotekę SPI.h
// #include <SD.h>                                          //dodaj bilbiotekę SD.h
// //GPS:
// #include <SoftwareSerial.h>
// #include <TinyGPS.h>
//
// //Karta pamieci:
// File plik;
//
//
//
//
// void logger(double x, double y, double z)
// {
//
// plik = SD.open("123.txt", FILE_WRITE);                   //otwórz plik 123.txt
// plik.print("Wysokość: ");
// plik.println(x);
// plik.println("GPS: ");
// plik.print("Szerokosc: ");
// plik.println(y);
// plik.print("Dlugosc: ");
// plik.println(z);
// plik.close();                                            //zamknij/zapisz plik
// delay(300);                                              //oczekaj 0,3s
// Serial.println("Zapisano !");                            //poinformuj o zapisaniu pliku
// }
//
// //Barometr:
// BMP280 bmp280;
// float pressure = 0;
// float srednia = 0;
// float temp = 0;
// float suma=0;
// static float meters, altitude;
//
// //GPS:
// TinyGPS gps;
// SoftwareSerial nss(2, 3);
//
// void setup()
// {
//     Serial.begin(9600);
//
//     //Karta pamieci:
//
//     Serial.println("Gotowy! (1/3)");
//     Serial.println("Szukam karte... (2/3");
//
//     if (!SD.begin(10))                                       //sprawdź czy nie ma karty na pinie ChipSelect 4
//     {
//        Serial.println("Nie wykryto karty(ERR)");            //błąd wykrycia karty
//        return;                                              //przerwij program
//     }
//
//     Serial.println("Karta Wykryta (3/3))");                 //Karta wykryta
//
//
//     if (SD.exists("123.txt"))                               //sprawdź czy istnieje plik o nazwie 123.csv
//     {
//
//      Serial.println("Plik o podanej nazwie istnieje !");
//
//     }
//
//     else                                                   //jeżeli nie istnieje to
//     {
//
//      plik = SD.open("123.txt", FILE_WRITE);                //utwórz plik
//      Serial.println("Utworzono plik o nazwie 123.txt");
//
//     }
//
//     //Barometr:
//     Serial.print("Probe BMP280: ");
//     if (bmp280.initialize()) Serial.println("Sensor found");
//     else
//     {
//         Serial.println("Sensor missing");
//         while (1) {}
//     }
//
//     // onetime-measure:
//     bmp280.setEnabled(0);
//     bmp280.triggerMeasurement();
//
//     for(int i=0;i<10;i++)
//     {
//       bmp280.awaitMeasurement();
//       bmp280.getTemperature(temp);
//       bmp280.getPressure(pressure);
//       srednia=srednia+pressure;
//       bmp280.triggerMeasurement();
//     }
//     srednia=srednia/10;
//
//     //GPS:
//     nss.begin(9600);
//
// }
//
// void loop()
// {
//     //Barometr:
//     bmp280.awaitMeasurement();
//
//     bmp280.getTemperature(temp);
//
//     bmp280.getPressure(pressure);
//
//     bmp280.getAltitude(meters,srednia);
//     altitude = (altitude * 10 + meters)/11;
//
//     bmp280.triggerMeasurement();
//
//     // Serial.print("D:");
//     // Serial.print(temp);
//     // Serial.print(":");
//     // Serial.print(pressure);
//     // Serial.print(":");
//     // Serial.print(altitude);
//     // Serial.println();
//
//     //GPS:
//     while (nss.available())
//     {
//       int c = nss.read();
//       if (gps.encode(c))
//       {
//         long lat, lon;
//         unsigned long fix_age;
//         gps.get_position(&lat, &lon, &fix_age);
//
//         // Serial.print("Szerokosc:");Serial.println(lat);
//         // Serial.print("Dlugosc:");Serial.println(lon);
//         logger(altitude, lat, lon);
//       }
//     }
//
//
//
// }
//
// /**<
//
// Program size:
// A1.0.5:
// A1.5.7: 9680b
// A1.6.3: 9664b / 561b
//
//  */
