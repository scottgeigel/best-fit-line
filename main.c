#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "linear_regression.h"

static double calc_error(const double expected, const double actual);

int main ()
{
    lg_point_t test_points[] = 
    {
        {1.5, 40},
        {2, 50},
        {4.2, 55},
        {5, 60}
    };

    lg_line_t test_line;

    lg_line_build(&test_line, sizeof(test_points) / sizeof(test_points[0]), test_points);

    printf("line is y = %f * x + %f\n", test_line.slope, test_line.intercept);

    for ( int i = 0; i < ( sizeof(test_points) / sizeof(test_points[0]) ); i++ )
    {
        double plotted_y = lg_line_plot(&test_line, test_points[i].x);
        printf("checking point (%f, %f)\t\t%f\t\t%%%f\n", test_points[i].x, test_points[i].y, plotted_y, calc_error(test_points[i].y, plotted_y));
    }
}

double calc_error(const double expected, const double actual)
{
    return fabs( (actual - expected) / expected);
}


