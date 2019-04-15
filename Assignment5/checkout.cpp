// Name
// Section #
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "person.cpp"
#include "book.cpp"

using namespace std;

void printMenu() {
    cout << "----------Library Book Rental System----------" << endl;
    cout << "1.  Book checkout" << endl;
    cout << "2.  Book return" << endl;
    cout << "3.  View all available books" << endl;
    cout << "4.  View all outstanding rentals" << endl;
    cout << "5.  View outstanding rentals for a cardholder" << endl;
    cout << "6.  Open new library card" << endl;
    cout << "7.  Close library card" << endl;
    cout << "8.  Exit system" << endl;
    cout << "Please enter a choice: ";
}

void readBooks(vector<Book *> & myBooks) {
  ifstream file;
  file.open("books.txt");
  int bookID;
  string title;
  string author;
  string category;
  int count = 0;
  Book* bookPtr;


  while(file >> bookID){
    getline(file, title);
    getline(file, author);
    getline(file, category);
    bookPtr = new Book(bookID, title, author, category);
    myBooks.push_back(bookPtr);
  }

  file.close();
  delete bookPtr;
  bookPtr = NULL;
}

int readPersons(vector<Person *> & myCardholders) {
  ifstream file;
  file.open("persons.txt");

  int cardID;
  int lastCardID = 0;
  bool isActive = false;
  string fName;
  string lName;
  Person* personPtr;


  while(file >> cardID){
    file >> isActive;
    file >> fName;
    file >> lName;
    personPtr = new Person(cardID, isActive, fName, lName);
    myCardholders.push_back(personPtr);
    lastCardID = cardID;
  }

  file.close();
  lastCardID += 1;
  return lastCardID;
  delete personPtr;
  personPtr = NULL;
}

void readRentals(vector<Book *> & myBooks, vector<Person *> myCardholders) {
  ifstream file;
  file.open("rentals.txt");

  int bookID;
  int cardID;


}

void openCard(vector<Person *> & myCardholders, int nextID) {
  string fName;
  string lName;
  // bool isActive = false;
  Person* P = new Person;

  cout << "Please enter the first name: ";
  cin >> fName;

  cout << "Please enter the last name: ";
  cin >> lName;

  myCardHolders.push_back(Person(nextID, true, fName, lName));

  delete P;
}

Book * searchBook(vector<Book *> myBooks, int id) {

  return nullptr;
}


int main()
{
    vector<Book *> books;
    vector<Person *> cardholders;

    int choice;
    do
    {
        // If you use cin anywhere, don't forget that you have to handle the <ENTER> key that
        // the user pressed when entering a menu option. This is still in the input stream.
        printMenu();
        cin >> choice;
        switch(choice)
        {
            case 1:
                // Book checkout
                break;

            case 2:
                // Book return
                break;

            case 3:
                // View all available books
                break;

            case 4:
                // View all outstanding rentals
                break;

            case 5:
                // View outstanding rentals for a cardholder
                break;

            case 6:
                // Open new library card
                int newID;
                newID = readPersons(cardHolders);
                openCard(cardHolders, newID);
                break;

            case 7:
                // Close library card
                break;

            case 8:
                // Must update records in files here before exiting the program
                break;

            default:
                cout << "Invalid entry" << endl;
                break;
        }
        cout << endl;
   } while(choice != 8);
      return 0;
}
