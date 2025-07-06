#include <iostream>
#include <string>
using namespace std;
//Proyecto 2

int main()
{
    cout << "PROYECTO #2" << endl;
    
    string str;
    cin >> str;
    
    char c[str.length()+1];
    
    for (int i = 0; i < sizeof(c); i++) 
    { 
        c[i] = str[i]; 
        cout << c[i] << " "; 
    } 

    return 0;
}