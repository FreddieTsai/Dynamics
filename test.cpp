#include <cstdio>
#include <conio.h>
#include <ctype.h>
#include <iostream>

using namespace std;

void double_to_char( char *buffer, double double_value, size_t arrctr );

int main()
{
    char charr[32], *pch = charr;
    double dv;
    cin >> dv;
    double_to_char( charr, dv, sizeof(charr) );
    // char *pch = charr;

    // for ( size_t i = 0; i < sizeof(charr) && (charr[i] >= '0' && charr[i] <= '9'); i++ ) {
    //     tmparr[i] = charr[i];
    //     cout << charr[i];
    // }
    // cout << endl;

    // while ( (*pch >= '0' && *pch <= '9') || *pch == '.' )
    // {
    //     cout << *pch;
    //     pch += 1;
    // }
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