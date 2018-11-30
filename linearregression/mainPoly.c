#include <string.h>
#include "polyfit.h"


const int ELEMENT_COUNT=11;
const int ORDER=3;

void print_equation(double *coefficients);

int main()
{
    double xA[]={0,1,2,3,4,5,6,7,8,9,10};
    double yA[]={1,6,17,34,57,86,121,162,209,262,321};
    double* x=xA;
    double* y=yA;
    double c[ORDER];
    double* coefficients=c;
    int result=polyfit(x,y,ELEMENT_COUNT,ORDER,coefficients);
    if (result==1)
    {
        printf("ERROR\n");
        return EXIT_FAILURE;
    }
    print_equation(coefficients);
    return 0;
}

void print_equation(double *coefficients)
{
    for (int i=0;i<ORDER;i++)
    {
        if (i!=ORDER-1)
            printf("%.2fx^%d + ",coefficients[ORDER-i-1],ORDER-i-1);
        else
            printf("%.2f\n",coefficients[ORDER-i-1]);
    }
}
