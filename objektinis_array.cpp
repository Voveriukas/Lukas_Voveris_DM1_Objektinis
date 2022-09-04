#include <bits/stdc++.h>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

using namespace std;

struct Studentas {
  string st_Vardas;
  string st_Pavarde;
  int nd_kiekis = 0;
  int *nd_balai = new int[nd_kiekis];
  int egz_rez;
  double rez = 99.00;
  string vid_or_med;
};

void getDataTerminal(Studentas &first_st, int &temp) {
  // Egzo rezultatas
  cout << "Studento egzamino rezultatas (10-baleje sistemoje): ";cin >> first_st.egz_rez;
  while (cin.fail() || first_st.egz_rez > 10 || first_st.egz_rez < 1) {
    cout << "Egzamino rezultatas turi buti skaicius 10-baleje sistemoje"<< endl;
    cout << "Bandykite is naujo: " << endl;
    cin.clear();
    cin.ignore(256, '\n');
    cin >> first_st.egz_rez;
  }

  // Namu darbu ivertinimai

  cout << "Paeiliui iveskite namu darbu ivercius" << endl;
  bool endLoop = false;
  while (!endLoop) {
    first_st.nd_kiekis++;
    cout << "Iveskite " << first_st.nd_kiekis << " namu darbu iverti, jei tokio nera iveskite 11: ";
    cin >> first_st.nd_balai[first_st.nd_kiekis - 1];
    while (cin.fail() || first_st.nd_balai[first_st.nd_kiekis - 1] > 10 || first_st.nd_balai[first_st.nd_kiekis - 1] < 1) {
      if (first_st.nd_balai[first_st.nd_kiekis - 1] == 11) {
        endLoop = true;
        first_st.nd_kiekis--;
        break;
      } else {
        cout << "Namu darbu rezultatai turi buti skaicius 10-baleje sistemoje."<< endl;
        cout << "Bandykite is naujo: " << endl;
        cin.clear();
        cin.ignore(256, '\n');
        cin >> first_st.nd_balai[first_st.nd_kiekis - 1];
      }
    }
    if (endLoop)
      break;
    temp += first_st.nd_balai[first_st.nd_kiekis - 1];
  }
}

void getDataRandom(Studentas &first_st, int &temp) {
  first_st.egz_rez = rand() % 10 + 1;
  cout << "Sugeneruotas egzamino rezultatas (10-baleje sistemoje): "<< first_st.egz_rez << endl;
  first_st.nd_kiekis = rand() % 8 + 1;
  cout << "Nd kiekis : " << first_st.nd_kiekis << endl;
  for (int i = 0; i < first_st.nd_kiekis; i++) {
    first_st.nd_balai[i] = rand() % 10 + 1;
    cout << "Sugeneruotas " << i + 1 << " namu darbu ivertinimas (10-baleje sistemoje): "<< first_st.nd_balai[i] << endl;
    temp += first_st.nd_balai[i];
  }
}

void getDataMain(Studentas &first_st) {
  int temp = 0;
  char yesOrNo;
  cout << "Studento vardas: ";
  cin >> first_st.st_Vardas;
  cout << "Studento pavarde: ";
  cin >> first_st.st_Pavarde;
  cout << "Ar norite, kad rezultatai butu sugeneruoti atsitiktinai? (T / N)";
  cin >> yesOrNo;
  while (yesOrNo != 'T' && yesOrNo != 'N') {
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

  cout << "Ar norite suzinoti studento rezultata skaiciuota su mediana ar vidurkiu? (med / vid)";cin >> first_st.vid_or_med;
  while (first_st.vid_or_med != "vid" && first_st.vid_or_med != "med") {
    cout << "Ivedama reiksme turi buti arba vid arba med." << endl;
    cout << "Bandykite is naujo: " << endl;
    cin.clear();
    cin.ignore(256, '\n');
    cin >> first_st.vid_or_med;
  }

  double mediOrAvg;
  if (first_st.vid_or_med == "vid") {
    if (first_st.nd_kiekis == 0) mediOrAvg = 0;
    else mediOrAvg = double(temp) / double(first_st.nd_kiekis);
  } else {
    // Mediana
    if (first_st.nd_kiekis == 0) mediOrAvg = 0;
    else {
      sort(first_st.nd_balai, first_st.nd_balai + first_st.nd_kiekis);
      if (first_st.nd_kiekis % 2 != 0) mediOrAvg = (double)first_st.nd_balai[(first_st.nd_kiekis - 1) / 2];
      else mediOrAvg = (double)(first_st.nd_balai[((first_st.nd_kiekis / 2) - 1)] + first_st.nd_balai[first_st.nd_kiekis / 2]) /2.0;
    }
  }
  first_st.rez = mediOrAvg * 0.4 + (double)first_st.egz_rez * 0.6;
}

void printF(Studentas first_st) {
  printf("| %-10s %-10s Galutinis (%s.) |\n", "Vardas", "Pavarde",first_st.vid_or_med.c_str());
  cout << "|" << string(40, '-') << "|" << endl;
  printf("| %-10s %-10s %-16.2lf |\n", first_st.st_Vardas.c_str(),first_st.st_Pavarde.c_str(), first_st.rez);
}

int main() {
  srand(time(NULL));
  Studentas first_st;
  getDataMain(first_st);
  printF(first_st);
  return 0;
}
