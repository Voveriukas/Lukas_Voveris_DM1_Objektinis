#include "studentas.h"

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
    printF(first_st, student_kiekis, vid_or_med);
  }
  else
  {
    int fileSize = 1000;
    while (fileSize < 10000000)
    {
      vector <Studentas> galvociai;
      vector <Studentas> nuskriaustieji;
      string file_name = "studentai_" + to_string(fileSize) + ".txt";
      string pavad1 = "galvociai_" + to_string(fileSize) + ".txt";
      string pavad2 = "nuskriaustieji_" + to_string(fileSize) + ".txt";

      // File create
      auto start1 = std::chrono::high_resolution_clock::now();
      generateFile(fileSize, file_name);
      auto end1 = std::chrono::high_resolution_clock::now();
      std::chrono::duration<double> diff1 = end1 - start1;
      cout<< fileSize << " studentu failo sukurimas uztruko: "<<diff1.count()<<endl;

      // File read
      failo_skaitymas(first_st, fileSize, file_name, vid_or_med);

      auto start3 = std::chrono::high_resolution_clock::now();
      sort(first_st.begin(), first_st.end(), compareTwoStudents);
      auto end3 = std::chrono::high_resolution_clock::now();
      std::chrono::duration<double> diff3 = end3 - start3;
      cout<<fileSize << " studentu failo rusiavimas naudojant sort() uztruko: "<<diff3.count()<<endl;

      auto start4 = std::chrono::high_resolution_clock::now();
      for (int i = 0; i<fileSize; i++)
      {
        if(first_st.at(i).rez < 5.00)
        {
            nuskriaustieji.push_back(first_st.at(i));
        }
        else
        {
          galvociai.push_back(first_st.at(i));
        }
      }
      auto end4 = std::chrono::high_resolution_clock::now();
      std::chrono::duration<double> diff4 = end4 - start4;
      cout<<fileSize << " studentu rusiavimas i galvocius ir nuskriaustuosius uztruko: "<<diff4.count()<<endl;
      int galv = galvociai.size();
      int nus = nuskriaustieji.size();
      auto start5 = std::chrono::high_resolution_clock::now();
      writeToFile(galvociai, pavad1, galv);
      auto end5 = std::chrono::high_resolution_clock::now();
      std::chrono::duration<double> diff5 = end5 - start5;
      cout<<fileSize << " galvociu irasymas i faila uztruko: "<<diff5.count()<<endl;

      auto start6 = std::chrono::high_resolution_clock::now();
      writeToFile(nuskriaustieji, pavad2, nus);
      auto end6 = std::chrono::high_resolution_clock::now();
      std::chrono::duration<double> diff6 = end6 - start6;
      cout<<fileSize << " nuskriaustuju irasymas i faila uztruko: "<<diff6.count()<<endl;
      cout << "----------------------------" << endl;
      // first_st.clear();
      // nuskriaustieji.clear();
      // galvociai.clear();
      fileSize = fileSize *10;
    }
    
  }
  return 0;
}
