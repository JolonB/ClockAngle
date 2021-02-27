#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TIME_LEN 3

union Time {
    struct Time_s {
        short hour;
        short minute;
        short second;
    } times_s;
    short times[TIME_LEN];
};

void error(const char *msg) {
    fprintf(stderr, "%s\n", msg);
    exit(1);
}

void time_str(union Time *t, char* buffer) {
    short char_index = 0;
    for (short i = 0; i < TIME_LEN; i++) {
        char_index += sprintf(buffer+char_index, "%02i:", t->times[i]);
    }
    buffer[char_index-1] = '\0';
}

union Time time_diff(union Time *t1, union Time *t2, short *max) {
    short diff;
    union Time d;
    short carry = 0;
    for (int i = TIME_LEN - 1; i >= 0; i--) {
        diff = t2->times[i] - t1->times[i] + carry;
        if (diff < 0) {
            diff = max[i] + diff; // loop back around
            carry = -1;
        } else {
            carry = 0;
        }
        d.times[i] = diff;
    }
    return d;
}

double get_angle(union Time *time_diff, short *max, short *cycles) {
    double angle = 0;
    double div_angle = 360;
    for (int i = 0; i < TIME_LEN; i++) {
        div_angle *= cycles[i]/(1.0*max[i]);
        angle += time_diff->times[i]*div_angle;
    }
    if (angle < 0) {
        angle *= -1;
    }
    while (angle >= 360) {
        angle -= 360;
    }
    if (angle > 180) {
        angle = 360 - angle;
    }
    return angle;
}

int string_to_int(char *str, short max) {
    char *str_end;
    char msg[64];
    short v = strtol(str, &str_end, 10);
    if (*str_end != '\0') {
        error("Please ensure input argument is an integer");
    }
    if (v >= max) {
        sprintf(msg, "Please ensure input argument %i is less than %i", v, max);
        error(msg);
    }

    return v;
}

void get_time(union Time *t, char *str_time, short *max) {
    // Initialise the struct with all zeros
    *t = (union Time) {.times = {0, 0, 0}};

    const char sep[2] = ":";
    char* values;
    short count = 0;

    values = strtok(str_time, sep);
    while (values != NULL && count < 3) {
        t->times[count] = string_to_int(values, max[count]);
        values = strtok(NULL, sep);
        count++;
    }
}

int two_time(char **argv, short *max, short *cycles) {
    union Time start_time;
    union Time end_time;

    get_time(&start_time, argv[1], max);
    get_time(&end_time, argv[2], max);

    char str_buffer[TIME_LEN*3] = ""; // this assumes that each time unit has two digits and they are all followed by a colon (except the last which is followed by a \0)

    #ifdef DEBUG
    time_str(&start_time, str_buffer);
    printf("%s\n", str_buffer);
    time_str(&end_time, str_buffer);
    printf("%s\n", str_buffer);
    #endif

    union Time diff = time_diff(&start_time, &end_time, max);
    #ifdef DEBUG
    time_str(&diff, str_buffer);
    printf("%s\n", str_buffer);
    #endif
    printf("Angle between hour hands: %.4f degrees\n", get_angle(&diff, max, cycles));

    return 0;
}

int one_time(char **argv, short *max, short *cycles) {

}

int main(int argc, char **argv) {
    /* Maximum value of each element */
    short max[TIME_LEN] = {24, 60, 60};
    /* Number of cycles on the clock needed to reach the max value */
    short cycles[TIME_LEN] = {2, 1, 1};

    if (argc == 2) {

    } else if (argc == 3) {
        two_time(argv, max, cycles);
    } else {
        error("Please provide one time to find the angle between the minute and hour hands or two times to find the angle between the hour hands.");
    }

    
}