#include <iostream>
#include <string>
using namespace std;

int table1[10], table2[10], table3[10], table4[10];

// Initialize all tables to 0
void initializeTables() {
    for (int i = 0; i < 10; i++) {
        table1[i] = 0;
        table2[i] = 0;
        table3[i] = 0;
        table4[i] = 0;
    }
}

// Hash functions
int hashFunc1(int value) {
    return (value * 2 + 2) % 10;
}

int hashFunc2(int value) {
    return (value * 3 + 3) % 10;
}

int hashFunc3(int value) {
    return (value * 4 + 4) % 10;
}

int hashFunc4(int value) {
    return (value * 5 + 5) % 10;
}

// Convert string to number by summing ASCII values
int convertStringToNumber(string str) {
    int result = 0;
    int len = str.length();
    for (int i = 0; i < len; ++i) {
        result += (int)str[i];
    }
    return result;
}

// Print all hash tables
void printTables() {
    cout << "\nHash Table 1: ";
    for (int i = 0; i < 10; i++) cout << table1[i] << " ";
    cout << "\nHash Table 2: ";
    for (int i = 0; i < 10; i++) cout << table2[i] << " ";
    cout << "\nHash Table 3: ";
    for (int i = 0; i < 10; i++) cout << table3[i] << " ";
    cout << "\nHash Table 4: ";
    for (int i = 0; i < 10; i++) cout << table4[i] << " ";
    cout << endl;
}

// Insert value into the Count-Min Sketch
void insertValue(string str) {
    int num = convertStringToNumber(str);
    int h1 = hashFunc1(num);
    int h2 = hashFunc2(num);
    int h3 = hashFunc3(num);
    int h4 = hashFunc4(num);

    table1[h1]++;
    table2[h2]++;
    table3[h3]++;
    table4[h4]++;

    cout << "\nInserting data: " << str << "\nHash values: h1 => " << h1 
         << ", h2 => " << h2 << ", h3 => " << h3 << ", h4 => " << h4;
    
    printTables();
}

// Get count of a value from the Count-Min Sketch
void getCount(string str) {
    int num = convertStringToNumber(str);
    int h1 = hashFunc1(num);
    int h2 = hashFunc2(num);
    int h3 = hashFunc3(num);
    int h4 = hashFunc4(num);

    int counts[4] = { table1[h1], table2[h2], table3[h3], table4[h4] };
    
    int minCount = counts[0];
    for (int i = 1; i < 4; i++) {
        if (counts[i] < minCount) {
            minCount = counts[i];
        }
    }

    cout << "\nSearching for data: " << str << "\nHash values: h1 => " << h1 
         << ", h2 => " << h2 << ", h3 => " << h3 << ", h4 => " << h4;
    
    cout << "\nThe data has been received " << minCount << " times.";
}

int main() {
    string inputData;
    int continueInput = 1;

    initializeTables(); // Initialize tables to zero

    // Input loop for inserting data
    do {
        cout << "\nEnter data to insert: ";
        cin >> inputData;
        insertValue(inputData);

        cout << "\nDo you want to insert more data? (0/1): ";
        cin >> continueInput;
    } while (continueInput != 0);

    // Input loop for searching data count
    continueInput = 1;
    do {
        cout << "\nEnter data to search: ";
        cin >> inputData;
        getCount(inputData);

        cout << "\nDo you want to search for more data? (0/1): ";
        cin >> continueInput;
    } while (continueInput != 0);

    return 0;
}