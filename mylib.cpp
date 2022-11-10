#include "mylib.h"

double mediOrAvg (string vid_or_med, vector<int> &arr, int n, int egz_rez)
{
  double mediOrAvg;
  if (vid_or_med == "vid") {
    if (n == 0) mediOrAvg = 0;
    else mediOrAvg = std::accumulate(arr.begin(), arr.end(),0.0)/(double)n;
  }
  else
  {
    if (n == 0)
    {
      mediOrAvg = 0;
    }
    else{
      std::sort(arr.begin(),arr.end());
      if (n % 2 == 0)
      {
          mediOrAvg = (double)arr[n/2];;
      }
      else
      {
          mediOrAvg = (double)(arr[(n-1)/2]+arr[n/2])/2.0;
      }
    }

  }
  return mediOrAvg * 0.4 + (double)egz_rez * 0.6;
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

  first_st[student_kiekis].rez = mediOrAvg(vid_or_med, first_st[student_kiekis].nd_balai, first_st[student_kiekis].nd_kiekis, first_st[student_kiekis].egz_rez);
}



void printF(vector <Studentas> first_st, int student_kiekis, string vid_or_med) {
  string A;
  printf("| %-20s %-20s Galutinis (%s.) |\n", "Vardas", "Pavarde",vid_or_med.c_str());
  cout << "|" << string(60, '-') << "|" << endl;
  for (int i=0; i<student_kiekis; i++)
  {
    A += first_st[i].st_Vardas + first_st[i].st_Pavarde + to_string(first_st[i].rez)+ "\n";
  }
  // printf("| %-20s %-20s %-16.2lf |\n", first_st[i].st_Vardas.c_str(),first_st[i].st_Pavarde.c_str(), first_st[i].rez);
  printf("%s", A.c_str());
}

void generateFile(int fileSize, string name)
{
    stringstream buffer;
    std::ofstream out(name);
    int temp = (rand()% 10 + 1);
    buffer << "Vardas" << setw(15) << "Pavarde";
    for(int i = 0; i < temp; i++){
        buffer << setw(15) << "ND" << i+1;
    }
    buffer << setw(15) << "Egz.\n";
    for(int i = 0; i < fileSize; i++){
        buffer << "Vardas" << i+1 << setw(15) << "Pavarde" << i+1;
        for(int j = 0; j < temp; j++){
            buffer << setw(15) << (rand()% 10 + 1);
        }
        buffer << setw(15) << (rand()% 10 + 1) << "\n";
    }
    out << buffer.str();
    buffer.clear();
    out.close();
}


void writeToFile(vector <Studentas> &stud, string &file_name, int &fileSize)
{
  ofstream o(file_name);
  for (int i = 0; i<fileSize; i++)
    {
      o <<stud.at(i).st_Vardas<<  std::setw(20) << stud.at(i).st_Pavarde << std::setw (20) << stud.at(i).rez<< endl;
    }
   o.close();
}

void writeToFile(list <Studentas> &stud, string &file_name, int &fileSize)
{
  ofstream o(file_name);
  for (const auto& laik : stud)
    {
      o <<laik.st_Vardas<<  std::setw(20) << laik.st_Pavarde << std::setw (20) << laik.rez<< endl;
    }
   o.close();
}

void failo_skaitymasvec(vector<Studentas> &sar, string filename, string vid_or_med, int &studentu_skaicius)
{
   try{
        std::ifstream fr(filename);
        if(!fr.fail()){
        int sk;
        string line;
        string temp,pirmaEil;
        int kiekNd = -3;
        std::getline(fr >> std::ws,pirmaEil);
       stringstream iss(pirmaEil);
        while(iss >> temp)
        {
            kiekNd++;
        }
        while(std::getline(fr >> std::ws,line)){
            Studentas s;
            stringstream iss(line);
            s.nd_kiekis = kiekNd;
            iss>> s.st_Vardas;
            iss >> s.st_Pavarde;
            for(int i = 0; i < kiekNd; i++){
                iss>> sk;
                s.nd_balai.push_back(sk);
            }
            iss >> sk;
            s.egz_rez=sk;

            s.rez = mediOrAvg(vid_or_med,s.nd_balai,s.nd_kiekis, s.egz_rez);
            sar.push_back(s);
        }
        }
        else{
            throw std::runtime_error(filename);
        }
        studentu_skaicius=sar.size();
    }
    catch(std::exception &e){
     cout << "Ivyko problema nuskaitant faila: " << e.what() << "\n";
     std::exit(0);
  }
}

void failo_skaitymas_list(list<Studentas> &sar, string filename, string vid_or_med, int &studentu_skaicius)
{
    try{
        std::ifstream fr(filename);
        if(!fr.fail()){
        int sk;
        string line;
        string temp,pirmaEil;
        int kiekNd = -3;
        std::getline(fr >> std::ws,pirmaEil);
        stringstream iss(pirmaEil);
        while(iss >> temp)
        {
            kiekNd++;
        }
        while(std::getline(fr >> std::ws,line)){
            Studentas s;
            stringstream iss(line);
            s.nd_kiekis = kiekNd;
            iss>> s.st_Vardas;
            iss >> s.st_Pavarde;
            for(int i = 0; i < kiekNd; i++){
                iss>> sk;
                s.nd_balai.push_back(sk);
            }
            iss >> sk;
            s.egz_rez=sk;
            s.rez = mediOrAvg(vid_or_med,s.nd_balai,s.nd_kiekis, s.egz_rez);
            sar.push_back(s);
        }
        }
        else{
            throw std::runtime_error(filename);
        }
        studentu_skaicius=sar.size();
    }
    catch(std::exception &e){
     cout << "Ivyko problema nuskaitant faila: " << e.what() << "\n";
     std::exit(0);
  }
}

void dalintiSarasa(vector<Studentas>&sar, vector<Studentas> &nuskriaustieji, vector<Studentas> &galvociai){
    for(auto &s: sar){
        if(s.rez<5.00) nuskriaustieji.push_back(s);
        else galvociai.push_back(s);
    }
}
void dalintiSarasa(list<Studentas>&sar, list<Studentas> &nuskriaustieji, list<Studentas> &galvociai){
    for(auto &s: sar){
        if(s.rez<5.00) nuskriaustieji.push_back(s);
        else galvociai.push_back(s);
    }
}
bool compareTwoStudents(Studentas a, Studentas b)
{
    return a.rez > b.rez;
}

