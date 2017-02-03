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
			if (count == 1) {
				*(tempCompressedString + pos) = currentLetter;
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

	CompressedString::compressedString = tempCompressedString;
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

