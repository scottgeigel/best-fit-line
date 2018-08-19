#include <stdio.h>
#include <stdint.h>

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

void lg_build_line(lg_line_t* this, int count, struct point* points)
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

    lg_build_line(&test_line, sizeof(test_points) / sizeof(test_points[0]), test_points);

    printf("line is y = %f * x + %f\n", test_line.slope, test_line.intercept);
}
