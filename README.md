# BASE64

Can I implement BASE64 in C++? 

> My simplified C++ implementation of BASE64 encoding/decoding algorithm(Probably easy to understand, relatively.). Referred to the Wikipedia's BASE64 specification.

<br><br>
To-Do List (probably)
- [X] Encode (for ASCII range string)
- [x] Decode (for ASCII range string)
- [ ] Commandline
- [ ] Binary File support 

<br><br>
Very **ez** to use my implementation. Just `BASE64::BASE64Encode()` and `BASE64::BASE64Decode()`, that's all!

```c++
int main() {

	// You can run encode and decode function immediately
	// because the functions are provided as static member functions of class BASE64.

	// encoding example
	cout << BASE64::BASE64Encode("A") << endl;									// QQ==
	cout << BASE64::BASE64Encode("Github") << endl;								// R2l0aHVi
	cout << BASE64::BASE64Encode("@KnightChaser") << endl;						// QEtuaWdodENoYXNlcg==
	cout << BASE64::BASE64Encode("https://www.github.com/") << endl;			// aHR0cHM6Ly93d3cuZ2l0aHViLmNvbS8=

	// decoding example
	cout << endl;
	cout << BASE64::BASE64Decode("QQ==") << endl;								// A
	cout << BASE64::BASE64Decode("R2l0aHVi") << endl;							// Github
	cout << BASE64::BASE64Decode("QEtuaWdodENoYXNlcg==") << endl;				// @KnightChaser
	cout << BASE64::BASE64Decode("aHR0cHM6Ly93d3cuZ2l0aHViLmNvbS8=") << endl;	// https://www.github.com

}
```
```
QQ==
R2l0aHVi
QEtuaWdodENoYXNlcg==
aHR0cHM6Ly93d3cuZ2l0aHViLmNvbS8=

A
Github
@KnightChaser
https://www.github.com/
```


#### Testing (Implementation verification)
Ya feelin' doubtful now on my implementation? Then you can test my implementation with multiple randomly generated string that consists various ASCII printable characters. A testing can be implemented like... (Thanks to ChatGPT who did write that dull testing code.)
```c++

// Add this function that generates random ASCII string
#include <random>

std::string generateRandomString() {
	std::random_device rd;
	std::mt19937 gen(rd());

	// Define the set of characters allowed in the random string
	std::string allowedChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&\'()*+,-./:;<=>?@[]^_`{|}~";

	// Define the range of string lengths (between 8 and 16 characters)
	std::uniform_int_distribution<> lengthDist(8, 16);
	int length = lengthDist(gen);

	// Generate the random string
	std::string randomString;
	std::uniform_int_distribution<> charDist(0, allowedChars.size() - 1);
	for (int i = 0; i < length; ++i) {
		randomString += allowedChars[charDist(gen)];
	}

	return randomString;
}


int main() {

	// Verify with multiple implementation testing with randomly generated strings.
	for (int _seq = 0; _seq < 100; _seq++) {
		string randomString = generateRandomString();
		cout << randomString << " ";
		if ((BASE64::BASE64Decode(BASE64::BASE64Encode(randomString)) == randomString)) {
			cout << "[OK]" << endl;
		}
		else {
			cout << "[FAIL]" << endl;
		}
	}

}
```
