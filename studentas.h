#pragma once
#include <bits/stdc++.h>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <stdexcept>
#include <chrono>
#include <stdlib.h>
#include <fstream>
#include <sstream> 
#include <vector> 

using std::cout;
using std::cin;
using std::string;
using std::endl;
using std::sort;
using std::vector;
using std::ifstream;
using std::ofstream;
using std::ws;
using std::istream_iterator;
using std::distance;
using std::stringstream;
using std::exception;
using std::setw;
using std::left;
using std::to_string;

struct Studentas {
  string st_Vardas;
  string st_Pavarde;
  int nd_kiekis = 0;
  vector <int> nd_balai;
  int egz_rez;
  double rez;
};

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
  ofstream o(name);
  int nd_k = rand() % 8 + 1;
  o<<setw(20)<<left<<"Vardas"<<setw(20)<<left<<"Pavarde";
  for(int i=0; i<nd_k; i++)
  {
    o<<setw(20)<<left<<"Nd_"+to_string(i);
  }
  o << setw(20)<<left<<"Egz" << endl;
  for(int i=0; i<fileSize; i++)
  {
    o<<setw(20)<<left<<"Vardas_"+ to_string(i)<<setw(20)<<left<<"Pavarde_"+ to_string(i);
    for (int i=0; i<nd_k; i++)
    {
      int nd = rand() % 10 + 1;
      o<<setw(20)<<left<<nd;
    }
    int egz = rand() % 10 + 1;
    o <<setw(20)<<left<<egz << endl;
  }
}

void writeToFile(vector <Studentas> &stud, string &file_name, int &fileSize)
{
  ofstream o(file_name);
  for (int i = 0; i<fileSize; i++)
    {
      o <<stud.at(i).st_Vardas<<  std::setw(20) << stud.at(i).st_Pavarde << std::setw (20) << stud.at(i).rez<< endl;
    }
}

void failo_skaitymas(vector<Studentas> &kint, int fileSize, string file_name, string vid_or_med)
{
  int stud = 0;
  int paz_sk;
  double temp, s;
  ifstream fileRead(file_name);
  auto start = std::chrono::high_resolution_clock::now();
  string buff;
  if(fileRead.is_open())
  {
    getline (fileRead >> ws, buff);
    stringstream stream(buff);
    paz_sk = (distance(istream_iterator<string>(stream), istream_iterator<string>())) - 3;
    while(stud < fileSize)
    {
      kint.resize(kint.size() + 1);
      fileRead>>kint.at(stud).st_Vardas;
      fileRead>>kint.at(stud).st_Pavarde;
      s=0;
      for (int i=0;i<paz_sk; i++)
      {
        fileRead >> temp;
        kint.at(stud).nd_balai.push_back(temp);
        s+=temp;
      }
      fileRead >> kint.at(stud).egz_rez;
      kint[stud].rez = mediOrAvg(vid_or_med, kint, s, stud);
      stud ++;
    }
  }
auto end = std::chrono::high_resolution_clock::now();
std::chrono::duration<double> diff = end - start;
cout<<fileSize << " studentu nuskaitymas uztruko: "<<diff.count()<<endl;
}  


bool compareTwoStudents(Studentas a, Studentas b)
{
    if (a.rez != b.rez)
        return a.rez > b.rez;
    return a.st_Vardas > b.st_Vardas;
}