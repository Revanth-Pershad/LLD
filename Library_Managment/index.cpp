#include <bits/stdc++.h>
#include <chrono>
#include <shared_mutex>

using namespace std;

class InterfaceBook{
    protected:
        int     id;
        string  title, author, publisher, isbn;
        int     year;
        bool    available;
    public:
        virtual void setId          (int _id) = 0;
        virtual void setYear        (int _yr) = 0;
        virtual void setTitle       (string _sT) = 0;
        virtual void setAuthor      (string _sA) = 0;
        virtual void setPublisher   (string _sP) = 0;
        virtual void setisbn        (string _sP) = 0;
        virtual void setAvailable   (bool _sP) = 0;
        
        virtual int getId           ()= 0;
        virtual int getYear         ()= 0;
        virtual string getTitle     ()= 0;
        virtual string getAuthor    ()= 0;
        virtual string getPublisher ()= 0;
        virtual string getisbn      ()= 0;
        virtual bool getAvailable   ()= 0;
};

class Book : public InterfaceBook{
    public:
        void setId          (int _id) { id = _id; }
        void setYear        (int _yr) { year = _yr; }
        void setTitle       (string _sT) { title = _sT; }
        void setAuthor      (string _sA) { author = _sA; }
        void setPublisher   (string _sP) { publisher = _sP; }
        void setisbn        (string _sP) { isbn = _sP; }
        void setAvailable   (bool x) { available = x; }
        void setBorrowed    () { setAvailable(false); }
        void setReturned    () { setAvailable(true); }
        
        int getId           () { return id; }
        int getYear         () { return year; }
        string getTitle     () { return title; }
        string getAuthor    () { return author; }
        string getPublisher () { return publisher; }
        string getisbn      () { return isbn; }
        bool getAvailable   () { return available; }

        Book(int _id,string _title,string _author, string _publisher,string _isbn,int _year,bool _avail=true){
            id = _id; 
            title = _title; 
            author = _author;
            publisher = _publisher; 
            isbn = _isbn;
            year = _year; 
            available = _avail;
        }
};

class Loan{
    public:
        int bookId;
        chrono::system_clock::time_point borrowedAt;

        Loan(int bid, chrono::system_clock::time_point tt){
            bookId = bid;
            borrowedAt = tt;
        }
};

class InterfaceMember{
    protected:
        int id;
        string name, email, phone;

        int maxBorrow;
        vector<Loan *> borrowedBooks;
    public:
        virtual void setId      (int x)     = 0;
        virtual void setName    (string x)  = 0;
        virtual void setEmail   (string x)  = 0;
        virtual void setPhone   (string x)  = 0;
        virtual void setBorrow  (int x)     = 0;

        
        virtual int getId           ()  = 0;
        virtual string getName      ()  = 0;
        virtual string getEmail     ()  = 0;
        virtual string getPhone     ()  = 0;
        virtual int getBorrow       ()  = 0;
        virtual const vector<Loan*>& getLoans() = 0;

};

class Member : public InterfaceMember{
    public:  
        void setId      (int x)     { id = x; }
        void setName    (string x)  { name = x; }
        void setEmail   (string x)  { email = x; }
        void setPhone   (string x)  { phone = x; }
        void setBorrow  (int x)     { maxBorrow = x; }

        
        int getId           ()  { return id; }
        string getName      ()  { return name; }
        string getEmail     ()  { return email; }
        string getPhone     ()  { return phone; }
        int getBorrow       ()  { return maxBorrow; }
        const vector<Loan*>& getLoans() {return borrowedBooks; }
        bool canBorrow(){ return borrowedBooks.size() < maxBorrow; }

        void borrowBook(int bid){
            Loan *ll = new Loan(bid, chrono::system_clock::now());
            borrowedBooks.push_back(ll);
        }

        void returnBook(int bid) {
            auto it = borrowedBooks.begin();
            while (it != borrowedBooks.end()) {
                if ((*it)->bookId == bid) {
                    delete *it; 
                    it = borrowedBooks.erase(it);
                } else {
                    ++it;
                }
            }
        }


        Member(int _id,string _name,string _email,string _phone,int _max=5){
            id = _id; 
            name = _name; 
            email = _email; 
            phone = _phone;
            maxBorrow = _max;
        }
};

class Library{
    protected:
        unordered_map<int, Book*>   books;
        unordered_map<int, Member*> members;
        int seqBook{1}, seqMember{1};
    public:
        int AddBook(string title, string author, string publisher, string isbn, int year){
            Book *b = new Book(seqBook++, title, author, publisher, isbn, year, true);
            books[seqBook-1] = b;
            return seqBook-1;
        }

        void RemoveBook(int id){
            if(books.find(id) == books.end() || books[id]->getAvailable() == false){
                cout << "This book is unavailable\n";
                return;
            }

            books.erase(books.find(id));
            cout << "Book Removed";
        }

        int AddMember(string name, string email, string phone){
            int id = seqMember++;
            Member *m = new Member(id, name, email, phone, 5);
            members[id] = m;
            return id;
        }

        void RemoveMember(int id){
            if(members.find(id) == members.end()){
                cout << "No Member Exists\n";
                return;
            }

            members.erase(members.find(id));
            cout << "Member Removed \n";
        }

        void BorrowBook(int mid, int bid){
            if(books.find(bid) == books.end() || books[bid]->getAvailable() == false){
                cout << "Book Not Available\n";
                return;
            }

            books[bid]->setBorrowed();
            members[mid]->borrowBook(bid);

            cout << books[bid]->getTitle() << " Borrowed by " << members[mid]->getName() << "\n";
        }

        void ReturnBook(int mid, int bid){
            if(books.find(bid) == books.end() || books[bid]->getAvailable() == true){
                cout << "Book does not exist or already returned\n";
                return;
            }

            books[bid]->setReturned();
            members[mid]->returnBook(bid);

            cout << books[bid]->getTitle() << " Returned by " << members[mid]->getName() << endl;
        }

        void ShowLoans(){
            for(auto x : members){
                auto mem = x.second;
                for(auto y : mem->getLoans()){
                    Loan *ll = y;
                    int bid = ll->bookId;
                    int mid = x.first;

                    cout << books[bid]->getTitle() << " owned by " << members[mid]->getName() << endl;
                }
            }
        }
};

int main() {
    Library lib;

    int aliceId = lib.AddMember("Alice", "alice@example.com", "1234567890");
    int bobId = lib.AddMember("Bob", "bob@example.com", "9876543210");

    int book1 = lib.AddBook("1984", "George Orwell", "Secker & Warburg", "978-0451524935", 1949);
    int book2 = lib.AddBook("The Hobbit", "J.R.R. Tolkien", "Allen & Unwin", "978-0618968633", 1937);

    cout << "\n--- Borrowing Books ---\n";
    lib.BorrowBook(aliceId, book1);
    lib.BorrowBook(bobId, book2);

    cout << "\n--- Showing Loans ---\n";
    lib.ShowLoans();

    cout << "\n--- Returning Books ---\n";
    lib.ReturnBook(aliceId, book1);

    cout << "\n--- Showing Loans After Return ---\n";
    lib.ShowLoans();

    return 0;
}
