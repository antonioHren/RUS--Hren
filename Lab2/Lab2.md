Lab2 - Upravljanje potrošnjom energije

Platforma
ESP32

Varijanta
B - Datalogger okoliša

Opis projekta
Projekt demonstrira korištenje Deep Sleep moda na ESP32 mikrokontroleru.

ESP32 se periodički budi svakih 30 sekundi pomoću timer wake-up mehanizma.

Nakon buđenja:
- simulira očitanje temperature i vlage
- sprema podatke u RTC memoriju
- nakon 10 mjerenja ispisuje sve podatke
- resetira spremnik
- vraća se u Deep Sleep

Sleep mode
Deep Sleep

Wake-up
Timer wake-up

Čuvanje podataka
RTC memorija - RTC_DATA_ATTR

Wokwi link
https://wokwi.com/projects/463750237589524481
