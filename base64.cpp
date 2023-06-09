// Written in C++ 20, For ASCII-based text
// @KnightChaser

#include <iostream>
#include <bitset>
#include <vector>
#include <string>
#include <regex>
using namespace std;

template <typename Tx>
ostream& operator<< (ostream& os, const vector<Tx> givenVector) {

	for (Tx element : givenVector) {
		os << element << " ";
	}

	return os;

}

class BASE64 {
private:
	// RFC 4648 Base64 Table (for encoding)
	const char BASE64EncodingTable[64] = {
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
		'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
		'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
		'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
		'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
		'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
		'w', 'x', 'y', 'z', '0', '1', '2', '3',
		'4', '5', '6', '7', '8', '9', '+', '/'
	};
	
	// RFC 4648 Base64 Table (for decoding(remaked))
	// Char in ASCII(BASE64EncodedMessage) -> Reverse of BASE64EncodingTable
	const int BASE64DecodingTable[131] = {
	    // Corresponding values with BASE64Table            // ASCII
	    -1,                                                 // 00
	    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,             // 01 ~ 10
	    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,             // 11 ~ 20
	    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,             // 21 ~ 30
	    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,             // 31 ~ 40
	    -1, -1, 62, -1, -1, -1, 63, 52, 53, 54,             // 41 ~ 50     (- - + - - - / 0 1 2)
	    55, 56, 57, 58, 59, 60, 61, -1, -1, -1,             // 51 ~ 60     (3 4 5 6 7 8 9 - - -)
	    -1, -1, -1, -1, -1,  0,  1,  2,  3,  4,             // 61 ~ 70     (- - - - - A B C D E)
	     5,  6,  7,  8,  9, 10, 11, 12, 13, 14,             // 71 ~ 80     (F G H I J K L M N O)
	    15, 16, 17, 18, 19, 20, 21, 22, 23, 24,             // 81 ~ 90     (P Q R S T U V W X Y)
	    25, -1, -1, -1, -1, -1, 26, 27, 28, 29,             // 91 ~ 100    (Z - - - - - a b c d)
	    30, 31, 32, 33, 34, 35, 36, 37, 38, 39,             // 101 ~ 110   (e f g h i j k l m n)
	    40, 41, 42, 43, 44, 45, 46, 47, 48, 49,             // 111 ~ 120   (o p q r s t u v w x)
	    50, 51, -1, -1, -1, -1, -1, -1, -1, -1,             // 121 ~ 130   (y z - - - - - - - -)
	};
public:
	int binaryStringToDecimal(string binaryString);			// Binary style string -> Decimal integer

	string binaryStringToBASE64(string binaryMessage);
	string BASE64Encode(string message);					// Encode Base64 (integrated process)
	void BASE64Decode(string message);                    // Decode BASE64
};


// Binary style string -> Decimal integer
int BASE64::binaryStringToDecimal(string binaryString) {

	int num = stoi(binaryString);
	int decimalValue = 0;

	// Initializing base value to 1, i.e 2^0
	int base = 1;
	int temp = num;

	while (temp) {

		int lastDigit = temp % 10;
		temp = temp / 10;

		decimalValue += lastDigit * base;

		base = base * 2;

	}

	return decimalValue;
}


// ** BASE64 ENCODE **
string BASE64::BASE64Encode(string message) {
    
    // Convert normal string to binary style string
    string binaryMessage = "";
    for (char character : message)
        binaryMessage += bitset<8>(character).to_string();

	// append padding (The input length should be the multiple of 24 bits(6 bits * 4 sextets), 
	// but the bigger/the same comparing to the) given input message length()
	if (binaryMessage.length() % 24 != 0) {
		int padLength = (binaryMessage.length() / 24 + 1) * 24 - binaryMessage.length();

		for (int _seq = 0; _seq <= padLength; ++_seq)
			binaryMessage.push_back('~');               // Use "~" special characters which isn't used in BASE64 formatting
														// to distinguish they are not the real part of the given data
	}

	// splitting
	vector<string> BASE64Vector;
	string unit;
	int currentPosition = 1;

	for (char bit : binaryMessage) {
		unit.push_back(bit);
		if (currentPosition % 6 == 0) {
			BASE64Vector.push_back(unit);
			unit = "";
		}
		currentPosition++;
	}

	// substitution
	string BASE64String = "";
	for (string chunk : BASE64Vector) {
		if (chunk == "~~~~~~") {                    	    // pure padding
			BASE64String += '=';                            // In Base64, "=" is for padding

		}
		else {												// Just data (Non consecutive 6 "~" string is originally data)
			regex regexForTilde("~");
			chunk = regex_replace(chunk, regexForTilde, "0");

			int decimalConvertedCharacter = BASE64::binaryStringToDecimal(chunk);
			BASE64String.push_back(BASE64::BASE64EncodingTable[decimalConvertedCharacter]);
		}
	}

	// Consecutive "A"s in BASE64string should be replaced to "="(padding) because
	// they are originally 0b000000 to match the multiple of 24, not the real data.

	return BASE64String;

}


// **BASE64 DECODE**
void BASE64::BASE64Decode(string message) {
    
    // ASCII(BASE64 encoded) to binary
    vector<string> binaryBASE64EncodedMessage;
    for(char character : message)
        binaryBASE64EncodedMessage.push_back(bitset<8> ((int)character).to_string());
        
    cout << binaryBASE64EncodedMessage << endl;
    
}

int main() {

	BASE64 base64;

    cout << base64.BASE64Encode("M") << endl;
 	base64.BASE64Decode("TQ==");

}
