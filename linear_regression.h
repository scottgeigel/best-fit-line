#ifndef LINEAR_REGRESSION_H
#define LINEAR_REGRESSION_H

typedef struct 
{
    double x;
    double y;
} lg_point_t;

typedef struct
{
    double slope;
    double intercept;
} lg_line_t;


void lg_line_build(lg_line_t* this, const int count, const lg_point_t* points);
double lg_line_plot(const lg_line_t* this, double x);

#endif
