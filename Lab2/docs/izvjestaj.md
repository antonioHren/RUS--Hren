Izvještaj

Korišteni nač mirovanja
ESP32 Deep Sleep

Način buđenja
Timer wake-up pomoću esp_sleep_enable_timer_wakeup()

Opis implementacije
ESP32 se nalazi u Deep Sleep modu većinu vremena.

Svakih 60 sekundi:
1. sustav se probudi
2. simulira mjerenje temperature i vlage
3. sprema podatke u RTC memoriju
4. vraća se u Deep Sleep

Nakon 10 mjerenja:
- ispisuju se spremljeni podaci
- memorija se resetira

Čuvanje stanja
Podaci se čuvaju pomoću RTC_DATA_ATTR memorije koja ostaje dostupna nakon Deep Sleep buđenja.

Analiza potrošnje

Pretpostavke:
- aktivna struja: 80 mA
- sleep struja: 0.01 mA
- aktivno vrijeme: 3 s
- sleep vrijeme: 57 s

Formula:

I_avg = (I_active × t_active + I_sleep × t_sleep) / ukupno vrijeme

I_avg = (80×3 + 0.01×57) / 60

I_avg ≈ 4.01 mA

Baterija:
2500 mAh

Trajanje:

2500 / 4.01 ≈ 623 sata

≈ 26 dana
