#include <iostream>
#include <fstream>
using namespace std;


struct bookNode {
    string title;
    string author;
    string price;
    bookNode* next; 
    bookNode(string t, string a, string p, bookNode* n = nullptr) : title(t), author(a), price(p), next(n) {}
};


void displayBooks() {
    ifstream ip("bookdata.csv");

    if (!ip.is_open()) {
        cout << "Error opening csv file" << '\n';
        return;
    }

    string bookTitle;
    string author;
    string price;
    while (getline(ip, bookTitle, ',') &&
           getline(ip, author, ',') &&
           getline(ip, price, '\n')) {
        cout << "Book Title: " << bookTitle << '\n';
        cout << "Author: " << author << '\n';
        cout << "Price: " << price << '\n';
        cout << "--------------------------------------------------" << '\n';
    }

    ip.close();
}


void recommendedBooks(const bookNode* book) {
    cout << "Book Title: " << book->title << '\n';
    cout << "Author: " << book->author << '\n';
    cout << "Price: " << book->price << '\n';
    cout << "--------------------------------" << '\n';
}


void recommendations() {
    cout << "Recommended Books: \n";
    bookNode* firstBook = new bookNode("The Book Thief", "Markus Zusak", "$17.99");
    bookNode* secondBook = new bookNode("To Kill a Mockingbird", "Harper Lee", "$20.99");

    firstBook->next = secondBook;
    bookNode* currentBook = firstBook;
    while (currentBook != nullptr) {
        recommendedBooks(currentBook);
        currentBook = currentBook->next;
    }

}


void addBooks() {
    ofstream op("bookdata.csv", ios::app);

    if (!op.is_open()) {
        cout << "Error opening csv file" << '\n';
        return;
    }

    string bookTitle;
    string author;
    string price;

    cin.ignore(); 
    cout << "Please enter the Book Title: ";
    getline(cin, bookTitle);
    cout << "Please enter the Author: ";
    getline(cin, author);
    cout << "Pleace enter the Price: ";
    getline(cin, price);

    op << bookTitle << ',' << author << ',' << price << '\n';
    cout << "We have taken note of the book you requested, and our workers were on it so we have it in stock now!\n";
    op.close();
}

void buyBook(){
    displayBooks();
    cout << "Which book would you like to buy?: \n";
    string bookBuy;
    cin.ignore(); 
    getline(cin, bookBuy);

    ifstream ip("bookdata.csv");
    if (!ip.is_open()) {
        cout << "Error opening csv file" << '\n';
        return;
    }

    string bookTitle;
    bool bookAvailable = false;
    while (getline(ip, bookTitle, ',')) {
        if (bookTitle == bookBuy) {
            bookAvailable = true;
            break;
        }
        ip.ignore(numeric_limits<streamsize>::max(), '\n'); 
    }

    ip.close();

    if (bookAvailable) {
        cout << "You have purchased \"" << bookBuy << "\"! Thank you for shopping at Fayza's Book Shop:)" << endl;
    } else {
        cout << "We apologize we don't have \"" << bookBuy << "\" in stock." << endl;
    }
}


int main() {
    int choice;

    do {
        cout << "Welcome to Fayza's Book Shop:)" << endl;
        cout << "THE BEST book shop you'll find in Boston" << endl;
        cout << "1. Please display the books you offer!" << endl;
        cout << "2. Please give me some recommendations!" << endl;
        cout << "3. Please buy this book - I've been trying to find it everywhere and no one seems to sell it!" << endl;
        cout << "4. I'd love to purchase a Book" << endl;
        cout << "5. Forget I came in... I gotta go" << endl;
        cout << "What brings you in today?";
        cin.ignore();
        cin >> choice;

        switch (choice) {
            case 1:
                displayBooks();
                break;
            case 2:
                recommendations();
                break;
            case 3:
                addBooks();
                break;
            case 4:
                buyBook();
                break;
            case 5:
                cout << "You're missing out! bye bye now!" << endl;
                break;
            default:
                cout << "Invalid Please try again." << endl;
        }
    } while (choice != 0);

    return 0;
}