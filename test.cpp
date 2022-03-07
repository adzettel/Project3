#include <iostream>

using namespace std;

int main() {
    char str[8] = { 'e', 'e', 'c', 's', '2', '8', '0', '\0' };
    cout << str + 4 << endl; 		// A
    cout << *(str + 6) << endl; 	// B
    
    char *ptr = str + 3;
    *ptr++ = '\0';
    cout << str << endl; 		     // C
    cout << ++ptr << endl; 		// D
}
