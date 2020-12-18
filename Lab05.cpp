
//+===================================================================
// File lab_5.cpp
// Вивчення  МП Intel х86
// Вариант 14
// Задание:  Эта программа делает умножение 
// и деление с помощью сдвигов
//
//	Сіденко Є. В. 2020
//-===================================================================

#include <stdio.h>
#include <iostream>

using namespace std;

unsigned int x, Z, Z_A;

int y, V, V_A;
    
int error = 0;
int main()
{
    for (;;)
    {
        Z = 0;
        Z_A = 0;
        V = 0;
        V_A = 0;
        // Y = x* 53 / 8 = (32x + 16x + 4x + x) / 8
        //Ввод целого безнакового числа
        printf("x :");
        scanf_s("%ui", &x); 
        //Ввод целого знакового числа
        printf("y :");
        scanf_s("%i", &y);
        Z = ( (x <<5) + (x << 4) + (x << 2) + (x<<1) ) >> 3;


        V = ((y << 5) + (y << 4) + (y << 2) + (y<<1)) >> 3;
        //беззнаковые числа
        __asm {
            mov     error,  0
            mov     edx,    x       //edx <= x
            mov     ebx,    edx     //ebx <= x
            mov     eax,    edx     //edx <= x

            shl     eax,    5       //32x
            jc      Error

            shl     ebx,    4       //16x
            jc      Error

            add     eax,    ebx     //32x+16x
            jc      Error

            add     eax,    edx     //32x+16x + x
            jc      Error

            shl     edx,    2       //4x
            jc      Error   

            add     eax,    edx     //32x+ 16x + 4x + x (eax)
            jc      Error

            shr     eax,    3       //(32x+ 16x + 4x + x)/8
            jc      Error

            jmp     End

            Error :
            inc error
            End :
            mov     Z_A,    eax     //eax => Z_A
        };
        if (error == 1)
        {
            printf("\t\tError Flag : unsigned integer \n");
        }
        else
        {
            printf("Unsigned hexadecimal number C++(Z)\t[%x]", Z);
            printf("\tUnsigned hexadecimal number Asm(Z_A) :\t[%x]\n", Z_A);
            printf("Unsigned decimal number  C++(Z):\t[%u]", Z);
            printf("\tUnsigned decimal number  Asm (Z_A):\t[%u]\n\n", Z_A);
        }
        //Знаковые числа
        __asm {
            mov     error,  0
            mov     edx, y       //edx <= x
            mov     ebx, edx     //ebx <= x
            mov     eax, edx     //edx <= x

            sal     eax, 5       //32x
            jc      Error2

            sal     ebx, 4       //16x
            jc      Error2

            add     eax, ebx     //32x+16x
            jc      Error2

            add     eax, edx     //32x+16x + x
            jc      Error2

            sal     edx, 2       //4x
            jc      Error2

            add     eax, edx     //32x+ 16x + 4x + x (eax)
            jc      Error2

            sar     eax, 3       //(32x+ 16x + 4x + x)/8
            jc      Error2

            jmp     End2

             Error2 :
             inc error
             End2 :
             mov     V_A, eax     //eax => Z_A
        };
        if (error == 1)
        {
            printf("\t\tError Flag : integer \n");
        }
        else
        {
            printf("Signed hexadecimal number C++(V) :\t[%x]", V);
            printf("\tSigned hexadecimal number Asm(V_A) :\t[%x]\n", V_A);
            printf("Signed decimal number  C++(V) :\t\t[%d]", V);
            printf("\tSigned decimal number Asm(V_A) :\t[%d]\n\n", V_A);
        }
    }

}
