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
Ya feelin' doubtful now on my implementation? You may do because this is written from scratch. So, you can test my implementation with multiple randomly generated string that consists various ASCII printable characters. Visit https://github.com/KnightChaser/BASE64/blob/main/base64Test.cpp to check and execute the verfication code on your own.
