#include "linear_regression.h"
#include <string.h>

void lg_line_build(lg_line_t* this, const int count, const lg_point_t* points)
{
    double sum_x=0, sum_xx=0, sum_xy=0;
    double sum_y=0, sum_yy=0;

    for (int i = 0; i < count; i++)
    {
        sum_x += points[i].x;
        sum_y += points[i].y;
        sum_xx += points[i].x * points[i].x;
        sum_yy += points[i].y * points[i].y;
        sum_xy += points[i].x * (double) points[i].y;
    }

    this->slope = ( (sum_xy * (double) count ) - ( sum_x * sum_y ) ) / ( ( sum_xx * (double) count ) - ( sum_x * sum_x ) );
    this->intercept = ( ( 1.0 / (double) count ) * sum_y ) - ( this->slope * ( 1.0 / (double) count ) * sum_x );
}

double lg_line_plot_y(const lg_line_t* this, double x)
{
    return ( this->slope * x ) + this->intercept;
}

double lg_line_plot_x(const lg_line_t* this, double y)
{
    return (y - this->intercept) / this->slope;
}

void lg_online_init(lg_online_line_t* this, size_t sample_size, const lg_point_t* initial_sample)
{
    const size_t sample_in_bytes = sizeof(lg_point_t) * sample_size;
    this->population = malloc(sample_in_bytes);
    this->population_count = sample_size;
    memcpy(this->population, initial_sample, sample_in_bytes);
    lg_line_build(&this->line, this->population_count, this->population);
}
const lg_line_t* lg_online_getline(const lg_online_line_t* this)
{
    return &this->line;
}

