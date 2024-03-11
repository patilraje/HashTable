
// ASU CSE310 Assignment #5 Spring 2024
// Name of Author:
// ASU ID:
// Description: this is the main program that reads input from a text file,
// it then call hash functions to execute hash commands given in the input.
// ---- is where you need to add your own code

/*****************************************************************************
//(1)Describe here what is your hash function? How do you get an input Car
//   object's hash value.
//(2)Did your hash function work well? For each of the four test cases, list here
//   your hash function's performance ratio and the longest LinkedList size.
//(3)If you had to change your hash function to reduce the number of collisions,
//   how will you change it?
********************************************************************************/

#include "Hash.h"
#include <sstream>
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// This function is used to get a Car key, which is the combination of model, make, and vin
// Function declarations
void extractCarInfo(string oneLine, string& model, string& make, int& vin, double& price);
void getKey(string oneLine, string& model, string& make, int& vin);

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

      cin >> command;

      // get one line command, extract the first token, if only one token
      if (command.compare("hashDisplay") == 0)
      {
         hashTable->hashDisplay();
      }

      else  // more than one token, check the command name, extract the remaining tokens
      {
         if (command.compare("hashSearch") == 0)
         {
            // Extract model, make, and vin
            hashTable->hashSearch(model, make, vin);
         }
         else if (command.compare("hashDelete") == 0)
         {
            // Extract model, make, and vin
            hashTable->hashDelete(model, make, vin);
         }

         else if (command.compare("hashLoadFactor") == 0)
         {
            hashTable->hashLoadFactor();
         }

         else
         {
            cout << "Invalid command" << endl;
         }
      }
   } // end for loop

   delete[] hashTable; // Free the allocated memory
   return 0;
}

// Given one line, this function extracts the model, make, vin info. of a Car
void getKey(string oneLine, string& model, string& make, int& vin, int& price)
{
   string delimiter = ","; // @suppress("Invalid arguments")
   int pos = oneLine.find(delimiter);
   string token = oneLine.substr(0, pos);
   string command = token;
   oneLine.erase(0, pos + delimiter.length());

   pos = oneLine.find(delimiter);
   token = oneLine.substr(0, pos);
   model = token;
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


// Function to extract all necessary information for adding cars
void extractCarInfo(string oneLine, string& model, string& make, int& vin, double& price)
{
    string delimiter = ","; // @suppress("Invalid arguments")
    int pos = oneLine.find(delimiter);
    model = oneLine.substr(0, pos);
    oneLine.erase(0, pos + delimiter.length());

    pos = oneLine.find(delimiter);
    make = oneLine.substr(0, pos);
    oneLine.erase(0, pos + delimiter.length());

    pos = oneLine.find(delimiter);
    vin = stoi(oneLine.substr(0, pos));
    oneLine.erase(0, pos + delimiter.length());

    pos = oneLine.find(delimiter);
    price = stod(oneLine.substr(0, pos));
}
