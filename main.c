#include <stdio.h>
#include <stdint.h>
#include <math.h>

struct point 
{
    double x;
    double y;
};

typedef struct
{
    double slope;
    double intercept;
} lg_line_t;

void lg_line_build(lg_line_t* this, int count, struct point* points)
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

double lg_line_plot(lg_line_t* this, double x)
{
    return ( this->slope * x ) + this->intercept;
}

double calc_error(double expected, double actual)
{
    return fabs( (actual - expected) / expected);
}

int main ()
{
    struct point test_points[] = 
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
