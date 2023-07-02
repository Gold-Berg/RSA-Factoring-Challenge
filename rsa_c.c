#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

double _sqrt(double x) {
    if (x < 0) {
        return -1.0; // Invalid input, return -1
    }

    if (x == 0 || x == 1) {
        return x; // Square root of 0 or 1 is the number itself
    }

    double precision = 1e-6; // Adjust the precision as needed
    double guess = x / 2; // Initial guess is half of x

    // Perform iterative approximation using Babylonian method
    while (fabs(guess * guess - x) > precision) {
        guess = 0.5 * (guess + x / guess);
    }

    return guess;
}

void factorize(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file: %s\n", filename);
        return;
    }

    char line[20];
    while (fgets(line, sizeof(line), file)) {
        // Trim leading and trailing white spaces
        int i = 0;
        while (line[i] == ' ' || line[i] == '\t' || line[i] == '\n') {
            i++;
        }
        int j = strlen(line) - 1;
        while (j >= i && (line[j] == ' ' || line[j] == '\t' || line[j] == '\n')) {
            j--;
        }
        line[j + 1] = '\0';

        // Convert the line to a number
        unsigned long long num = strtoull(&line[i], NULL, 10);

        // Factorize the number
        unsigned long long factor = 2;
        while (factor * factor <= num) {
            if (num % factor == 0) {
                printf("%llu=%llu*%llu\n", num, factor, num / factor);
                break;
            }
            factor++;
        }

        if (factor * factor > num) {
            printf("%llu is a prime number\n", num);
        }
    }

    fclose(file);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <file>\n", argv[0]);
        return 1;
    }

    factorize(argv[1]);

    return 0;
}
