//+===================================================================
// File lab_3.cpp
// Вивчення логічних команд МП Intel х86
// Вариант 13
//Задание:  Эта программа вычисляет условное арифметическое выражение
//
//            a/(b + 1) | a>b
//      x=    -2        | a=b
//            (a-b)/a   | a<b
//
//
//	Сіденко Є. В. 2020
//-===================================================================

#include <stdio.h>
#include <iostream>
#define var 14

int a, a1, b, b1, x, x_a, tmp;
int err, err_a;
int main()
{
    while (true)
    {
        //=============================== C ==================================\\

        printf("\n\tmade by Sidenko Y.V.");
        printf("\n\tEvaluate expression:");
        printf("\n\t\t { a/(b + 1)\t| a>b \t}");
        printf("\n\tx =\t < -2\t\t| a=b \t>");
        printf("\n\t\t { (a-b)/a\t| a<b \t}");
        printf("\n\twhere a=a/16, b=b/17\n");
        printf("\nInput integer value [a] and [b]: ");
        scanf_s("%li%li", &a, &b);

        a1 = a / (var + 2);
        b1 = b / (var + 3);

        err = 0;
        // a = b  x = -2
        if (a1 == b1)
            x = -2;
        else
            // (a>b)?  x = a/b + 1
            if (a1 > b1)
            {
                tmp = b1 + 1;
                if (tmp == 0)
                    err = 1;
                else
                    x = a1 / tmp;
            }
        // (a<b)? x = (a-b)/a
            else
            {
                if (a1 == 0)
                    err = 1;
                else
                    x = (a1 - b1) / a1;
            }
        //=============================== Asm ==================================\\

        // err_a=0; Нет ошибок
        __asm {
            mov err_a, 0
        }
        // Разделить исходные переменные на знаменатель VAR
        __asm {
        // b1=b/DENOM_A+3
            mov ebx, var+3
            mov eax, b
            cdq
            idiv ebx
            mov edi, eax // b1 -> edi
           // a1=a/DENOM_A+2
            mov ebx, var+2
            mov eax, a
            cdq
            idiv ebx // a1 -> eax
        }

        //eax - a1
        //edi - b1
        __asm {
            // Вычислить выражение
            // if (a1==b1)          
            cmp  eax,    edi           
            je   Equal          //a1 == b1
            jl   Less           //a1 < b1
             // x = a / (b + 1) | a>b
             Greater :          //a1 > b1
            test        edi,    edi           
            je          Error
            cdq
            idiv        edi
            inc         edi         
            jmp         Save
                //x = -2 | a=b
            Equal : 
            mov         eax, 2
            neg         eax                 
            jmp         Save
                //x = (a-b)/a | a<b
                Less :                
            test        eax,    eax
            je          Error
            sub         edi, eax
            cdq
            neg         edi
            xchg        eax, edi // edi > a, eax > a-b
            cdq
            idiv        edi

            Save :
            mov         x_a,     eax        
            jmp         End
                                    
            Error :                 
            inc         err_a
            End :
        }

        if (err)
            printf("***( C )*** Error: attempt to divide by 0\n");
        else
            printf("Result ( C ): %li\n", x);
        if (err_a)
            printf("***(Asm)*** Error: attempt to divide by 0\n");
        else
            printf("Reuslt (Asm): %li\n", x_a);

    }

}