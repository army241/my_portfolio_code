#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>

using namespace std;

// ================= STRUCTURE =================
struct Patient
{
    int id;
    char name[50];
    int age;
    char disease[50];
    char doctor[50];
};

// ================= FUNCTION DECLARATIONS =================
void addPatient();
void displayPatients();
void searchPatient();
void deletePatient();
void updatePatient();
void menu();

// ================= MAIN =================
int main()
{
    menu();
    return 0;
}

// ================= MENU =================
void menu()
{
    int choice;

    do
    {
        cout << "\n===== HOSPITAL MANAGEMENT SYSTEM =====\n";
        cout << "1. Add Patient Record\n";
        cout << "2. Display All Patients\n";
        cout << "3. Search Patient by ID\n";
        cout << "4. Delete Patient Record\n";
        cout << "5. Update Patient Record\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";

        while (!(cin >> choice))
        {
            cout << "Invalid input! Enter number: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }

        switch (choice)
        {
        case 1: addPatient(); break;
        case 2: displayPatients(); break;
        case 3: searchPatient(); break;
        case 4: deletePatient(); break;
        case 5: updatePatient(); break;
        case 6: cout << "Exiting...\n"; break;
        default: cout << "Invalid choice!\n";
        }

    } while (choice != 6);
}

// ================= ADD PATIENT =================
void addPatient()
{
    Patient p;
    ofstream file("hospital.dat", ios::binary | ios::app);

    cout << "\nEnter Patient ID: ";
    while (!(cin >> p.id))
    {
        cout << "Invalid ID! Enter number: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }
    cin.ignore();

    cout << "Enter Name: ";
    while (true)
    {
        cin.getline(p.name, 50);
        if (isalpha(p.name[0]))
            break;
        cout << "Invalid name! Enter letters only: ";
    }

    cout << "Enter Age: ";
    while (!(cin >> p.age))
    {
        cout << "Invalid age! Enter number: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }
    cin.ignore();

    cout << "Enter Disease: ";
    while (true)
    {
        cin.getline(p.disease, 50);
        if (isalpha(p.disease[0]))
            break;
        cout << "Invalid disease name! Enter letters: ";
    }

    cout << "Enter Doctor Name: ";
    while (true)
    {
        cin.getline(p.doctor, 50);
        if (isalpha(p.doctor[0]))
            break;
        cout << "Invalid doctor name! Enter letters: ";
    }

    file.write((char *)&p, sizeof(p));
    file.close();

    cout << "Patient added successfully!\n";
}

// ================= DISPLAY =================
void displayPatients()
{
    Patient p;
    ifstream file("hospital.dat", ios::binary);

    if (!file)
    {
        cout << "No records found!\n";
        return;
    }

    while (file.read((char *)&p, sizeof(p)))
    {
        cout << "\nID: " << p.id
             << "\nName: " << p.name
             << "\nAge: " << p.age
             << "\nDisease: " << p.disease
             << "\nDoctor: " << p.doctor
             << "\n-------------------\n";
    }

    file.close();
}

// ================= SEARCH =================
void searchPatient()
{
    Patient p;
    int searchId;
    bool found = false;

    ifstream file("hospital.dat", ios::binary);

    cout << "\nEnter Patient ID to search: ";
    while (!(cin >> searchId))
    {
        cout << "Invalid ID! Enter number: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }

    while (file.read((char *)&p, sizeof(p)))
    {
        if (p.id == searchId)
        {
            cout << "\nID: " << p.id
                 << "\nName: " << p.name
                 << "\nAge: " << p.age
                 << "\nDisease: " << p.disease
                 << "\nDoctor: " << p.doctor << endl;
            found = true;
            break;
        }
    }

    if (!found)
        cout << "Patient not found!\n";

    file.close();
}

// ================= DELETE =================
void deletePatient()
{
    Patient p;
    int deleteId;
    bool found = false;

    ifstream file("hospital.dat", ios::binary);
    ofstream temp("temp.dat", ios::binary);

    cout << "\nEnter Patient ID to delete: ";
    while (!(cin >> deleteId))
    {
        cout << "Invalid ID! Enter number: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }

    while (file.read((char *)&p, sizeof(p)))
    {
        if (p.id != deleteId)
            temp.write((char *)&p, sizeof(p));
        else
            found = true;
    }

    file.close();
    temp.close();

    remove("hospital.dat");
    rename("temp.dat", "hospital.dat");

    if (found)
        cout << "Record deleted successfully!\n";
    else
        cout << "Patient not found!\n";
}

// ================= UPDATE =================
void updatePatient()
{
    Patient p;
    int updateId;
    bool found = false;

    ifstream file("hospital.dat", ios::binary);
    ofstream temp("temp.dat", ios::binary);

    cout << "\nEnter Patient ID to update: ";
    while (!(cin >> updateId))
    {
        cout << "Invalid ID! Enter number: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }
    cin.ignore();

    while (file.read((char *)&p, sizeof(p)))
    {
        if (p.id == updateId)
        {
            cout << "Enter New Name: ";
            while (true)
            {
                cin.getline(p.name, 50);
                if (isalpha(p.name[0]))
                    break;
                cout << "Invalid name! Enter letters: ";
            }

            cout << "Enter New Age: ";
            while (!(cin >> p.age))
            {
                cout << "Invalid age! Enter number: ";
                cin.clear();
                cin.ignore(1000, '\n');
            }
            cin.ignore();

            cout << "Enter New Disease: ";
            while (true)
            {
                cin.getline(p.disease, 50);
                if (isalpha(p.disease[0]))
                    break;
                cout << "Invalid disease! Enter letters: ";
            }

            cout << "Enter New Doctor Name: ";
            while (true)
            {
                cin.getline(p.doctor, 50);
                if (isalpha(p.doctor[0]))
                    break;
                cout << "Invalid doctor name! Enter letters: ";
            }

            found = true;
        }

        temp.write((char *)&p, sizeof(p));
    }

    file.close();
    temp.close();

    remove("hospital.dat");
    rename("temp.dat", "hospital.dat");

    if (found)
        cout << "Record updated successfully!\n";
    else
        cout << "Patient not found!\n";
}
