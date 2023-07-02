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

void trimLeadingTrailingSpaces(char* str) {
    int i = 0;
    while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n') {
        i++;
    }
    int j = strlen(str) - 1;
    while (j >= i && (str[j] == ' ' || str[j] == '\t' || str[j] == '\n')) {
        j--;
    }
    str[j + 1] = '\0';
}

int isPrime(unsigned long long num) {
    if (num < 2) {
        return 0;
    }
    if (num < 4) {
        return 1;
    }
    if (num % 2 == 0 || num % 3 == 0) {
        return 0;
    }
    unsigned long long limit = (unsigned long long)_sqrt(num);
    for (unsigned long long i = 5; i <= limit; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0) {
            return 0;
        }
    }
    return 1;
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
        while (isspace(line[i])) {
            i++;
        }
        int j = strlen(line) - 1;
        while (j >= i && isspace(line[j])) {
            j--;
        }
        line[j + 1] = '\0';

        // Validate the line as a natural number
        char* endptr;
        unsigned long long num = strtoull(&line[i], &endptr, 10);
        if (*endptr != '\0') {
            printf("Invalid number: %s\n", line);
            continue;
        }
        if (num <= 1) {
            printf("Invalid number: %llu\n", num);
            continue;
        }

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

