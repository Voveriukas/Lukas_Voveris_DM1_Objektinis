#pragma once
#include <bits/stdc++.h>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <stdexcept>

using std::cout;
using std::cin;
using std::string;
using std::endl;
using std::sort;
using std::vector;
using std::ifstream;
using std::ws;
using std::istream_iterator;
using std::distance;
using std::stringstream;
using std::exception;

struct Studentas {
  string st_Vardas;
  string st_Pavarde;
  int nd_kiekis = 0;
  vector <int> nd_balai;
  int egz_rez;
  double rez;
};