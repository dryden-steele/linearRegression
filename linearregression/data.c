
#include<string.h>
#include<stdio.h>
#include<stdbool.h>

//--------------------------------------------------------
// FUNCTION populatedata
//--------------------------------------------------------
bool populatedata(double independent[8], double dependent[8], int dataset)
{
    bool success = true;

    switch(dataset)
    {
        case 1:
            memcpy(independent, (double[8]){10,20,40,45,60,65,75,80}, sizeof(double[8]));
            memcpy(dependent, (double[8]){32,44,68,74,92,98,110,116}, sizeof(double[8]));
            break;

        case 2:
            memcpy(independent, (double[8]){10,20,40,45,60,65,75,80}, sizeof(double[8]));
            memcpy(dependent, (double[8]){40,40,60,80,90,110,100,130}, sizeof(double[8]));
            break;

        case 3:
            memcpy(independent, (double[8]){10,20,40,45,60,65,75,80}, sizeof(double[8]));
            memcpy(dependent, (double[8]){100,10,130,90,40,80,180,50}, sizeof(double[8]));
            break;

        case 4:
            memcpy(independent, (double[8]){10,20,40,45,60,65,75,80}, sizeof(double[8]));
            memcpy(dependent, (double[8]){40,40,60,80,90,110,100,130}, sizeof(double[8]));
            break;

        case 5:
            memcpy(independent, (double[8]){10,20,40,45,60,65,75,80}, sizeof(double[8]));
            memcpy(dependent, (double[8]){100,10,130,90,40,80,180,50}, sizeof(double[8]));
            break;

        default:
            puts("Invalid dataset requested");
            success = false;
            break;
    }

    return success;
}

//january data set
bool populatedataJan(double independent[8], double dependent[8], int dataset)
{
    bool success = true;

    switch(dataset)
    {
        case 1:
            memcpy(independent, (double[8]){10,20,40,45,60,65,75,80}, sizeof(double[8]));
            memcpy(dependent, (double[8]){32,44,68,74,92,98,110,116}, sizeof(double[8]));
            break;

        case 2:
            memcpy(independent, (double[8]){10,20,40,45,60,65,75,80}, sizeof(double[8]));
            memcpy(dependent, (double[8]){40,40,60,80,90,110,100,130}, sizeof(double[8]));
            break;

        case 3:
            memcpy(independent, (double[8]){10,20,40,45,60,65,75,80}, sizeof(double[8]));
            memcpy(dependent, (double[8]){100,10,130,90,40,80,180,50}, sizeof(double[8]));
            break;

        case 4:
            memcpy(independent, (double[8]){10,20,40,45,60,65,75,80}, sizeof(double[8]));
            memcpy(dependent, (double[8]){40,40,60,80,90,110,100,130}, sizeof(double[8]));
            break;

        case 5:
            memcpy(independent, (double[8]){10,20,40,45,60,65,75,80}, sizeof(double[8]));
            memcpy(dependent, (double[8]){100,10,130,90,40,80,180,50}, sizeof(double[8]));
            break;

        default:
            puts("Invalid dataset requested. JAN");
            success = false;
            break;
    }

    return success;
}

//febuary data set
bool populatedataFeb(double independent[8], double dependent[8], int dataset)
{
    bool success = true;

    switch(dataset)
    {
        case 1:
            memcpy(independent, (double[8]){10,20,40,45,60,65,75,80}, sizeof(double[8]));
            memcpy(dependent, (double[8]){32,44,68,74,92,98,110,116}, sizeof(double[8]));
            break;

        case 2:
            memcpy(independent, (double[8]){10,20,40,45,60,65,75,80}, sizeof(double[8]));
            memcpy(dependent, (double[8]){40,40,60,80,90,110,100,130}, sizeof(double[8]));
            break;

        case 3:
            memcpy(independent, (double[8]){10,20,40,45,60,65,75,80}, sizeof(double[8]));
            memcpy(dependent, (double[8]){100,10,130,90,40,80,180,50}, sizeof(double[8]));
            break;

        case 4:
            memcpy(independent, (double[8]){10,20,40,45,60,65,75,80}, sizeof(double[8]));
            memcpy(dependent, (double[8]){40,40,60,80,90,110,100,130}, sizeof(double[8]));
            break;

        case 5:
            memcpy(independent, (double[8]){10,20,40,45,60,65,75,80}, sizeof(double[8]));
            memcpy(dependent, (double[8]){100,10,130,90,40,80,180,50}, sizeof(double[8]));
            break;

        default:
            puts("Invalid dataset requested, FEB");
            success = false;
            break;
    }

    return success;
}

//March data set
bool populatedataMar(double independent[8], double dependent[8], int dataset)
{
    bool success = true;

    switch(dataset)
    {
        case 1:
            memcpy(independent, (double[8]){10,20,40,45,60,65,75,80}, sizeof(double[8]));
            memcpy(dependent, (double[8]){32,44,68,74,92,98,110,116}, sizeof(double[8]));
            break;

        case 2:
            memcpy(independent, (double[8]){10,20,40,45,60,65,75,80}, sizeof(double[8]));
            memcpy(dependent, (double[8]){40,40,60,80,90,110,100,130}, sizeof(double[8]));
            break;

        case 3:
            memcpy(independent, (double[8]){10,20,40,45,60,65,75,80}, sizeof(double[8]));
            memcpy(dependent, (double[8]){100,10,130,90,40,80,180,50}, sizeof(double[8]));
            break;

        case 4:
            memcpy(independent, (double[8]){10,20,40,45,60,65,75,80}, sizeof(double[8]));
            memcpy(dependent, (double[8]){40,40,60,80,90,110,100,130}, sizeof(double[8]));
            break;

        case 5:
            memcpy(independent, (double[8]){10,20,40,45,60,65,75,80}, sizeof(double[8]));
            memcpy(dependent, (double[8]){100,10,130,90,40,80,180,50}, sizeof(double[8]));
            break;

        default:
            puts("Invalid dataset requested, MAR");
            success = false;
            break;
    }

    return success;
}

//april data set
bool populatedataApr(double independent[8], double dependent[8], int dataset)
{
    bool success = true;

    switch(dataset)
    {
        case 1:
            memcpy(independent, (double[8]){10,20,40,45,60,65,75,80}, sizeof(double[8]));
            memcpy(dependent, (double[8]){32,44,68,74,92,98,110,116}, sizeof(double[8]));
            break;

        case 2:
            memcpy(independent, (double[8]){10,20,40,45,60,65,75,80}, sizeof(double[8]));
            memcpy(dependent, (double[8]){40,40,60,80,90,110,100,130}, sizeof(double[8]));
            break;

        case 3:
            memcpy(independent, (double[8]){10,20,40,45,60,65,75,80}, sizeof(double[8]));
            memcpy(dependent, (double[8]){100,10,130,90,40,80,180,50}, sizeof(double[8]));
            break;

        case 4:
            memcpy(independent, (double[8]){10,20,40,45,60,65,75,80}, sizeof(double[8]));
            memcpy(dependent, (double[8]){40,40,60,80,90,110,100,130}, sizeof(double[8]));
            break;

        case 5:
            memcpy(independent, (double[8]){10,20,40,45,60,65,75,80}, sizeof(double[8]));
            memcpy(dependent, (double[8]){100,10,130,90,40,80,180,50}, sizeof(double[8]));
            break;

        default:
            puts("Invalid dataset requested, APR");
            success = false;
            break;
    }

    return success;
}

//may data set
bool populatedataMay(double independent[8], double dependent[8], int dataset)
{
    bool success = true;

    switch(dataset)
    {
        case 1:
            memcpy(independent, (double[8]){10,20,40,45,60,65,75,80}, sizeof(double[8]));
            memcpy(dependent, (double[8]){32,44,68,74,92,98,110,116}, sizeof(double[8]));
            break;

        case 2:
            memcpy(independent, (double[8]){10,20,40,45,60,65,75,80}, sizeof(double[8]));
            memcpy(dependent, (double[8]){40,40,60,80,90,110,100,130}, sizeof(double[8]));
            break;

        case 3:
            memcpy(independent, (double[8]){10,20,40,45,60,65,75,80}, sizeof(double[8]));
            memcpy(dependent, (double[8]){100,10,130,90,40,80,180,50}, sizeof(double[8]));
            break;

        case 4:
            memcpy(independent, (double[8]){10,20,40,45,60,65,75,80}, sizeof(double[8]));
            memcpy(dependent, (double[8]){40,40,60,80,90,110,100,130}, sizeof(double[8]));
            break;

        case 5:
            memcpy(independent, (double[8]){10,20,40,45,60,65,75,80}, sizeof(double[8]));
            memcpy(dependent, (double[8]){100,10,130,90,40,80,180,50}, sizeof(double[8]));
            break;

        default:
            puts("Invalid dataset requested, MAY");
            success = false;
            break;
    }

    return success;
}

//june data set
bool populatedataJun(double independent[8], double dependent[8], int dataset)
{
    bool success = true;

    switch(dataset)
    {
        case 1:
            memcpy(independent, (double[8]){10,20,40,45,60,65,75,80}, sizeof(double[8]));
            memcpy(dependent, (double[8]){32,44,68,74,92,98,110,116}, sizeof(double[8]));
            break;

        case 2:
            memcpy(independent, (double[8]){10,20,40,45,60,65,75,80}, sizeof(double[8]));
            memcpy(dependent, (double[8]){40,40,60,80,90,110,100,130}, sizeof(double[8]));
            break;

        case 3:
            memcpy(independent, (double[8]){10,20,40,45,60,65,75,80}, sizeof(double[8]));
            memcpy(dependent, (double[8]){100,10,130,90,40,80,180,50}, sizeof(double[8]));
            break;

        case 4:
            memcpy(independent, (double[8]){10,20,40,45,60,65,75,80}, sizeof(double[8]));
            memcpy(dependent, (double[8]){40,40,60,80,90,110,100,130}, sizeof(double[8]));
            break;

        case 5:
            memcpy(independent, (double[8]){10,20,40,45,60,65,75,80}, sizeof(double[8]));
            memcpy(dependent, (double[8]){100,10,130,90,40,80,180,50}, sizeof(double[8]));
            break;

        default:
            puts("Invalid dataset requested, JUN");
            success = false;
            break;
    }

    return success;
}

//july data set
bool populatedataJul(double independent[8], double dependent[8], int dataset)
{
    bool success = true;

    switch(dataset)
    {
        case 1:
            memcpy(independent, (double[8]){10,20,40,45,60,65,75,80}, sizeof(double[8]));
            memcpy(dependent, (double[8]){32,44,68,74,92,98,110,116}, sizeof(double[8]));
            break;

        case 2:
            memcpy(independent, (double[8]){10,20,40,45,60,65,75,80}, sizeof(double[8]));
            memcpy(dependent, (double[8]){40,40,60,80,90,110,100,130}, sizeof(double[8]));
            break;

        case 3:
            memcpy(independent, (double[8]){10,20,40,45,60,65,75,80}, sizeof(double[8]));
            memcpy(dependent, (double[8]){100,10,130,90,40,80,180,50}, sizeof(double[8]));
            break;

        case 4:
            memcpy(independent, (double[8]){10,20,40,45,60,65,75,80}, sizeof(double[8]));
            memcpy(dependent, (double[8]){40,40,60,80,90,110,100,130}, sizeof(double[8]));
            break;

        case 5:
            memcpy(independent, (double[8]){10,20,40,45,60,65,75,80}, sizeof(double[8]));
            memcpy(dependent, (double[8]){100,10,130,90,40,80,180,50}, sizeof(double[8]));
            break;

        default:
            puts("Invalid dataset requested, JUL");
            success = false;
            break;
    }

    return success;
}

//august data set
bool populatedataAug(double independent[8], double dependent[8], int dataset)
{
    bool success = true;

    switch(dataset)
    {
        case 1:
            memcpy(independent, (double[8]){10,20,40,45,60,65,75,80}, sizeof(double[8]));
            memcpy(dependent, (double[8]){32,44,68,74,92,98,110,116}, sizeof(double[8]));
            break;

        case 2:
            memcpy(independent, (double[8]){10,20,40,45,60,65,75,80}, sizeof(double[8]));
            memcpy(dependent, (double[8]){40,40,60,80,90,110,100,130}, sizeof(double[8]));
            break;

        case 3:
            memcpy(independent, (double[8]){10,20,40,45,60,65,75,80}, sizeof(double[8]));
            memcpy(dependent, (double[8]){100,10,130,90,40,80,180,50}, sizeof(double[8]));
            break;

        case 4:
            memcpy(independent, (double[8]){10,20,40,45,60,65,75,80}, sizeof(double[8]));
            memcpy(dependent, (double[8]){40,40,60,80,90,110,100,130}, sizeof(double[8]));
            break;

        case 5:
            memcpy(independent, (double[8]){10,20,40,45,60,65,75,80}, sizeof(double[8]));
            memcpy(dependent, (double[8]){100,10,130,90,40,80,180,50}, sizeof(double[8]));
            break;

        default:
            puts("Invalid dataset requested, AUG");
            success = false;
            break;
    }

    return success;
}

//Septmeber data set
bool populatedataSep(double independent[8], double dependent[8], int dataset)
{
    bool success = true;

    switch(dataset)
    {
        case 1:
            memcpy(independent, (double[8]){10,20,40,45,60,65,75,80}, sizeof(double[8]));
            memcpy(dependent, (double[8]){32,44,68,74,92,98,110,116}, sizeof(double[8]));
            break;

        case 2:
            memcpy(independent, (double[8]){10,20,40,45,60,65,75,80}, sizeof(double[8]));
            memcpy(dependent, (double[8]){40,40,60,80,90,110,100,130}, sizeof(double[8]));
            break;

        case 3:
            memcpy(independent, (double[8]){10,20,40,45,60,65,75,80}, sizeof(double[8]));
            memcpy(dependent, (double[8]){100,10,130,90,40,80,180,50}, sizeof(double[8]));
            break;

        case 4:
            memcpy(independent, (double[8]){10,20,40,45,60,65,75,80}, sizeof(double[8]));
            memcpy(dependent, (double[8]){40,40,60,80,90,110,100,130}, sizeof(double[8]));
            break;

        case 5:
            memcpy(independent, (double[8]){10,20,40,45,60,65,75,80}, sizeof(double[8]));
            memcpy(dependent, (double[8]){100,10,130,90,40,80,180,50}, sizeof(double[8]));
            break;

        default:
            puts("Invalid dataset requested, SEPT");
            success = false;
            break;
    }

    return success;
}

//october data set 
bool populatedataOct(double independent[8], double dependent[8], int dataset)
{
    bool success = true;

    switch(dataset)
    {
        case 1:
            memcpy(independent, (double[8]){10,20,40,45,60,65,75,80}, sizeof(double[8]));
            memcpy(dependent, (double[8]){32,44,68,74,92,98,110,116}, sizeof(double[8]));
            break;

        case 2:
            memcpy(independent, (double[8]){10,20,40,45,60,65,75,80}, sizeof(double[8]));
            memcpy(dependent, (double[8]){40,40,60,80,90,110,100,130}, sizeof(double[8]));
            break;

        case 3:
            memcpy(independent, (double[8]){10,20,40,45,60,65,75,80}, sizeof(double[8]));
            memcpy(dependent, (double[8]){100,10,130,90,40,80,180,50}, sizeof(double[8]));
            break;

        case 4:
            memcpy(independent, (double[8]){10,20,40,45,60,65,75,80}, sizeof(double[8]));
            memcpy(dependent, (double[8]){40,40,60,80,90,110,100,130}, sizeof(double[8]));
            break;

        case 5:
            memcpy(independent, (double[8]){10,20,40,45,60,65,75,80}, sizeof(double[8]));
            memcpy(dependent, (double[8]){100,10,130,90,40,80,180,50}, sizeof(double[8]));
            break;

        default:
            puts("Invalid dataset requested, OCT");
            success = false;
            break;
    }

    return success;
}

//november data set
bool populatedataNov(double independent[8], double dependent[8], int dataset)
{
    bool success = true;

    switch(dataset)
    {
        case 1:
            memcpy(independent, (double[8]){10,20,40,45,60,65,75,80}, sizeof(double[8]));
            memcpy(dependent, (double[8]){32,44,68,74,92,98,110,116}, sizeof(double[8]));
            break;

        case 2:
            memcpy(independent, (double[8]){10,20,40,45,60,65,75,80}, sizeof(double[8]));
            memcpy(dependent, (double[8]){40,40,60,80,90,110,100,130}, sizeof(double[8]));
            break;

        case 3:
            memcpy(independent, (double[8]){10,20,40,45,60,65,75,80}, sizeof(double[8]));
            memcpy(dependent, (double[8]){100,10,130,90,40,80,180,50}, sizeof(double[8]));
            break;

        case 4:
            memcpy(independent, (double[8]){10,20,40,45,60,65,75,80}, sizeof(double[8]));
            memcpy(dependent, (double[8]){40,40,60,80,90,110,100,130}, sizeof(double[8]));
            break;

        case 5:
            memcpy(independent, (double[8]){10,20,40,45,60,65,75,80}, sizeof(double[8]));
            memcpy(dependent, (double[8]){100,10,130,90,40,80,180,50}, sizeof(double[8]));
            break;

        default:
            puts("Invalid dataset requested, NOV");
            success = false;
            break;
    }

    return success;
}

//december data set 
bool populatedataDec(double independent[8], double dependent[8], int dataset)
{
    bool success = true;

    switch(dataset)
    {
        case 1:
            memcpy(independent, (double[8]){10,20,40,45,60,65,75,80}, sizeof(double[8]));
            memcpy(dependent, (double[8]){32,44,68,74,92,98,110,116}, sizeof(double[8]));
            break;

        case 2:
            memcpy(independent, (double[8]){10,20,40,45,60,65,75,80}, sizeof(double[8]));
            memcpy(dependent, (double[8]){40,40,60,80,90,110,100,130}, sizeof(double[8]));
            break;

        case 3:
            memcpy(independent, (double[8]){10,20,40,45,60,65,75,80}, sizeof(double[8]));
            memcpy(dependent, (double[8]){100,10,130,90,40,80,180,50}, sizeof(double[8]));
            break;

        case 4:
            memcpy(independent, (double[8]){10,20,40,45,60,65,75,80}, sizeof(double[8]));
            memcpy(dependent, (double[8]){40,40,60,80,90,110,100,130}, sizeof(double[8]));
            break;

        case 5:
            memcpy(independent, (double[8]){10,20,40,45,60,65,75,80}, sizeof(double[8]));
            memcpy(dependent, (double[8]){100,10,130,90,40,80,180,50}, sizeof(double[8]));
            break;

        default:
            puts("Invalid dataset requested, DEC");
            success = false;
            break;
    }

    return success;
}
