
// ASU CSE310 Assignment #5 Spring 2024
// Name of Author:
// ASU ID:
// Description: this is the main program that reads input from a text file,
// it then call hash functions to execute hash commands given in the input.
// ---- is where you need to add your own code

/*****************************************************************************
//(1)Describe here what is your hash function? How do you get an input Car
//   object's hash value.
 * My hash function takes a concatenated string of model,make and vin (making the key) and then adds the ascii
 * value of every element in it, moving forward I add the number of elements in the key to the calculated
 * ascii sum and then mod it by hash table size.
 * i started with analyzing Dr. Feng's output trying to reverse engineer it and this is the closest
 * I could get with some values
//(2)Did your hash function work well? For each of the four test cases, list here
//   your hash function's performance ratio and the longest LinkedList size.
 * Yes it was decent function, the performance ratio was less than 2 mostly which I think is really good.
 * TEST CASE 1:
	Load factor is: 4.00
	performance ratio is: 1.25
 *TEST CASE 2:
	Load factor is: 9.00
	performance ratio is: 1.66
 *TEST CASE 3:
	Load factor is: 8.00
	performance ratio is: 1.69
 *TEST CASE 4:
	Load factor is: 27.00
	performance ratio is: 1.56

//(3)If you had to change your hash function to reduce the number of collisions,
//   how will you change it?
 * I tried my best finding an optimal solution, if I had to tweak it to make it better I
 * would possibly increase the hash table size and experiment to see if that works, or maybe
 * experiment with diving every key with the key length along with increasing hash table size.
 * I think increasing Hash table size would help with decreasing collisions.
********************************************************************************/

#include "Hash.h"
#include <sstream>
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// This function is used to get a Car key, which is the combination of model, make, and vin
// Function declarations
void getKey(string oneLine, string& model, string& make, int& vin);
void extractCarInfo(string oneLine, string& model, string& make, int& vin, double& price);

int main()
{
   int size = 0;
   int numOfCommand = 0;
   string model, make, command, oneLine;
   int vin;
   double price= 0.0;

   // Declare any other necessary variables here

   cout << "Enter the size of the hash table: ";
   cin >> size;
   cin.ignore(20, '\n');

   // Instantiate the hash table with the relevant number of slots
   Hash* hashTable = new Hash(size);

   // Use this do-while loop to repeatedly get one line of Car info and extract tokens
   // Create one Car object and insert it inside the hashTable until seeing the message
   // "InsertionEnd" to terminate
   do
   {
      getline(cin, oneLine);

      if (oneLine == "InsertionEnd")
      {
         break;
      }

      //for insert in particular
      extractCarInfo(oneLine, model, make, vin, price);
      // Insert the car into the hash table
      hashTable->hashInsert(model, make, vin, price);

   } while (true);

   // cout << "\nEnter number of commands: ";   //***need to comment out in submitting
   cin >> numOfCommand;
   cin.ignore(20, '\n');

   for (int i = 0; i < numOfCommand; i++)
   {
      //cin >> command;
	  getline(cin, oneLine); //reads the line that has the command

      // get one line command, extract the first token, if only one token
      if (oneLine.compare("hashDisplay") == 0) //hash display usually doesnt have any extra parameters
      {
         hashTable->hashDisplay();
      }

      else if(oneLine.compare("hashLoadFactor") == 0)
      {
    	  hashTable->hashLoadFactor();
      }

      else  // more than one token, check the command name, extract the remaining tokens
      {
    	 //WELL EXTRACTED FIRST COMMAND YAYY
    	  string delimiter = ","; // @suppress("Invalid arguments")
    	  int pos=oneLine.find(delimiter);
    	  string token = oneLine.substr(0,pos);;
    	  getKey(oneLine, model, make, vin);
    	  string command = token;//extracting remaining tokens
    	 //cout << oneLine.substr(0,pos);

         if (command.compare("hashSearch") == 0)
         {
            // Extract model, make, and vin
        	getKey(oneLine, model, make, vin);   //feeds getKey the read line and addresses for details
            hashTable->hashSearch(model, make, vin);
         }
         else if (command.compare("hashDelete") == 0)
         {
            // Extract model, make, and vin
        	getKey(oneLine, model, make, vin);   //feeds getKey the read line and addresses for details
            hashTable->hashDelete(model, make, vin);
         }

         else
         {
            cout << "Invalid command" << endl;
         }
      }
   } // end for loop

   //delete[] hashTable; // freeing the allocated memory
   return 0;
}

// Given one line, this function extracts the model, make, vin info. of a Car
void getKey(string oneLine, string& model, string& make, int& vin)
{
   string delimiter = ","; // @suppress("Invalid arguments")
   int pos=oneLine.find(delimiter);
   string token = oneLine.substr(0,pos);
   string command = token;
   oneLine.erase(0, pos+delimiter.length());

   pos=oneLine.find(delimiter);
   token = oneLine.substr(0,pos);
   model = token;
   oneLine.erase(0, pos+delimiter.length());

   pos=oneLine.find(delimiter);
   token = oneLine.substr(0,pos);
   make = token;
   oneLine.erase(0, pos+delimiter.length());

   pos=oneLine.find(delimiter);
   token = oneLine.substr(0,pos);
   vin = stoi(token);
   oneLine.erase(0, pos+delimiter.length());
}


// Function to extract all necessary information for adding cars
void extractCarInfo(string oneLine, string& model, string& make, int& vin, double& price)
{
    string delimiter = ","; // @suppress("Invalid arguments")
    int pos = oneLine.find(delimiter);
    string token = oneLine.substr(0, pos);
    model = oneLine.substr(0, pos);
    oneLine.erase(0, pos + delimiter.length());

    pos = oneLine.find(delimiter);
    token = oneLine.substr(0, pos);
    make = token;
    oneLine.erase(0, pos + delimiter.length());

    pos = oneLine.find(delimiter);
    token = oneLine.substr(0, pos);
    vin = stoi(token);
    oneLine.erase(0, pos + delimiter.length());

    pos = oneLine.find(delimiter);
    token = oneLine.substr(0, pos);
    price = stod(token);
    oneLine.erase(0, pos + delimiter.length());
}
