#include "erf_module.h"

double calculate_normal(double z) {
    return erf(z * sqrt(1/2.));
}

double calculate_student(double z, int df) {
    double correction = (1.0 - 1.0 / (4.0 * df));
    return erf(z * correction * sqrt(1/2.));
}
