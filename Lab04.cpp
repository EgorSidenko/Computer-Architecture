#include <iostream>
#include <iomanip>
#include <locale.h>
using namespace std;


/*
* 
* 31----+------+-----+-----+---+------0     
* | mod | reg1 | r_m | kop | w | reg2 |        
* +-----+------+-----+-----+---+------+
* |  4  |   6  |  12 |  4  | 1 |  5   |
* +-----+------+-----+-----+---+------+
* 
* Выходные данные:
* 3------0-----0
* | 0000 | mod |  mod
* +------+-----+
* 
* 9---------4-----0
* | 00 0000 |reg1 |  reg1
* +---------+-----+
* 
* 21---------------10----0
* | 0000 0000 0000 | r_m |  r_m
* +----------------+-----+
* 
* 25----22-----0
* | 0000 | kop |  kop
* +------+-----+
* 
* 26---26----0
* | 0  | w   |  w
* +----+-----+
* 
* 31-------27----0
* | 0 0000 | reg2|  reg2
* +--------+-----+
* 
*/

unsigned long value;
unsigned char mod, mod_a, reg1, reg1_a, kop, kop_a, w, w_a, reg2, reg2_a;
unsigned short r_m, r_m_a;

int main()
{
    cout << "\t\t31----+------+-----+-----+---+------0"     
        << "\n\t\t| mod | reg1 | r_m | kop | w | reg2 |"
        << "\n\t\t+-----+------+-----+-----+---+------+"
        << "\n\t\t|  4  |   6  |  12 |  4  | 1 |  5   |"
        << "\n\t\t+-----+------+-----+-----+---+------+" << endl;

    for (;;) {
        setlocale(LC_ALL, "Rus");
        printf("\n\tРаспаковать 32-битовое число Value");
        printf("\nПожалуйста, введите 8 16-ых цифр [ ");
        scanf_s("%x", &value);
        //Выделение памяти на C

        reg2 = value & 0x1f;
        w = (value >> 5) & 0x1;
        kop = (value >> 6) & 0xf;
        r_m = (value >> 10) & 0xfff;
        reg1 = (value >> 22) & 0x3f;
        mod = (value >> 27) & 0xf;
        __asm {
            mov eax, value
            // Выделение памяти для 4 битов (3-0) из value
            mov mod_a, al
            and mod_a, 0xf
            shr eax, 4
            // Выделение памяти для 6 битов (9 - 4) из value
            mov reg1_a, al
            and reg1_a, 0x3f
            shr eax, 6
            // Выделение памяти для 12 битов (21 - 10) из value
            mov r_m_a, ax
            and r_m_a, 0xfff
            shr eax, 12
            // Выделение памяти для 4 битов (25 - 22) из value
            mov kop_a, al
            and kop_a, 0xf
            shr eax, 4
            //Выделение памяти для 1 бита (27 - 26) из value
            mov w_a, al
            and w_a, 0x1
            shr eax, 1
            //Выделение памяти для 5 битов (31 - 28) из value
            mov reg2_a, al
            and reg2_a, 0x1f
        };

        cout << hex << "\tБитовая группа mod (C++): " << (unsigned int)mod << "\t Битовая группа mod (Asm): " << (int)mod_a
            << "\n\tБитовая группа reg1 (C++): " << (int)reg1 << "\t Битовая группа reg1 (Asm): " << (int)reg1_a
            << "\n\tБитовая группа r_m (C++): " << (int)r_m << "\t Битовая группа r_m (Asm): " << (int)r_m_a
            << "\n\tБитовая группа kop (C++): " << (int)kop << "\t Битовая группа kop (Asm): " << (int)kop_a
            << "\n\tБитовая группа w (C++): " << (int)w << "\t Битовая группа w (Asm): "        << (int)w_a
            << "\n\tБитовая группа reg2 (C++): " << (int)reg2 << "\t Битовая группа reg2 (Asm): " << (int)reg2
            << endl;
    }

}
