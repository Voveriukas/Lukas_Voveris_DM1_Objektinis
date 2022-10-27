#include "mylib.h"

int main() {
  srand(time(NULL));
  int student_kiekis=0;
  vector <Studentas> first_st;
  list <Studentas> second_st;
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
    int fileSize;
    char yra_st;
    cout << "Iveskite failo dydi: "; cin >> fileSize;
    vector <Studentas> galvociai;
    vector <Studentas> nuskriaustieji;
    list <Studentas> galvociai_list;
    list <Studentas> nuskriaustieji_list;
    string file_name = "studentai_" + to_string(fileSize) + ".txt";
    string pavad1 = "vector_galvociai_" + to_string(fileSize) + ".txt";
    string pavad2 = "vector_nuskriaustieji_" + to_string(fileSize) + ".txt";
    string pavad1_list = "list_galvociai_" + to_string(fileSize) + ".txt";
    string pavad2_list = "list_nuskriaustieji_" + to_string(fileSize) + ".txt";
    // File create
    cout << "Ar norite sugeneruoti nauja faila? (T / N) "; cin >> yra_st;
     while (yra_st != 'T' && yra_st != 'N' && yra_st !=  't' && yra_st != 'n') {
        cout << "Ivedama reiksme turi buti arba T arba N" << endl;
        cout << "Bandykite is naujo: " << endl;
        cin.clear();
        cin.ignore(256, '\n');
        cin >> yra_st;
      }
    if(yra_st=='T' || yra_st=='t')
    {
        generateFile(fileSize, file_name);
        cout << "Failas sugeneruotas" << endl;
    }
    // Vector operations
    auto start1 = std::chrono::high_resolution_clock::now();
    failo_skaitymasvec(first_st, file_name, vid_or_med, student_kiekis);
    auto end1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff1 = end1 - start1;

    std::chrono::duration<double> diff;
    auto start2 = std::chrono::high_resolution_clock::now();
    sort(first_st.begin(), first_st.end(), compareTwoStudents);
    dalintiSarasa(first_st, nuskriaustieji, galvociai);
    auto end2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff2 = end2 - start2;

    //List operations
    auto start3 = std::chrono::high_resolution_clock::now();
    failo_skaitymas_list(second_st, file_name, vid_or_med, student_kiekis);
    auto end3 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff3 = end3 - start3;

    auto start4 = std::chrono::high_resolution_clock::now();
    second_st.sort(compareTwoStudents);
    dalintiSarasaList(second_st, nuskriaustieji_list, galvociai_list);
    auto end4 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff4 = end4 - start4;

    //
    cout << string(99, '-')<< endl;
    cout << "|            Veiksmu su " << fileSize << " dydzio failu palyginimas naudojant list ir vector                    |" << endl;
    cout << string(99, '-')<< endl;
    cout << "| " << setw(50) << left << "Atliekamas veiksmas" << " | " << setw(20) << left << "Vector" << " | " << setw(20) << left << "List" << "|" << endl;
    cout << "| " << setw(50) << left << "Failo nuskaitymas" << " | " << setw(20) << left << diff1.count() << " | " << setw(20) << left << diff3.count() << "|" << endl;
    cout << "| " << setw(50) << left << "Failo rusiavimas i galvocius ir nuskriaustuosius" << " | " << setw(20) << left << diff2.count() << " | " << setw(20) << left << diff4.count() << "|" << endl;
    cout << "| " << setw(50) << left << "Bendras sugaistas laikas" << " | " << setw(20) << left << diff1.count()+diff2.count() << " | " << setw(20) << left << diff3.count()+diff4.count() << "|" << endl;
    cout << string(99, '-') << endl;
  }
  return 0;
}
