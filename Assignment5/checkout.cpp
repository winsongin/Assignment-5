// Name: Winson Gin
// Section #3
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
  Book* bookPtr = nullptr;

  if(!file){
    cout << "Error: Could not open file" << endl;
  }

  while(file >> bookID){
    getline(file, title);
    getline(file, author);
    getline(file, category);
    bookPtr = new Book(bookID, title, author, category);
    myBooks.push_back(bookPtr);
  }

  file.close();
}

int readPersons(vector<Person *> & myCardholders) {
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
  lastCardID += 1;
  return lastCardID;
}

void readRentals(vector<Book *> & myBooks, vector<Person *> myCardholders) {
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
    personPtr = searchPerson(myCardHolders, cardID);
    (*bookPtr).setPersonPtr(personPtr);
  }


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

Book * searchBook(vector<Book *> myBooks, int bookID) {
  Book* bookPtr = nullptr;

  for(int i = 0; i < myBooks.size(); i++){
    if(*myBooks).at(i).getId() == bookID){
      bookPtr = myBooks.at(i);
    }
  }

  return bookPtr;
}

Person * searchPerson(vector<Person *> myCardHolders, int cardID) {
  Person* personPtr = nullptr;

  for(int i = 0; i < myCardHolders.size(); i++){
    if(*myCardHolders).at(i).getId() == cardID){
      personPtr = myCardHolders.at(i);
    }
  }

  return personPtr;
}


int main()
{
    vector<Book *> books;
    vector<Person *> cardholders;
    int cardID;
    int bookID;
    int count = 0;
    Person* personPtr;
    Book* bookPtr;

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
                cout << "Please enter the card id: ";
                cin >> cardID;
                personPtr = searchPerson(cardHolders, cardID);
                if(personPtr = nullptr || (!(*personPtr).isActive())){
                  cout << "Card ID not found" << endl;
                }
                else{
                  cout << "Cardholder: " << (*personPtr).fullName();
                  cout << "Please enter the book id: ";
                  cin >> bookID;
                  bookPtr = searchBook(books, bookID);
                  if(bookPtr == nullptr){
                    cout << "Book ID not found" << endl;
                  }
                  else{
                    cout << "Title: " << (*bookPtr).getTitle();
                    bookPtr = searchBook(myBooks, bookID);
                    personPtr = searchPerson(myCardHolders, cardID);
                    (*bookPtr).setPersonPtr(personPtr);
                    cout << "Rental completed" << endl;
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
                }
                //Update book object
                break;

            case 3:
                // View all available books
                for(int i = 0; i < books.size(); i++){
                  if((*bookPtr).at(i).getPersonPtr() == nullptr){
                    cout << "Book ID: " << (*books).at(i).getId();
                    cout << "Title: " << (*books).at(i).getTitle();
                    cout << "Author: " << (*books).at(i).getAuthor();
                    cout << "Category: " << (*books).at(i).getCategory();
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
                  if((*bookPtr).getPersonPtr() != nullptr){
                    cout << "Book ID: " << (*bookPtr).at(i).getId();
                    cout << "Title: " << (*bookPtr).at(i).getTitle();
                    cout << "Author: " << (*bookPtr).at(i).getAuthor();
                    cout << "Category: " << (*bookPtr).at(i).getCategory();
                    cout << "Cardholder: " << (*bookPtr).at(i).(*getPersonPtr()).at(i).fullName();
                    cout << "Card ID: " << (*bookPtr).at(i).(*getPersonPtr()).at(i).getId();
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
                for(int i = 0; i < books.size(); i++){

                }
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
