#include <iostream>
#include <fstream>
#include <sstream>
#include "sais.cpp"
using namespace std;

int menu() {
  int choi;
  cout << "*****SELECCIONE LIBRO POR CARGAR*****" << endl;
  cout << "1. Metamorfosis de Franz Kafka" << endl;
  cout << "2. La Iliada de Homero" << endl;
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
      filename += "resources/theiliad.txt";
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
  cout << txt << endl;
}

int main() {
  int choi;
  string txt;
  
  for (;;) {
    choi = menu();
    if (choi == 0) break;
    fileReader(choi, txt);

    vector<int> T;
    for (auto& c : txt) T.push_back((int) c);
    vector<int> SA(T.size(), -1);
    //for (auto& c : T) cout << c << " ";

    sais(T, SA);

    cout << "[ ";
    for (auto& el : SA) cout << el << " ";
    cout << "]" << endl;
  }

  return 0;
}