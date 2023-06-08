  #include <iostream>
#include <bitset>
#include <vector>
#include <string>
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
	// RFC 4648 Base64 Table
	const char BASE64Table[64] = {
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
		'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
		'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
		'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
		'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
		'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
		'w', 'x', 'y', 'z', '0', '1', '2', '3',
		'4', '5', '6', '7', '8', '9', '+', '/'
	};
public:
	int binaryStringToDecimal(string binaryString);			// Binary style string -> Decimal integer
	string stringToBinaryString(const string message);		// General string -> Binary style string

	string binaryStringToBASE64(string binaryMessage);
	string BASE64Encode(string message);					// Encode Base64 (integrated process)
};


// Binary style string -> Decimal integer
int BASE64::binaryStringToDecimal(string binaryString)
{

	int num = stoi(binaryString);
	int dec_value = 0;

	// Initializing base value to 1, i.e 2^0
	int base = 1;

	int temp = num;

	while (temp) {

		int last_digit = temp % 10;
		temp = temp / 10;

		dec_value += last_digit * base;

		base = base * 2;

	}

	return dec_value;
}

// General string -> Binary style string
//  "ABCD..." -> "00010101010101111.."
string BASE64::stringToBinaryString(const string message) {

	string binaryString = "";

	for (char character : message) {
		binaryString += bitset<8>(character).to_string();
	}

	return binaryString;

}

// Binary style string -> BASE64 encoded string
string BASE64::binaryStringToBASE64(string binaryMessage) {

	// padding (The input length should be the multiple of 24 bits(6 bits * 4 sextets), 
	// but the bigger/the same comparing to the) given input message length()
	int padLength = (binaryMessage.length() / 24 + 1) * 24 - binaryMessage.length();

	for (int _seq = 0; _seq <= padLength; ++_seq)
		binaryMessage.push_back('0');


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
	for (string BASE64Character : BASE64Vector) {
		BASE64String.push_back(BASE64Table[binaryStringToDecimal(BASE64Character)]);
	}

	// Consecutive "A"s in BASE64string should be replaced to "="(padding) because
	// they are originally 0b000000 to match the multiple of 24, not the real data.
	int length = BASE64String.length();
	int i = length - 1;

	while (i >= 0 && BASE64String[i] == 'A')
		i--;

	if (i < length - 1)
		BASE64String.replace(i + 1, length - i - 1, length - i - 1, '=');

	return BASE64String;

}

// Encode Base64 (integrated process)
// ASCII text only
string BASE64::BASE64Encode(string message) {

	BASE64 base64;
	return base64.binaryStringToBASE64(base64.stringToBinaryString(message));

}

int main() {

	BASE64 base64;

	cout << base64.BASE64Encode("Hello World") << endl;
	cout << base64.BASE64Encode("https://stackoverflow.com/") << endl;

}
