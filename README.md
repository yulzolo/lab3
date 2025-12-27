# lab3 
Терминал, вычисление интеграла 

#include <stdio.h>
#include <stdlib.h>

char _getch() {
    system("stty raw -echo");
    char c = getchar();
    system("stty -raw echo");
    return c;
}

void PrintMenu() {
    printf("\nМеню:\n");
    printf("1 - Ввести пределы интегрирования\n");
    printf("2 - Ввести шаг интегрирования\n");
    printf("3 - Расчитать интеграл по методу трапеции\n");
    printf("4 - Расчитать погрешность\n");
    printf("5 - Завершение работы\n");
    fflush(stdout);
}

double f(double x) {
    return x*x*x + 2*x*x - 2*x + 11;
}

double p(double x) {
    return x*x*x*x/4.0 + 2*x*x*x/3.0 - x*x + 11*x;
}

void PickMenu(double *a, double *b, double *step, int *kstep) {
    int pick = 0;

    while (pick != 5) {
        PrintMenu();
        printf("Выберите пункт меню: ");

        char ch = _getch();
        if (ch < '0' || ch > '5') {
            printf("\nНекорректный ввод: %c\n", ch);
            continue;
        }
        fflush(stdout);
        pick = ch - '0';
        printf("%d\n", pick);

        switch (pick) {
            case 1:
                printf("Ввод пределов интегрирования: ");
                if (scanf("%lf %lf", a, b) != 2) {
                    printf("Ошибка ввода!\n");
                    *a = *b = 0;
                    while (getchar() != '\n'); // очистка буфера
                    break;
                }
                if (*a > *b) {
                    printf("Пределы интегрирования заданы некорректно.\n");
                    *a = *b = 0;
                } else {
                    printf("Нижний предел: %lf, Верхний предел: %lf\n", *a, *b);
                }
                break;

            case 2:
                printf("Введите шаг интегрирования: ");
                if (scanf("%lf", step) != 1 || *step <= 0) {
                    printf("Шаг задан некорректно.\n");
                    *step = 0;
                    while (getchar() != '\n'); // очистка буфера
                    break;
                }
                if (*a != *b) {
                    *kstep = (int)((*b - *a) / *step);
                    if (*kstep <= 0) *kstep = 1; // защита от нуля
                }
                printf("Шаг: %lf, количество шагов: %d\n", *step, *kstep);
                break;

            case 3:
                if (*step <= 0 || *a == *b || *kstep <= 0) {
                    printf("Сначала задайте корректные пределы и шаг!\n");
                    break;
                }
                {
                    double fa = f(*a);
                    double fb = f(*b);
                    if (fa < 0) fa = -fa;
                    if (fb < 0) fb = -fb;

                    double sm = (fa + fb) / 2.0;
                    for (int i = 1; i < *kstep; i++) {
                        double fx = f(*a + i * (*step));
                        if (fx < 0) fx = -fx;
                        sm += fx;
                    }
                    double trap = sm * (*step);
                    printf("Площадь фигуры методом трапеций: %lf\n", trap);
                }
                break;

            case 4:
                if (*step <= 0 || *a == *b || *kstep <= 0) {
                    printf("Сначала задайте корректные пределы и шаг!\n");
                    break;
                }
                {
                    double sum = 0.0;
                    for (int i = 0; i <= *kstep; i++) {
                        double x = *a + i * (*step);
                        double fx = f(x);
                        if (fx < 0) fx = -fx;

                        if (i == 0 || i == *kstep)
                            sum += fx / 2.0;
                        else
                            sum += fx;
                    }

                    double trap = sum * (*step);
                    double exact = p(*b) - p(*a);
                    if (exact < 0) exact = -exact;

                    double error = exact - trap;
                    if (error < 0) error = -error;

                    printf("Точная площадь: %lf\n", exact);
                    printf("Погрешность: %lf\n", error);
                }
                break;

            case 5:
                printf("Завершение работы.\n");
                break;
        }
    }
}

int main() {
    double a = 0, b = 0, step = 0;
    int kstep = 0;

    printf("Функция: x^3 + 2x^2 - 2x + 11\n");
    printf("Корень: -3.5\n");

    PickMenu(&a, &b, &step, &kstep);
    return 0;
}
