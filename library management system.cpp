#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// ---------- Book Class ----------
class Book {
public:
    int bookID;
    string title;
    string author;
    bool issued;

    void addBook() {
        cout << "\nEnter Book ID: ";
        cin >> bookID;
        cin.ignore();

        cout << "Enter Book Title: ";
        getline(cin, title);

        cout << "Enter Author Name: ";
        getline(cin, author);

        issued = false;
    }

    void displayBook() {
        cout << "\nBook ID     : " << bookID;
        cout << "\nTitle       : " << title;
        cout << "\nAuthor      : " << author;
        cout << "\nStatus      : " << (issued ? "Issued" : "Available") << endl;
    }
};

// ---------- Function Prototypes ----------
void addBook();
void viewBooks();
void searchBook();
void issueBook();
void returnBook();

// ---------- Main Function ----------
int main() {
    int choice;

    do {
        cout << "\n========== LIBRARY MANAGEMENT SYSTEM ==========";
        cout << "\n1. Add Book";
        cout << "\n2. View All Books";
        cout << "\n3. Search Book";
        cout << "\n4. Issue Book";
        cout << "\n5. Return Book";
        cout << "\n6. Exit";
        cout << "\nEnter Choice: ";
        cin >> choice;

        switch(choice) {
            case 1: addBook(); break;
            case 2: viewBooks(); break;
            case 3: searchBook(); break;
            case 4: issueBook(); break;
            case 5: returnBook(); break;
            case 6: cout << "\nThank You!\n"; break;
            default: cout << "\nInvalid Choice!\n";
        }

    } while(choice != 6);

    return 0;
}

// ---------- Add Book ----------
void addBook() {
    Book b;
    ofstream file("library.txt", ios::app);

    b.addBook();

    file << b.bookID << endl;
    file << b.title << endl;
    file << b.author << endl;
    file << b.issued << endl;

    file.close();

    cout << "\nBook Added Successfully!\n";
}

// ---------- View Books ----------
void viewBooks() {
    Book b;
    ifstream file("library.txt");

    while(file >> b.bookID) {
        file.ignore();
        getline(file, b.title);
        getline(file, b.author);
        file >> b.issued;
        file.ignore();

        b.displayBook();
        cout << "---------------------------------\n";
    }

    file.close();
}

// ---------- Search Book ----------
void searchBook() {
    Book b;
    ifstream file("library.txt");
    string key;
    bool found = false;

    cin.ignore();
    cout << "\nEnter Title or Author to Search: ";
    getline(cin, key);

    while(file >> b.bookID) {
        file.ignore();
        getline(file, b.title);
        getline(file, b.author);
        file >> b.issued;
        file.ignore();

        if (b.title == key || b.author == key) {
            b.displayBook();
            found = true;
        }
    }

    if(!found)
        cout << "\nBook Not Found!\n";

    file.close();
}

// ---------- Issue Book ----------
void issueBook() {
    Book b;
    ifstream file("library.txt");
    ofstream temp("temp.txt");

    int id;
    bool found = false;

    cout << "\nEnter Book ID to Issue: ";
    cin >> id;

    while(file >> b.bookID) {
        file.ignore();
        getline(file, b.title);
        getline(file, b.author);
        file >> b.issued;
        file.ignore();

        if(b.bookID == id && !b.issued) {
            b.issued = true;
            found = true;
            cout << "\nBook Issued Successfully!\n";
        }

        temp << b.bookID << endl;
        temp << b.title << endl;
        temp << b.author << endl;
        temp << b.issued << endl;
    }

    file.close();
    temp.close();

    remove("library.txt");
    rename("temp.txt", "library.txt");

    if(!found)
        cout << "\nBook Not Available!\n";
}

// ---------- Return Book ----------
void returnBook() {
    Book b;
    ifstream file("library.txt");
    ofstream temp("temp.txt");

    int id;
    bool found = false;

    cout << "\nEnter Book ID to Return: ";
    cin >> id;

    while(file >> b.bookID) {
        file.ignore();
        getline(file, b.title);
        getline(file, b.author);
        file >> b.issued;
        file.ignore();

        if(b.bookID == id && b.issued) {
            b.issued = false;
            found = true;
            cout << "\nBook Returned Successfully!\n";
        }

        temp << b.bookID << endl;
        temp << b.title << endl;
        temp << b.author << endl;
        temp << b.issued << endl;
    }

    file.close();
    temp.close();

    remove("library.txt");
    rename("temp.txt", "library.txt");

    if(!found)
        cout << "\nInvalid Return Request!\n";
}