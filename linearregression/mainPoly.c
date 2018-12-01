#include <stdio.h>
#include <string.h>
#include <math.h>
#include "polyfit.h"
#include "retrievedata.h"
#include "data.h"
// Get length of array, does not work if x is a pointer grrrrrr
#define NUM_OF(x) (sizeof(x)/sizeof(*x))

// Number of points
// Will probably not be a constant (considering the days in months vary)
// Just made it const for the sake of the dummy data
//const int ELEMENT_COUNT=11;

// Order of polynomial; ie. highest degree of x
// Will probably tweak this somehow to get more accurate without destrying our efficency
const int ORDER=5;
const int CSV_NUM=41;
// Prototype declarations boi
void print_equation(double *coefficients);
double predictTemp(double* coefficients,double f);

int main()
{

    struct weather_data* weather_array[CSV_NUM];
    
    for (int i=0;i<CSV_NUM;i++)
    {
        weather_array[i]=get_data_array(csv_files[i],csv_lines[i]);
    }
    
    int temp_max=0;
    int temp_min=0;
    for (int i=0;i<CSV_NUM;i++)
    {
        struct weather_data *tmp=weather_array[i];
        for (int j=0;j<csv_lines[i];j++)
        {
            if (strcmp(tmp[j].name,"TMAX")==0)
                temp_max++;
            if (strcmp(tmp[j].name,"TMIN")==0)
                temp_min++;
        }
    }

    double* t_x = malloc(sizeof(long int) * (temp_max + temp_min));
    double* t_y = malloc(sizeof(long int) * (temp_max + temp_min));

    int count_x = 0;
    for (int k=0;k<CSV_NUM;k++)
    {
        int count_max = 0;
        int count_min = 0;
        struct weather_data *tmp=weather_array[k];
        for (int i=0;i<csv_lines[k];i++)
        {
            if (strcmp(tmp[i].name,"TMAX") == 0)
            {
                t_x[count_x] = (double)count_max;
                t_y[count_x] = (double)tmp[i].value;
                count_max++;
                count_x++;
            }
            else if (strcmp(tmp[i].name,"TMIN") == 0)
            {
                t_x[count_x] = (double)count_min;
                t_y[count_x] = (double)tmp[i].value;
                count_min++;
                count_x++;
            }
        }
    }
    //prints all data points 
    //for (int i=0;i<temp_max+temp_min;i++)
    //{
    //    printf("(%.2f, %.2f)\n",t_y[i],t_x[i]);
    //}



    // Stores the coefficients;  coefficients[5]x^5/coefficients[4]x^4/....
    double c[ORDER];
    // Takes in two arrays for points, the # of elements, and the order and stores it in the coefficients pointer
    // return 0 -> we good
    // return -1 -> no good
    int result=polyfit(t_x,t_y,100,ORDER,c);
    if (result==-1)
    {
        printf("OwO whoopsie\n");
        return EXIT_FAILURE;
    }

    print_equation(c);
    // args - coefficients array and the X value it will use
    // X value will be the "day" we are predicting for
    // Will most likely need to add another arg for month
    //double prediction = predictTemp(c,100);
    //printf("%f",prediction);

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
