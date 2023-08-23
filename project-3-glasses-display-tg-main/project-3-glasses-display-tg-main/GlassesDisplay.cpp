#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include "GlassesDisplay.hpp"

using std::string;
using std::ifstream;
using std::cout;
using std::endl;

// function to return the hash value based on the first digit
unsigned int hashfct1(unsigned int barcode) {
    unsigned int d;
    d = (barcode / 1000000) % 10;
    return d;
}

// function to return the hash value based on the second digit
unsigned int hashfct2(unsigned int barcode) {
    unsigned int d;
    d = (barcode / 100000) % 10;
    return d;
}

// function to return the hash value based on the third digit
unsigned int hashfct3(unsigned int barcode) {
    unsigned int d;
    d = (barcode / 10000) % 10;
    return d;
}

// function to return the hash value based on the fourth digit
unsigned int hashfct4(unsigned int barcode) {
    unsigned int d;
    d = (barcode / 1000) % 10;
    return d;
}

// function to return the hash value based on the fifth digit
unsigned int hashfct5(unsigned int barcode) {
    unsigned int d;
    d = (barcode / 100) % 10;
    return d;
}

// function to return the hash value based on the fourth digit
unsigned int hashfct6(unsigned int barcode) {
    unsigned int d;
    d = (barcode / 10) % 10;
    return d;
}

// function to return the hash value based on the fifth digit
unsigned int hashfct7(unsigned int barcode) {
    unsigned int d;
    d = (barcode / 1) % 10;
    return d;
}


// Constructor for struct Item
Glasses::Glasses(string glassesColor, string glassesShape, string glassesBrand, unsigned int barcode): glassesColor_(glassesColor), glassesShape_(glassesShape), glassesBrand_(glassesBrand), barcode_(barcode)
{};

// Load information from a text file with the given filename
// THIS FUNCTION IS COMPLETE
void GlassesDisplay::readTextfile(string filename) {
  ifstream myfile(filename);

  if (myfile.is_open()) {
    cout << "Successfully opened file " << filename << endl;
    string glassesColor;
    string glassesShape;
    string glassesBrand;
    unsigned int barcode;
    while (myfile >> glassesColor >> glassesShape >> glassesBrand >> barcode) {
			if (glassesColor.size() > 0)
      	addGlasses(glassesColor, glassesShape, glassesBrand, barcode);
    }
    myfile.close();
  }
  else
    throw std::invalid_argument("Could not open file " + filename);
}

void GlassesDisplay::addGlasses(string glassesColor, string glassesShape, string glassesBrand, unsigned int barcode) {
  // function that adds the specified pair of glasses to main display (i.e., to all hash tables)
  
  // Create Glasses object
  Glasses glasses;
  glasses.glassesColor_ = glassesColor;
  glasses.glassesShape_ = glassesShape;
  glasses.glassesBrand_ = glassesBrand;
  glasses.barcode_ = barcode;
  
  // Add glasses to each hash table
  hT1[barcode] = glasses;
  hT2[barcode] = glasses;
  hT3[barcode] = glasses;
  hT4[barcode] = glasses;
  hT5[barcode] = glasses;
  hT6[barcode] = glasses;
  hT7[barcode] = glasses;
}

bool GlassesDisplay::removeGlasses(unsigned int barcode) {
  // function that removes the pair of glasses specified by the barcode from the display
  // if pair is found, then it is removed and the function returns true
  // else returns false
  bool found_pair = hT1.find(barcode) != hT1.end();
  if (found_pair) {
    hT1.erase(barcode);
	  hT2.erase(barcode);
	  hT3.erase(barcode);
	  hT4.erase(barcode);
	  hT5.erase(barcode);
	  hT6.erase(barcode);
	  hT7.erase(barcode);	
  return true;
  }

  return false;
}

unsigned int GlassesDisplay::bestHashing() {
  // function that decides the best has function, i.e. the ones among
  // fct1-fct7 that creates the most balanced hash table for the current
  // GlassDisplay data member allGlasses

	// Hints:
	// Calculate the balance of each hashtable, one by one.
	/*
	 for (unsigned i=0; i<10; ++i) {
    cout << hT1.bucket_size(i); // Call bucket_size() to get the size of each bucket
  }
	*/
	// Then, calculate the lowest balance

    unsigned int balance[8];
    balance[0] = 0;

    unsigned int min_loc=0, max_loc=0;

    // Hash table 1
    min_loc =  hT1.bucket_size(0);
    for (unsigned i = 0; i < 10; i++) {
      unsigned size = hT1.bucket_size(i);
      if (min_loc > size) {
        min_loc = size;
      }
      if (max_loc < size) {
        max_loc = size;
      }
    }
    balance[1] = max_loc - min_loc;
    
    // Hash table 2
    min_loc =  hT2.bucket_size(0);
    for (unsigned i = 0; i < 10; i++) {
      unsigned size = hT2.bucket_size(i);
      if (min_loc > size) {
        min_loc = size;
      }
      if (max_loc < size) {
        max_loc = size;
      }
    }
    balance[2] = max_loc - min_loc;

    // Hash table 3
    min_loc =  hT3.bucket_size(0);
    for (unsigned i = 0; i < 10; i++) {
      unsigned size = hT3.bucket_size(i);
      if (min_loc > size) {
        min_loc = size;
      }
      if (max_loc < size) {
        max_loc = size;
      }
    }
    balance[3] = max_loc - min_loc;

    // Hash table 4
    min_loc =  hT4.bucket_size(0);
    for (unsigned i = 0; i < 10; i++) {
      unsigned size = hT4.bucket_size(i);
      if (min_loc > size) {
        min_loc = size;
      }
      if (max_loc < size) {
        max_loc = size;
      }
    }
    balance[4] = max_loc - min_loc;

    // Hash table 5
    min_loc =  hT5.bucket_size(0);
    for (unsigned i = 0; i < 10; i++) {
      unsigned size = hT5.bucket_size(i);
      if (min_loc > size) {
        min_loc = size;
      }
      if (max_loc < size) {
        max_loc = size;
      }
    }
    balance[5] = max_loc - min_loc;

    // Hash table 6
    min_loc =  hT6.bucket_size(0);
    for (unsigned i = 0; i < 10; i++) {
      unsigned size = hT6.bucket_size(i);
      if (min_loc > size) {
        min_loc = size;
      }
      if (max_loc < size) {
        max_loc = size;
      }
    }
    balance[6] = max_loc - min_loc;

    // Hash table 7
    min_loc =  hT7.bucket_size(0);
    for (unsigned i = 0; i < 10; i++) {
      unsigned size = hT7.bucket_size(i);
      if (min_loc > size) {
        min_loc = size;
      }
      if (max_loc < size) {
        max_loc = size;
      }
    }
    balance[7] = max_loc - min_loc;

    // Calculate lowest balance
    // Initialize the first hash table with the lowest
    unsigned int lowest_balance = 1;
    // Iterate through the hash table from 1-7
    for (unsigned i = 1; i <= 7; i++){
      if (balance[i] < balance[lowest_balance]){
        balance[lowest_balance] = balance[i];
        lowest_balance = i;
      }
    }
    return lowest_balance;
}

// ALREADY COMPLETED
size_t GlassesDisplay::size() {
    if ((hT1.size() != hT2.size()) || (hT1.size() != hT3.size()) || (hT1.size() != hT4.size()) || (hT1.size() != hT5.size())|| (hT1.size() != hT6.size()) || (hT1.size() != hT7.size()))
  	throw std::length_error("Hash table sizes are not the same");
    
return hT1.size();
}
