#ifndef POLYFIT_H_
#define POLYFIT_H_

#include <stdio.h>
#include <stdlib.h>
int polyfit(const double* const dependentValues,
            const double* const independentValues, unsigned int countOfElements,
            unsigned int order, long double* coefficients);
#endif
