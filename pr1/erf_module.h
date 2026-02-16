#ifndef ERF_MODULE_H
#define ERF_MODULE_H

#include <math.h>
#define CI90 1.64485
#define CI95 1.95996
#define CI99 2.57583

double calculate_normal(double z);
double calculate_student(double z, int df);

#endif
