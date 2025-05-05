#include <iostream>
#include <string>
#include <climits>
using namespace std;

int bloomHash1(const string &s, int size) {
    int hash = 0;
    for (char c : s) {
        hash += static_cast<int>(c);
        hash %= size;
    }
    return hash;
}

int bloomHash2(const string &s, int size) {
    int hash = 1;
    for (size_t i = 0; i < s.size(); ++i) {
        hash += (i * static_cast<int>(s[i]));
        hash %= size;
    }
    return hash;
}

int bloomHash3(const string &s, int size) {
    int hash = 2;
    for (char c : s) {
        hash = (hash * 31 + static_cast<int>(c)) % size;
    }
    return hash;
}

void insertBloom(int bloomFilter[], const string &name, int size) {
    int a = bloomHash1(name, size);
    int b = bloomHash2(name, size);
    int c = bloomHash3(name, size);

    if (bloomFilter[a] == 1 && bloomFilter[b] == 1 && bloomFilter[c] == 1) {
        cout << "\nThe Name is Probably Present !!";
    } else {
        bloomFilter[a] = 1;
        bloomFilter[b] = 1;
        bloomFilter[c] = 1;
        cout << name << " is inserted !!";
    }

    cout << "\nBloom Filter Bit Array: ";
    for (int i = 0; i < size; ++i) {
        cout << bloomFilter[i] << " ";
    }
    cout << endl;
}

int cmsHash(const string& str, int seed, int mod) {
    int hash = seed;
    for (char c : str) {
        hash = (hash * 31 + c) % mod;
    }
    return hash;
}

void insertCMS(int cms[][20], const string& str, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        int idx = cmsHash(str, i + 17, cols);
        cms[i][idx]++;
    }
}

int estimateCMS(int cms[][20], const string& str, int rows, int cols) {
    int minCount = INT_MAX;
    for (int i = 0; i < rows; i++) {
        int idx = cmsHash(str, i + 17, cols);
        minCount = min(minCount, cms[i][idx]);
    }
    return minCount;
}

int main() {
    int choice;
    do {
        cout << "\nWhich Filter Do You Want To Choose\n(1) Bloom Filter\n(2) Count-Min Sketch\n(0) Exit\nEnter Your Choice-- > ";
        cin >> choice;

        if (choice == 1) {
            int bloomFilter[10] = {0};
            string name;
            int continueInsert;
            do {
                cout << "\nEnter the name you want to insert: ";
                cin >> name;
                insertBloom(bloomFilter, name, 10);
                cout << "\nDo you want to insert another name (1/0): ";
                cin >> continueInsert;
            } while (continueInsert != 0);
        }
        else if (choice == 2) {
            int cms[4][20] = {0};
            string name;
            int continueInsert;
            do {
                cout << "\nEnter string to insert in CMS: ";
                cin >> name;
                insertCMS(cms, name, 4, 20);
                cout << name << " inserted in CMS!";
                cout << "\nEstimated frequency: " << estimateCMS(cms, name, 4, 20);
                cout << "\nDo you want to insert more strings (1/0): ";
                cin >> continueInsert;
            } while (continueInsert != 0);
        }
        else if (choice == 0) {
            cout << "Exiting Program...";
            break;
        }
        else {
            cout << "Invalid Input!!!";
        }
    } while (choice != 0);

    return 0;
}
