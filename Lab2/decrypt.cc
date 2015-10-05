#include <iostream>
#include <chrono>
#include <map>

#include "Key.h"

typedef map<Key, Key> keymap;

void decrypt(Key encrypted)
{   
    unsigned char buffer[C+1];     // temporary string buffer
    Key candidate = {{0}};         // a password candidate
    Key candenc;                   // the encrypted password candidate
    Key halffullkey = {{0}};       // hurr durr
    Key zero = {{0}};              // the all zero key
    Key T[N];                      // table T
    keymap bBrute;                 // Bruteforced lower half of T
    unsigned char halfword[C];
    unsigned char incrementString[C];

    for (int i = 0; i < C; ++i)
    {
	incrementString[i] = ALPHABET[0];
	if (i == (C/2) - 1)
	{
	    incrementString[i] = ALPHABET[1];
	}
	if (i < C/2)
	{
	    halfword[i] = ALPHABET[0];
	}
	else
	{
	    halfword[i] = ALPHABET[R-1];
	}
    }
    halffullkey = KEYinit(halfword);

    for (int i{0}; i < N; ++i)
    {
	scanf("%s", buffer);
	T[i] = KEYinit(buffer);
    }
    
    auto begin1 = chrono::high_resolution_clock::now();
    
    // Get all the Ubrute values
    while (candidate != halffullkey)
    {
	++candidate;
	Key subtraction = encrypted - KEYsubsetsum(candidate, T);
	bBrute[subtraction] = candidate;
    }
    
    auto end1 = chrono::high_resolution_clock::now();

    cout << "Part 1 took: " << chrono::duration_cast<chrono::milliseconds>(end1 - begin1).count() << " milliseconds" << endl;
    
    auto begin2 = chrono::high_resolution_clock::now();

    Key increment = KEYinit(incrementString);  
    ++candidate;
    do
    {
	candenc = KEYsubsetsum(candidate, T);
	if (bBrute.find(candenc) != bBrute.end())
	{
	    cout << bBrute[candenc] + candidate << endl;
	}
	candidate = candidate + increment;
    }
    while (candidate != zero);

    auto end2 = chrono::high_resolution_clock::now();
    cout << "Part 2 took: " << chrono::duration_cast<chrono::milliseconds>(end2 - begin2).count() << " milliseconds" << endl;

    cout << "Total time: " << chrono::duration_cast<chrono::milliseconds>(end2 - begin1).count() << " milliseconds" << endl;
}

int main(int argc, char* argv[])
{
    unsigned char halfword[C];
    unsigned char incrementString[C];

    if (argc != 2)
    {
	cout << "Usage:" << endl << argv[0] << " password < rand8.txt" << endl;
	return 1;
    }

    decrypt(KEYinit((unsigned char*) argv[1]));
  
    return 0;
}
