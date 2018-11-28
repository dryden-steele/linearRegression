
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




    //one of these for loops for each month    
    for(int dataset = 1; dataset <=5; dataset++)
    {
        if(populatedataJan(independent, dependent, dataset))//populateDataJan
        {
            printf("Data Set %d\n-----------\n", dataset);

            printdata(independent, dependent, 8);

            lin_reg lr;

            linear_regression(independent, dependent, 8, &lr);

            printf("y = %gx + %g\n\n", lr.a, lr.b);
        }
    }

for(int dataset = 1; dataset <=5; dataset++)
    {
        if(populatedataFeb(independent, dependent, dataset))//populateDataFeb
        {
            printf("Data Set %d\n-----------\n", dataset);

            printdata(independent, dependent, 8);

            lin_reg lr;

            linear_regression(independent, dependent, 8, &lr);

            printf("y = %gx + %g\n\n", lr.a, lr.b);
        }
    }

for(int dataset = 1; dataset <=5; dataset++)
    {
        if(populatedataMar(independent, dependent, dataset))//populateDataMar
        {
            printf("Data Set %d\n-----------\n", dataset);

            printdata(independent, dependent, 8);

            lin_reg lr;

            linear_regression(independent, dependent, 8, &lr);

            printf("y = %gx + %g\n\n", lr.a, lr.b);
        }
    }
for(int dataset = 1; dataset <=5; dataset++)
    {
        if(populatedataApr(independent, dependent, dataset))//populateDataApr
        {
            printf("Data Set %d\n-----------\n", dataset);

            printdata(independent, dependent, 8);

            lin_reg lr;

            linear_regression(independent, dependent, 8, &lr);

            printf("y = %gx + %g\n\n", lr.a, lr.b);
        }
    }
for(int dataset = 1; dataset <=5; dataset++)
    {
        if(populatedataMay(independent, dependent, dataset))//populateDataMay
        {
            printf("Data Set %d\n-----------\n", dataset);

            printdata(independent, dependent, 8);

            lin_reg lr;

            linear_regression(independent, dependent, 8, &lr);

            printf("y = %gx + %g\n\n", lr.a, lr.b);
        }
    }
for(int dataset = 1; dataset <=5; dataset++)
    {
        if(populatedataJun(independent, dependent, dataset))//populateDataJun
        {
            printf("Data Set %d\n-----------\n", dataset);

            printdata(independent, dependent, 8);

            lin_reg lr;

            linear_regression(independent, dependent, 8, &lr);

            printf("y = %gx + %g\n\n", lr.a, lr.b);
        }
    }
for(int dataset = 1; dataset <=5; dataset++)
    {
        if(populatedataJul(independent, dependent, dataset))//populateDataJul
        {
            printf("Data Set %d\n-----------\n", dataset);

            printdata(independent, dependent, 8);

            lin_reg lr;

            linear_regression(independent, dependent, 8, &lr);

            printf("y = %gx + %g\n\n", lr.a, lr.b);
        }
    }
for(int dataset = 1; dataset <=5; dataset++)
    {
        if(populatedataAug(independent, dependent, dataset))//populateDataAug
        {
            printf("Data Set %d\n-----------\n", dataset);

            printdata(independent, dependent, 8);

            lin_reg lr;

            linear_regression(independent, dependent, 8, &lr);

            printf("y = %gx + %g\n\n", lr.a, lr.b);
        }
    }
for(int dataset = 1; dataset <=5; dataset++)
    {
        if(populatedataOct(independent, dependent, dataset))//populateDataOct
        {
            printf("Data Set %d\n-----------\n", dataset);

            printdata(independent, dependent, 8);

            lin_reg lr;

            linear_regression(independent, dependent, 8, &lr);

            printf("y = %gx + %g\n\n", lr.a, lr.b);
        }
    }

for(int dataset = 1; dataset <=5; dataset++)
    {
        if(populatedataSept(independent, dependent, dataset))//populateDataSept
        {
            printf("Data Set %d\n-----------\n", dataset);

            printdata(independent, dependent, 8);

            lin_reg lr;

            linear_regression(independent, dependent, 8, &lr);

            printf("y = %gx + %g\n\n", lr.a, lr.b);
        }
    }
for(int dataset = 1; dataset <=5; dataset++)
    {
        if(populatedataNov(independent, dependent, dataset))//populateDataNov
        {
            printf("Data Set %d\n-----------\n", dataset);

            printdata(independent, dependent, 8);

            lin_reg lr;

            linear_regression(independent, dependent, 8, &lr);

            printf("y = %gx + %g\n\n", lr.a, lr.b);
        }
    }

for(int dataset = 1; dataset <=5; dataset++)
    {
        if(populatedataDec(independent, dependent, dataset))//populateDataDec
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
