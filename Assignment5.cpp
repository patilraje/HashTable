// ASU CSE310 Assignment #5 Spring 2024
// Name of Author: Raje Patil
// ASU ID: 1231031453
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
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

using namespace std;

//This function used to get a Car key which is the combination of model, make and vin
void getKey(string oneLine, string& model, string& make, int& vin);
//this function for price too
void getKeyTwo(string oneLine, string& model, string& make, int& vin, double& price);

int main()
{
   int size = 0 ;
   int numOfCommand = 0;
   string model, make, oneLine;  //added oneLine
   int vin;
   double price;
   string command;   //newly added string

   //declare any other necessary variables here


   cout << "Enter the size of the hash table: ";
   cin >> size;
   cin.ignore(20, '\n');

   //Instantiate the hash table with the relevant number of slots
   //RECHECK
  Hash* hashTable = new Hash(size);

   //use this do..while loop to repeatedly get one line Car info. and extract tokens
   //create one Car object and insert it inside the hashTable until seeing the message
   //"InsertionEnd" to terminate
   do
   {
	   getline(cin,oneLine);


	   if(oneLine == "InsertionEnd")
	   {
		   break;
	   }

	   getKeyTwo(oneLine, model, make, vin, price);  //extract the model make and vin and price, this functtion get key
	   	   	   	   	   	   	   	   	   	   	   	   	 //is for insertion
	   hashTable->hashInsert(model, make, vin, price); // add the car to the table


   } while(true);


   	  //cout << "\nEnter number of commands: ";   //***need to comment out in submitting
      cin >> numOfCommand;
      cin.ignore(20, '\n');



      for(int i= 0; i < numOfCommand; i++)
      {
      	//get one line command, extract the first token, if only one token
   	  cin >> command;  ///getting command for as long as the command goes??

         if(command.compare("hashDisplay") == 0)   //if(firstToken.compare("hashDisplay") == 0)
         {
            hashTable->hashDisplay();
            //hashTable->~Hash();
            break;
         }

         else  //more than one tokens, check the command name, extract the remaining tokens
         {

            if(command.compare("hashSearch")==0)
            {
            	hashTable->hashSearch(model, make, vin);
            }

            else  if(command.compare("hashDelete")==0)
            {
            	hashTable->hashDelete(model, make, vin);  //calls the delete function in hash header file
            }

            else if(command.compare("hashLoadFactor")==0)
            {
				 hashTable->hashLoadFactor();  //calling load factor function in hash header file
			}

            else
            {
           	 cout<<"Invalid command"<<endl;
            }
         }
      } //end for loop
      return 0;
}



//****************************************************************************************
//Given one line, this function extracts the model, make, vin info. of a Car
//This function is completed and given here as a study guide for extracting tokens
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

void getKeyTwo(string oneLine, string& model, string& make, int& vin, double& price)
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

   pos=oneLine.find(delimiter);
   token = oneLine.substr(0,pos);
   price = stoi(token);
   oneLine.erase(0, pos+delimiter.length());
}

