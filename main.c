#include <stdio.h>
#include <math.h>
#include <time.h>
#include "linear_regression.h"

#define MAX_SAMPLES (5)
#define MAX_VERIFICATION (2)

static double calc_error(const double expected, const double actual);
static double sim_flow_meter(const int pulses);
static double sim_read_flask(double real_measurement);

int main ()
{
    lg_online_line_t trainer;
    lg_point_t initial_pool[MAX_SAMPLES];
    lg_point_t feedback_pool[MAX_VERIFICATION];
    const lg_line_t* temp_line = NULL;
    int samples_collected = 0;

    srand(time(NULL));

    while (!feof(stdin) && (samples_collected < MAX_SAMPLES))
    {
        int pulses;
        double ml;
        double observed_ml;

        printf("How many pulses do you want? > ");
        if (scanf("%d", &pulses))
        {
            ml = sim_flow_meter(pulses);
            observed_ml = sim_read_flask(ml);
            printf("That's %lf ml, but you read it as %lf\n", ml, observed_ml);
            initial_pool[samples_collected].x = pulses;
            initial_pool[samples_collected].y = observed_ml;
            samples_collected++;
        }
    }

    lg_online_init(&trainer, MAX_SAMPLES, initial_pool);
    temp_line = lg_online_getline(&trainer);
    printf("came up with line y=(%lf)x+%lf\n", temp_line->slope, temp_line->intercept);

    printf("\n\nnow type in verification samples\n\t(ctrl+D to quit)\n");
    while (!feof(stdin))
    {
        int pulses;
        double requested_ml = 0;
        double ml;
        double observed_ml;
        double accuracy;

        printf("How many ml do you want? > ");
        if (scanf("%lf", &requested_ml))
        {
            pulses = (int) round(lg_line_plot_x(temp_line, requested_ml));
            ml = sim_flow_meter(pulses);
            observed_ml = sim_read_flask(ml);
            printf("That's %lf ml, but you read it as %lf\n", ml, observed_ml);
            accuracy = (fabs(requested_ml - ml) / requested_ml) * 100.0f;
            printf("\tit was accurate to %lf%% accurate\n", accuracy);
            accuracy = (fabs(requested_ml - observed_ml) / requested_ml) * 100.0f;
            printf("\tit was observed to be %lf%% accurate\n", accuracy);
        }
    }
}

double calc_error(const double expected, const double actual)
{
    return fabs( (actual - expected) / expected);
}

static double sim_read_flask(double real_measurement)
{
    //range defined to simulate 2% accuracy of measuring vessel
    //so on a 100ml flask, +- 1ml
    static const int range_max = 100;
    static const int range_min = -100;
    int rn = rand();
    int prefloat = (rn % (range_max - range_min + 1)) + range_min;
    double error_measurement = real_measurement * (1.0f + ( (double) prefloat ) / 10000.0f);
    //for 0-100ml, you can probably read it up to the closes half
    if (error_measurement <= 100.0f)
    {
        error_measurement *= 2.0f;
        error_measurement = round(error_measurement);
        error_measurement /= 2.0f;
    }
    else
    {
        //for 101-500ml, you're going to need to round to the nearest ml
        error_measurement = round(error_measurement);
    }
    return error_measurement;
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
