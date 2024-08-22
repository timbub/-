#include <stdio.h>
#include <math.h>
#include <TXLib.h>
enum number_roots {
    INFINITY_ROOTS = -1,
    ZERO_ROOTS,
    ONE_ROOTS,
    TWO_ROOTS
};

struct Test_Data
{
    int num_test;
    double a,b,c;
    double x1exp;
    double x2exp;
    int nRootsexp;
};

struct base_numbers
{

    double a,b,c;
    double root_1;
    double root_2;
    int nRoots;
};

const double EPP = 1e-7;
const int END_TEST = 3;
const int windows_eof = 26;

enum number_roots solve_square(double a, double b, double c, double* root_1, double* root_2);
void input(double* a, double* b, double* c);
void output(int nRoots, double root_1, double root_2);
bool compare_doubles(double a, double b);
void skipline();
void RunTest(struct Test_Data test);
double maximum(double a, double b);
double minimum(double a, double b) ;

int main() {
    struct Test_Data test1 = {.num_test = 1, .a = 1, .b = 1,  .c = -6, .x1exp = -3,  .x2exp = 2, .nRootsexp = 2};
    struct Test_Data test2 = {.num_test = 2, .a = 1, .b = -4, .c = 4,  .x1exp = 2,   .x2exp = 2, .nRootsexp = 1};
    struct Test_Data test3 = {.num_test = 3, .a = 2, .b = -3, .c = 1,  .x1exp = 0.5, .x2exp = 1, .nRootsexp = 2};
    RunTest(test1);
    RunTest(test2);
    RunTest(test3);
    struct base_numbers numbers = {.a = NAN, .b = NAN, .c = NAN, .root_1 = NAN, .root_2 = NAN, .nRoots = NAN} ;
    double a = NAN, b = NAN, c = NAN, root_1 = NAN, root_2 = NAN; // TODO: add structure
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
            *root_2 = -c/b;
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
            *root_2 = -b/(2*a);
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
    int c = getchar();
    while (c != '\n' && c != EOF && c != windows_eof)
    {
        c = getchar();
    }
}

void RunTest(struct Test_Data test)
{
    double x1 = NAN, x2 = NAN;//test->a (*test).a mass[2] == *(mass+2)
    int nRoots = solve_square(test.a,test.b,test.c, &x1, &x2); //
    if (nRoots != test.nRootsexp || x1 != maximum(test.x1exp, test.x2exp) || x2 != minimum(test.x1exp, test.x2exp))
    {
        if (test.nRootsexp == 2 )
        {
            printf("Ошибка теста %d: a = %lg, b = %lg, c = %lg, root_1 = %lg, root_2 = %lg, nRoots = %d\n"
                "Ожидаемые результаты: root_1 = %lg, root_2 = %lg, nRoots = %d\n",test.num_test, test.a, test.b, test.c, x1, x2, nRoots, test.x1exp, test.x2exp, test.nRootsexp);
        }
        else if (test.nRootsexp == 1 || x2 != x1)
        {
                printf("Ошибка теста %d: a = %lg, b = %lg, c = %lg, root_1 = %lg, root_2 = %lg, nRoots = %d\n"
                "Ожидаемые результаты: root_1 = %lg, root_2 = %lg nRoots = %d\n",test.num_test, test.a, test.b, test.c, x1, x2, nRoots, test.x1exp, test.x2exp, test.nRootsexp);
        }
        else if (test.nRootsexp == 0)
        {
                 printf("Ошибка теста %d: a = %lg, b = %lg, c = %lg, root_1 = %lg, root_2 = %lg, nRoots = %d\n"
                "Ожидаемые результаты: Нет решений, nRoots = %d\n",test.num_test, test.a, test.b, test.c, x1, x2, nRoots, test.nRootsexp);
        }

    }
    else
    {
        printf("Тест %d пройден\n", test.num_test);
    }
}

double maximum(double a, double b)
{
    if (a > b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

double minimum(double a, double b)
{
    if (a < b)
    {
        return a;
    } else
        return b;
}
