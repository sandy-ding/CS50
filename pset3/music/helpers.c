// Helper functions for music

#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "helpers.h"
#define semi 0.083333


// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    //get numerator and denominator
    char nu[2] = {fraction[0], '\0'};
    char de[2] = {fraction[2], '\0'};
    //convert char into int; int atoi(string str);
    float n = atoi(nu);
    float d = atoi(de);
    //get duration
    int q = round(n / d * 8);
    return q;
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    int o;
    int n;
    char a = '0';
    int f;
    if (note[1] != '#' && note[1] != 'b')
    {
        //get octave
        char c[2] = {note[1], '\0'};
        o = atoi(c);
    }
    else
    {
        //get octave and # or b
        char c[2] = {note[2], '\0'};
        o = atoi(c);
        a = note[1];
    }
    //calculate octave
    f = round(440 * pow(2, o - 4));

    //n from 'A'
    switch (note[0])
    {
        case 'C':
            n = -9;
            break;
        case 'D':
            n = -7;
            break;
        case 'E':
            n = -5;
            break;
        case 'F':
            n = -4;
            break;
        case 'G':
            n = -2;
            break;
        case 'A':
            n = 0;
            break;
        case 'B':
            n = 2;
            break;

    }

    //n plus # or b
    if (a == '#')
    {
        n++;
    }
    else if (a == 'b')
    {
        n--;
    }

    //get frequency
    f = round(f * pow(2, n * semi));
    return f;
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    //strcmp will return 0 if the two strings are equal
    if (strcmp(s, "") == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
