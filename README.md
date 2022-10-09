# 1-oji užduotis

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
