#include <stdio.h>
#include <locale.h>
#define DENOM 14
long int a, b, c, a1, b1, c1, left, right, left_a, right_a;
int err_a;
//(a-b-c)**2 = a 2 +b 2 +c 2 -2ab-2ac+2bc
int main(void) {
	for (;;)
	{
		printf("---------------------\nInput a, b , c: \n");
		scanf_s("%li%li%li", &a, &b, &c);
		printf("\n");
		//printf(" a:%li,b:%li,c:%li\n", a,b,c);
		//С подсчёт левой ч.
		a1 = a / (DENOM + 2);
		b1 = b / (DENOM + 3);
		c1 = c / (DENOM + 4);
		left = (a1 - b1 - c1) * (a1 - b1 - c1);
		//С подсчёт правой ч.
		right = a1 * a1 + b1 * b1 + c1 * c1 - 2 * a1 * b1 - 2 * a1 * c1 + 2 * b1 * c1;
		//assabler
		__asm {mov err_a, 0};
		// a1 = a/(DENOM+2);
		__asm {
			mov ebx, DENOM + 2
			mov eax, a
			cdq
			idiv ebx
			mov esi, eax
		};
		// b1 = b/(DENOM+3);
		__asm {
			mov ebx, DENOM + 3
			mov eax, b
			cdq
			idiv ebx
			mov edi, eax
		};
		// c1 = c/(DENOM+4);
		__asm {
			mov ebx, DENOM + 4
			mov eax, c
			cdq
			idiv ebx
			mov ecx, eax
		};
		// left = (a1 - b1 - c1) * (a1 - b1 - c1);
		__asm {
			mov eax, esi //esi = a1
			sub eax, edi //edi = b1
			sub eax, ecx //ecx = c1
			imul eax, eax //(a1 - b1 - c1) * (a1 - b1 - c1)
			jo error
			mov left_a, eax
		};
		// right = a1 * a1 + b1 * b1 + c1 * c1 - 2 * a1 * b1 - 2 * a1 * c1 + 2 * b1 * c1;
		__asm {
			mov eax, esi // a1>eax
			imul eax, eax // a1*a1 = eax
			jo error
			mov edx, edi // b1>edx
			imul edx, edx // b1*b1=edx
			jo error
			add eax, edx // a1*a1+b1*b1 = eax
			jo error
			mov edx, ecx // c1>edx
			imul edx, edx // c1*c1>edx
			jo error
			add eax, edx // a1*a1+b1*b1+c1*c1 = eax
			jo error
			mov ebx, eax // ebx = a1*a1+b1*b1+c1*c1
			mov eax, esi // a1>eax
			imul eax, -2 // a1*(-2) = eax
			jo error
			imul eax, edi // a1*(-2) * b1 = eax
			jo error
			add eax, ebx // a1*a1+b1*b1+c1*c1 + a1*(-2) * b1 = eax
			jo error
			mov ebx, eax // ebx = a1*a1+b1*b1+c1*c1 + a1*(-2) * b1
			mov eax, esi // a1>eax
			imul eax, -2 // a1*(-2) = eax
			jo error
			imul eax, ecx // a1*(-2) * c1 = eax
			jo error
			add eax, ebx // a1*a1+b1*b1+c1*c1 + a1*(-2) * b1 + a1*(-2) * c1= eax
			jo error
			mov ebx, eax // ebx = a1*a1+b1*b1+c1*c1 + a1*(-2) * b1 + a1*(-2) * c1
			mov eax, edi // b1>eax
			imul eax, 2 // b1*2 = eax
			jo error
			imul eax, ecx // b1*2 * c1 = eax
			jo error
			add eax, ebx
			jo error
			mov right_a, eax// eax > right_a
			jmp end
			error :
			mov err_a, 1
				end :
		};
		if (err_a == 1) {
			printf("|OverFlow|\n\n");
			printf("%-10li Asm - code left\n", left_a);
			printf("%-10li C code left\n", left);
			printf("%-10li Asm - code right\n", right_a);
			printf("%-10li C code right\n\n", right);
		}
		else
		{
			printf("%-10li Asm - code left\n", left_a);
			printf("%-10li C code left\n", left);
			printf("%-10li Asm - code right\n", right_a);
			printf("%-10li C code right\n\n", right);
		}
	}
}