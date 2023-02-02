#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <list>
using namespace std;

struct Book
{
    string title;
    string author;
    int numPages;
    double price;
};

void readFile(string fname, list<Book> &bk);
void parseLine(string line, Book &bk);
void display(const Book &bk);
void displayBooks(const list<Book> &bks);

int main() {
    list<Book> books;
    readFile("books.csv", books);
    displayBooks(books);


    for(Book &bk: books)
    {
        bk.price = bk.price *.9;
      //  display(bk);
    }
    cout << "After reduction of price: "<<endl;
    displayBooks(books);

    cout << "After Sort"<<endl;
    auto func = [](Book &b1, Book &b2)
    {return b1.numPages < b2.numPages;};

    books.sort(func);
    displayBooks(books);
    return 0;
}
void displayBooks(const list<Book> &bks) {
    cout << left << setw(50) << "Title"
         << setw(20) << "Author"
         << setw(8) << "Price"
         << setw(5) << "Pages" << endl;
    cout << string(83, '=') << endl;

//    for(int i =0; i < bks.size();i++)
//    {
//        display(bks[i]);
//    }

    for (list<Book>::const_iterator iter = bks.begin();
         iter != bks.end(); iter++)
    {
        display(*iter);
    }


}
void readFile(string fname, list<Book> &bks)
{
    ifstream fin(fname);
    if(fin.good())
    {

        string line;
      //  int i = 0;
        while(!fin.eof())
        {
            getline(fin, line);
          //  if(i!=0)
           // {
                Book bk;
                parseLine(line, bk);
                bks.push_back(bk);
           // }
           // i++;
        }
        fin.close();
        cout << "File closed."<<endl;
    }
    else
    {
        cout << "Error opening file."<<endl;
    }
}

void parseLine(string line, Book &bk)
{
    try {
        stringstream ss(line);
        getline(ss, bk.title, ',');
        getline(ss, bk.author, ',');
        string temp;
        getline(ss, temp, ',');

        bk.numPages = stoi(temp);
        getline(ss, temp, ',');
        bk.price = stod(temp);
    }
    catch(std::invalid_argument const& e)
    {
        cout <<"Error" <<endl;
        cout << e.what() <<endl;

    }
}

void display(const Book &bk)
{
    cout << left << setw(50) << bk.title
        <<setw(20) << bk.author
        <<setw(8) << bk.price
        << setw(5) << bk.numPages<<endl;
}