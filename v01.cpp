#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

struct Studentas {
    string vardas;
    string pavarde;
    vector<int> nd;
    double egzaminas;
};

double vidurkis(vector<int> nd) {
    double suma = 0;
    for (int i = 0; i < nd.size(); i++) {
        suma += nd[i];
    }
    return suma / nd.size();
}

double mediana(vector<int> nd) {
    vector<int> temp = nd;
    sort(temp.begin(), temp.end());
    int n = temp.size();
    if (n % 2 == 0) {
        return (temp[n/2 - 1] + temp[n/2]) / 2.0;
    } else {
        return temp[n/2];
    }
}


int main() {
    srand(time(0)); 
    vector<Studentas> studentai;
    char meniu_pasirinkimas;
    char skaiciavimo_pasirinkimas;
    char testi = 't';

    while (true) {
        cout << endl << "MENU" << endl;
        cout << "1. Sarasas" << endl;
        cout << "2. Prideti studenta" << endl;
        cout << "3. Stabdyti programa" << endl;
        cout << "Pasirinkite veiksma (1-3): ";
        cin >> meniu_pasirinkimas;

        if (meniu_pasirinkimas == '1') {
            if (studentai.empty()) {
                cout << "Studentu sarasas tuscias!" << endl;
                continue;
            }
            
            cout << "Pasirinkite skaiciavimo metoda (v - vidurkis, m - mediana, a - abu): ";
            cin >> skaiciavimo_pasirinkimas;
            
            if (skaiciavimo_pasirinkimas == 'v') {
                cout << "Vardas" << setw(15) << "Pavarde" << setw(35) << "Galutinis (Vid.)" << endl;
                cout << "--------------------------------------------------------------" << endl;
                for (const auto& studentas : studentai) {
                    double galutinis_vid = 0.4 * vidurkis(studentas.nd) + 0.6 * studentas.egzaminas;
                    cout << fixed << setprecision(2) << studentas.vardas << setw(15) << studentas.pavarde << setw(15) << galutinis_vid << endl;
                }
            } else if (skaiciavimo_pasirinkimas == 'm') {
                cout << "Vardas" << setw(15) << "Pavarde" << setw(35) << "Galutinis (Med.)" << endl;
                cout << "--------------------------------------------------------------" << endl;
                for (const auto& studentas : studentai) {
                    double galutinis_med = 0.4 * mediana(studentas.nd) + 0.6 * studentas.egzaminas;
                    cout << fixed << setprecision(2) << studentas.vardas << setw(15) << studentas.pavarde << setw(15) << galutinis_med << endl;
                }
            } else if (skaiciavimo_pasirinkimas == 'a') {
                cout << "Vardas" << setw(15) << "Pavarde" << setw(20) << "Galutinis (Vid.)" << setw(20) << "Galutinis (Med.)" << endl;
                cout << "----------------------------------------------------------------" << endl;
                for (const auto& studentas : studentai) {
                    double galutinis_vid = 0.4 * vidurkis(studentas.nd) + 0.6 * studentas.egzaminas;
                    double galutinis_med = 0.4 * mediana(studentas.nd) + 0.6 * studentas.egzaminas;
                    cout << fixed << setprecision(2) << studentas.vardas << setw(15) << studentas.pavarde << setw(15) << galutinis_vid << setw(15) << galutinis_med << endl;
                }
            } else {
                cout << "Neteisingas pasirinkimas! Naudojamas vidurkis." << endl;
                cout << "Vardas" << setw(15) << "Pavarde" << setw(35) << "Galutinis (Vid.)" << endl;
                cout << "--------------------------------------------------------------" << endl;
                for (const auto& studentas : studentai) {
                    double galutinis_vid = 0.4 * vidurkis(studentas.nd) + 0.6 * studentas.egzaminas;
                    cout << fixed << setprecision(2) << studentas.vardas << setw(15) << studentas.pavarde << setw(15) << galutinis_vid << endl;
                }
            }
        } else if (meniu_pasirinkimas == '2') {
            while (testi == 't') {
                Studentas studentas;
                
                cout << "Iveskite studento varda ir pavarde: ";
                cin >> studentas.vardas >> studentas.pavarde;

                char generuoti;
                cout << "Ar norite generuoti pazymius atsitiktinai? (t - taip, n - ne): ";
                cin >> generuoti;

                if (generuoti == 't') {
                    int k = 20;
                    int nd_skaicius = rand() % k + 1; 
                    
                    for (int i = 0; i < nd_skaicius; i++) {
                        studentas.nd.push_back(rand() % 10 + 1);
                    }
                    
                    studentas.egzaminas = rand() % 10 + 1;
                    cout << "Sugeneruota " << nd_skaicius << " namu darbu pazymiu ir egzamino pazymys!" << endl;
                } else {
                    cout << "Iveskite namu darbu pazymius (baigti - du kartus ENTER): ";
                    string eilute;
                    getline(cin >> ws, eilute);

                    while (!eilute.empty()) {
                        int pazymys = stoi(eilute);
                        studentas.nd.push_back(pazymys);
                        getline(cin, eilute);
                    }
                    
                    cout << "Iveskite egzamino pazymi: ";
                    cin >> studentas.egzaminas;
                }
                
                studentai.push_back(studentas);
                cout << "Ar norite ivesti kita studenta? (t - taip, n - ne): ";
                cin >> testi;
            }
            testi = 't';
        } else if (meniu_pasirinkimas == '3') {
            cout << "Programa stabdoma..." << endl;
            break;
        } else {
            cout << "Neteisingas pasirinkimas! Bandykite dar kartą." << endl;
        }
    }

    return 0;
}