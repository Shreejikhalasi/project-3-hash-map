#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <array>
#include "ItemPallet.hpp"

using std::string;
using std::ifstream;
using std::cout;
using std::endl;

// function to return the hash value based on the first digit
unsigned int hashfct1(unsigned int sku) {
  unsigned int s=sku;
  s= ((s)/(100000));
  s= ((s)%(10));
	return (s);
}

// function to return the hash value based on the second digit
unsigned int hashfct2(unsigned int sku) {
  unsigned int s=sku;
  s= ((s)/(10000));
  s=((s)%(10));
	return (s);
}

// function to return the hash value based on the third digit
unsigned int hashfct3(unsigned int sku) {
	unsigned int s=sku;
	s= ((s)/(1000));
	s=((s)%(10));
	return (s);
}

// function to return the hash value based on the fourth digit
unsigned int hashfct4(unsigned int sku) {
  unsigned int s=sku;
	s= ((s)/(100));
	s=((s)%(10));
	return (s);
}

// function to return the hash value based on the fifth digit
unsigned int hashfct5(unsigned int sku) {
  unsigned int s=sku;
	s= ((s)/(10));
	s= ((s)%(10));
	return (s);
}

// function to return the hash value based on the fourth digit
unsigned int hashfct6(unsigned int sku) {
  unsigned int s=sku;
  s=((s)%(10));
	return (s);
}

// Constructor for struct Item
Item::Item(string itemName, unsigned int sku):itemName_(itemName), sku_(sku)
{};

// Load information from a text file with the given filename
void ItemPallet::readTextfile(string filename) {
  ifstream myfile(filename);
  if (myfile.is_open()) {
    cout << "Successfully opened file " << filename << endl;
    string itemName;
    unsigned int sku;
    while (myfile >> itemName >> sku) {
			if (itemName.size() > 0)
      	addItem(itemName, sku);
    }
    myfile.close();
  }
  else
    throw std::invalid_argument("Could not open file " + filename);
}

  // function that adds the specified SKU to the pallet (i.e., to all hash tables)
void ItemPallet::addItem(string itemName, unsigned int sku) {
	hT1[sku] = itemName;
	hT2[sku] = itemName;
  hT3[sku] = itemName;
  hT4[sku] = itemName;
  hT5[sku] = itemName;
  hT6[sku] = itemName;
}

bool ItemPallet::removeItem(unsigned int sku) {
  try {
		hT1.erase(hT1.find(sku));
		hT2.erase(hT2.find(sku));
		hT3.erase(hT3.find(sku));
		hT4.erase(hT4.find(sku));
		hT5.erase(hT5.find(sku));
		hT6.erase(hT6.find(sku));
		throw (-1);
	}
  catch (int e) {
		return false;
	}
  return true;

}

// returns the optimal method of hashing
unsigned int ItemPallet::bestHashing() {
	std::array<int, 6> bucketSizes = {0, 0, 0, 0, 0, 0};
	std::array<int, 6> balanceSizes = {0, 0, 0, 0, 0, 0};
  int indexMax = -1;
  int indexMin = -1;
	for (unsigned int i = 0; i <= 6; i++) {
		bucketSizes[i] = hT1.bucket_size(i);
	}
  indexMax = std::distance(bucketSizes.begin(), std::max_element(bucketSizes.begin(), bucketSizes.end()));
	indexMin = std::distance(bucketSizes.begin(), std::min_element(bucketSizes.begin(), bucketSizes.end()));
	balanceSizes[0] = bucketSizes[indexMax] - bucketSizes[indexMin];
	for (unsigned int i = 0; i <= 6; i++) {
		bucketSizes[i] = hT2.bucket_size(i);
	}
  indexMax = std::distance(bucketSizes.begin(), std::max_element(bucketSizes.begin(), bucketSizes.end()));
	indexMin = std::distance(bucketSizes.begin(), std::min_element(bucketSizes.begin(), bucketSizes.end()));
	balanceSizes[1] = bucketSizes[indexMax] - bucketSizes[indexMin];
	for (unsigned int i = 0; i <= 6; i++) {
		bucketSizes[i] = hT3.bucket_size(i);
	}
  indexMax = std::distance(bucketSizes.begin(), std::max_element(bucketSizes.begin(), bucketSizes.end()));
	indexMin = std::distance(bucketSizes.begin(), std::min_element(bucketSizes.begin(), bucketSizes.end()));
	balanceSizes[2] = bucketSizes[indexMax] - bucketSizes[indexMin];
	for (unsigned int i = 0; i <= 6; i++) {
		bucketSizes[i] = hT4.bucket_size(i);
	}
  indexMax = std::distance(bucketSizes.begin(), std::max_element(bucketSizes.begin(), bucketSizes.end()));
	indexMin = std::distance(bucketSizes.begin(), std::min_element(bucketSizes.begin(), bucketSizes.end()));
	balanceSizes[3] = bucketSizes[indexMax] - bucketSizes[indexMin];
	for (unsigned int i = 0; i <= 6; i++) {
		bucketSizes[i] = hT5.bucket_size(i);
	}
  indexMax = std::distance(bucketSizes.begin(), std::max_element(bucketSizes.begin(), bucketSizes.end()));
	indexMin = std::distance(bucketSizes.begin(), std::min_element(bucketSizes.begin(), bucketSizes.end()));
	balanceSizes[4] = bucketSizes[indexMax] - bucketSizes[indexMin];
	for (unsigned int i = 0; i <= 6; i++) {
		bucketSizes[i] = hT6.bucket_size(i);
	}
  indexMax = std::distance(bucketSizes.begin(), std::max_element(bucketSizes.begin(), bucketSizes.end()));
	indexMin = std::distance(bucketSizes.begin(), std::min_element(bucketSizes.begin(), bucketSizes.end()));
	balanceSizes[5] = bucketSizes[indexMax] - bucketSizes[indexMin];

  indexMin = std::distance(balanceSizes.begin(), std::min_element(balanceSizes.begin(), balanceSizes.end()));
  indexMin++; //to correspond to the hash functions (which start at 1)
	return (unsigned int) indexMin;
}

size_t ItemPallet::size() {
  if ((hT1.size() != hT2.size()) || (hT1.size() != hT3.size()) || (hT1.size() != hT4.size()) || (hT1.size() != hT5.size())|| (hT1.size() != hT6.size()) ) {
  	throw std::length_error("Hash table sizes are not the same");
  }
	return hT1.size();
}
