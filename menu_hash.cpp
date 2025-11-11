#include <iostream>
using namespace std;

const int TABLE_SIZE = 10;

struct Client {
    string name;
    string phone;
    bool occupied;

    Client() {
        name = "";
        phone = "";
        occupied = false;
    }
};

int hashFunction(string key) {
    int sum = 0;
    for (int i = 0; i < key.length(); i++)
        sum += key[i];
    return sum % TABLE_SIZE;
}

int secondHash(string key) {
    int sum = 0;
    for (int i = 0; i < key.length(); i++)
        sum += key[i];
    return 7 - (sum % 7); // For double hashing
}

void insert(Client table[], string name, string phone, int method) {
    int index = hashFunction(name);
    int originalIndex = index;
    int step = 1;

    for (int i = 0; i < TABLE_SIZE; i++) {
        if (!table[index].occupied) {
            table[index].name = name;
            table[index].phone = phone;
            table[index].occupied = true;
            return;
        }

        // Collision Handling
        if (method == 1)        // Linear Probing
            index = (originalIndex + step) % TABLE_SIZE;
        else if (method == 2)   // Quadratic Probing
            index = (originalIndex + step * step) % TABLE_SIZE;
        else if (method == 3)   // Double Hashing
            index = (originalIndex + step * secondHash(name)) % TABLE_SIZE;

        step++;
    }

    cout << "Hash table is full! Cannot insert.\n";
}

string search(Client table[], string name, int method) {
    int index = hashFunction(name);
    int originalIndex = index;
    int step = 1;

    for (int i = 0; i < TABLE_SIZE; i++) {
        if (!table[index].occupied)
            return "Not found";

        if (table[index].name == name)
            return table[index].phone;

        if (method == 1)
            index = (originalIndex + step) % TABLE_SIZE;
        else if (method == 2)
            index = (originalIndex + step * step) % TABLE_SIZE;
        else if (method == 3)
            index = (originalIndex + step * secondHash(name)) % TABLE_SIZE;

        step++;
    }

    return "Not found";
}

void display(Client table[]) {
    cout << "\nHash Table:\n";
    for (int i = 0; i < TABLE_SIZE; i++) {
        cout << i << ": ";
        if (table[i].occupied)
            cout << table[i].name << " -> " << table[i].phone;
        else
            cout << "Empty";
        cout << endl;
    }
}
int main() {
    Client table[TABLE_SIZE];
    int method, choice;
    string name, phone;

    cout << "Select collision handling method:\n";
    cout << "1. Linear Probing\n";
    cout << "2. Quadratic Probing\n";
    cout << "3. Double Hashing\n";
    cout << "Enter your choice (1/2/3): ";
    cin >> method;

    if (method < 1 || method > 3) {
        cout << "Invalid method selected.\n";
        return 1;
    }

    do {
        cout << "\nMenu:\n";
        cout << "1. Insert client\n";
        cout << "2. Search client\n";
        cout << "3. Display table\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter name: ";
            cin >> name;
            cout << "Enter phone number: ";
            cin >> phone;
            insert(table, name, phone, method);
            break;
        case 2:
            cout << "Enter name to search: ";
            cin >> name;
            phone = search(table, name, method);
            cout << "Result: " << phone << endl;
            break;
        case 3:
            display(table);
            break;
        case 0:
            cout << "Exiting program.\n";
            break;
        default:
            cout << "Invalid choice!\n";
        }

    } while (choice != 0);

    return 0;
}

