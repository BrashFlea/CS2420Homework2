#include "compressedString.h"

#include <iostream>
#include <sstream>
#include <string>

using std::cout;
using std::endl;
using std::string;
using std::ostringstream;

template <class T>
void checkTest(string test, T expected, T actual){

   if(expected == actual){
      cout << "Passed " << test << endl;
   }
   else{
      cout << "***Failed " << test << "***" << endl;
      cout << "Expected: " << expected << " Actual: " << actual << endl;
   }
}

int main(){

   //Check Constructor
   CompressedString s1("aaabbbccc");
   checkTest("Test 1", 6, s1.length());
   CompressedString s2("abc");
   checkTest("Test 2", 3, s2.length());
   CompressedString s3("cbbbaa");
   checkTest("Test 3", 5, s3.length());

   //Check Copy Constructor and Destructor
   CompressedString s4(s1);
   checkTest("Test 4", 6, s4.length());
   CompressedString* sp1 = new CompressedString("Goooooal");
   CompressedString* sp2 = new CompressedString(*sp1);
   CompressedString s5(*sp1);
   delete sp1;
   delete sp2;
   sp1 = NULL;
   sp2 = NULL;
   checkTest("Test 5", 0, 0);

   //Check Assignment Operator
   CompressedString s6 = s1;
   checkTest("Test 6", 6, s6.length());
   sp1 = new CompressedString("Goooooal");
   sp2 = new CompressedString("");
   *sp2 = *sp1;
   checkTest("Test7", 5, sp2->length());
   delete sp1;
   delete sp2;
   sp1 = NULL;
   sp2 = NULL;
   checkTest("Test8", 0, 0);

   //Check Concatenation
   CompressedString s7("aaabbb");
   CompressedString s8("ccccdddd");
   s7 += s8;
   checkTest("Test 9", 8, s7.length());
   checkTest("Test 10", 4, s8.length());
   CompressedString s9("cccccbbbbbbaaa");
   s9 += s1;
   checkTest("Test 11", 10, s9.length());
   CompressedString s10 = s1 + s3;
   checkTest("Test 12", 10, s10.length());
   s2 += "ccddd";
   checkTest("Test 13", 6, s2.length());

   //Check stream operator
   ostringstream os;
   os << s1;
   checkTest("Test 14", string("a3b3c3"), os.str());
   os.str("");
   os.clear();
   os << s2;
   checkTest("Test 15", string("abc3d3"), os.str());
   os.str("");
   os.clear();

   //Check reverse
   CompressedString s11(s1.reverse());
   checkTest("Test 16", 6, s11.length());
   os << s11;
   checkTest("Test 17", string("c3b3a3"), os.str());
   os.str("");
   os.clear();
   s11 = s2.reverse();
   os << s11;
   checkTest("Test 18", string("d3c3ba"), os.str());

   //Check original length and compression ratio
   checkTest("Test 19", 9, s1.originalLength());
   checkTest("Test 20", 6/9.0, s1.compressionRatio());
   checkTest("Test 21", 14, s7.originalLength());
   checkTest("Test 22", 23, s9.originalLength());
   CompressedString s12;
   checkTest("Test 23", 1.0, s12.compressionRatio());

   //Check decompression
   char* str = new char[s1.originalLength()+1];
   str[0] = '\0';
   s1.decompress(str, s1.originalLength()+1);
   checkTest("Test 24", string("aaabbbccc"), string(str));
   delete [] str;
   str = new char[s2.originalLength()+1];
   str[0] = '\0';
   s2.decompress(str, s2.originalLength()+1);
   checkTest("Test 25", string("abcccddd"), string(str));
   s1.decompress(str, s2.originalLength()+1);
   checkTest("Test 26", string("aaabbbcc"), string(str));
   delete [] str;
   str = NULL;


   //Large compressions
   cout << endl << "***Bonus Tests***" << endl << endl;
   CompressedString large("aaaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbbbbbbbccdddddddd");
   checkTest("Test 27", 10, large.length());
   CompressedString backwards(large.reverse());
   checkTest("Test 28", 10, backwards.length());
   CompressedString larger = backwards + large;
   checkTest("Test 29", 17, larger.length());
   str = new char[large.originalLength()+1];
   str[0] = '\0';
   large.decompress(str, large.originalLength()+1);
   checkTest("Test 30", string("aaaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbbbbbbbccdddddddd"), string(str));
   delete [] str;
   str = NULL;
   

}
