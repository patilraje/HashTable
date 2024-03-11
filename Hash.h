// ASU CSE310 Assignment #5 Spring 2024
// Name of Author:
// ASU ID:
// Description: this is where you need to design functions on Hash hashTable,
// such as hashInsert, hashDelete, hashSearch and hashDisplay
// ---- is where you should add your own code

//only include necessary header file here
#include <iostream>
#include <iomanip>
#include <string>
#include "LinkedList.h"

using namespace std;

class Hash
{
   private:
      LinkedList* hashTable;     //hashTable is a one-dimensional array of LinkedList
      int m;                     //slots number of the hash table
	public:
      Hash(int size);
      ~Hash();
      bool hashSearch(string model, string make, int vin);
      bool hashInsert(string model, string make, int vin, double price);
      bool hashDelete(string model, string make, int vin);
      void hashLoadFactor();
      void hashDisplay();
      int hashFunction(string key);
      int numberCars();
};


//constructor
//initializing hashTable and m attributes.
Hash::Hash(int size)
{
	this->m=size;
	hashTable = new LinkedList[m]; //hashTable is initialized to a one dimensional array of size LinkedList
}



// Destructor
Hash::~Hash()
{
    // delete the whole table, which automatically calls the destructor for each LinkedList
    delete[] hashTable;
}


//This function searches for a key inside the hash table and
//return true if it is found and false otherwise
//Note: key is the combination of model, make and vin
//UTILIZES HASH FUNCTION*********
bool Hash::hashSearch(string model, string make, int vin)
{
   bool found = false;

   int hashValue = hashFunction(model + make + to_string(vin));
   found = hashTable[hashValue].searchCar(vin);

   if (found == true)
   {
      cout << "\n" << left
          << setw(18) << model
          << setw(18) << make
          << setw(8)  << vin
          << " is found inside the hash table." << endl;
      return true;
   }

   else
   {
      cout << "\n" << left
           << setw(18) << model
           << setw(18) << make
           << setw(8)  << vin
           << " is NOT found inside the hash table." << endl;
      return false;
   }

}


//hashInsert inserts a Car with the relevant info. into the hashTable.
//it returns true if the data is inserted successfully and false otherwise
//UTILIZES HASH FUNCTION*********
bool Hash::hashInsert(string model, string make, int vin, double price)
{
	bool add = false;
	int hashValue = hashFunction(model + make + to_string(vin)); //calculate hash value
	add = hashTable[hashValue].insertCar(model,make,vin,price); //insert hash in the slot calculated by function above'

	if (add==true)
	{
		//cout <<"success insert\n";
		return true;
	}

	else
	{
		//cout <<"fail insert\n";
		return false;
	}
}


//hashDelete deletes a Car with the relevant key from the hashTable.
//it returns true if it is deleted successfully and false otherwise
//Note: key is the combination of model, make and vin
//UTILIZES HASH FUNCTION*********
bool Hash::hashDelete(string model, string make, int vin)
{
	int hashValue = hashFunction(model + make + to_string(vin)); //calculate hash value
	bool del = hashTable[hashValue].deleteCar(vin); //call delete function from linked list file

	hashSearch(model, make, vin);

	if(del==true)
	{

      cout << "\n";
      cout << setw(18) << model
           << setw(18) << make
           << setw(8)  << vin
           << " is deleted from hash table.\n" << endl;
      return true;
	}

	else
	{
      cout << "\n";
      cout << setw(18) << model
           << setw(18) << make
           << setw(8)  << vin
           << " is NOT deleted from hash table.\n" << endl;
      return false;
	}
}



//This function computes your hash table real load factor
//it is the longest linked list size
//CHANGED FROM INT TO VOID
void Hash::hashLoadFactor()
{
    int actualLoad = 0;
    int total = 0;

    for (int i = 0; i < m; i++)
    {
        int currentLoad = hashTable[i].getSize();
        if (currentLoad > actualLoad)
            actualLoad = currentLoad;
    }

    total = numberCars();  // Call get number of cars
    double idealLoadFactor = static_cast<double>(total) / m;  // Use double for precision
    double performanceRatio = static_cast<double>(actualLoad) / idealLoadFactor;

    // Set precision to display up to two decimal places
    cout << fixed << setprecision(2);

    cout << "The ideal load factor is: " << idealLoadFactor << endl;
    cout << "My hash table real load factor is: " << actualLoad << endl;
    cout << "My hash table performance ratio is: " << performanceRatio << endl;
}

//This function prints all elements from the hashTable.
void Hash::hashDisplay()
{
  for(int i=0; i < m ; i++)
  {
	  cout << "\nHashTable[" << i <<"], size =" << hashTable[i].getSize() << endl;
	  hashTable[i].displayList();
  }
}


//This is the hash function you need to design. Given a
//string key, the function should return the slot number
//where we will hash the key to
//HASH KEY DRIVER********
int Hash::hashFunction(string key)
{
    int hashed = 0;
    int keyLength = key.length();

    for (int i = 0; i < keyLength; i++)
    {
        hashed += static_cast<int>(key[i]);
    }

    hashed += keyLength;
    hashed = hashed % m;

    return hashed;
}



int Hash::numberCars()
{
    int totalCars = 0;

    for (int i = 0; i < m; i++)
    {
        totalCars += hashTable[i].getSize();
    }
    //cout << totalCars;

    return totalCars;
}
