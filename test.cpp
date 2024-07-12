#include <cstdio>
#include <conio.h>
#include <ctype.h>
#include <iostream>
#include <string.h>

using namespace std;


char *double_to_char( char *buffer, double double_value, size_t sz );

int main()
{
    char charr[9];
    double d = 1.00000;

    cout << strlen( double_to_char( charr, d, 9 ) ) << endl;
}

char *double_to_char( char *buffer, double double_value, size_t sz )
{
    snprintf( buffer, sz-1, "%f", double_value );
    
    // clear redundant 0s
    for ( size_t i = sz-1; i >= 0; i-- ) {
        if ( buffer[i] != '\0' ) {
            if ( buffer[i] != '0' || buffer[i] == '.' ) {
                break;
            }

            if ( buffer[i] == '0' ) {
                buffer[i] = '\0';
                break;
            }
        }
    }

    // for ( size_t i = 0; i < sz; i++ ) {
    //         cout << buffer[i] << '/';
    // }
    // cout << endl;

    return buffer;
}