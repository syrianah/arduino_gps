//arduino_on-board-rocket-computer

#include <Arduino.h>

//Barometr:
#include <Wire.h>
#include "/Users/wojciechkubiak/Documents/PlatformIO/Projects/arduino_gps/lib/I2C-Sensor-Lib_iLib/src/i2c.h"
#include "/Users/wojciechkubiak/Documents/PlatformIO/Projects/arduino_gps/lib/I2C-Sensor-Lib_iLib/src/i2c_BMP280.h"

//Karta pamieci:
#include <SPI.h>
#include <SD.h>

//GPS:
#include <SoftwareSerial.h>
#include <TinyGPS.h>

#define SD_cs 10

#define BMP280_Probe 10

//Karta pamieci:
File plik;

//Barometr:
BMP280 bmp280;
float pressure = 0;
float srednia = 0;
float temp = 0;
float suma=0;
float meters, altitude;

//GPS:
int gps_read;
long lat = 0, lon = 0;
unsigned long fix_age = 0;
TinyGPS gps;
SoftwareSerial nss(2, 3);

//Save data to SD card
void logger(double x, double y, double z);

//BMP280 initialize
void setup_BMP280();

//GPS initialize
void setup_GPS();

//SD card initialize
void setup_SD();

int main(void)
{
    Serial.begin(9600);
    //setup
    setup_BMP280();
    setup_GPS();
    setup_SD();

    //loop
    while (1)
    {
        //Barometr:
      bmp280.awaitMeasurement();

        bmp280.getTemperature(temp);

        bmp280.getPressure(pressure);

        bmp280.getAltitude(meters,srednia);
        altitude = (altitude * 10 + meters)/11;

        bmp280.triggerMeasurement();

        //GPS:
        while (nss.available())
        {
            gps_read = nss.read();
            if (gps.encode(gps_read))
            {
                gps.get_position(&lat, &lon, &fix_age);
            }
        }
        //zapis na karte
        logger(lat, lon, altitude);
    }

}

void logger(double x, double y, double z)
{
    plik = SD.open("data.txt", FILE_WRITE);                   //otwórz plik 123.txt
    plik.print("Szerokosc: ");
    plik.println(x);
    plik.print("Dlugosc: ");
    plik.println(y);
    plik.print("Wysokość: ");
    plik.println(z);
    plik.close();                                            //zamknij/zapisz plik
    delay(300);                                              //oczekaj 0,3s
    Serial.println("Zapisano !");                            //poinformuj o zapisaniu pliku
}

void setup_BMP280()
{
    //Barometr:
    Serial.print("Probe BMP280: ");
    if (bmp280.initialize()) Serial.println("Sensor found");
    else
    {
      Serial.println("Sensor missing");
      // while (1) {}
    }

    // onetime-measure:
    bmp280.setEnabled(0);
    bmp280.triggerMeasurement();

    for(int i=0;i<BMP280_Probe;i++)
    {
        bmp280.awaitMeasurement();
        bmp280.getTemperature(temp);
        bmp280.getPressure(pressure);
        srednia=srednia+pressure;
        bmp280.triggerMeasurement();
    }
    srednia=srednia/BMP280_Probe;
}

void setup_GPS()
{
    //GPS:
    nss.begin(9600);
}

void setup_SD()
{
    Serial.println("Gotowy! (1/3)");
    Serial.println("Szukam karte... (2/3");

    if (!SD.begin(SD_cs))                                       //sprawdź czy nie ma karty na pinie ChipSelect 4
    {
        Serial.println("Nie wykryto karty(ERR)");            //błąd wykrycia karty
        while (1) {}                                             //przerwij program
    }

    Serial.println("Karta Wykryta (3/3))");                 //Karta wykryta


    if (SD.exists("data.txt"))                               //sprawdź czy istnieje plik o nazwie 123.csv
    {

        Serial.println("Plik o podanej nazwie istnieje !");

    }

      else                                                   //jeżeli nie istnieje to
      {

          plik = SD.open("data.txt", FILE_WRITE);                //utwórz plik
          Serial.println("Utworzono plik o nazwie data.txt");

      }
}
