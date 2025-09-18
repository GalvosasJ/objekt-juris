#include <iostream>
#include <vector>
#include <iomanip>
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


int main() {
    Studentas studentas;
    int n;

    cout << "Iveskite studento varda ir pavarde: ";
    cin >> studentas.vardas >> studentas.pavarde;

    cout << "Iveskite studento namu darbu skaiciu: ";
    cin >> n;

    cout << "Iveskite " << n << " nd pazymius: ";
    for (int i = 0; i < n; i++) {
        int pazymys;
        cin >> pazymys;
        studentas.nd.push_back(pazymys);
    }
    cout << "Iveskite studento egzamino pazymi: ";
    cin >> studentas.egzaminas;

    double galutinis = 0.4 * vidurkis(studentas.nd) + 0.6 * studentas.egzaminas;

    cout << "Vardas" << setw(15) << "Pavarde" << setw(35) << "Galutinis (Vid.)" << endl;
    cout << "--------------------------------------------------------------" << endl;
    cout << studentas.vardas << setw(15) << studentas.pavarde << setw(15) << galutinis << endl;


    return 0;
}