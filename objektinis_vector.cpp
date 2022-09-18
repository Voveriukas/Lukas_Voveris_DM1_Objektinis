#include <bits/stdc++.h>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::string;
using std::endl;
using std::sort;
using std::vector;

struct Studentas {
  string st_Vardas;
  string st_Pavarde;
  int nd_kiekis = 0;
  vector <int> nd_balai;
  int egz_rez;
  double rez;
};

void getDataTerminal(Studentas &first_st, int &temp) {
  // Egzo rezultatas

  cout << "Studento egzamino rezultatas (10-baleje sistemoje): ";
  cin >> first_st.egz_rez;
  while (cin.fail() || first_st.egz_rez > 10 || first_st.egz_rez < 1) {
    cout << "Egzamino rezultatas turi buti skaicius 10-baleje sistemoje"<< endl;
    cout << "Bandykite is naujo: " << endl;
    cin.clear();
    cin.ignore(256, '\n');
    cin >> first_st.egz_rez;
  }

  // Namu darbu ivertinimai
  int tempN;
  cout << "Paeiliui iveskite namu darbu ivercius" << endl;
  bool endLoop = false;
  while (!endLoop) {
    first_st.nd_kiekis++;
    cout << "Iveskite " << first_st.nd_kiekis << " namu darbu iverti, jei daugiau iverciu nera iveskite 11: "; cin >> tempN;
    while (cin.fail() || tempN > 10 ||
        tempN < 1) {
      if (tempN == 11) {
        endLoop = true;
        break;
      } else {
        cout << "Namu darbu rezultatas turi buti skaicius 10-baleje sistemoje."<< endl;
        cout << "Bandykite is naujo: " << endl;
        cin.clear();
        cin.ignore(256, '\n');
        cin >> tempN;
      }
    }
    if (endLoop) break;
    first_st.nd_balai.push_back(tempN);
    temp += tempN;
  }
}

void getDataRandom(Studentas &first_st, int &temp) {
  int tempN;
  first_st.egz_rez = rand() % 10 + 1;
  cout << "Sugeneruotas egzamino rezultatas (10-baleje sistemoje): " << first_st.egz_rez << endl;
  first_st.nd_kiekis = rand() % 8 + 1;
  cout << "Nd kiekis : " << first_st.nd_kiekis << endl;
  for (int i = 0; i < first_st.nd_kiekis; i++) {
    tempN = rand() % 10 + 1;
    first_st.nd_balai.push_back(tempN);
    cout << "Sugeneruotas " << i + 1 << " namu darbu ivertinimas (10-baleje sistemoje): "<< tempN << endl;
    temp += tempN;
  }
}

void getDataMain(Studentas &first_st, string vid_or_med) {
  int temp = 0;
  char yesOrNo;
  cout << "Studento vardas: ";
  cin >> first_st.st_Vardas;
  cout << "Studento pavarde: ";
  cin >> first_st.st_Pavarde;
  cout << "Ar norite, kad rezultatai butu sugeneruoti atsitiktinai? (T / N)";
  cin >> yesOrNo;
  while (yesOrNo != 'T' && yesOrNo != 'N' && yesOrNo !=  't' && yesOrNo != 'n') {
    cout << "Ivedama reiksme turi buti arba T arba N" << endl;
    cout << "Bandykite is naujo: " << endl;
    cin.clear();
    cin.ignore(256, '\n');
    cin >> yesOrNo;
  }
  if (yesOrNo == 'N')
    getDataTerminal(first_st, temp);
  else
    getDataRandom(first_st, temp);

  // Mediana / vidurkis

  double mediOrAvg;
  if (vid_or_med == "vid") {
    if (first_st.nd_balai.size() == 0) mediOrAvg = 0;
    else mediOrAvg = double(temp) / double(first_st.nd_kiekis);
  } else {
    // Mediana;
        if (first_st.nd_balai.size() == 0) 
        {
            mediOrAvg = 0;
        }
        else{
            sort(first_st.nd_balai.begin(), first_st.nd_balai.end());
            if (first_st.nd_kiekis % 2 == 0)
            {
                mediOrAvg = (first_st.nd_balai[first_st.nd_kiekis / 2 - 1] + first_st.nd_balai[first_st.nd_kiekis / 2]) / 2;
            }
            else 
            {
                mediOrAvg = first_st.nd_balai[first_st.nd_kiekis / 2];
            }
        }
  }
  first_st.rez = mediOrAvg * 0.4 + (double)first_st.egz_rez * 0.6;
}

void printF(Studentas *first_st, int student_kiekis, string vid_or_med) {
  printf("| %-10s %-10s Galutinis (%s.) |\n", "Vardas", "Pavarde",vid_or_med.c_str());
  cout << "|" << string(40, '-') << "|" << endl;
  for (int i=0; i<student_kiekis; i++)
  {
  printf("| %-10s %-10s %-16.2lf |\n", first_st[i].st_Vardas.c_str(),first_st[i].st_Pavarde.c_str(), first_st[i].rez);
  }
}

int main() {
  srand(time(NULL));
  int student_kiekis;
  cout << "Keliu studentu rezultatus norite ivesti?";cin >> student_kiekis;
  while (cin.fail() || student_kiekis < 1) {
    cout << "Studentu skaicius turi buti NENEIGIAMAS SKAICIUS"<< endl;
    cout << "Bandykite is naujo: " << endl;
    cin.clear();
    cin.ignore(256, '\n');
    cin >> student_kiekis;
  }
  Studentas first_st[student_kiekis];
  string vid_or_med;
  cout << "Ar norite suzinoti studento (-u) rezultata skaiciuota su mediana ar vidurkiu? (med / vid)";cin >> vid_or_med;
  while (vid_or_med != "vid" && vid_or_med != "med") {
    cout << "Ivedama reiksme turi buti arba vid arba med." << endl;
    cout << "Bandykite is naujo: " << endl;
    cin.clear();
    cin.ignore(256, '\n');
    cin >> vid_or_med;
  }
  for (int i=0; i<student_kiekis; i++)
  {
    getDataMain(first_st[i], vid_or_med);
  }
  printF(first_st, student_kiekis, vid_or_med);
  return 0;
}
