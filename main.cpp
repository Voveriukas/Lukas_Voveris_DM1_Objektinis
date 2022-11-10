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
    vector <Studentas> nuskriaustieji_scnd;
    list <Studentas> galvociai_list;
    list <Studentas> nuskriaustieji_list;
    list <Studentas> nuskriaustieji_scnd_list;
    string file_name = "studentai_" + to_string(fileSize) + ".txt";
    string pavad1 = "vector_galvociai_" + to_string(fileSize) + ".txt";
    string pavad2 = "vector_nuskriaustieji_" + to_string(fileSize) + ".txt";
    string pavad1_list = "list_galvociai_" + to_string(fileSize) + ".txt";
    string pavad2_list = "list_nuskriaustieji_" + to_string(fileSize) + ".txt";
    string pavad1_scnd_list = "list_galvociai_scnd_" + to_string(fileSize) + ".txt";
    string pavad2_scnd_list = "list_nuskriaustieji_scnd_" + to_string(fileSize) + ".txt";
    string pavad_scnd_vector = "vector_2nd_nuskriaustieji_" + to_string(fileSize) + ".txt";
    string pavad_scnd_galv_vector = "vector_2nd_galv_" + to_string(fileSize) + ".txt";
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
    // Vector operations 1st
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

    int kiek2 = nuskriaustieji.size();
    writeToFile(nuskriaustieji, pavad2,kiek2);
    int kiek4 = galvociai.size();
    writeToFile(galvociai, pavad1,kiek4);
    //List operations 1st
    auto start3 = std::chrono::high_resolution_clock::now();
    failo_skaitymas_list(second_st, file_name, vid_or_med, student_kiekis);
    auto end3 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff3 = end3 - start3;

    auto start4 = std::chrono::high_resolution_clock::now();
    second_st.sort(compareTwoStudents);
    dalintiSarasa(second_st, nuskriaustieji_list, galvociai_list);
    auto end4 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff4 = end4 - start4;
    int kiek5 = nuskriaustieji_list.size();
    writeToFile(nuskriaustieji, pavad2_list,kiek5);
    int kiek6 = galvociai_list.size();
    writeToFile(galvociai, pavad1_list,kiek6);

    // Vector operation 2nd

    auto start5 = std::chrono::high_resolution_clock::now();
    sort(first_st.begin(), first_st.end(), compareTwoStudents);
    first_st.erase(remove_if(first_st.begin(), first_st.end(), [&nuskriaustieji_scnd](Studentas s) {
        if (s.rez < 5.00) {
            nuskriaustieji_scnd.push_back(s);
            return true;
        }
        else { return false; }
        }), first_st.end());
    auto end5 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff5 = end5 - start5;
    int kiek1 = nuskriaustieji_scnd.size();
    int kiek3 = first_st.size();
    writeToFile(nuskriaustieji_scnd, pavad_scnd_vector,kiek1);
    writeToFile(first_st, pavad_scnd_galv_vector,kiek3);

    // List operation 2nd

    auto start6 = std::chrono::high_resolution_clock::now();
    second_st.sort(compareTwoStudents);
    second_st.erase(remove_if(second_st.begin(), second_st.end(), [&nuskriaustieji_scnd_list](Studentas s) {
        if (s.rez < 5.00) {
            nuskriaustieji_scnd_list.push_back(s);
            return true;
        }
        else { return false; }
        }), second_st.end());
    auto end6 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff6 = end6 - start6;
    int kiek7 = nuskriaustieji_scnd_list.size();
    int kiek8 = second_st.size();
    writeToFile(nuskriaustieji_scnd_list, pavad2_scnd_list,kiek1);
    writeToFile(second_st, pavad1_scnd_list,kiek3);
    //
    cout << string(82, '-')<< endl;
    cout << "|        Veiksmu su " << fileSize << " dydzio failu palyginimas naudojant list ir vector       |" << endl;
    cout << string(82, '-')<< endl;
    cout << "| " << setw(30) << left << "Naudojamas konteineris" << " | " << setw(45) << left << "Rusiavimas i nuskriaustuosius ir galvocius" << " | " << endl;
    cout << "| " << setw(30) << left << "Vector 1 strategija" << " | " << setw(45) << left << diff2.count() << " | " << endl;
    cout << "| " << setw(30) << left << "List 1 strategija" << " | " << setw(45) << left << diff4.count() << " | " << endl;
    cout << "| " << setw(30) << left << "Vector 2 strategija" << " | " << setw(45) << left << diff5.count() << " | " << endl;
    cout << "| " << setw(30) << left << "List 2 strategija" << " | " << setw(45) << left << diff6.count() << " | " << endl;
    cout << string(82, '-') << endl;
  }
  return 0;
}
