// Importing necessary libraries
#include <iostream>   // For standard I/O like cin and cout
#include <string>     // To work with the string data type
#include <vector>     // To work with dynamic arrays (vectors)

using namespace std;

// ================================
// UNION: One variable shares memory
// ================================
union ContactInfo {
    char phone[20];  // If user selects phone
    char email[50];  // If user selects email
    // Only one of them will store value at a time
};

// ================================
// STRUCT: Represents a customer
// ================================
struct Customer {
    string name;           // Customer name
    ContactInfo contact;   // Contact info (phone/email)
    bool isPhone;          // True = phone used, False = email used
    string address;        // Customer address
    string category;       // Category: VIP or Regular
};

// Vectors to store customers and simulate 2D arrays
vector<Customer> customers;                // Main list of customers
vector<vector<string>> nameTable;          // 2D name array (used with pointers)
vector<string*> namePointers;              // Pointer to each customer's name

// ================================
// Function Declarations
// ================================
void addCustomer();
void showCustomers();
void findCustomer();
void editCustomer();
void removeCustomer();
void showByCategory();

// ================================
// MAIN FUNCTION: Starting point
// ================================
int main() {
    int option;

    do {
        // Display menu
        
         cout<<"\n|||||||> --- CRM System Menu By AMUT --- <||||||| \n";
         cout<<endl;
        cout<<" |    1 --> Add Customer\n";
        cout<<" |    2 --> View Customer\n";
        cout<<" |    3 --> Search Customer\n";
        cout<<" |    4 --> Update Customer\n";
        cout<<" |    5 --> Delete Customer\n";
        cout<<" |    6 --> List Customers by Category\n";
        cout<<" |    0 --> Exit The Menu\n";
          cout<<endl;
        cout<<" Choose an Option \n";
        cin >> option;

        // Select and run option
        switch(option) {
            case 1: addCustomer(); break;
            case 2: showCustomers(); break;
            case 3: findCustomer(); break;
            case 4: editCustomer(); break;
            case 5: removeCustomer(); break;
            case 6: showByCategory(); break;
            case 0: cout << "Exiting CRM System. Bye!\n"; break;
            default: cout << "Invalid option. Try again.\n";
        }

    } while(option != 0);  // Repeat until user selects Exit

    return 0;
}

// ================================
// FUNCTION: Add a customer
// ================================
void addCustomer() {
    Customer c;

    cout << "\nEnter customer name: ";
    getline(cin >> ws, c.name);  // ws clears extra whitespace

    // Ask for contact type (phone/email)
    int type;
    cout << "Contact Type (1. Phone, 2. Email): ";
    cin >> type;

    if (type == 1) {
        c.isPhone = true;
        cout << "Enter phone: ";
        cin >> ws;
        cin.getline(c.contact.phone, 20);  // getline reads full line
    } else {
        c.isPhone = false;
        cout << "Enter email: ";
        cin >> ws;
        cin.getline(c.contact.email, 50);
    }

    cout << "Enter address: ";
    getline(cin >> ws, c.address);

    // Accept category as VIP or Regular only
    do {
        cout << "Enter category (VIP / Regular): ";
        getline(cin >> ws, c.category);
    } while (c.category != "VIP" && c.category != "Regular");

    // Store in main vector
    customers.push_back(c);

    // Store name in 2D array simulation
    nameTable.push_back({c.name});              // add row
    namePointers.push_back(&nameTable.back()[0]);  // store pointer to name

    cout << "✅ Customer added successfully.\n";
}

// ================================
// FUNCTION: Show all customers
// ================================
void showCustomers() {
    if (customers.empty()) {
        cout << "No customer records found.\n";
        return;
    }

    for (size_t i = 0; i < customers.size(); i++) {
        cout << "\nCustomer #" << i + 1 << ":\n";
        cout << "Name: " << *namePointers[i] << endl;

        if (customers[i].isPhone)
            cout << "Phone: " << customers[i].contact.phone << endl;
        else
            cout << "Email: " << customers[i].contact.email << endl;

        cout << "Address: " << customers[i].address << endl;
        cout << "Category: " << customers[i].category << endl;
    }
}

// ================================
// FUNCTION: Search for a customer
// ================================
void findCustomer() {
    string keyword;
    cout << "\nEnter name or email to search: ";
    getline(cin >> ws, keyword);

    bool found = false;

    for (size_t i = 0; i < customers.size(); i++) {
        if (customers[i].name == keyword ||
           (!customers[i].isPhone && keyword == customers[i].contact.email)) {
            cout << "\n✅ Customer Found:\n";
            cout << "Name: " << customers[i].name << endl;
            if (customers[i].isPhone)
                cout << "Phone: " << customers[i].contact.phone << endl;
            else
                cout << "Email: " << customers[i].contact.email << endl;

            cout << "Address: " << customers[i].address << endl;
            cout << "Category: " << customers[i].category << endl;
            found = true;
            break;
        }
    }

    if (!found)
        cout << "❌ Customer not found.\n";
}

// ================================
// FUNCTION: Edit customer info
// ================================
void editCustomer() {
    string searchName;
    cout << "\nEnter name to edit: ";
    getline(cin >> ws, searchName);

    bool found = false;

    for (size_t i = 0; i < customers.size(); i++) {
        if (customers[i].name == searchName) {
            cout << "New contact type (1. Phone, 2. Email): ";
            int type;
            cin >> type;

            if (type == 1) {
                customers[i].isPhone = true;
                cout << "Enter new phone: ";
                cin >> ws;
                cin.getline(customers[i].contact.phone, 20);
            } else {
                customers[i].isPhone = false;
                cout << "Enter new email: ";
                cin >> ws;
                cin.getline(customers[i].contact.email, 50);
            }

            cout << "New address: ";
            getline(cin >> ws, customers[i].address);

            do {
                cout << "New category (VIP / Regular): ";
                getline(cin >> ws, customers[i].category);
            } while (customers[i].category != "VIP" && customers[i].category != "Regular");

            // Update nameTable
            nameTable[i][0] = customers[i].name;

            cout << "✅ Customer info updated.\n";
            found = true;
            break;
        }
    }

    if (!found)
        cout << "❌ Customer not found.\n";
}

// ================================
// FUNCTION: Delete a customer
// ================================
void removeCustomer() {
    string nameToDelete;
    cout << "\nEnter name to delete: ";
    getline(cin >> ws, nameToDelete);

    bool found = false;

    for (size_t i = 0; i < customers.size(); i++) {
        if (customers[i].name == nameToDelete) {
            customers.erase(customers.begin() + i);
            nameTable.erase(nameTable.begin() + i);
            namePointers.erase(namePointers.begin() + i);
            cout << "✅ Customer deleted.\n";
            found = true;
            break;
        }
    }

    if (!found)
        cout << "❌ Customer not found.\n";
}

// ================================
// FUNCTION: Show by category
// ================================
void showByCategory() {
    int choice;
    string category;

    cout << "\n1. VIP Customers\n";
    cout << "2. Regular Customers\n";
    cout << "Enter choice: ";
    cin >> choice;

    if (choice == 1)
        category = "VIP";
    else if (choice == 2)
        category = "Regular";
    else {
        cout << "❌ Invalid category.\n";
        return;
    }

    bool found = false;

    for (size_t i = 0; i < customers.size(); i++) {
        if (customers[i].category == category) {
            cout << "\nCustomer #" << i + 1 << ":\n";
            cout << "Name: " << *namePointers[i] << endl;
            if (customers[i].isPhone)
                cout << "Phone: " << customers[i].contact.phone << endl;
            else
                cout << "Email: " << customers[i].contact.email << endl;

            cout << "Address: " << customers[i].address << endl;
            cout << "Category: " << customers[i].category << endl;
            found = true;
        }
    }

    if (!found)
        cout << "❌ No customers in this category.\n";
}
