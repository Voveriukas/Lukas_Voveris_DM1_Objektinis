# 1-oji užduotis

## v0.1

#### Programos veikimo principo pakeitimai:
```diff
+ Pridėti 2 strategijų (vector ir list konteineriams) palyginimas.
- Programa nelygina vector ir list konteinerių failų kūrimo greičių
```

#### Strategijos
**1 strategija:** Bendro studentai konteinerio (vector ir list tipų) skaidymas (rūšiavimas) į du naujus to paties tipo konteinerius: "nuskriaustųjų" ir "galvočių". Tokiu būdu tas pats studentas yra dvejuose konteineriuose: bendrame studentai ir viename iš suskaidytų (vargšiukai arba kietiakai).
**2 strategija:** Bendro studentų konteinerio (vector ir list) skaidymas (rūšiavimas) panaudojant tik vieną naują konteinerį: "nuskriaustieji". Tokiu būdu, jei studentas yra nuskriaustasis, jį turime įkelti į naująjį "nuskriaustųjų" konteinerį ir ištrinti iš bendro studentai konteinerio. Po šio žingsnio studentai konteineryje liks vien tik galvočiai.

Palyginimų rezultatai:

![image](https://user-images.githubusercontent.com/77852914/201079829-7079fa22-83ac-479f-89e7-cd9ad935d771.png)
![image](https://user-images.githubusercontent.com/77852914/201079908-04ae851b-6bb9-49b8-8412-7575f8a7751c.png)
![image](https://user-images.githubusercontent.com/77852914/201080439-e90b5280-30b3-4885-b56f-b853aa5dc603.png)
![image](https://user-images.githubusercontent.com/77852914/201100008-09e908e8-0ef4-46c3-87a4-f716e41407fc.png)
![image](https://user-images.githubusercontent.com/77852914/201102656-f1bb77e7-8466-4234-97dd-539df7569337.png)


## v0.4

#### Programos veikimo principo papildymas:
```diff
+ Vykdant skaitimą iš failo, vykdomas palyginimas tarp realizacijų naudojant list ir vector konteinerius.
```

#### Palyginimo rezultatai:

##Kompiuterio parametrai:
```
CPU - Intel Core i5-8300H 2.30GHz
RAM - 16 Gb
HDD - ST1000LM035-1RK172 1T talpos
```

##Testavimai

![image](https://user-images.githubusercontent.com/77852914/198313804-50589df7-9562-4421-959a-7357cfab97ce.png)
![image](https://user-images.githubusercontent.com/77852914/198313695-c51f3a92-6c87-487d-bc80-d5cb3d6c91f0.png)
![image](https://user-images.githubusercontent.com/77852914/198313575-1a17b2f6-bd4d-4dd9-9993-e91b8a06607f.png)
![image](https://user-images.githubusercontent.com/77852914/198313402-cd3a39aa-163c-4528-bb08-5f2eb853ecf6.png)
![image](https://user-images.githubusercontent.com/77852914/198320093-1a071bed-634c-470c-85e4-b56e9cd356f0.png)

## v0.3

#### Programos veikimo principo papildymas

```diff
+ Vartotojui pasirenkant duomenų vedimą iš failo sugeneruojami 5 duomenų failai ir skaitoma iš jų.
+ Studentai suskirstomi į vargšelius ir galvočius, tų kurių galutinis balas mažesnis už 5 ir kurių mažesnis.
+ Šie studentai išvedami į atskirus failus.
```

#### Failai

Sugeneruojami penki atsitiktiniai studentų sąrašų failai, sudaryti iš: 1 000, 10 000, 100 000, 1 000 000, 10 000 000 įrašų. Failai pavadinami pagal šį šabloną - `studentai_[failoDydis].txt`
Nuskaityti ir surušiuoti iš šių failų yra įrašomi į 2 naujus kiekvienam sąrašui (iš viso 10 skirtingų failų), pavadinti pagal šį šabloną: `galvociai_[failoDydis].txt` ir `nuskriaustieji_[failoDydis].txt`

## v0.2

#### Programos veikimo principo papildymas

```diff
+ Vartotojo paklausiama ar jis nori duomenis vesti iš failo ar ranka.
+ Pasirinkus vedima ranka, vartotojo yra paklausiama ar jis rezultatus nori vesti ranka ar juos sugeneruoti atsitiktinai.
```

#### Failai

Vartotojui duodamas pasirinkimas įvesti duomenis iš failo arba vesti ranka. Pasirinkus vedimą iš failo, duomenys yra vedami iš failo kursiokai.txt

## v0.1

#### Programos veikimo principas

```diff
+ Vartotojas yra paprašomas įvesti studento vardą bei pavardę.
+ Vartotojo yra paklausiama ar jis rezultatus nori vesti ranka ar juos sugeneruoti atsitiktinai.
+ Priklausomai nuo pasirinkimo, jo yra paprašoma įvesti egzamino ir namų darbų rezultatus, arba jie sugeneruojami atsitiktinai.
+ Vartotojo yra paklausiama ar jis studento galutinį rezultatą nori sužinoto skaičiuotą su mediana ar vidurkiu.
+ Vartotojui yra išvedama lentelė su jo vardu ir pavarde, bei galutiniu rezultatu skaičiuotu su mediana arba vidurkiu.
```

#### Limitacijos

Programoje yra integruotos "apsaugos" ir limitacijos dėl vartotojo duomenų įvedimo.

- Vartotojo atsakymas į klausimą ar šis nori egzaminų ir namų darbų rezultatus vesti ranka ar sugeneruoti atsitiktinai gali būti tik **T** arba **N** įvedus bet kokią kitokią reikšmę, ši bus atmesta ir vartotojas bus paprašomas reikšmę vesti iš naujo. Logikos kodas:
```cpp
 while (yesOrNo != 'T' && yesOrNo != 'N' && yesOrNo !=  't' && yesOrNo != 'n') {
    cout << "Ivedama reiksme turi buti arba T arba N" << endl;
    cout << "Bandykite is naujo: " << endl;
    cin.clear();
    cin.ignore(256, '\n');
    cin >> yesOrNo;
  }
```
- Egzamino ir namų darbus vedant ranka yra taikomi apribojimai, kad visos vedamos reikšmės **privalo** būti skaičiai ne didesni nei 10 ir ne mažesni nei 1. Įvedus bet kokį neskaitinį simbolį arba skaitines reikšmes neapibrėžtas nustatytuose rėžiuose, jos bus atmestos ir vartotojas bus paprašomas reikšmę vesti iš naujo. **IŠIMTIS** vedant namų darbų rezultatus įvedus skaičių 11 namų darbų rezultatų vedimas yra nutraukiamas. Logikos kodas:
```cpp
while (cin.fail() || first_st.egz_rez > 10 || first_st.egz_rez < 1) {
    cout << "Egzamino rezultatas turi buti skaicius 10-baleje sistemoje"<< endl;
    cout << "Bandykite is naujo: " << endl;
    cin.clear();
    cin.ignore(256, '\n');
    cin >> first_st.egz_rez;
  }
```
- Vartotojui vedant ar jis studento galutinį rezultatą nori sužinoto skaičiuotą su mediana ar vidurkiu yra priimamos tik dvi reikšmės **vid** arba **med** įvedus bet kokią kitokią reikšmę, ši bus atmesta ir vartotojas bus paprašomas reikšmę vesti iš naujo. Logikos kodas:
```cpp
while (first_st.vid_or_med != "vid" && first_st.vid_or_med != "med") {
    cout << "ivedama reiksme turi buti arba vid arba med." << endl;
    cout << "Bandykite is naujo: " << endl;
    cin.clear();
    cin.ignore(256, '\n');
    cin >> first_st.vid_or_med;
  }
```

#### Random

Vartotojui pasirinkus atsitiktinį generavimą, studento egzaminų ir namų darbų rezultatai sugeneruojami atsitiktinai naudojant `rand()` funkciją.
Kompiuterio vidinis laikrodis yra naudojamas, `rand()` fukcijos sėklos (seed) pasirinkime. Sėklos (seed) nustatymui naudojama funkcija: `srand(time(NULL))`

#### Failai

1-oji užduoties v0,1 versijos atšakoje (branch) yra prisegami du `.cpp` failai: `objektinis_array.cpp` ir `objektinis_vector.cpp`.
Šiuose failuose programos logika nekinta, jie skiriasi tik tuom, kad `objektinis_array.cpp` namų darbų įverčiams laikyti yra naudojamas **dinaminis masyvas**, o `objektinis_vector.cpp` tiems patiems įverčiams laikyti yra naudojamas **vektorius**.
