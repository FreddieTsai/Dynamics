#include <cstdio>
#include <conio.h>
#include <ctype.h>
#include <iostream>

using namespace std;

void double_to_char( char *buffer, double double_value, size_t arrctr );

int main()
{
    
}

void double_to_char( char *buffer, double double_value, size_t arrctr )
{
    snprintf( buffer, arrctr, "%f", double_value );
    for ( size_t i = 0; i < arrctr; i++ ) {
        if ( (buffer[i] >= '0' && buffer[i] <= '9') || buffer[i] == '.' )
            cout << buffer[i];
        else {
            buffer[i] = '0';
            cout << buffer[i];
        }
    }
    cout << endl;
}