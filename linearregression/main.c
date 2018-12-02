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
    int num_processes;
    int rank;
    int local_size;
    int local_output_array_size;
    int* data_sizes;
    int* data_displacements;
    int* data_output_array_sizes;
    int* data_output_array_displacements;
    int* local_csv_lines;
    long int* temp_maxes;
    long int* temp_mins;
    long int* local_temp_maxes;
    long int* local_temp_mins;
    double* t_x;
    double* t_y;
    double* local_t_x;
    double* local_t_y;
    long long int temp_max=0;
    long long int temp_min=0;
    long int local_temp_max=0;
    long int local_temp_min=0;

    MPI_Datatype mpi_weather_data;
    int blocklens[3];
    MPI_Aint indices[3];
    MPI_Datatype old_types[3];

    omp_set_num_threads(atoi(argv[1]));
    MPI_Init(&argc,&argv);
    MPI_Comm_size (MPI_COMM_WORLD, &num_processes);
    MPI_Comm_rank (MPI_COMM_WORLD, &rank);

    float starttime=MPI_Wtime();
    struct weather_data** local_weather_array;
    struct weather_data* weather_array[CSV_NUM];
    
    // Build mpi_weather_data datatype
    blocklens[0] = 1;
    blocklens[1] = 1;
    blocklens[2] = 8;
    old_types[0] = MPI_INT;
    old_types[1] = MPI_INT;
    old_types[2] = MPI_CHAR;
    indices[0] = 0;
    indices[1] = sizeof(int);
    indices[2] = sizeof(int) * 2;
    MPI_Type_struct(3, blocklens, indices, old_types, &mpi_weather_data);
    MPI_Type_commit(&mpi_weather_data);

    // calculate sizes and displacements for following data
    data_sizes = malloc(sizeof(int) * num_processes);
    data_displacements = malloc(sizeof(int) * num_processes);

    printf("CSV_NUM = %d on processes with rank %d\n", CSV_NUM, rank);
    local_size = CSV_NUM / num_processes;
    int remainder = CSV_NUM % num_processes;

    // Build size and displacement arrays
    for (int i = 0; i < num_processes; i++) {
        // Start with base size
        data_sizes[i] = local_size;

        // Account for first displacement
        if (i == 0) {
            data_displacements[i] = 0;
        }
        else {
            data_displacements[i] = data_displacements[i - 1] + data_sizes[i - 1];
        }

        // Add remainder until it is all accounted for
        if (remainder > 0) {
            data_sizes[i]++;
            remainder--;
        }
    }

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

        printf("temp_max = %lld\ttemp_min = %lld\nsum = %lld\n", temp_max, temp_min, temp_max + temp_min);
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

        // Build output data sizes and displacements
        data_output_array_sizes = malloc(sizeof(int) * num_processes);
        data_output_array_displacements = malloc(sizeof(long int) * num_processes);
        for (int i = 0; i < num_processes; i++) {
            data_output_array_sizes[i] = 0;

            for (int j = 0; j < data_sizes[i]; j++) {
                data_output_array_sizes[i] += temp_maxes[j + data_displacements[i]] + temp_mins[j + data_displacements[i]];
            }
            
            if (i == 0) {
                data_output_array_displacements[i] = 0;
            }
            else {
                data_output_array_displacements[i] = data_output_array_displacements[i - 1] + data_output_array_sizes[i - 1];
            }
        }
    }

    // Build receiving arrays
    local_weather_array = malloc(sizeof(struct weather_data*) * data_sizes[rank]);
    //local_temp_maxes = malloc(sizeof(long int) * data_sizes[rank]);
    //local_temp_mins = malloc(sizeof(long int) * data_sizes[rank]);
    local_csv_lines = malloc(sizeof(int) * data_sizes[rank]);

    if (rank == 0) {
        for (int i = 1; i < num_processes; i++) {
            for (int j = 0; j < data_sizes[rank]; i++) {
                long int index = j + data_displacements[i];
                MPI_Send(weather_array[index], csv_lines[index], );
            }
        }
    }
    else {
        for (int i = 0; i < data_sizes[rank]; i++) {
            MPI_Recv();
            //Send each weather array one by one to each other process from processes 0 and have them receive it on their end in the appropriate spot
        }
    }

    // scatter weather array
    //MPI_Scatterv(weather_array, data_sizes, data_displacements, mpi_weather_data, local_weather_array, data_sizes[rank], mpi_weather_data, 0, MPI_COMM_WORLD);

    // scatter temp maxes
    //MPI_Scatterv(&temp_maxes, data_sizes, data_displacements, MPI_LONG, &local_temp_maxes, data_sizes[rank], MPI_LONG, 0, MPI_COMM_WORLD);

    // scatter temp mins
    //MPI_Scatterv(&temp_mins, data_sizes, data_displacements, MPI_LONG, &local_temp_mins, data_sizes[rank], MPI_LONG, 0, MPI_COMM_WORLD);

    // scatter output array sizes
    MPI_Scatter(data_output_array_sizes, 1, MPI_INT, &local_output_array_size, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // scatter csv lines
    MPI_Scatterv(csv_lines, data_sizes, data_displacements, MPI_INT, local_csv_lines, data_sizes[rank], MPI_INT, 0, MPI_COMM_WORLD);

    local_t_x = malloc(sizeof(double) * local_output_array_size);
    local_t_y = malloc(sizeof(double) * local_output_array_size);

    long long int count_x = 0;
    for (long int k=0;k<data_sizes[rank];k++)
    {
        long long int count_max = 0;
        long long int count_min = 0;
        struct weather_data* tmp = local_weather_array[k];
        for (long long int i=0;i<local_csv_lines[k];i++)
        {
            if (strcmp(tmp[i].name,"TMAX") == 0)
            {
                local_t_x[count_x] = (double)count_max;
                local_t_y[count_x] = (double)tmp[i].value;
                count_max++;
                count_x++;
            }
            else if (strcmp(tmp[i].name,"TMIN") == 0)
            {
                local_t_x[count_x] = (double)count_min;
                local_t_y[count_x] = (double)tmp[i].value;
                count_min++;
                count_x++;
            }
        }
    }

    // gather local t x
    MPI_Gatherv(local_t_x, local_output_array_size, MPI_DOUBLE, t_x, data_output_array_sizes, data_output_array_displacements, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // gather local t y
    MPI_Gatherv(local_t_y, local_output_array_size, MPI_DOUBLE, t_y, data_output_array_sizes, data_output_array_displacements, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Do prediction
    if (rank == 0) {
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
    }

    //float endtime=MPI_Wtime()-starttime;
    //printf("Mid time:%f\n",midtime);
    //printf("End time:%f\n",endtime);
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
