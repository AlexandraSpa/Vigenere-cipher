// cripto_tema1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <cstring>
#include <cctype>
#include <stdio.h>
#include <stdlib.h>
#include<time.h>

using namespace std;


char sample[1000]="criptografie!";
int plaintext[1000], ciphertext[1000], decryptext[1000], text_length, key[26], key_length;
double f[26], IC[27][27], average[26];

int change(const char * letter)
{
    if (isupper(letter[0]))
    {
        return (letter[0] + 32 - 'a');
    }
    return (letter[0] -'a');

}
void filter_text(const char* text, int text2[], int& length)
{
    int text_length = strlen(text);
    length = 0;
    for (int i = 0; i < text_length; i++)
    {
        if (isalpha(text[i]))
        {
            text2[length++] = change(text + i);
        }
    }
}
void get_text(int text[], int length)
{
    for (int i = 0; i < length; i++)
    {
        cout << (char)('a' + text[i]) << " ";
    }
    cout << endl;
}
void encryption()
{
    cout << "Introduce the key length: ";
cin >> key_length;
cout << endl;
srand(time(0));
for (int i = 0; i < key_length; i++)
{
    key[i] = rand() % 10;
}
cout << "Your key is: " << endl;
for (int i = 0; i < key_length; i++)
{
    cout << key[i] << " ";
}
cout << endl;
for (int i = 0; i < text_length; i++)
{
    ciphertext[i] = (plaintext[i] + key[i % key_length]) % 26;
}

}
void decryption()
{
    for (int i = 0; i < text_length; i++)
    {
        decryptext[i] = ciphertext[i] - key[i % key_length];
        if (decryptext[i] < 0)
        {
            decryptext[i] += 26;
        }
        else
        {
            decryptext[i] = decryptext[i] % 26;
        }
    }
}
void init_f()
{
    for (int i = 0; i < 26; i++)
    {
        f[i] = 0;
    }
}
void init_IC()
{
    for (int i = 1; i <= 26; i++)
    {
        for (int j = 1; j <= 26; j++)
        {
            IC[i][j] = 0;
        }
    }
}
void get_IC(int cipherstring[], int txtlength)
{
    for (int l_key = 1; l_key <= 26; l_key++)  //key's length
    {
        for (int sb = 0; sb < l_key; sb++)  //no. of substrings
        {
            int i = sb;
            int sblength = 0;
            init_f();
            while (i < txtlength)
            {
                f[cipherstring[i]]++;
                i += l_key;
                sblength++;
            }
            int operation;
            for (int w = 0; w < 26; w++)
            {
                double operation = (f[w] / sblength) * ((f[w] - 1) / (sblength - 1));
                IC[l_key][sb + 1] = IC[l_key][sb + 1] + operation;
            }
        }
    }
}
void determine_key_length()
{
    init_IC();
    get_IC(ciphertext, text_length);

    for (int i = 1; i <= 26; i++)
    {
        for (int j = 1; j <= 26; j++)
        {
            average[i] += IC[i][j];
        }
        average[i] = average[i] / i;

    }
    int key_len;
    double minimum, minimum2;
    minimum = (average[2] <= 0.065 ? (0.065 - average[2]) : (average[2] - 0.065));
    key_len = 2;
    for (int i = 3; i <= 26; i++)
    {
        minimum2 = (average[i] <= 0.065 ? (0.065 - average[i]) : (average[i] - 0.065));
        if (minimum > minimum2)
        {
            //if ((i % key_len) != 0) && ((minimum - minimum2) >= 0.01)
            if ((i % key_len) != 0)
            {
            minimum = minimum2;
            key_len = i;
            }
        }
    }
    cout << "The length of the key is: " << key_len;
    cout << endl;
}

int main()
{
    //filtring the text, ecrypting and decrypting with the key
    cin.get(sample, 1000);
    filter_text(sample, plaintext, text_length);

    cout << "Your plaintext is:" << endl;
    get_text(plaintext, text_length);

    encryption();

    cout << "Your ciphertext is:" << endl;
    get_text(ciphertext, text_length);

    decryption();

    cout << "Your decrypted text, using the key= ";
    for (int i = 0; i < key_length; i++)
    {
        cout << key[i] << " ";
    }

    cout << "is: " << endl;
    get_text(decryptext, text_length);
    determine_key_length();
    for (int i = 3; i <= 26; i++)
    {
        cout << i<<" "<< average[i];
        cout << endl;
    }
    
    
    
}