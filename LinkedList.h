// ASU CSE310 Assignment #5 Spring 2024
// Name of Author: Raje Patil
// ASU ID: 1231031453
// Description: A simple linked list that implements a list of Car objects. A user can
//              perform searching, insertion or deletion on the linked list.
//              //---- is where you should add your own code

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

struct Car
{
   string model, make;
   int vin;
   double price;
   struct Car* next;
};

class LinkedList
{
   private:
     struct Car* head;
     int size;      //a variable represents number of Cars inside the list
   public:
     LinkedList();
     ~LinkedList();
     Car* getHead();
     int getSize();
     bool searchCar(int carVIN);
     bool insertCar(string model, string make, int vin, double price);
     bool deleteCar(int carVIN);
     void displayList();
};

//Constructor
LinkedList::LinkedList()
{
   head=NULL;
   size=0;
}

//Destructor
LinkedList::~LinkedList()
{
	//int carCount=0;
	Car* curr = head;
	while(curr!=NULL)
	{
		Car* nextCar= curr->next;
		delete curr;
		curr = nextCar;
		//carCount++;
	}

	head=NULL;

    //cout<< "The number of deleted Car is: " << carCount <<"\n";
}


Car* LinkedList::getHead()
{
    return head;
}

//Return number of Cars inside the Linked list
int LinkedList::getSize()
{
	size=0;
	Car* temp = head;
    while(temp!=NULL)
    {
    	size++;
    	temp=temp->next;

    }
    return size;
}

//This function does a linear search on the Car list with the given Car VIN
//it returns true if the corresponding Car is found, otherwise it returns false.
bool LinkedList::searchCar(int carVIN)
{
	Car* curr=head;
	if(curr==NULL)   //if its an empty car return false
	{
		return false;
	}

	while(curr != NULL ) //checking if the car has some value
	{
		if(curr->vin == carVIN)   //if they find the match return true
		{
			return true;
		}
		curr=curr->next; //moving to next node in the list
	}

	return false; //did not find the car
}

//Insert the parameter Car at the head of the linked list.
//return true if it is inserted successfully and false otherwise
bool LinkedList::insertCar(string model, string make, int vin, double price)
{
	Car* newCar = new Car();
	newCar->model=model;
	newCar->make=make;
	newCar->vin=vin;
	newCar->price=price;

	//if list is empty add new car as the first element
	if(head==NULL)
	{
		head=newCar;
		return true;
	}
	else
	{
		newCar->next=head;
		head=newCar;
	}
	return true;
}



//Delete the Car with the given Car VIN from the linked list.
//Return true if it is deleted successfully and false otherwise
bool LinkedList::deleteCar(int carVIN)
{
	Car* curr = head;
	Car* prev = NULL;

	if (curr == NULL)   // If it's an empty car return false
	{
		return false;
	}

	// Checking if the car to be removed is the head
	if (head->vin == carVIN)
	{
		curr = head->next;
		delete head;  // using delete instead of free
		head = curr;
		return true;
	}

	// Checking if current isn't empty
	while (curr != NULL)
	{
		if (curr->vin == carVIN)
		{
			prev->next = curr->next;
			delete curr;  // using delete instead of free
			return true;
		}

		prev = curr;
		curr = curr->next; // Moving to the next node in the list
	}

	return false; // Did not find the car
}



//This function displays the content of the linked lists from the hash table.
void LinkedList::displayList()
{
   struct Car *temp = head;
   if(head == NULL)
   {
   	//empty linked list, print nothing here
	   return;
   }
   else
   {
      while(temp != NULL)
      {
         cout << left    << setw(18) << temp->model
              << left    << setw(18) << temp->make
              << right   << setw(8)  << temp->vin
              << setw(10) << fixed << setprecision(2) << temp->price << "\n";
         temp = temp->next;
      }
   }
}
