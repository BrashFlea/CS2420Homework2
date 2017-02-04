#include "compressedString.h"

using std::ostream;

/*Jonathan Mirabile
CS2420 - Assignment 2*/

CompressedString::CompressedString(){
	
}

CompressedString::CompressedString(const char* str){
	int i = 0; //for iteration
	int pos = 0;
	int uLength = 0; //length of uncompressed string
	int cLength = 0; //length of compressed string
	int count = 1; //of occurences
	char currentLetter = ' ';
	char nextLetter = ' ';
	
	//Determine length of string
	while (*str != NULL) {
		uLength++;
		i++;
		str++;
	}

	char* tempCompressedString = new char[uLength + 1]; //create array to store values

	for (int i = 0; i < uLength + 1; i++) {
		*(tempCompressedString + i) = '0';
	}


	//Reset the pointer to original position
	//Note: i resets to zero in this step
	while (i > 0) {
		i--;
		str--;
	}

	//Begin compression
	for (i; i < uLength; i++) {
		currentLetter = *(str + i);
		nextLetter = *(str + (i + 1));
		if (nextLetter == NULL) {
			if (count == 1) {
				*(tempCompressedString + pos) = currentLetter; //save the last letter
				*(tempCompressedString + (pos + 1)) = '\0'; //null terminate
			}
			else {
				*(tempCompressedString + (pos + 1)) = (count + '0'); //Conversion to char
				*(tempCompressedString + (pos + 2)) = '\0'; //null terminate
			}		
			break;
		}
		if (currentLetter == nextLetter){
			*(tempCompressedString + pos) = currentLetter;
			count++;
		}
		else if (currentLetter != nextLetter) {
			if (count == 1) {
				*(tempCompressedString + pos) = currentLetter;
				pos += 1; //skip ahead and don't record count
				count = 1; //reset count 
			}
			else {
				*(tempCompressedString + (pos + 1)) = (count + '0'); //Conversion to char
				pos += 2;
				count = 1; //reset count 
			}
			
		}
		
	}

	//Determine length of compressed string
	while (*tempCompressedString != NULL) {
		cLength++;
		tempCompressedString++;
	}

	//Reset the pointer to original position
	tempCompressedString -= cLength;

	this->compressedString = tempCompressedString;
	this->unCompLength = uLength; //uncompressed length
	this->compLength = cLength; //compressed length

}

CompressedString::CompressedString(const CompressedString& other){

	compressedString = other.compressedString;
	this->compLength = other.compLength;
	this->unCompLength = other.unCompLength;
}

CompressedString::~CompressedString(){
	compressedString = NULL;

}

void CompressedString::operator=(const CompressedString& other){

	char* newCompressedString = new char[other.compLength + 1]; //create array to store values

	for (int i = 0; i < other.compLength; i++) {
		*(newCompressedString + i) = *(other.compressedString + i);

	}
	*(newCompressedString + other.compLength) = '\0';

	compressedString = other.compressedString;
	this->compLength = other.compLength;
	this->unCompLength = other.unCompLength;

	//delete[] newCompressedString;
	newCompressedString = NULL;

}

void CompressedString::operator+=(const CompressedString& other){

	int newLength = compLength + other.compLength;
	char* newCompressedString = new char[newLength + 1]; //create array to store values
	int j = 0;
	int pos = (newLength - compLength);
	//Initalize array to zeroes
	for (int i = 0; i < newLength + 1; i++) {
		*(newCompressedString + i) = '0';
	}
	//First compressed string
	for (int i = 0; i < compLength; i++) {
		*(newCompressedString + i) = *(compressedString + i);
	}

	//Concatenation check
	if (*(newCompressedString + (compLength - 2)) == *(other.compressedString)) {
		*(newCompressedString + (compLength -1)) += (*(other.compressedString + 1) - '0'); //Take the number and add it to the count
		newLength -= 2;
		j += 2;
	}
	else if (*(newCompressedString + (compLength - 1)) == *(other.compressedString)) {
		//Single character check
	}

	//Second compressed string
	for (int i = pos; i < newLength; i++) {
		*(newCompressedString + i) = *(other.compressedString + j);
		j++;
	}
	//Append null terminator
	*(newCompressedString + newLength) = '\0';

	//Construct new CompressedString
	compressedString = newCompressedString;
	this->compLength = newLength;
	this->unCompLength = unCompLength + other.unCompLength;
	newCompressedString = NULL;

}

void CompressedString::operator+=(const char* str){

	int length = 0;
	int i = 0;

	//Determine length
	while (*str != NULL) {
		length++;
		i++;
		str++;
	}

	//Reset the pointer to original position
	//Note: i resets to zero in this step
	while (i > 0) {
		i--;
		str--;
	}

	int j = 0;
	int count = 0;
	int occurance = 1;
	int newLength = compLength + length;
	int pos = (newLength - compLength);

	char* newCompressedString = new char[newLength + 1]; //create array to store values

	//Initalize array to zeroes
	for (int i = 0; i < newLength + 1; i++) {
		*(newCompressedString + i) = '0';
	}

	//First compressed string
	for (int i = 0; i < compLength; i++) {
		*(newCompressedString + i) = *(compressedString + i);
	}

	//Concatenation check
	if (*(newCompressedString + (compLength - 2)) == *(str)) {
		*(newCompressedString + (compLength - 1)) += (*(str + 1) - '0'); //Take the number and add it to the count
		newLength -= 2;
		j += 2;
	}
	//Single character check
	else if (*(newCompressedString + (compLength - 1)) == *(str)) {
		while (*(newCompressedString + (compLength - 1)) == *(str + count)) {
			count++;
		}
		*(newCompressedString + (compLength)) = ((count + 1) + '0'); //Convert and add the count
		newLength -= count;
		j += count;
		pos--;
	}

	//Second string compression
	for (int i = pos; i <= newLength; i++) {
		if (*(str + j) != *(str + j + 1)) {
		*(newCompressedString + (i - 1)) = (occurance + '0');
		}
		else if (*(str + j) == *(str + j + 1)) {
			*(newCompressedString + pos) = *(str + j);
			occurance += 1;
			j++;
		}
	}
	//Append null terminator
	*(newCompressedString + newLength) = '\0';

	//Construct new CompressedString
	compressedString = newCompressedString;
	this->compLength = newLength;
	//this->unCompLength = unCompLength + other.unCompLength;
	newCompressedString = NULL;

}

CompressedString CompressedString::operator+(const CompressedString& other) const{
   return CompressedString("");
}

CompressedString CompressedString::reverse() const{
   return CompressedString("");
}

void CompressedString::decompress(char* str, int size) const{
}

int CompressedString::length() const{
   return compLength;
}

int CompressedString::originalLength() const{
   return unCompLength;
}

double CompressedString::compressionRatio() const{
	double compressionRatio = double(compLength) / double(unCompLength);
    return compressionRatio;
}

ostream& operator<<(ostream& outs, const CompressedString& source){
	int i = 0;
	while (*(source.compressedString + i) != NULL) {
		outs << *(source.compressedString + i);
		i++;
	}
   return outs;
}

