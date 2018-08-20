#ifndef LINEAR_REGRESSION_H
#define LINEAR_REGRESSION_H
#include <stdlib.h>

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
double lg_line_plot_y(const lg_line_t* this, double x);
double lg_line_plot_x(const lg_line_t* this, double y);

typedef struct 
{
    lg_line_t line;
    lg_point_t* population;
    size_t population_count;
} lg_online_line_t;

void lg_online_init(lg_online_line_t* this, size_t sample_size, const lg_point_t* initial_sample);
const lg_line_t* lg_online_getline(const lg_online_line_t* this);
#endif
