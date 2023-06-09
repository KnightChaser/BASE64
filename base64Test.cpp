// Written in C++ 20, For ASCII-based text
// @KnightChaser

// THIS CODE IS WRITTEN TO VERIFY MY IMPLEMENTATION OF BASE64 ENCODING AND DECODING.

#include <iostream>
#include <iomanip>
#include <bitset>
#include <vector>
#include <string>
#include <regex>
#include <random>
using namespace std;

class BASE64 {
private:
	// RFC 4648 Base64 Table (for encoding)
	static const char BASE64EncodingTable[64];

	// RFC 4648 Base64 Table (for decoding(remaked))
	// Char in ASCII(BASE64EncodedMessage) -> Reverse of BASE64EncodingTable
	static const int BASE64DecodingTable[131];

	static int binaryStringToDecimal(string binaryString);			// Binary style string -> Decimal integer
public:
	static string BASE64Encode(string message);					// Encode Base64 (integrated process)
	static string BASE64Decode(string message);                      // Decode BASE64
};

const char BASE64::BASE64EncodingTable[64] = {
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
		'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
		'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
		'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
		'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
		'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
		'w', 'x', 'y', 'z', '0', '1', '2', '3',
		'4', '5', '6', '7', '8', '9', '+', '/'
};


const int BASE64::BASE64DecodingTable[131] = {
		// Corresponding values with BASE64Table            // ASCII
		-1,                                                 // 000
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1,             // 001 ~ 010
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1,             // 011 ~ 020
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1,             // 021 ~ 030
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1,             // 031 ~ 040
		-1, -1, 62, -1, -1, -1, 63, 52, 53, 54,             // 041 ~ 050   (- - + - - - / 0 1 2)
		55, 56, 57, 58, 59, 60, 61, -1, -1, -1,             // 051 ~ 060   (3 4 5 6 7 8 9 - - -)
		-1, -1, -1, -1,  0,  1,  2,  3,  4,  5,             // 061 ~ 070   (- - - - A B C D E F)
		 6,  7,  8,  9, 10, 11, 12, 13, 14, 15,             // 071 ~ 080   (G H I J K L M N O P)
		16, 17, 18, 19, 20, 21, 22, 23, 24, 25,             // 081 ~ 090   (Q R S T U V W X Y Z)
		-1, -1, -1, -1, -1, -1, 26, 27, 28, 29,             // 091 ~ 100   (- - - - - - a b c d)
		30, 31, 32, 33, 34, 35, 36, 37, 38, 39,             // 101 ~ 110   (e f g h i j k l m n)
		40, 41, 42, 43, 44, 45, 46, 47, 48, 49,             // 111 ~ 120   (o p q r s t u v w x)
		50, 51, -1, -1, -1, -1, -1, -1, -1, -1,             // 121 ~ 130   (y z - - - - - - - -)
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
string BASE64::BASE64Decode(string message) {

	// ASCII(BASE64 encoded) to binary
	string binaryDecodedMessage;

	// delete padding (Not used during decode process)
	size_t pos = message.find("=");
	while (pos != std::string::npos) {
		message.erase(pos, 1);
		pos = message.find("=", pos);
	}

	// Disintegrate the given message input(without padding)
	// and every BASE64Encoded string character matches to the reverse version of Base64 Table
	for (char character : message) {
		string binaryOneByteMessage = bitset<8>((int)character).to_string();
		int    sextetDecimal = BASE64::BASE64DecodingTable[BASE64::binaryStringToDecimal(binaryOneByteMessage)];

		binaryDecodedMessage.append(bitset<6>(sextetDecimal).to_string());
	}

	string decodedMessage;
	string characterBuffer;
	int counter = 0;								// every 8 bits (1 byte)
	
	// Currently, the message has been processed as a binary format.
	// To finalize, this procedure translates binary data to ASCII text format.
	for (char character : binaryDecodedMessage) {

		characterBuffer += character;
		counter++;

		if (counter % 8 == 0 && counter > 1) {

			int octat = BASE64::binaryStringToDecimal(characterBuffer);

			// Only printable ASCII characters are acceptable and transformable.
			// Data which are out of range equals invalid characters or padding(=) in BASE64 encoding.
			if (octat >= 32 && octat <= 126) {
				decodedMessage += (char)octat;
			}

			characterBuffer = "";

		}

	}

	return decodedMessage;


}

// For testing
string generateRandomString() {
    
    random_device rd;
    mt19937 gen(rd());
    
    string allowedChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&\'()*+,-./:;<=>?@[]^_`{|}~";
    
    uniform_int_distribution<> lengthDist(1, 30);
    int length = lengthDist(gen);
    
    // Generate the random string
    string randomString;
    uniform_int_distribution<> charDist(0, allowedChars.size() - 1);
    for (int i = 0; i < length; ++i)
    	randomString += allowedChars[charDist(gen)];
    
    return randomString;
}

int main() {

	// Verify with multiple implementation testing with randomly generated strings.
	bool verify = true;
	for (int _seq = 0; _seq < 100; _seq++) {
	    
		string randomString = generateRandomString();
		
		string encodedString = BASE64::BASE64Encode(randomString);
		
		if ((BASE64::BASE64Decode(encodedString) == randomString))
			cout << "[O]" << randomString << " ---> " << encodedString << endl;
		else {
			cout << "[X]" << randomString << " ---> " << encodedString << endl;
			bool verify = false;
		}
		
	}
	
	string result = verify ? "PASS" : "FAIL";
	cout << "TEST RESULT: " << result << endl;

}
