#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define PI 3.14159265358979323846264

/*
* This method calculate the PI in parallel then print the value of 'mypi', 'mypi -PI' and 'execution time' and return the
* 'execution time'. For calculating PI in parallel I used #pragma command as well as done the reduction on the shared variables.
*/
double calculatePI (int i, int iterations, double ni, double m, double mypi, int threads) 
{
    double start_time = omp_get_wtime();
    #pragma omp parallel for num_threads(threads), reduction(+:ni), reduction(+:mypi)
        for (i = 0; i < iterations; i++)
        {
            ni = ((double)i + 0.5) * m; 
            mypi += 4.0 / (1.0 + ni * ni); 
        }
    
    double end_time =  omp_get_wtime() - start_time;
    
    mypi *= m; 
    printf(" MyPI = %.20lf\n", mypi); 
    printf("MyPI - PI = %.20lf\n", (mypi - PI));
    printf("Execution time with %i threads and %i iteration = %.2lf\n\n", threads, iterations, end_time);
    return end_time;
}

/*
* This method takes an array of execution times and then calculate and print the average time out of that.
*/
void calculateAverage (double *arr, int length) 
{
    double total = 0.0;
    printf("------------------------------------------------------------------\nAll execution times = {");
    for (int i = 0; i < length; i++)
    {
        total += arr[i];
        i == length - 1 ? printf("%.2lf}\n", arr[i]) : printf("%.2lf, ", arr[i]);
    }
    printf("Average time = %.2lf\n------------------------------------------------------------------\n\n", (total/(double)length));
}

/*
* This method simply calculate the PI with various threads and iterations provided in 'iteration and threads array'. Currently,
* this method runs 5 times for each thread with each iteration. 
*/
int main (int argc, char *argv[])
{
    double m, ni, mypi = 0.0; 
    int i; 
    int iterations[]=  {24000000, 48000000, 96000000}, threads[] = {1, 6, 12, 24, 48};
    double execution_times[5];

    for(int j = 0; j < 5; j++) 
    {    
        for(int k = 0; k < 3; k++)
        {
            m = 1.0 / (double)iterations[k];

            for(int l = 0; l < 5; l++)
            {
                execution_times[l] = calculatePI(i, iterations[k], ni, m, mypi, threads[j]);
            }
            calculateAverage(execution_times, 5);
        }
    }
}