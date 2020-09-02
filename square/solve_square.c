#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>

#define SOLVE_EQUATION_INF -1
#define MAXTRIES_OF_INPUT 100
#define EPSILON 1e-8

double* Input_coeffs(const char text[],int number_of_coeffs);
//--------------------------------------------------
//! input double values
//!
//! @param [in] text[] -explanation for user
//! @param [in] number_of_coeffs - how much double values program should read
//!
//! @return adress to array of double values
//!
//! @note if you try to enter more then MAXTRIES_OF_INPUT program will break
//--------------------------------------------------

int Solve_Square(double* coeffs,double* roots);
//--------------------------------------------------
//! Solves square equation ax^2 + bx + c = 0
//!
//! @param [in]  coeffs- adress to the coefficients array
//! @param [out] roots- adress to the roots array
//!
//! @return Number of roots
//--------------------------------------------------

int Solve_lineal(double* coeffs,double* roots);
//--------------------------------------------------
//! Solves linear equation bx + c = 0
//!
//! @param [in]  coeffs- adress to the coefficients array
//! @param [out] roots-adress to the roots array
//!
//! @return Number of roots
//--------------------------------------------------

void clear_stdin();
//--------------------------------------------------
//! Clear stdin
//--------------------------------------------------

int Doubles_Compare(double a, double b);
//--------------------------------------------------
//! Compare two double numbers
//!
//! @param [in] a a-first double
//! @param [in] b b-second double
//!
//! @return 1, if a > b;
//!        -1, if a < b;
//!         0, if a == b;
//--------------------------------------------------

int main()
{
     printf("# scuare equation solver\n"
           "# (c) Ivakin, 2019\n");


     double* roots = (double*)calloc(2, sizeof(double));
     double* coeffs = Input_coeffs("# enter a, b, c: ",3);

     int Number_of_solutions = Solve_Square(coeffs,roots);

     switch(Number_of_solutions)
    {
        case 0: printf("No solutions");
                break;

        case 1: printf("x = %lg\n",roots[0]);
                break;

        case 2: printf("x = %lg, x = %lg", roots[0], roots[1]);
                break;

        case SOLVE_EQUATION_INF: printf("Any numbers");
                break;

        default : printf("ERROR: Number_of_solutions = %d", Number_of_solutions);

    }

}

double* Input_coeffs(const char text[],int number_of_coeffs)
{
    double* coeffs = (double*)calloc(number_of_coeffs, sizeof(double));

    assert(text != NULL);
    assert(number_of_coeffs > 0);
    assert(number_of_coeffs <= MAXTRIES_OF_INPUT);

    printf("%s",text);

    int correct_input = 0;
    int tries = 0;
    while (correct_input < number_of_coeffs)
    {
        if(scanf("%lg",coeffs + correct_input) == 1)
        {
           correct_input += 1;
        }
        else
        {
           printf("UNCORRECT INPUT, TRY AGAIN\n");
           clear_stdin();

           tries += 1;
        }

        if(tries > MAXTRIES_OF_INPUT)
        {
            printf("ERROR: SOMETHING GOES WRONG WITH INPUT");
            exit(1);
        }
    }
    return coeffs;
}

int Solve_Square(double* coeffs,double* roots)
{
    assert(coeffs != NULL);
    assert(roots != NULL);

    assert(isfinite(coeffs[0]));
    assert(isfinite(coeffs[0]));
    assert(isfinite(coeffs[2]));

    double a = coeffs[0];
    double b = coeffs[1];
    double c = coeffs[2];

    if (Doubles_Compare(a,0) == 0)
        return Solve_lineal(coeffs + 1, roots);

    double D = b * b - 4 * a * c;

    if (Doubles_Compare(D,0) == 1)
    {
        double first_solution  = (-b + sqrt(D)) / (2 * a);
        double second_solution = (-b - sqrt(D)) / (2 * a);

        roots[0] = first_solution;
        roots[1] = second_solution;

        return 2;
    }

    if (Doubles_Compare(D,0) == 0)
    {
        double first_solution = (-b) / (2 * a);

        roots[0] = first_solution;
        roots[1] = first_solution;

        return 1;
    }

    if (Doubles_Compare(D,0) == -1)
        return 0;

}

int Solve_lineal(double* coeffs,double* roots)
{
    assert(coeffs != NULL);
    assert(roots != NULL);

    assert(isfinite(coeffs[0]));
    assert(isfinite(coeffs[1]));

    double b = coeffs[0];
    double c = coeffs[1];

    if (Doubles_Compare(b,0) == 0)
        return (Doubles_Compare(c,0) == 0) ? SOLVE_EQUATION_INF : 0;

    else
    {
         double solution = (- c / b);

        roots[0] = solution;

        return 1;
    }
}

void clear_stdin()
{
    while (getchar() != '\n');
}

int Doubles_Compare(double a, double b)
{

   assert(isfinite(a));
   assert(isfinite(b));

   if (a - b > EPSILON) return 1;
   if (b - a > EPSILON) return -1;
   else return 0;
}


void test1()
{
   double coeff[] = {1, -5, 4};
   double expected[] = {1, 4};
   double actual[2];
   Solve_Square(coeff, actual);

   if ((actual[0] != expected[0]) || (actual[1] != expected[1]))
       printf("test 1 failed");
}

void test2()
{
   double coeff[] = {0, -4, 4};
   double expected[] = {1};
   double actual[1];
   Solve_Square(coeff, actual);

   if (actual[0] != expected[0])
       printf("test 1 failed");
}


