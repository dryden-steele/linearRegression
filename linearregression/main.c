
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#include"data.h"
#include"linearregression.h"

//--------------------------------------------------------
// FUNCTION PROTOTYPES
//--------------------------------------------------------
void printdata(double* independent, double* dependent, int size);

//--------------------------------------------------------
// FUNCTION main
//--------------------------------------------------------
int main(void)
{
    puts("-------------------------------------\n| code-in-c.com - Linear Regression |\n-------------------------------------\n");

    //months
    double independent[8];

    //temperatures
    double dependent[8];

    for(int dataset = 1; dataset <=3; dataset++)
    {
        if(populatedata(independent, dependent, dataset))
        {
            printf("Data Set %d\n-----------\n", dataset);

            printdata(independent, dependent, 8);

            lin_reg lr;

            linear_regression(independent, dependent, 8, &lr);

            printf("y = %gx + %g\n\n", lr.a, lr.b);
        }
    }

    return EXIT_SUCCESS;
}

//--------------------------------------------------------
// FUNCTION printdata
//--------------------------------------------------------
void printdata(double* independent, double* dependent, int size)
{
    for(int i = 0; i < size; i++)
    {
        printf("%3.0lf\t%3.0lf\n", independent[i], dependent[i]);
    }
}
