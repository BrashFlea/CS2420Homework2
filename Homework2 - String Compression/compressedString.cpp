#include "compressedString.h"

using std::ostream;

/*Jonathan Mirabile
CS2420 - Assignment 2*/

CompressedString::CompressedString(){
	
}

CompressedString::CompressedString(const char* str){
	int i = 0; //for iteration
	int uLength = 1; //length of uncompressed string
	int cLength = 1; //length of compressed string
	int count = 0; //of occurences
	char currentLetter = ' ';
	char nextLetter = ' ';
	
	//Determine length of string
	while (*str != NULL) {
		uLength++;
		i++;
		str++;
	}

	char* tempCompressedString = new char[uLength]; //create array to store values

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
			break;
		}
		if (currentLetter == nextLetter){
			*(tempCompressedString + i) = currentLetter;
			count++;
		}
		else if (currentLetter != nextLetter) {
			*(tempCompressedString + (i+1)) = (count + '0'); //Conversion to char
		}
		
	}

	//CompressedString::compressedString = tempCompressedString;
	CompressedString::unCompLength = uLength; //uncompressed length
	CompressedString::compLength = cLength; //compressed length
}

CompressedString::CompressedString(const CompressedString& other){

}

CompressedString::~CompressedString(){

}

void CompressedString::operator=(const CompressedString& other){

}

void CompressedString::operator+=(const CompressedString& other){

}

void CompressedString::operator+=(const char* str){

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
   //return (compLength / unCompLength);
	return 0;
}

ostream& operator<<(ostream& outs, const CompressedString& source){
   return outs;
}

