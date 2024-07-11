#include <cstdio>
#include <conio.h>
#include <ctype.h>
#include <iostream>

using namespace std;


double char_to_double( char *buffer, size_t sz );

int main()
{
    char ch = 'D', buffer[32];
    size_t sz = 0;
    while ( ch != '\r' )
    {
        ch = getch();
        ch = toupper(ch);
        cout << ch << endl;
        buffer[sz] = ch;
        sz += 1;
        // cout << char_to_double( buffer, idx ) << endl;
    }
    cout << char_to_double( buffer, sz-1 );
    double d = 12345.67891;
    cout << d << endl;
}

/**
 * @brief get the double value from a char array
 * 
 * @param char *buffer
 * @param size_t sz : size of char array
 */
double char_to_double( char *buffer, size_t sz )
{
    // make sure buffer has content
    if ( sz <= 0 ) {
        return 0.0;
    }

    double double_value = 0.0;
    size_t i = 0;
    
    // get the integer part of double value
    for ( i = 0; i < sz && buffer[i] != '.'; i++ ) {

        double_value *= 10;
        double_value += (buffer[i]-'0');
    }

    // reach end of buffer (get all numbers in buffer)
    if ( i == sz ) {
        return double_value;
    }

    // to get the digit after the decimal point
    i += 1;

    // get the float part of double value
    for ( double offset = 0.1 ; i < sz; i++ ) {

        double_value += (offset * (buffer[i]-'0'));
        offset *= 0.1;
    }
    return double_value;
}