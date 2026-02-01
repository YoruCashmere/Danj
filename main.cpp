#include <iostream>
#include <vector>
#include <limits>
#include<iomanip>
#include<ctime> //lets you use functions that display the current time and date
#include <stdexcept> //this will help us just exception
// honestly for this project i am thinking big bank and its the 31 of dec2025 so just go with flow

//system is almost completed hope you master all you learn ...what will your next project
 
class Book
{

public:
    std::string Name;
    std::string AuthorsName;
    std::string ShelfNum;
    std::string holder="Available";
    
    bool BookState;
//    if(!BookState){
    
//    }
    void CreateBook()
    {
        std::cout << "Enter Books name: ";
        std::getline(std::cin, Name);
        std::cout << "Enter Books Shelf number: ";
        std::cin >> ShelfNum;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Enter Books Authors name: ";
        std::getline(std::cin, AuthorsName);
        BookState = true;
    }

};
class Shelfs
{
public:
    std::string ShelfID;
    std::string ShelfDescription;
    size_t  ShelfSize;  //this datatype is unknown to me but it is just a really large range of unsigned characters
    std::vector<Book> Shelf;
    void CreateShelf()
    {
        std::cout << "Enter shelf address: ";
        getline(std::cin , ShelfID);
        std::cout << "Enter size: ";
        std::cin >> ShelfSize;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Enter any info about the shelf: ";
        std::getline(std::cin, ShelfDescription);
    }
};

std::vector<Shelfs> ShelfStore; // where shelfs are stored
void CreateShelf()  // This procedure create and store a specific shelf in shelfstore
{ 
    int NumOfShelfs;
    bool IDFound=false;
    std::cout << "How many shelf do you have: ";
    std::cin >> NumOfShelfs;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    for (int i = 0; i < NumOfShelfs; i++)
    {
        std::cout << "Create a Shelf: "<<std::endl;
        Shelfs shelf1;
        shelf1.CreateShelf();
        for(Shelfs element:ShelfStore){
            if(shelf1.ShelfID==element.ShelfID){
                std::cout<<"A shelf with this ID already exist"<<std::endl;
                std::cout<<"Shelf creation failed \n";
                IDFound=true;
            }
        }if(!IDFound){
            ShelfStore.push_back(shelf1);
        }
        
    }
}

std::ostream& operator<<(std::ostream &COUT, Shelfs &shelf1) //this function teaches the computer how to display shelfs 
    {
    COUT<<"SHELF ID: "<<shelf1.ShelfID<<"\t";
    COUT<<"Shelf size: "<<shelf1.ShelfSize<<"\t";
    COUT<<"SHELF Description: "<<shelf1.ShelfDescription<<"\t";
    return COUT;

}

std::ostream& operator<<(std::ostream &COUT,Book book1)     //THIS FUNCTION TEACHES THE COMPILER HOW TO display a book
{
    COUT<<"Book Name: "<<book1.Name<<"\t";
    COUT<<"Book authors name: "<<book1.AuthorsName<<"\t";
    COUT<<"Books ShelfNumber: "<<book1.ShelfNum<<"\t";
    COUT<<"BOOK Holder: "<<book1.holder;
    COUT<<"Book status: "<<book1.BookState<<"\n";
    return COUT;

}

void DisplayShelfs()    //this procedure display shelfs present
{
    std::cout<<"Here are the following shelfs present"<<std::endl;
    for(Shelfs element:ShelfStore){
        std::cout<<element<<'\n';
    }
   std::cout<<std::endl;

}

Shelfs *Findshelf(std::string SavingShelf)  // function to find a particular shelf from the shelfstore
{   // the &  before the function tells you it is returning an address instead of a value
    
    for (Shelfs &element : ShelfStore)
    {
        if (element.ShelfID == SavingShelf)
        {    
            return &element;
        }
    }
    return nullptr;
}

void DisplayBooksOnShelf(const Shelfs &Shelf) // procedure to display all books on a specific shelf
{
    std::cout << "The following books are onshelf" << std::endl;
    for (Book element : Shelf.Shelf)
    {
       std::cout<<element<<"\t";
    }
}

void StoreBookOnShelf(Book &book, Shelfs &Shelf1) // function to store a books in a shelf
{
    bool DuplicateFound = false;

    if (Shelf1.ShelfSize==Shelf1.Shelf.size())
    {
        std::string NewShelf1;
        
        std::cout << "This book shelf is full..please try another shelf to store the book"<<std::endl;
        DisplayShelfs();
        std::cin>>NewShelf1;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        Shelfs *requiredshelf=Findshelf(NewShelf1);
        if(requiredshelf != nullptr){
            StoreBookOnShelf(book,*requiredshelf);
        }else{
            std::cout<<"Shelf not found \n";
        }
        
    }
    for (Book element : Shelf1.Shelf)
    {
        if (element.ShelfNum == book.ShelfNum)
        {
            DuplicateFound = true;
            std::cout << "A book with this shelf number " << book.ShelfNum;
            std::cout << " Already exist..." << std::endl;
            std::cout << "Book save failed" << std::endl;
            break;
        }
    }
    if (!DuplicateFound)
    {
        Shelf1.Shelf.push_back(book);
        std::cout << std::endl;
    }
    
}

void Createbook()   //this function create books
{
    size_t  NwBooks;
    std::string SavingShelf;
    std::cout << "How many books do you plan on creating: ";
    std::cin >> NwBooks;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "On what shelf would you like to save these books: ";
    getline(std::cin, SavingShelf);
    Shelfs *requiredshelf=Findshelf(SavingShelf);
    if(requiredshelf->ShelfSize<NwBooks){
        std::cout<<"This Shelf is too small to contain all books "<<std::endl;
        std::cout<<"The current shelf can contain "<<requiredshelf->ShelfSize<<" Books only \n";    //this *requireshelf.shelfsize is same as requireshelf->shelfsize

    }   
    if (requiredshelf!=nullptr)
    {
        std::cout << "Book Creation has been Initialized" << std::endl;
        for (size_t i = 0; i<NwBooks; i++)
        { // here am using < on propose bec the first element was stored without usin the loop
            Book booki;
            // requiredshelf->BookID=booki.ShelfNum+requiredshelf->ShelfID;
            booki.CreateBook();
            booki.ShelfNum=requiredshelf->ShelfID+booki.ShelfNum;
            StoreBookOnShelf(booki, *requiredshelf);
        }
        DisplayBooksOnShelf(*requiredshelf);
    }else{
            std::cout<<"The shelf your looking "<<SavingShelf;
            std::cout<<" for is not found"<<std::endl;
        }
}

Shelfs& Delete()   //this function delete a book from a the database incase the book is destroyed or lost
{
    std::string BookID,shelf;
    std::cout<<"\nEnter the address of the book you wish to delete (address is the combination of a bookid and shelfID) \n ";
    std::cout<<"Enter shelf number: ";
    std::cin>>shelf; 
    std::cout<<"Enter bookID: ";
    std::cin>>BookID;
    BookID=shelf+BookID;
    Shelfs* targetShelf=Findshelf(shelf); 
    if(targetShelf!=nullptr){
        for(auto it=targetShelf->Shelf.begin(); it!=targetShelf->Shelf.end();){    //auto creates a dynamic pointer thats stores the address of the opperator
            if(it->ShelfNum==BookID){
                targetShelf->Shelf.erase(it);
            }else{
                it++;
            }
        }
    }else{
      std::cout<<"Book succesfully deleted";  
    }
    
    return *targetShelf; 
}

void Display_All_Books(){
    for(Shelfs element: ShelfStore){
        for(Book element1:element.Shelf){
            std::cout<<element1;
        }
    }
}

void Display_All_Shelfs(){
    for(Shelfs element: ShelfStore){
        std::cout<<element;
    }
}

Book* FindBook(std::string id){
    for(Shelfs &element: ShelfStore){
        for(Book &element1:element.Shelf){
            if(element1.ShelfNum==id){
                return &element1;
            }            
        }
    }
    return nullptr;
}

class Student{
    public:
    std::string Name;
    std::string Matricule;


    std::string& CurrentDate(){
    int week=7*24*60*60;
    std::time_t now= std::time(nullptr);
    std::time_t nextweek=now+week;
    std::string current_date=std::ctime(&now);
    std::string return_date=std::ctime(&nextweek);
    std::cout<<"Borrowed date: "<<current_date<<std::endl;
    std::cout<<"Return date: "<<return_date<<std::endl;
    return return_date;
}
std::string &Duration=CurrentDate();

    void BorrowBk(){
    std::string choice,id,action,shelf;
    int fees;
    std::cout<<"Would you like to borrow book to read(read) or borrow book to return home(readhome):";
    std::cin>>choice;
    if(choice=="read"){
        std::cout<<"Which book do you want(bookid) or you would like to consult our libraries(consultLibraries)";
        std::cin>>action;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if(action=="bookid"){
             std::cout<<"Enter book you: ";
            std::cin>>id;
            std::cout<<"Your request to borrow book is been processed \n";
            Book *targetbook=FindBook(id);
            if(targetbook!=nullptr){
                    if(targetbook->BookState){
                        targetbook->BookState=false;
                        targetbook->holder=Matricule+" to read";
                        // targetbook.Duration="";
                        std::cout<<"The book has been successfully borowed to read\n";
                    }else{
                        std::cout<<"book is not available \n";
                        std::cout<<"Book curently held by "<<targetbook->holder<<"to return on "<<Duration;    
                    }                    
                }
                else{
                    std::cout<<"Error: Book not found\n";
                }
        }else if(action=="consultlibraries"){ 
            Display_All_Books();
            std::cout<<"Enter the shelf you would like to see its contain: ";
            std::cin>>shelf;  
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            Shelfs *target=Findshelf(shelf);   
            if(target!=nullptr){
                DisplayBooksOnShelf(*target);
                std::cout<<"Pick a book: ";
                std::cin>>id;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                Book *targetbook=FindBook(id);
                if(targetbook!=nullptr){
                    if(targetbook->BookState){
                        targetbook->BookState=false;
                        targetbook->holder=Matricule+" to read";
                        std::cout<<"The book has been successfully borowed\n";
                    }else{
                        std::cout<<"book is not available \n";
                        std::cout<<"Book location "<<targetbook->holder;
                    }                    
                }
                
            }else{
                std::cout<<"invalid operation: \n";
            }      
        }
    }else if(choice=="readhome"){
        std::cout<<"###########Eligability test########\n";
        std::cout<<"Enter your fees:";
        std::cin>>fees;
        if(fees>=200000){
            std::cout<<"Eligeble"<<std::endl;
            std::cout<<"Which book do you want(bookid) or you would like to consult our libraries(consultLibraries)";
        std::cin>>action;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if(action=="bookid"){
             std::cout<<"Enter book you: ";
            std::cin>>id;
            Book *targetbook=FindBook(id);
            if(targetbook!=nullptr){
                    if(targetbook->BookState){
                        targetbook->BookState=false;
                        targetbook->holder=Matricule+" to read at home \n The book will available on: "+Duration;
                        std::cout<<"\nThe book has been successfully borowed\n";
                        CurrentDate();
                    }else{
                        std::cout<<"book not found \n";
                    }                    
                }
        }else if(action=="consultlibraries"){ 
            Display_All_Books();
            std::cout<<"Enter the shelf you would like to see its contain: ";
            std::cin>>shelf;  
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            Shelfs *target=Findshelf(shelf);   
            if(target!=nullptr){
                DisplayBooksOnShelf(*target);
                std::cout<<"Pick a book: ";
                std::cin>>id;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                Book *targetbook=FindBook(id);
                if(targetbook!=nullptr){
                    if(targetbook->BookState){
                        targetbook->BookState=false;
                        targetbook->holder=Matricule+" to read";
                        std::cout<<"The book has been successfully borowed\n";
                    }else{
                        std::cout<<"book is not available \n";
                        std::cout<<"Book location "<<targetbook->holder;
                    }                    
                }
                
            }else{
                std::cout<<"Element not found: \n";
            }      
        }
        }else{
            std::cout<<"Not eligable "<<std::endl;
        }
    }
    
}
void return_book(){
    std::string id;
    std::cout<<"Enter bookid";
    std::cin>>id;
    Book *targetbook=FindBook(id);
    targetbook->BookState=true;
    targetbook->holder="available";
}
    
};
std::vector<Student> SaveStudents;
void CreateStudent(){
    Student student1;
     std::cout<<"Enter your name: ";
    std::cin>>student1.Name;
    std::cout<<"Enter your matricule: ";
    std::cin>>student1.Matricule;
    SaveStudents.push_back(student1);
}                           
int main()
{

    CreateShelf();
    DisplayShelfs();
    Createbook();
    //DisplayBooksOnShelf(Delete());
    Student student1;
    student1.BorrowBk();



    return 0;
}