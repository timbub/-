#include <stdio.h>
#include <math.h>
#include <TXLib.h>
enum number_roots {
    INFINITY_ROOTS = -1,
    ZERO_ROOTS,
    ONE_ROOTS,
    TWO_ROOTS
};

const double EPP = 1e-7;
const int END_TEST = 3;
const int windows_eof = 26;

enum number_roots solve_square(double a, double b, double c, double* root_1, double* root_2);
void input(double* a, double* b, double* c);
void output(int nRoots, double root_1, double root_2);
bool compare_doubles(double a, double b);
void skipline();
void RunTest(int num_test, double a, double b, double c, double x1exp, double x2exp, int nRootsexp);

int main() {
    RunTest(1, 1, 1, -6, -3, 2, 2);
    RunTest(2, 1,-4, 4, 2, 0, 1);
    RunTest(3, 2, -3, 1, 0.5, 1, 2);
    double a = NAN, b = NAN, c = NAN, root_1 = NAN, root_2 = NAN;
    input(&a, &b, &c);
    enum number_roots nRoots = solve_square(a, b, c, &root_1, &root_2);
    output(nRoots, root_1, root_2);
    return 0;
}

void input(double* a, double* b, double* c) {
    printf("Введите коэфиценты a,b,c уравнения вида a*x^2 + b*x + c\n");
    while (scanf("%lg %lg %lg", a, b, c)  < 3)
    {
        printf("Попробуйте еще раз\n");
        skipline();
    }
}

enum number_roots solve_square(double a, double b, double c, double* root_1, double* root_2)
{
    assert(root_1 != NULL);
    assert(root_2 != NULL);
    assert(root_1 != root_2);

    if (compare_doubles(a,0) == true)
    {
        if (compare_doubles(b,0) == false)
        {
            *root_1 = -c/b;
            return ONE_ROOTS;
        } else {
            if (compare_doubles(c,0) == true)
            {
                return INFINITY_ROOTS;
            } else {
                return ZERO_ROOTS;
            }
        }

    }
    else {
        double d = b * b - 4*a*c;
        if (compare_doubles(d,0) == true)
        {
            *root_1 = -b/(2*a);
            return ONE_ROOTS;
        }
        if (d > 0)
        {
            *root_1 = (-b + sqrt(d))/ (2*a);
            *root_2 = (-b - sqrt(d))/ (2*a);
            return TWO_ROOTS;
        }
        else
        {
            return ZERO_ROOTS;
        }
    }
}

void output(int nRoots, double root_1, double root_2){
    switch(nRoots) {
        case ZERO_ROOTS:
            printf("Корней нет");
            break;
        case ONE_ROOTS:
            printf("Корень уравнения %lg", root_1);
            break;
        case TWO_ROOTS:
            printf("Корни уравнения %lg и %lg", root_1, root_2);
            break;
        case INFINITY_ROOTS:
            printf("Корней бесконечно много");
            break;
        default:
            printf("Ошибка");
            break;

    }
}

bool compare_doubles(double a,double b) {
        if (fabs(a - b) < EPP) {
            return true;
        } else {
            return false;
        }
}
void skipline() {
    char c = getchar();
    while (c != '\n' && c != EOF && c != windows_eof)
    {
        c = getchar();
    }
}

void RunTest(int num_test, double a, double b, double c, double x1exp, double x2exp, int nRootsexp)
{
    double x1 = 0, x2 = 0;
    int nRoots = solve_square(a,b,c, &x1, &x2);
    if (nRoots != nRootsexp || x1 != max(x1exp, x2exp) ||  x2 != min(x2exp, x1exp))
    {
        printf("Ошибка теста %d: a = %lg, b = %lg, c = %lg, root_1 = %lg, root_2 = %lg, nRoots = %d\n Ожидаемые результаты: root_1 = %lg, root_2 = %lg, nRoots = %lg\n",num_test, a, b, c, x1, x2, nRoots, x1exp, x2exp, nRootsexp);
    } else
    {
        printf("Тест %d пройден\n", num_test);
    }
}
