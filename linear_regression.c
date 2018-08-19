#include "linear_regression.h"

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

double lg_line_plot(const lg_line_t* this, double x)
{
    return ( this->slope * x ) + this->intercept;
}


