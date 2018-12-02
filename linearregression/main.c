#include <stdio.h>
#include <string.h>
#include <math.h>
#include <mpi.h>
#include <omp.h>
#include "polyfit.h"
#include "retrievedata.h"
#include "data.h"

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

int main(int argc, char* argv[])
{
    int n;
    int rank;
    int local_csv_num;
    int local_n;
    int* data_sizes;
    int* data_displacements;
    long int *temp_maxes;
    long int *temp_mins;
    long int* local_temp_maxes;
    long int* local_temp_mins;
    double* t_x;
    double* t_y;
    double* local_t_x;
    double* local_t_y;
    long long int temp_max=0;
    long long int temp_min=0;

    omp_set_num_threads(atoi(argv[1]));
    MPI_Init(&argc,&argv);
    MPI_Comm_size (MPI_COMM_WORLD, &n);
    MPI_Comm_rank (MPI_COMM_WORLD, &rank);

    float starttime=MPI_Wtime();
    struct weather_data* local_weather_array;
    struct weather_data* weather_array[CSV_NUM];
    
    if (rank == 0) {
        for (int i=0;i<CSV_NUM;i++)
        {
            weather_array[i]=get_data_array(csv_files[i],csv_lines[i]);
        }
        
        *temp_maxes = (long int*) malloc(sizeof(long int) * CSV_NUM);
        *temp_mins = (long int*) malloc(sizeof(long int) * CSV_NUM);
        for (int i=0;i<CSV_NUM;i++) {
            temp_maxes[i] = 0;
            temp_mins[i] = 0;
        }

        #pragma omp parallel for
        for (int i=0;i<CSV_NUM;i++)
        {
            struct weather_data *tmp=weather_array[i];
            for (long int j=0;j<csv_lines[i];j++)
            {
                if (strcmp(tmp[j].name,"TMAX")==0)
                    temp_maxes[i]++;
                if (strcmp(tmp[j].name,"TMIN")==0)
                    temp_mins[i]++;
            }
        }

        for (int i=0;i<CSV_NUM; i++) {
            temp_max += temp_maxes[i];
            temp_min += temp_mins[i];
        }

        printf("temp_max = %ld\ttemp_min = %ld\nsum = %ld\n", temp_max, temp_min, temp_max + temp_min);
        t_x = (double*) malloc(sizeof(double) * (temp_max + temp_min));
        if (t_x == NULL) {
            printf("Not enough memory for x\n");
            return 1;
        }
        t_y = (double*) malloc(sizeof(double) * (temp_max + temp_min));
        if (t_y == NULL) {
            printf("Not enough memory for y\n");
            return 1;
        }
    }


    // calculate sizes and displacements for following data

    // scatter weather array
    // scatter temp maxes
    // scatter temp mins

    long long int count_x = 0;
    for (long int k=0;k<CSV_NUM;k++)
    {
        long long int count_max = 0;
        long long int count_min = 0;
        struct weather_data *tmp=weather_array[k];
        for (long long int i=0;i<csv_lines[k];i++)
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

    // gather local t x
    // gather local t y

    //prints all data points 
    //for (int i=0;i<temp_max+temp_min;i++)
    //{
    //    printf("(%.3f, %.3f)\n",t_y[i],t_x[i]);
    //}

    // Stores the coefficients;  coefficients[5]x^5/coefficients[4]x^4/....
    double c[ORDER];
    // Takes in two arrays for points, the # of elements, and the order and stores it in the coefficients pointer
    // return 0 -> we good
    // return -1 -> no good
    float midtime=MPI_Wtime()-starttime;
    int result=polyfit(t_x,t_y,temp_max+temp_min,ORDER,c);
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
    printf("%f\n",prediction);
    float endtime=MPI_Wtime()-starttime;
    printf("Mid time:%f\n",midtime);
    printf("End time:%f\n",endtime);
    MPI_Finalize();
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
