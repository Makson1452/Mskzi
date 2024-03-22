#include <iostream>
#include <stdio.h>
#include <fstream>
using namespace std;

int main()
{
    int short rlz1 = 1023;  // Начальное состояние РЛЗ1
    int short bit_gamma = 0;          // Символ выходной последовательности такте
    int short buffer = 0;             // Переменная для переноса числа в другую ячейку массива
    long long int rlz2[2] = { 13523568565465,54266675758343421 };   //Начальное состояние РЛЗ2
    long long int mask = 0;
    long long int data = 0;
    long long int gamma = 0;              // Выходная последовательность бит
    char Name[16] = {};
    char name[16] = {};
    cout << "Enter the ciphertext file name ";
    cin >> name;
    cout << "Enter file with open text ";
    cin >> Name;
    ofstream out(name, ios::binary);
    ifstream in(Name, ios::binary);
    while (in.read((char*)&data, sizeof(long long int))) {
        for (int i = 0; i < 64; i++) {
            gamma = gamma << 1;
            bit_gamma = ((((rlz1 >> 10) ^ (rlz1 >> 7)) & 0x1) ^ (((rlz2[0] >> 97) ^ (rlz2[0] >> 91)) & 0x1));
            gamma = gamma + bit_gamma;
            rlz1 = rlz1 << 1;
            rlz1 = rlz1 + (((rlz1 >> 10) ^ (rlz1 >> 7)) & 0x1);   // Запись бита обратной связи
            buffer = (rlz2[1] >> 63) & 0x1;
            rlz2[0] = rlz2[0] << 1;
            rlz2[1] = rlz2[1] << 1;
            rlz2[0] = rlz2[0] + buffer;
            rlz2[1] = rlz2[1] + (((rlz2[0] >> 97) ^ (rlz2[0] >> 91)) & 0x1);   // Запись бита обратной связи
        }
        mask = data ^ gamma;
        out.write((char*)&mask, sizeof(long long int));
    }
    in.close();
    out.close();
    return 0;
}
