#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    CELSIUS,
    FAHRENHEIT,
    KELVIN
} Unit;

static int parse_unit(const char *text, Unit *unit) {
    if (strcmp(text, "C") == 0 || strcmp(text, "c") == 0) {
        *unit = CELSIUS;
        return 1;
    }
    if (strcmp(text, "F") == 0 || strcmp(text, "f") == 0) {
        *unit = FAHRENHEIT;
        return 1;
    }
    if (strcmp(text, "K") == 0 || strcmp(text, "k") == 0) {
        *unit = KELVIN;
        return 1;
    }
    return 0;
}

static double to_kelvin(double value, Unit unit) {
    if (unit == CELSIUS) return value + 273.15;
    if (unit == FAHRENHEIT) return (value - 32.0) * 5.0 / 9.0 + 273.15;
    return value;
}

static double from_kelvin(double value, Unit unit) {
    if (unit == CELSIUS) return value - 273.15;
    if (unit == FAHRENHEIT) return (value - 273.15) * 9.0 / 5.0 + 32.0;
    return value;
}

static const char *unit_symbol(Unit unit) {
    if (unit == CELSIUS) return "C";
    if (unit == FAHRENHEIT) return "F";
    return "K";
}

int main(int argc, char **argv) {
    char *end = NULL;
    double input;
    Unit from;
    Unit to;

    if (argc != 4) {
        fprintf(stderr, "Usage: %s <temperature> <from: C|F|K> <to: C|F|K>\n", argv[0]);
        return 1;
    }

    errno = 0;
    input = strtod(argv[1], &end);
    if (errno != 0 || end == argv[1] || *end != '\0' || !isfinite(input)) {
        fprintf(stderr, "Error: temperature must be a finite number.\n");
        return 1;
    }
    if (!parse_unit(argv[2], &from) || !parse_unit(argv[3], &to)) {
        fprintf(stderr, "Error: units must be C, F, or K.\n");
        return 1;
    }

    if (input < -273.15 && from == CELSIUS) {
        fprintf(stderr, "Error: temperature is below absolute zero.\n");
        return 1;
    }
    if (input < -459.67 && from == FAHRENHEIT) {
        fprintf(stderr, "Error: temperature is below absolute zero.\n");
        return 1;
    }
    if (input < 0.0 && from == KELVIN) {
        fprintf(stderr, "Error: temperature is below absolute zero.\n");
        return 1;
    }

    printf("%.2f %s\n", from_kelvin(to_kelvin(input, from), to), unit_symbol(to));
    return 0;
}