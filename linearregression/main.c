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
const int ORDER=100;
const int CSV_NUM=40;
const int days_in_month[]={31,59,90,120,151,181,212,243,273,303,333};
// Prototype declarations boi
void print_equation(long double *coefficients);
double predictTemp(long double* coefficients,double f);
void reverse(char s[]);
void itoa(int n, char s[]);

//reverses the given string
void reverse(char s[])
{
     int i, j;
     char c;

     for (i = 0, j = strlen(s)-1; i<j; i++, j--)
     {
         c = s[i];
         s[i] = s[j];
         s[j] = c;
     }
}

//turns an integer into a String
void itoa(int n, char s[])
{
     int i, sign;

     if ((sign = n) < 0)  /* record sign */
         n = -n;          /* make n positive */
     i = 0;
     do /* generate digits in reverse order */
     {
         s[i++] = n % 10 + '0';   /* get next digit */
     } while ((n /= 10) > 0);     /* delete it */
     if (sign < 0)
         s[i++] = '-';
     s[i] = '\0';
     reverse(s);
}  


int main(int argc, char* argv[])
{
    int num_processes;
    int rank;
    int local_size;
    int remainder;
    int* data_sizes;
    int* data_displacements;
    int* local_csv_lines;
    char** local_csv_files;
    int local_output_array_size = 0;
    int output_array_size;
    int* local_output_array_sizes;
    int* local_output_array_displacements;
    int* local_temp_maxes;
    int* local_temp_mins;
    int local_temp_max;
    int local_temp_min;
    double* t_x;
    double* t_y;
    double* local_t_x;
    double* local_t_y;

    if (argc < 2) {
        printf("USAGE: mpiexec -n <n> linearprog <thread_num>\n");
        return 0;
    }

    omp_set_num_threads(atoi(argv[1]));
    MPI_Init(&argc,&argv);
    MPI_Comm_size (MPI_COMM_WORLD, &num_processes);
    MPI_Comm_rank (MPI_COMM_WORLD, &rank);

    double starttime = MPI_Wtime();
    struct weather_data** local_weather_array;

    data_sizes = malloc(sizeof(int) * num_processes);
    data_displacements = malloc(sizeof(int) * num_processes);

    local_size = CSV_NUM / num_processes;
    remainder = CSV_NUM % num_processes;

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

    // Distribute input filenames and their line sizes
    if (rank == 0) {
        //printf("START SENDING FILENAMES AND FILE SIZES\n");
        //fflush(stdout);

        for(int i = 1; i < num_processes; i++) {
            for(int j = 0; j < data_sizes[i]; j++) {
                int index = j + data_displacements[i];

                // Send filename
                //printf("Sending filename \"%s\" to process %d from process %d\n", csv_files[index], i, rank);
                //fflush(stdout);
                MPI_Send(&csv_files[index], strlen(csv_files[index]), MPI_CHAR, i, 0, MPI_COMM_WORLD);

                // Send file size
                //printf("Sending file length %d to process %d from process %d\n", csv_lines[index], i, rank);
                //fflush(stdout);
                MPI_Send(&csv_lines[index], 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            }
        }

        //printf("END SENDING FILENAMES AND FILE SIZES\n");
        //fflush(stdout);

        local_csv_files = malloc(sizeof(char*) * data_sizes[rank]);
        local_csv_lines = malloc(sizeof(int) * data_sizes[rank]);
        
        //printf("START SETTING FILENAMES AND FILE SIZES ON PROCESSES %d\n", rank);
        //fflush(stdout);
       
        for (int i = 0; i < data_sizes[0]; i++) {
            local_csv_files[i] = strdup(csv_files[i]);
            //printf("Process %d placed filename \"%s\" for index %d\n", rank, local_csv_files[i], i);
            //fflush(stdout);

            local_csv_lines[i] = csv_lines[i];
            //printf("Process %d placed file length %d for index %d\n", rank, local_csv_lines[i], i);
            //fflush(stdout);
        }

        //printf("END SETTING FILENAMES AND FILE SIZES ON PROCESSES %d\n", rank);
        //fflush(stdout);
    }
    else {
        local_csv_files = malloc(sizeof(char*) * data_sizes[rank]);
        local_csv_lines = malloc(sizeof(int) * data_sizes[rank]);

        //printf("START RECEIVEING FILENAME AND FILE SIZE ON PROCESS %d\n", rank);
        //fflush(stdout);

        for (int i = 0; i < data_sizes[rank]; i++) {
            local_csv_files[i] = malloc(sizeof(char) * 16);

            // Receive filename
            MPI_Recv(&local_csv_files[i], 16, MPI_CHAR, 0, 0, MPI_COMM_WORLD, NULL);
            //printf("Process %d received filename \"%s\" for index %d\n", rank, local_csv_files[i], i);
            //fflush(stdout);

            // Receive file size
            MPI_Recv(&local_csv_lines[i], 1, MPI_INT, 0, 0, MPI_COMM_WORLD, NULL);
            //printf("Process %d received file length %d for index %d\n", rank, local_csv_lines[i], i);
            //fflush(stdout);
        }

        //printf("END RECEIVEING FILENAME AND FILE SIZE ON PROCESS %d\n", rank);
        //fflush(stdout);
    }


    //MPI_Barrier(MPI_COMM_WORLD);

    
    local_weather_array = malloc(sizeof(struct weather_data*) * data_sizes[rank]);

    //printf("START GETTING WEATHER DATA FOR FILES ON PROCESS %d\n", rank);
    //fflush(stdout);

    for (int i = 0; i < data_sizes[rank]; i++)
    {
        //printf("GETTING WEATHER DATA FOR FILE %s (LENGTH %d) ON PROCESS %d AT INDEX %d\n", local_csv_files[i], local_csv_lines[i], rank, i);
        //fflush(stdout);
        local_weather_array[i] = get_data_array(local_csv_files[i], local_csv_lines[i]);
    }
    
    //printf("END GETTING WEATHER DATA FOR FILES ON PROCESS %d\n", rank);
    //fflush(stdout);


    //MPI_Barrier(MPI_COMM_WORLD);


    //printf("START INITIALIZING OF TEMP MAX AND MIN ON PROCESS %d\n", rank);
    //fflush(stdout);

    local_temp_maxes = (int*) malloc(sizeof(int) * data_sizes[rank]);
    local_temp_mins = (int*) malloc(sizeof(int) * data_sizes[rank]);
    for (int i = 0; i < data_sizes[rank]; i++) {
        local_temp_maxes[i] = 0;
        local_temp_mins[i] = 0;
    }

    //printf("END INITIALIZING OF TEMP MAX AND MIN ON PROCESS %d\n", rank);
    //fflush(stdout);


    //MPI_Barrier(MPI_COMM_WORLD);


    //printf("START COUNTING NUMBER OF TEMP MAX AND MIN ON PROCESS %d\n", rank);
    //fflush(stdout);

    #pragma omp parallel for
    for (int i = 0; i < data_sizes[rank]; i++)
    {
        struct weather_data *tmp = local_weather_array[i];
        for (int j = 0; j < local_csv_lines[i]; j++)
        {
            if (strcmp(tmp[j].name,"TMAX")==0)
                local_temp_maxes[i]++;
            if (strcmp(tmp[j].name,"TMIN")==0)
                local_temp_mins[i]++;
        }
    }

    //printf("END COUNTING NUMBER OF TEMP MAX AND MIN ON PROCESS %d\n", rank);
    //fflush(stdout);


    //MPI_Barrier(MPI_COMM_WORLD);


    //printf("START ADDING NUMBER OF TEMP MAX AND MIN ON PROCESS %d\n", rank);
    //fflush(stdout);

    local_temp_max = 0;
    local_temp_min = 0;
    for (int i = 0; i < data_sizes[rank]; i++) {
        local_temp_max += local_temp_maxes[i];
        local_temp_min += local_temp_mins[i];
    }
    
    local_output_array_size = local_temp_max + local_temp_min;

    //printf("END ADDING NUMBER OF TEMP MAX AND MIN ON PROCESS %d\n", rank);
    //fflush(stdout);

    //printf("PROCESS %d local_temp_max = %d\tlocal_temp_min = %d\nlocal sum = %d\n", rank, local_temp_max, local_temp_min, local_output_array_size);
    //fflush(stdout);

    //MPI_Barrier(MPI_COMM_WORLD);

    local_t_x = (double*) malloc(sizeof(double) * (local_output_array_size));
    if (local_t_x == NULL) {
        printf("Not enough memory for x\n");
        fflush(stdout);
        return 1;
    }
    local_t_y = (double*) malloc(sizeof(double) * (local_output_array_size));
    if (local_t_y == NULL) {
        printf("Not enough memory for y\n");
        fflush(stdout);
        return 1;
    }

    // calculate sizes and displacements for following data

    //printf("START BUILDING LOCAL TX AND TY ARRAYS ON PROCESS %d\n", rank);
    //fflush(stdout);

    int local_count_x = 0;
    for (int k = 0; k < data_sizes[rank]; k++)
    {
        int count_max = 0;
        int count_min = 0;
        struct weather_data *tmp = local_weather_array[k];
        for (int i = 0; i < local_csv_lines[k]; i++)
        {
            if (strcmp(tmp[i].name,"TMAX") == 0)
            {
                //local_t_x[local_count_x] = (double)count_max;
                char cdate[8];
                char cmonth[3];
                char cday[3];
                int month;
                int day;
                itoa(tmp[i].date,cdate);
                memcpy(cmonth,&cdate[4],2);
                memcpy(cday,&cdate[6],2);
                cmonth[2]='\0';
                cday[2]='\0';
                month=atoi(cmonth);
                day=atoi(cday);
                if (month!=1)
                    local_t_x[local_count_x] = (double)days_in_month[month-2]+day;
                else
                    local_t_x[local_count_x] = (double)day;
                local_t_y[local_count_x] = (double)tmp[i].value;
                count_max++;
                local_count_x++;
            }
            else if (strcmp(tmp[i].name,"TMIN") == 0)
            {
                //local_t_x[local_count_x] = (double)count_max;
                char cdate[8];
                char cmonth[3];
                char cday[3];
                int month;
                int day;
                itoa(tmp[i].date,cdate);
                memcpy(cmonth,&cdate[4],2);
                memcpy(cday,&cdate[6],2);
                cmonth[2]='\0';
                cday[2]='\0';
                month=atoi(cmonth);
                day=atoi(cday);
                if (month!=1)
                    local_t_x[local_count_x] = (double)days_in_month[month-2]+day;
                else
                    local_t_x[local_count_x] = (double)day;

                local_t_y[local_count_x] = (double)tmp[i].value;
                count_min++;
                local_count_x++;
            }
        }
    }

    //printf("END BUILDING LOCAL TX AND TY ARRAYS ON PROCESS %d\n", rank);
    //fflush(stdout);


    //printf("PROCESS %d HAS REACHED THE FINAL BARRIER\n", rank);
    //fflush(stdout);
    //MPI_Barrier(MPI_COMM_WORLD);


    if (rank == 0) {
        local_output_array_sizes = malloc(sizeof(int) * num_processes);
    }

    // retrieve size of arrays from each rank
    //printf("PROCESS %d: SENDING OUTPUT ARRAY SIZE %d AND NUM_PROCESSES %d\n", rank, local_output_array_size, num_processes);
    //fflush(stdout);
    MPI_Gather(&local_output_array_size, 1, MPI_INT, local_output_array_sizes, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        //for (int i = 0; i < num_processes; i++) {
        //    printf("PROCESS %d: OUTPUT ARRAY SIZE OF PROCESS %d WAS RECEIVED AS %d\n", rank, i, local_output_array_sizes[i]);
        //    fflush(stdout);
        //}

        local_output_array_displacements = malloc(sizeof(int) * num_processes);

        output_array_size = 0;
        for (int i = 0; i < num_processes; i++) {
            output_array_size += local_output_array_sizes[i];
            
            if (i == 0) {
                local_output_array_displacements[i] = 0;
            }
            else {
                local_output_array_displacements[i] = local_output_array_displacements[i - 1] + local_output_array_sizes[i - 1];
            }
        }
        
        //for (int i = 0; i < num_processes; i++) {
        //    printf("SIZE FOR ARRAY ON PROCESS %d IS %d\n", i, local_output_array_sizes[i]);
        //    printf("DISPLACEMENT FOR ARRAY ON PROCESS %d IS %d\n", i, local_output_array_displacements[i]);
        //    fflush(stdout);
        //}

        //printf("PROCESS %d: FINAL OUTPUT ARRAY SIZE IS %d\n", rank, output_array_size);
        //fflush(stdout);

        t_x = (double*) malloc(sizeof(double) * (output_array_size));
        if (t_x == NULL) {
            printf("Not enough memory for x\n");
            fflush(stdout);
            return 1;
        }

        t_y = (double*) malloc(sizeof(double) * (output_array_size));
        if (t_y == NULL) {
            printf("Not enough memory for y\n");
            fflush(stdout);
            return 1;
        }
    }

    // gather t x to single array
    //printf("PROCESS %d: SENDING LOCAL OUTPUT ARRAY T X AND NUM_PROCESSES %d\n", rank, num_processes);
    //fflush(stdout);
    MPI_Gatherv(local_t_x, local_output_array_size, MPI_DOUBLE, t_x, local_output_array_sizes, local_output_array_displacements, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // gather t y to single array
    //printf("PROCESS %d: SENDING LOCAL OUTPUT ARRAY T Y AND NUM_PROCESSES %d\n", rank, num_processes);
    //fflush(stdout);
    MPI_Gatherv(local_t_y, local_output_array_size, MPI_DOUBLE, t_y, local_output_array_sizes, local_output_array_displacements, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    //prints all data points 
    //for (int i=0;i<temp_max+temp_min;i++)
    //{
    //    printf("(%.3f, %.3f)\n",t_y[i],t_x[i]);
    //}


    //printf("MPI COMMUNICATION COMPLETE ON PROCESS %d\n", rank);
    MPI_Barrier(MPI_COMM_WORLD);


    if (rank == 0) {
        // Stores the coefficients;  coefficients[5]x^5/coefficients[4]x^4/....
        long double c[ORDER+1];
        // Takes in two arrays for points, the # of elements, and the order and stores it in the coefficients pointer
        // return 0 -> we good
        // return -1 -> no good

        //double midtime = MPI_Wtime();
        
        //for (int i=0;i<output_array_size;++i) //prints all the data points 
        //{
        //    printf("%f,%f\n",t_x[i],t_y[i]);
        //}
        int result = polyfit(t_x, t_y, output_array_size, ORDER, c);

        if (result == -1)
        {
            printf("OwO whoopsie\n");
            printf("%ld",sizeof(c)/sizeof(*c));
            return EXIT_FAILURE;
        }
        printf("\n");
        print_equation(c);

        // args - coefficients array and the X value it will use
        // X value will be the "day" we are predicting for
        // Will most likely need to add another arg for month
        //double endtime = MPI_Wtime(); 
        //printf("Mid time taken:%f\n", midtime - starttime); 
        //printf("End time taken:%f\n", endtime - midtime);
        //printf("P=%d\tT=%s\n",num_processes,argv[1]);
        //printf("Total time taken:%f\n\n\n", endtime - starttime);
        int input;
        scanf("%d",&input);
        while(input!=-1)
        {
            double prediction = predictTemp(c,input); 
            printf("Average:\t%.2fC / %.2fF\n",prediction,prediction*1.8+32); 
            fflush(stdout);
            scanf("%d",&input);
        }
    }
    MPI_Finalize();
    return 0;
}

// Calculates 'y' for a given 'x'
// Returns the 'y' value which would be the prediction
// Will need to change this up soon to accept a month as well and then pick from the correct month
// ^ this will require coefficients to also change
double predictTemp(long double *coefficients,double x_point)
{
    double y_point=0;
    int i;
    for (i=ORDER;i>=0;i--)
    {
        long tmp;
        tmp=coefficients[i]*pow(x_point,i);
        //printf("DOING %LE * %f\n",coefficients[i],pow(x_point,i));
        y_point+=tmp;
    }
    return y_point/10;
}

// Prints out the polynomial in human readable form
void print_equation(long double *coefficients)
{
    for (int i=0;i<ORDER+1;i++)
    {
        if (i!=ORDER)
            printf("%LEx^%d + ",coefficients[ORDER-i],ORDER-i);
        else
            printf("%Lf\n",coefficients[ORDER-i]);
    }
}
