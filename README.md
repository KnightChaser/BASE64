# BASE64

Can I implement BASE64 in C++? 

> My C++ implementation of BASE64 encoding/decoding algorithm. Referred to the Wikipedia's BASE64 specification.

<br>
Very ez to use my implementation. Refer to the example.

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


<br><br><br>
To-Do List (probably)
- [X] Encode (for ASCII range string)
- [x] Decode (for ASCII range string)
- [ ] Commandline
- [ ] Binary File support 
