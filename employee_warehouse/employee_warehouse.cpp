#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>

using namespace std;

// Create a struct to hold the data
struct Inventory {
    char partName[20];
    int NumberOfParts;
};

// Function prototypes
int ReadEmpData(Inventory item[]);
void PrintEmpData(Inventory data);
void headings();
void menu(Inventory item[], int numWares);

int main() {
    headings();
    Inventory wares[10];
    int numWares = ReadEmpData(wares);
    for (int i = 0; i < numWares; i++) {
        PrintEmpData(wares[i]);
    }
    menu(wares, numWares);
    return 0;
}

// Function to read the data from the file and input it into the struct
int ReadEmpData(Inventory item[]) {
    int ware_records = 0;
    ifstream fin("warehouseInventory.txt");

    if (fin.is_open()) {
        while (ware_records < 11 && fin.peek() != EOF) {
            string line;
            getline(fin, line);

            stringstream ss(line);
            ss >> item[ware_records].partName >> item[ware_records].NumberOfParts;
            ware_records++;
        }
        fin.close();
    }
    else {
        cout << "Error: File not found" << endl;
    }

    return ware_records;
}

// Function to print the headings for the table
void headings() {
    cout << right << setw(1) << "Description of parts"
        << right << setw(20) << "Number of parts"
        << endl;
}

// Function to print the inventory data
void PrintEmpData(Inventory data) {
    cout << left << setw(15) << data.partName
        << right << setw(20) << data.NumberOfParts << endl;
}

// Function to add or remove parts from inventory and to save and exit
void menu(Inventory item[], int numWares) {
    string menuChoice;
    int index, change;

    while (true) {
        cout << "Would you like to add or remove parts? (Type 'save' to exit and save the changes): ";
        cin >> menuChoice;
        //saving the changes to the txt file 
        if (menuChoice == "save") {
            ofstream fout("warehouseInventory.txt");
            if (fout.is_open()) {
                for (int i = 0; i < numWares; i++) {
                    fout << item[i].partName << " " << item[i].NumberOfParts << endl;
                }
                fout.close();
                cout << "Changes saved to file." << endl;
            }
            else {
                cout << "Error: Unable to open file for writing." << endl;
            }
            break;
        }
        //choosing to use indexes instead of pointers hopefully wont be docked points 
        cout << "Which part (Enter index 0 to " << numWares - 1 << "): ";
        cin >> index;
        if (index < 0 || index >= numWares) {
            cout << "Invalid index. Please enter a number between 0 and " << numWares - 1 << "." << endl;
            continue;
        }
        //adding or removing parts 
        cout << "How many parts: ";
        cin >> change;
        if (menuChoice == "add") {
            if (change < 0 || item[index].NumberOfParts + change > 30) {
                cout << "Invalid number of parts to add." << endl;
            }
            else {
                item[index].NumberOfParts += change;
            }
        }
        else if (menuChoice == "remove") {
            if (change < 0 || item[index].NumberOfParts - change < 0) {
                cout << "Invalid number of parts to remove." << endl;
            }
            else {
                item[index].NumberOfParts -= change;
            }
        }
        else {
            cout << "Invalid choice." << endl;
        }

        cout << "Updated inventory:" << endl;
        for (int i = 0; i < numWares; i++) {
            PrintEmpData(item[i]);
        }
    }
}
