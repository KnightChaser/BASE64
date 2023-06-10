# BASE64

> My Simple C++ implementation of BASE64 encoding/decoding algorithm(Probably easy to understand, relatively.). Referred to the Wikipedia's BASE64 specification.

<br><br>
To-Do List (probably)
- [X] Encode (for ASCII range string)
- [x] Decode (for ASCII range string)
- [x] Commandline
- [ ] Binary File support 

<br><br>
**Usage example** <br>
To convenience, the program has been developed for commandline usage. The program supports only 3 options to utilize, and you can check the detail at the following example image below. If you want to use in your computer, download the program at the `Release` tab of this repository, and move the `base64.exe` file to `C:\Windows\System32`. Then, you should be able to use BASE64 program anytime on the commandline. <br>
<img src="https://raw.githubusercontent.com/KnightChaser/BASE64/main/usage_example.png" width = "650">


#### Testing (Implementation verification)
Ya feelin' doubtful now on my implementation? You may do because this is written from scratch. So, you can test my implementation with multiple randomly generated string that consists various ASCII printable characters. Visit https://github.com/KnightChaser/BASE64/blob/main/base64Test.cpp to check and execute the verfication code on your own.
