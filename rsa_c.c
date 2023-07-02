#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double custom_sqrt(double x) {
    double result = x;  // Initial approximation
    double epsilon = 0.000001;  // Desired precision

    while (fabs(result * result - x) > epsilon) {
        result = (result + x / result) / 2.0;
    }

    return result;
}

void factorize_numbers(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file: %s\n", filename);
        return;
    }

    char buffer[100];
    while (fgets(buffer, sizeof(buffer), file)) {
        int number = atoi(buffer);
        int p = 2;

        while (p <= custom_sqrt(number)) {
            if (number % p == 0) {
                int q = number / p;
                printf("%d=%d*%d\n", number, p, q);
                break;
            }
            p++;
        }
    }

    fclose(file);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        return 1;
    }

    const char* filename = argv[1];
    factorize_numbers(filename);

    return 0;
}

