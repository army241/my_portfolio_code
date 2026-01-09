#include <iostream>
#include <fstream>
using namespace std;

struct Address {
    char sub_city[50];
    int woreda;
    int house_number;
};

struct student {
    int idno;
    char fname[20];
    double gpa;
    Address address;
};

student getData() {
    student s;
    cout << "Enter ID: ";
    cin >> s.idno;
    cout << "Enter name: ";
    cin >> s.fname;
    cout << "Enter GPA: ";
    cin >> s.gpa;
    cout << "Enter Sub city: ";
    cin >> s.address.sub_city;
    cout << "Enter woreda: ";
    cin >> s.address.woreda;
    cout << "Enter house number: ";
    cin >> s.address.house_number;
    return s;
}

void registerStudent(const char* filename) {
    student s = getData();
    ofstream file(filename, ios::binary);
    if (!file) {
        cout << "Error opening file\n";
        return;
    }
    file.write(reinterpret_cast<char*>(&s), sizeof(student));
    cout << "Student registered successfully.\n";
    file.close();
}

void displayStudents(const char* filename) {
    ifstream infile(filename, ios::binary);
    if (!infile) {
        cout << "Error opening file\n";
        return;
    }

    student s;
    int count = 0;
    while (infile.read(reinterpret_cast<char*>(&s), sizeof(student))) {
    	count++;
        cout << "\nID: " << s.idno << endl;
        cout << "Name: " << s.fname << endl;
        cout << "GPA: " << s.gpa << endl;
        cout << "Sub city: " << s.address.sub_city << endl;
        cout << "Woreda: " << s.address.woreda << endl;
        cout << "House number: " << s.address.house_number << endl;
         cout << "\nTotal number of "<<count<<" record:"<<endl;
    }
    infile.close();
}

void searchStudentByID(const char* filename, int id) {
    student s;
    bool found = false;
    ifstream inFile(filename, ios::binary);
    
    while (inFile.read(reinterpret_cast<char*>(&s), sizeof(student))) {
        if (s.idno == id) {
            cout << "ID: " << s.idno << ", Name: " << s.fname << ", GPA: " << s.gpa 
                 << ", Address: " << s.address.sub_city << ", Woreda: " << s.address.woreda 
                 << ", House Number: " << s.address.house_number << endl;
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Student with ID " << id << " not found." << endl;
    }
    inFile.close();
}

int main() {
    int choice;
    const char* filename = "filename.dat";
	int id;
    do {
        cout << "\n===== MENU =====\n";
        cout << "1. Register a student\n";
        cout << "2. Display all students\n";
        cout<< "3. Search student by ID \n";
		cout<< "3. Update Student file \n";
		cout<< "3. delete student file \n";
        cout << "4. Exit\n";
        
        cout << "Your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                registerStudent(filename);
                break;
            case 2:
                displayStudents(filename);
                break;
            case 3:
            	cout<<"Search ID number: ";
            	cin>>id;
            	searchStudentByID(filename, id);
                break;
            case 4:
            	cout << "Exiting application...\n";
            	break;
            default:
                cout << "Invalid choice\n";
        }
    } while (choice != 3);

    return 0;
}
