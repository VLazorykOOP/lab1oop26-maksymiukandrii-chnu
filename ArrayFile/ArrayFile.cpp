#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

template <typename T>
void Enter(const string& fName) {
    int nA;
    cout << "Enter array size: "; cin >> nA;
    if (nA <= 0) return;

    T* mas = new T[nA];
    cout << "Enter " << nA << " elements:\n";
    for (int i = 0; i < nA; i++) cin >> mas[i];

    ofstream fOut(fName);
    if (fOut.is_open()) {
        fOut << nA << endl;
        for (int i = 0; i < nA; i++) fOut << mas[i] << " ";
        fOut.close();
    }
    delete[] mas;
}

template <typename T>
void Generate(const string& fName) {
    int nA;
    cout << "Enter array size: "; cin >> nA;
    if (nA <= 0) return;

    T* mas = new T[nA];
    for (int i = 0; i < nA; i++) {
        mas[i] = (rand() % 100 - 50);
    }

    ofstream fOut(fName, ios::binary);
    if (fOut.is_open()) {
        fOut.write((char*)&nA, sizeof(int));
        fOut.write((char*)mas, nA * sizeof(T));
        fOut.close();
    }
    delete[] mas;
}

//Saved file

template <typename T>
void Print(const string& fName, bool isBin) {
    vector<T> v;
    int nA;

    if (isBin) {
        ifstream fIn(fName, ios::binary);
        if (!fIn) return;
        fIn.read((char*)&nA, sizeof(int));
        v.resize(nA);
        fIn.read((char*)v.data(), nA * sizeof(T));
        fIn.close();
    }
    else {
        ifstream fIn(fName);
        if (!fIn) return;
        fIn >> nA;
        v.resize(nA);
        for (int i = 0; i < nA; i++) fIn >> v[i];
        fIn.close();
    }

    cout << "Data: ";
    for (int i = 0; i < v.size(); i++) cout << v[i] << " ";
    cout << endl;
}

//Task 1
void Task1(const string& inF, bool isBin, const string& outF) {
    int nA;
    int* A;
    if (isBin) {
        ifstream fIn(inF, ios::binary);
        fIn.read((char*)&nA, sizeof(int));
        A = new int[nA];
        fIn.read((char*)A, nA * sizeof(int));
        fIn.close();
    }
    else {
        ifstream fIn(inF);
        fIn >> nA;
        A = new int[nA];
        for (int i = 0; i < nA; i++) fIn >> A[i];
        fIn.close();
    }
    long long* C = new long long[nA];
    ofstream fOut(outF);
    fOut << nA << endl;
    for (int i = 0; i < nA; i++) {
        C[i] = (long long)A[i] * (1LL << (i + 1));
        cout << C[i] << " ";
        fOut << C[i] << " ";
    }
    cout << endl;
    fOut.close();
    delete[] A; delete[] C;
}

//Task 2
void Task2(const string& inF, bool isBin, const string& outF) {
    int nA;
    ifstream fIn(inF, isBin ? ios::binary : ios::in);
    if (isBin) fIn.read((char*)&nA, sizeof(int)); else fIn >> nA;
    int* mas = new int[nA];
    if (isBin) fIn.read((char*)mas, nA * sizeof(int)); else for (int i = 0; i < nA; i++) fIn >> mas[i];
    fIn.close();
    int c, d;
    cout << "Range [c, d]: "; cin >> c >> d;
    int* p = mas;
    int maxVal = -1000000, maxIdx = -1;
    bool hasMatch = false;
    for (int i = 0; i < nA; i++, p++) {
        if (*p % 2 == 0) break;
        if (*p >= c && *p <= d) {
            if (!hasMatch || *p >= maxVal) {
                maxVal = *p; maxIdx = i; hasMatch = true;
            }
        }
    }
    if (hasMatch) cout << "Idx: " << maxIdx << " Val: " << maxVal << endl;
    else cout << "Not found" << endl;
    delete[] mas;
}

//Task 3
void Task3(const string& inF, bool isBin, const string& outF) {
    int nA;
    ifstream fIn(inF, isBin ? ios::binary : ios::in);
    if (isBin) fIn.read((char*)&nA, sizeof(int)); else fIn >> nA;
    double* A = new double[nA];
    if (isBin) fIn.read((char*)A, nA * sizeof(double)); else for (int i = 0; i < nA; i++) fIn >> A[i];
    fIn.close();
    double sumRep = 0, prdUnq = 1;
    bool foundRep = false, foundUnq = false;
    for (int i = 0; i < nA; i++) {
        int count = 0;
        for (int j = 0; j < nA; j++) if (A[i] == A[j]) count++;
        if (count > 1) { sumRep += A[i]; foundRep = true; }
        else if (count == 1) { prdUnq *= A[i]; foundUnq = true; }
    }
    if (foundRep) cout << "Sum Rep: " << sumRep << endl;
    if (foundUnq) cout << "Prd Unq: " << prdUnq << endl;
    delete[] A;
}

//Menu

void handleTask(int TaskN) {
    int cmd;
    do {
        cout << "\nTask " << TaskN << "\n";
        cout << "1. Enter\n2. Generate\n3. Solve (TXT)\n4. Solve (BIN)\n5. Print TXT\n6. Print BIN\n0. Back Menu\nChoice: ";
        cin >> cmd;

        string inF = "data" + to_string(TaskN) + ".txt";
        string bFile = "data" + to_string(TaskN) + ".bin";
        string outF = "res" + to_string(TaskN) + ".txt";

        if (cmd == 1) TaskN == 3 ? Enter<double>(inF) : Enter<int>(inF);
        else if (cmd == 2) TaskN == 3 ? Generate<double>(bFile) : Generate<int>(bFile);
        else if (cmd == 3) {
            if (TaskN == 1) Task1(inF, false, outF);
            else if (TaskN == 2) Task2(inF, false, outF);
            else Task3(inF, false, outF);
        }
        else if (cmd == 4) {
            if (TaskN == 1) Task1(bFile, true, outF);
            else if (TaskN == 2) Task2(bFile, true, outF);
            else Task3(bFile, true, outF);
        }
        else if (cmd == 5) TaskN == 3 ? Print<double>(inF, false) : Print<int>(inF, false);
        else if (cmd == 6) TaskN == 3 ? Print<double>(bFile, true) : Print<int>(bFile, true);
    } while (cmd != 0);
}

int main() {
    srand(time(0));
    int menu;
    do {
        cout << "\n--- Menu ---\n";
        cout << "1. Task 1\n2. Task 2\n3. Task 3\n0. Exit\nChoice: ";
        cin >> menu;
        if (menu > 0 && menu <= 3) handleTask(menu);
    } while (menu != 0);
    return 0;
}