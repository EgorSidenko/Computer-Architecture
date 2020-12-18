//+===================================================================
// File lab_2.cpp
// Линейная логическая программа
// Вариант 13
// Эта программа вычисляет три логические функции
//
//	F1 (x3, x2, x1, x0) = 0 2 4 6 8 10 12 
//	F2 (x3, x2, x1, x0) = 1 2 3 4 5 6
//	F3 (x3, x2, x1, x0) = 0 2 4 6 8 
//
//	Сіденко Є. В. 2020
//-===================================================================

#include <iostream>
#include <stdio.h>
using namespace std;
int count;
bool x3, x2, x1, x0, f1, f2, f3, F1_a, f2_a, f3_a;
int main() {
	int counter = 0;
	printf("\n\t\t Sidenko Y. V., 2020");
	printf("\n\tF1 (x3, x2, x1, x0) = 0 2 4 6 8 10 12");
	printf("\n\tF2 (x3, x2, x1, x0) = 1 2 3 4 5 6");
	printf("\n\tF3 (x3, x2, x1, x0) = 0 2 4 6 8");
	for (;;) {
		printf("\nTest number = [%d]", counter);
		//Ввод данных (х0, х1, х2, х3)
		cout << "\n\t\nInput boolen varieablies x3, x2, x1, x0\n";
		cout << "x0\t";		cin >> x0;
		cout << "x1\t";		cin >> x1;
		cout << "x2\t";		cin >> x2;
		cout << "x3\t";		cin >> x3;
		//Вычесление на С
		f1 = !(x0 || (x3 && x2 && x1));
		f2 = !x3 && ((x2 ^ x1) || (x1 ^ x0));
		f3 = !x0 && (!(x3 && (x2 || x1)));
		//Вычесление на ассемблере
		//f1 = !(x0 || (x3 && x2 && x1))
		__asm {
		mov		ah,		x3
		and		ah,		x2
		and		ah,		x1
		or		ah,		x0	
		not		ah
		and		ah,		1
		mov		F1_a,	ah
		};
		//f2  !x3 && ((x2 ^ x1) || (x1 ^ x0))
		__asm {
		mov		al,		x1
		xor		al,		x0
		mov		ah,		x2
		xor		ah,		x1
		or		al,		ah
		mov		ah,		x3
		not		ah
		and		al,		ah
		mov		f2_a,	al
		};
		//f3 = !x0 && (!(x3 && (x2 || x1)))
		__asm {
		mov		al,		x2
		or		al,		x1
		and		al,		x3
		not		al
		mov		ah,		x0
		not		ah
		and		al,		1
		and		al,		ah
		mov		f3_a,	al
		};
		
		//Вывод результата на С и на ассемблере
		printf("\n\tF1 = %s - C code \t", f1 ? "true" : "false");
		printf("F1 = %s - Asm code", F1_a ? "true" : "false");

		printf("\n\tF2 = %s - C code\t", f2 ? "true" : "false");
		printf("F2 = %s - Asm code", f2_a ? "true" : "false");

		printf("\n\tF3 = %s - C code\t", f3 ? "true" : "false");
		printf("F3 = %s - Asm code", f3_a ? "true" : "false");
		counter++;
	}
}
