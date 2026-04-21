#include <stdio.h>
#include <stdlib.h>

void PrintMenu() {
    printf("\nМеню:\n");
    printf("1 - Ввести пределы интегрирования\n");
    printf("2 - Ввести шаг интегрирования\n");
    printf("3 - Рассчитать интеграл по методу трапеций\n");
    printf("4 - Рассчитать среднюю абсолютную ошибку (MAE)\n");
    printf("5 - Завершение работы\n");
    fflush(stdout);
}

// Функция, которую интегрируем
double f(double x) {
    return x*x*x + 2*x*x - 2*x + 11;
}

// Первообразная для точного вычисления интеграла
double p(double x) {
    return x*x*x*x/4.0 + 2*x*x*x/3.0 - x*x + 11*x;
}

void PickMenu(double *a, double *b, double *step, int *kstep) {
    int pick = 0;

    PrintMenu();

    while (pick != 5) {
        printf("\nВыберите пункт меню: ");
        fflush(stdout);
        if (scanf("%d", &pick) != 1) {
            printf("Некорректный ввод.\n");
            int c; while ((c = getchar()) != '\n' && c != EOF) {} // очистка буфера
            continue;
        }

        switch (pick) {
            case 1:
                printf("Введите пределы интегрирования (a b): ");
                if (scanf("%lf %lf", a, b) != 2) {
                    printf("Ошибка ввода!\n");
                    *a = *b = 0;
                    int c; while ((c = getchar()) != '\n' && c != EOF) {}
                } else if (*a > *b) {
                    printf("Пределы заданы некорректно.\n");
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
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF) {}
                }
                else if (*a != *b) {
                    *kstep = (int)((*b - *a)/(*step));
                    if (*kstep <= 0) *kstep = 1;
                    printf("Шаг: %lf, количество шагов: %d\n", *step, *kstep);
                }
                break;

            case 3:
                if (*step <= 0 || *a == *b || *kstep <= 0) {
                    printf("Сначала задайте корректные пределы и шаг!\n");
                    break;
                }
                double trap = 0.0;
                for (int i = 0; i < *kstep; i++) {

                    double x1 = *a + i * (*step);
                    double x2 = *a + (i + 1) * (*step);
                    double y1 = f(x1);
                    double y2 = f(x2);
                    trap += (y1 + y2) / 2.0 * (*step);
                }
                printf("Площадь фигуры методом трапеций: %lf\n", trap);
                break;

            case 4:
                if (*step <= 0 || *a == *b || *kstep <= 0) {
                    printf("Сначала задайте корректные пределы и шаг!\n");
                    break;
                }
                double mae_sum = 0.0;
                for (int i = 0; i < *kstep; i++) {
                    double x1 = *a + i * (*step);
                    double x2 = *a + (i + 1) * (*step);

                    double exact = p(x2) - p(x1); // точная площадь на маленьком интервале
                    double approx = (f(x1) + f(x2)) / 2.0 * (*step); // приближение методом трапеций

                    double diff = exact - approx; //разница между точным и приближенным значение функции
                    if (diff < 0) {
                        diff = -diff;// модуль ошибки
                    }
                    mae_sum += diff;
                }
                double mae = mae_sum / (*kstep); // средняя абсолютная ошибка
                printf("Средняя абсолютная ошибка (MAE): %lf\n", mae);
                break;

            case 5:
                printf("Завершение работы.\n");
                break;

            default:
                printf("Некорректный выбор. Попробуйте снова.\n");
                break;
        }
    }
}

int main() {
    double a = 0, b = 0, step = 0;
    int kstep = 0;

    printf("Функция: 1*x^3 + 2*x^2 - 2*x + 11\n");
    PickMenu(&a, &b, &step, &kstep);

    return 0;
}