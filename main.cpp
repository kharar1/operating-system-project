#include<iostream>
#include<queue>
using namespace std;

 
enum VisitorType
{ STUDENT, TEACHER };

 
class Book
{
  
    // Book class
};


 
class Visitor
{
  
    // Visitor class
public:
virtual void dummy ()
  {
  }				// virtual function
};


 
 
class Student:public Visitor
{
  
    // Student class
};


 
class Teacher:public Visitor
{
  
    // Teacher class
};


 
class Library
{
  
queue < Visitor * >student_queue;
  
queue < Visitor * >teacher_queue;
  
Visitor * current_visitor;
  
VisitorType current_visitor_type;
  
Book * books;

 
public:
Library (Book * books)
  {
    
this->books = books;
    
current_visitor = nullptr;
  
} 
 
void addVisitor (Visitor * visitor)
  {
    
if (dynamic_cast < Student * >(visitor))
      {
	
student_queue.push (visitor);
      
}
    
    else if (dynamic_cast < Teacher * >(visitor))
      {
	
teacher_queue.push (visitor);
      
}
  
}
  
 
void serviceVisitor ()
  {
    
if (current_visitor == nullptr)
      {
	
if (!teacher_queue.empty ())
	  {
	    
current_visitor = teacher_queue.front ();
	    
teacher_queue.pop ();
	    
current_visitor_type = TEACHER;
	  
}
	
	else if (!student_queue.empty ())
	  {
	    
current_visitor = student_queue.front ();
	    
student_queue.pop ();
	    
current_visitor_type = STUDENT;
	  
}
      
}
    
 
if (current_visitor != nullptr)
      {
	
	  // service the current visitor
	  // issue books
	  // return books
	  // update visitor history
	  if (current_visitor_type == STUDENT)
	  {
	    
cout << "Student serviced" << endl;
	  
}
	
	else if (current_visitor_type == TEACHER)
	  {
	    
cout << "Teacher serviced" << endl;
	  
}
	
current_visitor = nullptr;
      
}
  
}

};


int
main ()
{
  
    // Create library object
    Book books[10];
  
Library library (books);
  
 
    // Add visitors to library based on user input
    while (true)
    {
      
cout <<
	"Enter visitor type (1 for student, 2 for teacher, or 0 to exit): ";
      
int type;
      
cin >> type;
      
if (type == 0)
	break;
      
if (type == 1)
	{
	  
Student * student = new Student ();
	  
library.addVisitor (student);
	
}
      else if (type == 2)
	{
	  
Teacher * teacher = new Teacher ();
	  
library.addVisitor (teacher);
	
}
      else
	{
	  
cout << "Invalid input. Try again." << endl;
	
}
    
}
  
 
    // Service visitors
    while (true)
    {
      
library.serviceVisitor ();
      
cout << "Press enter to continue or type 'exit' to quit: ";
      
string input;
      
getline (cin, input);
      
if (input == "exit")
	break;
    
}
  
 
return 0;

}
