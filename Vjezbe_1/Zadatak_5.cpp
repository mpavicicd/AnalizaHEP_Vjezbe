#include <iostream>
using namespace std;

float _my_cube(float num) {
   return num*num*num; 
}

int main() {
    float x, kub;
    cout << "Type a number: "; // Type a number and press enter
    cin >> x; // Get user input from the keyboard
    kub = _my_cube(x);
    cout << "Cube is : " << kub << endl;
    return 0;
}
