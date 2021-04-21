#define _CRT_SECURE_NO_WARNINGS 
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    system("chcp 1251");
    system("cls");
    printf(" Введите натуральное число N: ");
    int n;
    scanf_s("%d", &n);
    isFalse(n);
    printf("A = %d", n);
    getchar(); getchar();
    return 0;

}

void isFalse(int n) {
    if (n > 0) {
        if (n % 1 == 0) {
            printf(" Число является натуральным: ");
            printf(" num = %d", n);
        }
    }

}
