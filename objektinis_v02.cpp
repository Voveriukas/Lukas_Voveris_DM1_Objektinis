#include "studentas.h"

double mediOrAvg (string vid_or_med, vector <Studentas> first_st, int temp, int student_kiekis)
{
  double mediOrAvg;
  if (vid_or_med == "vid") {
    if (first_st[student_kiekis].nd_balai.size() == 0) mediOrAvg = 0;
    else mediOrAvg = double(temp) / double(first_st[student_kiekis].nd_kiekis);
  } 
  else 
  {
    if (first_st[student_kiekis].nd_balai.size() == 0) 
    {
      mediOrAvg = 0;
    }
    else{
      sort(first_st[student_kiekis].nd_balai.begin(), first_st[student_kiekis].nd_balai.end());
      if (first_st[student_kiekis].nd_kiekis % 2 == 0)
      {
          mediOrAvg = (first_st[student_kiekis].nd_balai[first_st[student_kiekis].nd_kiekis / 2 - 1] + first_st[student_kiekis].nd_balai[first_st[student_kiekis].nd_kiekis / 2]) / 2;
      }
      else 
      {
          mediOrAvg = first_st[student_kiekis].nd_balai[first_st[student_kiekis].nd_kiekis / 2];
      }
    }
    
  }
  first_st[student_kiekis].rez = mediOrAvg * 0.4 + (double)first_st[student_kiekis].egz_rez * 0.6;
  return first_st[student_kiekis].rez;
}

void getDataTerminal(vector <Studentas> &first_st, int &temp, int student_kiekis) {
  // Egzo rezultatas

  cout << "Studento egzamino rezultatas (10-baleje sistemoje): ";
  cin >> first_st[student_kiekis].egz_rez;
  while (cin.fail() || first_st[student_kiekis].egz_rez > 10 || first_st[student_kiekis].egz_rez < 1) {
    cout << "Egzamino rezultatas turi buti skaicius 10-baleje sistemoje"<< endl;
    cout << "Bandykite is naujo: " << endl;
    cin.clear();
    cin.ignore(256, '\n');
    cin >> first_st[student_kiekis].egz_rez;
  }

  // Namu darbu ivertinimai
  int tempN;
  cout << "Paeiliui iveskite namu darbu ivercius" << endl;
  bool endLoop = false;
  while (!endLoop) {
    first_st[student_kiekis].nd_kiekis++;
    cout << "Iveskite " << first_st[student_kiekis].nd_kiekis << " namu darbu iverti, jei daugiau iverciu nera iveskite 11: "; cin >> tempN;
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
    first_st[student_kiekis].nd_balai.push_back(tempN);
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

void getDataMain(vector <Studentas> &first_st, string vid_or_med, int student_kiekis) {
  int temp = 0;
  char yesOrNo;
  cout << "Studento vardas: ";
  cin >> first_st[student_kiekis].st_Vardas;
  cout << "Studento pavarde: ";
  cin >> first_st[student_kiekis].st_Pavarde;
  cout << "Ar norite, kad rezultatai butu sugeneruoti atsitiktinai? (T / N)";
  cin >> yesOrNo;
  while (yesOrNo != 'T' && yesOrNo != 'N' && yesOrNo !=  't' && yesOrNo != 'n') {
    cout << "Ivedama reiksme turi buti arba T arba N" << endl;
    cout << "Bandykite is naujo: " << endl;
    cin.clear();
    cin.ignore(256, '\n');
    cin >> yesOrNo;
  }
  if (yesOrNo == 'N' or yesOrNo == 'n')
    getDataTerminal(first_st, temp, student_kiekis);
  else
    getDataRandom(first_st[student_kiekis], temp);

  first_st[student_kiekis].rez = mediOrAvg(vid_or_med, first_st, temp, student_kiekis);
}



void printF(vector <Studentas> first_st, int student_kiekis, string vid_or_med) {
  printf("| %-20s %-20s Galutinis (%s.) |\n", "Vardas", "Pavarde",vid_or_med.c_str());
  cout << "|" << string(60, '-') << "|" << endl;
  for (int i=0; i<student_kiekis; i++)
  {
  printf("| %-20s %-20s %-16.2lf |\n", first_st[i].st_Vardas.c_str(),first_st[i].st_Pavarde.c_str(), first_st[i].rez);
  }
}

void readF(vector <Studentas> &first_st, int &student_kiekis, string vid_or_med)
{
    try
    {
      float temp, s;
      ifstream fileRead("kursiokai.txt");
      fileRead.exceptions(ifstream::eofbit | ifstream::failbit | ifstream::badbit);
      string test;
      if (fileRead.is_open())
      {
        int paz_sk;
        getline(fileRead >> ws, test);
        stringstream stream(test);
        paz_sk = (distance(istream_iterator<string>(stream), istream_iterator<string>())) - 3;
        while (true)
        {
          first_st.resize(first_st.size() + 1);
          fileRead >> first_st.at(student_kiekis).st_Vardas;
          if (fileRead.eof()) { first_st.pop_back(); break;}
          fileRead >> first_st.at(student_kiekis).st_Pavarde;
          s=0;
          first_st.at(student_kiekis).nd_kiekis=paz_sk;
          for (int i = 0; i < first_st.at(student_kiekis).nd_kiekis; i++)
          {
            fileRead >> temp;
            first_st.at(student_kiekis).nd_balai.push_back(temp);
            s+=temp;
          }
          fileRead >> first_st.at(student_kiekis).egz_rez;
          first_st[student_kiekis].rez = mediOrAvg(vid_or_med, first_st, s, student_kiekis);
          student_kiekis++;
        }
      }
    }
    catch(exception const& e){
     cout << "Ivyko problema nuskaitant faila" << endl;
  }
}

bool compareTwoStudents(Studentas a, Studentas b)
{
    if (a.st_Vardas != b.st_Vardas)
        return a.st_Vardas > b.st_Vardas;
    if (a.st_Pavarde != b.st_Pavarde)
        return a.st_Pavarde > b.st_Pavarde;
    return a.rez > b.rez;
}

int main() {
  srand(time(NULL));
  int student_kiekis=0;
  vector <Studentas> first_st;
  string vid_or_med;
  char inputType;
  cout << "Ar norite suzinoti studento (-u) rezultata skaiciuota su mediana ar vidurkiu? (med / vid)";cin >> vid_or_med;
  while (vid_or_med != "vid" && vid_or_med != "med") {
    cout << "Ivedama reiksme turi buti arba vid arba med." << endl;
    cout << "Bandykite is naujo: " << endl;
    cin.clear();
    cin.ignore(256, '\n');
    cin >> vid_or_med;
  }
  cout << "Ar duomenis skiatysite is failo ar vesit ranka? (F / R) ";cin >> inputType;
  while (inputType != 'F' && inputType != 'R' && inputType !=  'f' && inputType != 'r') {
    cout << "Ivedama reiksme turi buti arba T arba N" << endl;
    cout << "Bandykite is naujo: " << endl;
    cin.clear();
    cin.ignore(256, '\n');
    cin >> inputType;
  }
  if (inputType == 'R' || inputType == 'r')
  {
    char yra_st='t';
    while (yra_st=='t' || yra_st=='T')
    {
      first_st.resize(first_st.size() + 1);
      getDataMain(first_st, vid_or_med, student_kiekis);
      cout << "Ar norite ivesti dar viena studenta? T / N" << endl;
      cin >> yra_st;
      while (yra_st != 'T' && yra_st != 'N' && yra_st !=  't' && yra_st != 'n') {
        cout << "Ivedama reiksme turi buti arba T arba N" << endl;
        cout << "Bandykite is naujo: " << endl;
        cin.clear();
        cin.ignore(256, '\n');
        cin >> yra_st;
      }
      student_kiekis++;
    }
  }
  else
  {
    readF(first_st, student_kiekis, vid_or_med);
  }
  sort(first_st.begin(), first_st.end(), compareTwoStudents);
  
  printF(first_st, student_kiekis, vid_or_med);
  return 0;
}
