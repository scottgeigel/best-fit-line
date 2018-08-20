#include <stdio.h>
#include <math.h>
#include "linear_regression.h"

static double calc_error(const double expected, const double actual);
static double sim_flow_meter(const int pulses);

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

    while (!feof(stdin))
    {
        int pulses;
        double ml;
        printf("How many pulses do you want? > ");
        scanf("%d", &pulses);
        ml = sim_flow_meter(pulses);
        printf("That's %f ml\n", ml);
    }
}

double calc_error(const double expected, const double actual)
{
    return fabs( (actual - expected) / expected);
}

static double sim_flow_meter(int pulses)
{
    double ml = 0.0f;

    //simulate the first 50 pulses as 5 pulses per ml
    if (pulses > 0)
    {
        ml += ((double)(pulses % 50)) / 5.0f;
        pulses -= pulses % 50;
    }
    //simulate the next 50 pulses as 7.35 pulses per ml
    if (pulses > 0)
    {
        ml += ((double)(pulses % 50)) / 7.35f;
        pulses -= pulses % 50;
    }
    //simulate the next 100 pulses as 8.9 pulses per ml
    if (pulses > 0)
    {
        ml += ((double)(pulses % 100)) / 8.9f;
        pulses -= pulses % 100;
    }
    //simulate any remaining pulses as 10.25 pulses per ml
    if (pulses > 0)
    {
        ml += ((double) pulses) / 10.25f;
    }
    return ml;
}
