#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
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
    vector<Studentas> studentai;
    char pasirinkimas;
    char testi = 't';

    while (testi == 't') {
        Studentas studentas;
        
        cout << "Iveskite studento varda ir pavarde: ";
        cin >> studentas.vardas >> studentas.pavarde;

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
        
        studentai.push_back(studentas);
        
        cout << "Ar norite ivesti kita studenta? (t - taip, n - ne): ";
        cin >> testi;
    }

    cout << "Pasirinkite skaiciavimo metoda (v - vidurkis, m - mediana, a - abu): ";
    cin >> pasirinkimas;

    if (pasirinkimas == 'v') {
        cout << "Vardas" << setw(15) << "Pavarde" << setw(35) << "Galutinis (Vid.)" << endl;
        cout << "--------------------------------------------------------------" << endl;
        for (const auto& studentas : studentai) {
            double galutinis_vid = 0.4 * vidurkis(studentas.nd) + 0.6 * studentas.egzaminas;
            cout << fixed << setprecision(2) << studentas.vardas << setw(15) << studentas.pavarde << setw(15) << galutinis_vid << endl;
        }
    } else if (pasirinkimas == 'm') {
        cout << "Vardas" << setw(15) << "Pavarde" << setw(35) << "Galutinis (Med.)" << endl;
        cout << "--------------------------------------------------------------" << endl;
        for (const auto& studentas : studentai) {
            double galutinis_med = 0.4 * mediana(studentas.nd) + 0.6 * studentas.egzaminas;
            cout << fixed << setprecision(2) << studentas.vardas << setw(15) << studentas.pavarde << setw(15) << galutinis_med << endl;
        }
    } else if (pasirinkimas == 'a') {
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

    

    return 0;
}