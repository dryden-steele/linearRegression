#include <math.h>
#include "polyfit.h"

// Number of points
// Will probably not be a constant (considering the days in months vary)
// Just made it const for the sake of the dummy data
const int ELEMENT_COUNT=11;

// Order of polynomial; ie. highest degree of x
// Will probably tweak this somehow to get more accurate without destrying our efficency
const int ORDER=3;

// Prototype declarations boi
void print_equation(double *coefficients);
double predictTemp(double* coefficients,double f);

int main()
{
    // Will need to change how we get data, this is just dummy data ya dummy
    double xA[]={0,1,2,3,4,5,6,7,8,9,10};
    double yA[]={1,6,17,34,57,86,121,162,209,262,321};
    double* x=xA;
    double* y=yA;


    // Stores the coefficients;  coefficients[5]x^5/coefficients[4]x^4/....
    double c[ORDER];
    double* coefficients=c;
    
    // Takes in two arrays for points, the # of elements, and the order and stores it in the coefficients pointer
    // return 0 -> we good
    // return -1 -> no good
    int result=polyfit(x,y,ELEMENT_COUNT,ORDER,coefficients);
    if (result==-1)
    {
        printf("OwO whoopsie\n");
        return EXIT_FAILURE;
    }

    print_equation(coefficients);
    // args - coefficients array and the X value it will use
    // X value will be the "day" we are predicting for
    // Will most likely need to add another arg for month
    double prediction = predictTemp(coefficients,2);

    printf("%f\n",prediction);

    return 0;
}

// Calculates 'y' for a given 'x'
// Returns the 'y' value which would be the prediction
// Will need to change this up soon to accept a month as well and then pick from the correct month
// ^ this will require coefficients to also change
double predictTemp(double *coefficients,double x_point)
{
    double y_point=0;
    for (int i=0;i<ORDER;i++)
    {
        double tmp;
        tmp=coefficients[ORDER-i-1]*pow(x_point,ORDER-i-1);
        y_point+=tmp;
    }
    return y_point;
}

// Prints out the polynomial in human readable form
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
