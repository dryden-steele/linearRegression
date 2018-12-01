#include <stdio.h>
#include <string.h>
#include <math.h>
#include "polyfit.h"
#include "retrievedata.h"
// Get length of array, does not work if x is a pointer grrrrrr
#define NUM_OF(x) (sizeof(x)/sizeof(*x))

// Number of points
// Will probably not be a constant (considering the days in months vary)
// Just made it const for the sake of the dummy data
//const int ELEMENT_COUNT=11;

// Order of polynomial; ie. highest degree of x
// Will probably tweak this somehow to get more accurate without destrying our efficency
const int ORDER=50;

// Prototype declarations boi
void print_equation(double *coefficients);
double predictTemp(double* coefficients,double f);

int main()
{
    fflush(stdout);
    struct weather_data* a=get_data_array("2015.csv",2290);
    printf("%s",a[0].name);
    int temp_max=0;
    int temp_min=0;
    for (int i=0;i<2290;i++)
    {

        if (strcmp(a[i].name,"TMAX") == 0)
            temp_max++;
        else if (strcmp(a[i].name,"TMIN") == 0)
            temp_min++;
    }

    double* t_x = malloc(sizeof(int) * (temp_max + temp_min));
    double* t_y = malloc(sizeof(int) * (temp_max + temp_min));

    int count_max = 0;
    int count_min = 0;
    int count_x = 0;
    int i=0;
    for (i=0;i<2290;i++)
    {
    
        if (strcmp(a[i].name,"TMAX") == 0)
        {
            t_x[count_x] = (double)count_max;
            t_y[count_x] = (double)a[i].value;
            count_max++;
            count_x++;
        }
        else if (strcmp(a[i].name,"TMIN") == 0)
        {
            t_x[count_x] = (double)count_min;
            t_y[count_x] = (double)a[i].value;
            count_min++;
            count_x++;
        }
    }


    // Will need to change how we get data, this is just dummy data ya dummy
//    double x[]={0,1,2,3,4,5,6,7,8,9,10};
//    double y[]={1,6,17,34,57,86,121,162,209,262,321};

    // Stores the coefficients;  coefficients[5]x^5/coefficients[4]x^4/....
  double c[ORDER];
    
    // Takes in two arrays for points, the # of elements, and the order and stores it in the coefficients pointer
    // return 0 -> we good
    // return -1 -> no good
    int result=polyfit(t_x,t_y,count_x,ORDER,c);
    if (result==-1)
    {
        printf("OwO whoopsie\n");
        return EXIT_FAILURE;
    }

    print_equation(c);
    // args - coefficients array and the X value it will use
    // X value will be the "day" we are predicting for
    // Will most likely need to add another arg for month
    double prediction = predictTemp(c,100);
    printf("%f",prediction);

    //for (int i=0;i<(temp_max + temp_min);i++)
    //{
    //
    //    printf("%f\n",t_y[i]);
    //}

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
