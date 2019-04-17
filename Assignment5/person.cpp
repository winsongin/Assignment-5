//Winson Gin
//Section #3

#include "person.h"

Person::Person(int cardNo, bool act, string fName, string lName) {
    cardID = cardNo;
    active = act;
    firstName = fName;
    lastName = lName;
}

string Person::getFirstName() {
    return firstName;
}

string Person::getLastName() {
    return lastName;
}

int Person::getId() {
    return cardID;
}

void Person::setActive(bool act) {
    active = act;
} // complete

bool Person::isActive() {
    return true;
}

string Person::fullName() {
    string fullname = getFirstName() + " " + getLastName();
    return fullname; // complete
}
