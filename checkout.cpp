// Name: Winson Gin
// Section #2

// Known logical errors:
// 1. Rentals wiped out the initial rentals after writing to the file,
// 2. When opening new card multiple times, the nextID is not being incremented

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "person.cpp"
#include "book.cpp"

using namespace std;

void readBooks(vector<Book *> & myBooks);
int readPersons(vector<Person *> &myCardholders);
void readRentals(vector<Book *> & myBooks, vector<Person *> &myCardholders);
void openCard(vector<Person *> & myCardholders, int lastID);
Book * searchBook(vector<Book *> &myBooks, int bookID);
Person * searchPerson(vector<Person *> &myCardholders, int cardID);
void deletePtrs(vector<Book *> &myBooks, vector<Person *> &myCardholders);
void writePersons(vector <Person *> &myCardholders);
void writeRentals(vector<Book *> &myBooks);

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
  string blank;
  string title;
  string author;
  string category;
  int count = 0;
  Book* bookPtr = nullptr;

  if(!file){
    cout << "Error: Could not open file" << endl;
  }

  while(file >> bookID){
    getline(file, blank);
    getline(file, title);
    getline(file, author);
    getline(file, category);
    bookPtr = new Book(bookID, title, author, category);
    myBooks.push_back(bookPtr);
  }

  file.close();
}

int readPersons(vector<Person *> &myCardholders) {
  ifstream file;
  file.open("persons.txt");

  int cardID;
  int lastCardID = 0;
  bool isActive = false;
  string fName;
  string lName;
  Person* personPtr = nullptr;

  if(!file){
    cout << "Error: Could not open file" << endl;
  }

  while(file >> cardID){
    file >> isActive;
    file >> fName;
    file >> lName;
    personPtr = new Person(cardID, isActive, fName, lName);
    myCardholders.push_back(personPtr);
    lastCardID = cardID;
  }

  file.close();
  // lastCardID += 1;
  return lastCardID;
}

// sets the personPtr that exists inside the book object
void readRentals(vector<Book *> & myBooks, vector<Person *> &myCardholders) {
  ifstream file;
  file.open("rentals.txt");
  Book* bookPtr;
  Person* personPtr = nullptr;

  int bookID;
  int cardID;

  if(!file){
    cout << "Error: Could not open file" << endl;
  }

  while(file >> bookID >> cardID){
    bookPtr = searchBook(myBooks, bookID);
    personPtr = searchPerson(myCardholders, cardID);
    (*bookPtr).setPersonPtr(personPtr); // this creates the association for the rental
  }

  file.close();
}

// this will push a new personPtr back into the vector
void openCard(vector<Person *> & myCardholders, int lastID) {
  string fName;
  string lName;
  int nextID = 0;
  nextID = lastID;
  Person* personPtr;

  cout << "Please enter the first name: ";
  cin >> fName;

  cout << "Please enter the last name: ";
  cin >> lName;

  personPtr = new Person(nextID, 1, fName, lName);
  myCardholders.push_back(personPtr);
  cout << "Card ID " << nextID << " active" << endl;
  cout << "Cardholder: " << fName << " " << lName << endl;
}

// this will set the person's boolean value to 0, which is false, making the card not active
string closeCard(vector<Person *> & myCardholders, int cardID){
  Person* personPtr;
  personPtr = searchPerson(myCardholders, cardID);
  if(personPtr != nullptr){
    (*personPtr).setActive(0);
  }
  return (*personPtr).fullName();
}

// this will return the pointer at the index where the bookID is found
Book * searchBook(vector<Book *> &myBooks, int bookID) {
  for(int i = 0; i < myBooks.size(); i++){
    if((*myBooks.at(i)).getId() == bookID){
      return myBooks.at(i); //this will the correct pointer that corresponds to the bookID from the books vector
    }
  }
  return nullptr;
}

Person * searchPerson(vector<Person *> &myCardholders, int cardID) {
  for(int i = 0; i < myCardholders.size(); i++){
    if((*myCardholders.at(i)).getId() == cardID){
      return myCardholders.at(i);
    }
  }
  return nullptr;
}

void deletePtrs(vector<Book *> &myBooks, vector<Person *> &myCardholders){
  for(int i = 0; i < myBooks.size(); i++){
    delete myBooks.at(i);
    myBooks.at(i) = NULL; // this handles dangling pointers
  }
  for(int i = 0; i < myCardholders.size(); i++){
    delete myCardholders.at(i);
    myCardholders.at(i) = NULL; // this handles dangling pointers
  }
}

void writePersons(vector <Person *> &myCardholders){
  ofstream file;
  file.open("persons.txt");

  if(!file){
    cout << "Error: Could not open file" << endl;
  }

  for(int i = 0; i < myCardholders.size(); i++){
    file << ((*myCardholders.at(i)).getId()) << " ";
    file << ((*myCardholders.at(i)).isActive()) << " ";
    file << ((*myCardholders.at(i)).fullName());
    file << endl;
  }

  file.close();
}

void writeRentals(vector<Book *> &myBooks){
  ofstream file;
  file.open("rentals.txt");

  if(!file){
    cout << "Error: Could not open file" << endl;
  }

  for(int i = 0; i < myBooks.size(); i++){
    if((*myBooks.at(i)).getPersonPtr() != nullptr){
      file << (*myBooks.at(i)).getId();
      file << " ";
      file << myBooks.at(i)->getPersonPtr()->getId();
      file << endl;
    }
  }

  file.close();
}

int main()
{
    vector<Book *> books;
    vector<Person *> cardHolders;
    int cardID;
    int bookID;
    int lastID;
    string fullname;
    string decision;
    readBooks(books);
    lastID = readPersons(cardHolders);
    readRentals(books, cardHolders);
    int count = 0; //might not be needed
    Person* personPtr;
    Book* bookPtr;

    int choice;
    do
    {
        // If you use cin anywhere, don't forget that you have to handle the <ENTER> key that
        // the user pressed when entering a menu option. This is still in the input stream.
        printMenu();
        cin >> choice;
        cin.ignore();
        switch(choice)
        {
            case 1:
                // Book checkout
                // bookCheckout();
                cout << "Please enter the card ID: ";
                cin >> cardID;
                personPtr = searchPerson(cardHolders, cardID);
                if(personPtr == nullptr){
                    cout << "Card ID not found" << endl;
                }
                else if(!((*personPtr).isActive())){
                  cout << "Card ID not found" << endl;
                }
                else{
                  cout << "Cardholder: " << (*personPtr).fullName() << endl;
                  cout << "Please enter the book ID: ";
                  cin >> bookID;
                  bookPtr = searchBook(books, bookID);
                  if(bookPtr == nullptr){
                    cout << "Book ID not found" << endl;
                  }
                  else if((*bookPtr).getPersonPtr() != nullptr){
                    cout << "Book already checked out" << endl;
                  }
                  else{
                    cout << "Title: " << (*bookPtr).getTitle() << endl;
                    bookPtr = searchBook(books, bookID);
                    personPtr = searchPerson(cardHolders, cardID);
                    (*bookPtr).setPersonPtr(personPtr);
                    cout << "Rental Completed" << endl;
                  }
                }
                break;

            case 2:
                // Book return
                cout << "Please enter the book ID to return: ";
                cin >> bookID;
                bookPtr = searchBook(books, bookID);
                if(bookPtr == nullptr){
                  cout << "Book ID not found" << endl;
                }
                else{
                  cout << "Title: " << (*bookPtr).getTitle() << endl;
                  (*bookPtr).setPersonPtr(nullptr);
                  cout << "Return completed" << endl;
                }
                break;

            case 3:
                // View all available books
                // Future implementation: Instead of running through a for loop, create a bool haveRentals = false; if it never changes, then there are no available books
                for(int i = 0; i < books.size(); i++){
                  if((*books.at(i)).getPersonPtr() == nullptr){
                    cout << "Book ID: " << (*books.at(i)).getId() << endl;
                    cout << "Title: " << (*books.at(i)).getTitle() << endl;
                    cout << "Author: " << (*books.at(i)).getAuthor() << endl;
                    cout << "Category: " << (*books.at(i)).getCategory() << endl;
                    cout << endl;
                  }
                  else{
                    count++;
                  }
                }
                if(count == books.size()){
                  cout << "No available books" << endl;
                }
                break;

            case 4:
                // View all outstanding rentals
                for(int i = 0; i < books.size(); i++){
                  if((*books.at(i)).getPersonPtr() != nullptr){
                    cout << "Book ID: " << (*books.at(i)).getId() << endl;
                    cout << "Title: " << (*books.at(i)).getTitle() << endl;
                    cout << "Author: " << (*books.at(i)).getAuthor() << endl;
                    cout << "Category: " << (*books.at(i)).getCategory() << endl;
                    cout << "Cardholder: " << books.at(i)->getPersonPtr()->fullName() << endl;
                    cout << "Card ID: " << books.at(i)->getPersonPtr()->getId() << endl;
                    cout << endl;
                  }
                  else{
                    count++;
                  }
                }
                if(count == books.size()){
                  cout << "No outstanding rentals" << endl;
                }
                break;

            case 5:
                // View outstanding rentals for a cardholder
                cout << "Please enter the card ID: ";
                cin >> cardID;
                // pass cardID to searchPerson function
                personPtr = searchPerson(cardHolders, cardID); //returns the pointer that we want from the vector
                if(personPtr != nullptr){
                  if((*personPtr).isActive()){
                  cout << "Cardholder: " << ((*personPtr).fullName()) << endl;
                    for(int i = 0; i < books.size(); i++){
                      if((*books.at(i)).getPersonPtr() == personPtr){
                        cout << "Book ID: " << (*books.at(i)).getId() << endl;
                        cout << "Title: " << (*books.at(i)).getTitle() << endl;
                        cout << "Author: " << (*books.at(i)).getAuthor() << endl;
                        cout << endl;
                      }
                    }
                  }
                }
                break;

            case 6:
                // Open new library card
                lastID++;
                openCard(cardHolders, lastID);
                break;

            case 7:
                // Close library card
                cout << "Please enter the card ID: ";
                cin >> cardID;
                personPtr = searchPerson(cardHolders, cardID);
                if(personPtr != nullptr){
                  cout << "Cardholder: " << (*personPtr).fullName() << endl;
                  cout << "Are you sure you want to deactivate card (y/n) ? ";
                  cin >> decision;
                  if(decision == "y"){
                    fullname = closeCard(cardHolders, cardID);
                    cout << "Card ID deactivated" << endl;
                  }
                }
                else{
                  cout << "Card ID not found" << endl;
                }
                break;
            case 8:
                // Must update records in files here before exiting the program
                writePersons(cardHolders);
                writeRentals(books);
                deletePtrs(books, cardHolders);
                break;

            default:
                cout << "Invalid entry" << endl;
                break;
        }
        cout << endl;
   } while(choice != 8);
      return 0;
}
