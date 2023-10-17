#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include "sais.cpp"
using namespace std;
using std::chrono::duration;
using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;
using std::chrono::milliseconds;

int menu() {
  int choi;
  cout << "*****SELECCIONE LIBRO POR CARGAR*****" << endl;
  cout << "1. Metamorfosis de Franz Kafka" << endl;
  cout << "2. Una modesta proposicion de Jonathan Swift" << endl;
  cout << "3. La Republica de Platon" << endl;
  cout << "4. Las Aventuras de Tom Sawyer de Mark Twain" << endl;
  cout << "5. Memorias del Subsuelo de Dostoyevski" << endl;
  cout << "0. Terminar ejecucion" << endl;
  cout << "*****ESCRIBA NUMERO DE SU ELECCION*****" << endl;
  cout << "> ";
  try {
    cin >> choi;
    while (choi < 0 || choi > 5) {
      cout << "Escriba un numero valido" << endl;
      cout << "> ";
      cin >> choi;
    }
  } 
  catch (...) {
    cout << "\nALERTA: Input invalido" << endl;
    cout << endl << endl << endl;
    choi = menu();
  }

  return choi;
}

void fileReader(int choi, string & txt) {
  string filename;
  if (choi == 1)
      filename += "resources/metamorphosis.txt";
  else if (choi == 2)
      filename += "resources/a_modest_proposal.txt";
  else if (choi == 3)
      filename += "resources/therepublic.txt";
  else if (choi == 4)
      filename += "resources/tomsawyer.txt";
  else if (choi == 5)
      filename += "resources/underground.txt";

  ifstream cin(filename);
  stringstream ss;
  string tmp;
  while (cin >> tmp) 
    ss << tmp << "_";

  txt = ss.str();
  txt[txt.size() - 1] = '$';
  txt = string(txt.begin() + 3, txt.end());
}

void search(const string& txt, const vector<int>& SA, const string& query,
            vector<int>& occurrences) {
  int n = txt.size(), m = query.size(), i;
  int left = 0, right = n - 1, mid;
  string suffix;
  while (left <= right) {
    mid = (left + right) / 2;
    suffix = string(txt.begin() + SA[mid],
                    txt.begin() + SA[mid] + m);  // Adjust here to use SA[mid]

    if (query == suffix) {
      // Found a match, append it to the list of occurrences
      occurrences.push_back(SA[mid]);

      // continue searching to the right
      i = mid + 1;
      while (i < n &&
             string(txt.begin() + SA[i], txt.begin() + SA[i] + m) == query) {
        occurrences.push_back(SA[i]);
        i += 1;
      }

      // continue searching to the left
      i = mid - 1;
      while (i >= 0 &&
             string(txt.begin() + SA[i], txt.begin() + SA[i] + m) == query) {
        occurrences.push_back(SA[i]);
        i -= 1;
      }

      break;
    }

    else if (query > suffix)
      left = mid + 1;
    else
      right = mid - 1;
  }

  sort(occurrences.begin(), occurrences.end());
}

int main() {
  int choi;
  string txt;
  
  for (;;) {
    choi = menu();
    if (choi == 0) break;
    auto t1 = high_resolution_clock::now();
    fileReader(choi, txt);

    vector<int> T;
    for (auto& c : txt) T.push_back((int) c);
    vector<int> SA(T.size(), -1);

    sais(T, SA);
    auto t2 = high_resolution_clock::now();
    duration<double, milli> ms_double = t2 - t1;

    //cout << "[ ";
    //for (auto& el : SA) cout << el << " ";
    //cout << "]" << endl << endl << endl;

    cout << "Substring to find: ";
    string query;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, query);
    vector<int> found;
    search(txt, SA, query, found);

    cout << "Ocurrences of '" << query << "' [ ";
    for (auto & ele : found)
      cout << ele << " ";
    cout << "]" << endl << endl << endl;

    cout << "\n*****TELEMETRIA DE LIBRO " << choi << "*****" << endl;
    cout << "Tiempo de ejecucion: " << ms_double.count() / 1000 << "s" << endl;
    cout << endl << endl;
  }

  return 0;
}