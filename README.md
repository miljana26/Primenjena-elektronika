# Projekat: Sistem za zaštitu i automatizaciju staklenika & Autonomno kretanje robota uz izbegavanje prepreka

## Opis

Ovaj projekat se sastoji od dva dela:

### 1. Sistem za zaštitu i automatizaciju staklenika
Projekat se fokusira na realizaciju sistema koji automatizuje i poboljšava uslove uzgoja biljaka u stakleniku. Korišćenjem različitih senzora i aktuatora, sistem omogućava precizno praćenje i kontrolu uslova u stakleniku, sa ciljem optimizacije rasta biljaka.

### 2. Autonomno kretanje robota uz izbegavanje prepreka
Drugi deo projekta uključuje razvoj robota koji se autonomno kreće i izbegava prepreke na svom putu. Robot koristi različite senzore za detekciju i izbegavanje prepreka, kao i za kontrolu kretanja i povratak na startnu poziciju.

## Ključne reči

- **Prvi deo:** Mikrokontroler dsPIC30F4013, PIR senzor, servo motor, piezo zujalica, fotootpornik, LM35, GLCD, Touchscreen, UART komunikacija
- **Drugi deo:** Mikrokontroler dsPIC30F4013, PICkit 3, Sharp GP2Y0A21YK0F IR senzor, HC-SR04 ultrazvučni senzor, LM7805 regulator napona, DC motor, L298N drajver, Bluetooth modul HC-06, UART komunikacija

## Prvi deo: Sistem za zaštitu i automatizaciju staklenika

### Kratak sadržaj projekta
Projekat **"Sistem za zaštitu i automatizaciju staklenika"** obuhvata sledeće ključne tačke:

#### 1. Uvod
- Predstavljanje ideje i ciljeva projekta.

#### 2. Korišćene komponente
- Detaljan opis komponenti korišćenih u projektu:
  - Razvojna ploča EasyPIC™ v7
  - Mikrokontroler dsPIC30F4013
  - PIR senzor, servo motor, piezo zujalica
  - Fotootpornik, LM35 senzor, GLCD ekran sa Touchscreen-om

#### 3. UART serijska komunikacija
- Objašnjenje serijske komunikacije između mikrokontrolera i računara, uz korišćenje RS232 i USB protokola.

#### 4. Algoritam rada
- Detaljan opis algoritma rada sistema, uključujući glavne blok dijagrame.

#### 5. Realizacija projekta
- Opis implementacije, korišćenje pinova, prikaz stanja na GLCD ekranu, objašnjenje funkcija u **main.c** datoteci.

#### 6. Zaključak
- Evaluacija postignutih rezultata i predlozi za poboljšanja, kao što su:
  - Dodavanje privremenog rashlađivanja prostorije
  - Uvođenje senzora za skeniranje otiska prsta
  - Implementacija otvaranja vrata na senzor blizine

## Drugi deo: Autonomno kretanje robota uz izbegavanje prepreka

### Kratak sadržaj projekta
Projekat **"Autonomno kretanje robota uz izbegavanje prepreka"** obuhvata sledeće ključne tačke:

#### 1. Uvod
- Predstavljanje ideje i ciljeva projekta.

#### 2. Analiza problema
- Podela realizacije na podsisteme i razmatranje različitih načina detekcije i izbegavanja prepreka.

#### 3. Korišćene komponente
- Detaljan opis komponenti korišćenih u projektu:
  - Mikrokontroler dsPIC30F4013
  - PICkit 3 debager/programator
  - Sharp GP2Y0A21YK0F IR senzor, HC-SR04 ultrazvučni senzor
  - LM7805 regulator napona, DC motor, L298N drajver
  - Bluetooth modul HC-06

#### 4. Projektovanje ploče u Altium Designer-u
- Dizajn PCB pločice, šematski prikaz i lejaut pločice.

#### 5. Algoritam rada
- Detaljan opis algoritma rada sistema, uključujući glavne blok dijagrame.

#### 6. Realizacija
- Opis realizacije projekta, uključujući korišćene pinove, izradu ploče, kompletiranje robota, i objašnjenje funkcija u **main.c** datoteci.

#### 7. Zaključak
- Evaluacija postignutih rezultata i diskusija o mogućim poboljšanjima, kao što su:
  - Dodavanje PID regulacije
  - Merenje struje kroz motor
  - Korišćenje baterije za napajanje
  - Postavljanje senzora sa obe strane robota
  - Dodavanje kamere
  - Dodavanje funkcije čišćenja, hvatanja, sortiranja i skladištenja
