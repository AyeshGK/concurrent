#include <stdio.h>
#include <omp.h>

int main()
{
    int thread_count = 4;
    int sum = 0; // shared variable

    omp_set_num_threads(thread_count);

/*
The #pragma omp parallel for reduction(+ : sum) directive is an OpenMP construct that tells
the compiler to parallelize the following for loop. The parallel for clause means that the iterations
of the loop will be divided among the available threads. The reduction(+ : sum) clause is used to safely
accumulate a sum from each thread into the variable sum.
The + indicates that the operation is addition, and sum is the variable that holds the result.

(operator: variable) is the syntax for reduction clause.

operators that can be use here
+ - * & ^ | && || min max

*/
#pragma omp parallel for reduction(+ : sum)
    for (int i = 0; i < 100; i++)
    {
        sum += i;
    }

    printf("sum = %d\n", sum);
    return 0;
}