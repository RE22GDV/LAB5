#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define input_filename "lr5_in.txt"
#define output_filename_txt "lr5_out.txt"
#define output_filename_bin "lr5_out.bin"

double expression(double x);

void files_output(double x1, double x2, int N, char group[20], char surname_name[50]);

void open_binary(char group[20], char surname_name[50]);

void print_answer(double *a, int N, char group[20], char surname_name[50]);


int main() {
    double x1, x2, delta;
    char group[20];
    char surname_name[50];
    int N;

    FILE *input_file;
    input_file = fopen(input_filename, "r");
    if (input_file == NULL) {
        printf("Error");
    } else {
        fscanf(input_file, "%lf", &x1);
        fscanf(input_file, "%lf", &x2);
        fscanf(input_file, "%d", &N);
        fscanf(input_file, "%lf\n", &delta);
        fgets(group, 20, input_file);
        fgets(surname_name, 50, input_file);
        files_output(x1, x2, N, group, surname_name);
        open_binary(group, surname_name);
    }
    fclose(input_file);
    return 0;
}


double expression(double x) { return (pow((x + 125), 3)) - 45 * x - 18; }

void files_output(double x1, double x2, int N, char group[20], char surname_name[50]) {
    double delta, k;
    FILE *output_file_txt;
    FILE *output_file_bin;
    output_file_txt = fopen(output_filename_txt, "w");
    output_file_bin = fopen(output_filename_bin, "w+b");
    if (output_file_txt == NULL || output_file_bin == NULL) {
        printf("Error");
    } else {
        delta = (x2 - x1) / (N - 1);

        fwrite(&N, sizeof(int), 1, output_file_bin);

        fprintf(output_file_txt, "\n+-------------------+\n");
        fprintf(output_file_txt, "|N|\t |x|\t|F(x)|");
        fprintf(output_file_txt, "\n+-------------------+\n");

        for (int n1 = 1; n1 != N + 1; n1++) {
            k = expression(x1);

            fprintf(output_file_txt, "|%d\t", n1);

            fprintf(output_file_txt, "|%.2f\t", x1);
            fwrite(&x1, sizeof(double), 1, output_file_bin);

            fprintf(output_file_txt, "|%.2f|\n", k);
            fwrite(&k, sizeof(double), 1, output_file_bin);

            fprintf(output_file_txt, "\n+-------------------+\n");
            x1 = x1 + delta;
        }
        fprintf(output_file_txt, "%s%s", group, surname_name);
        fclose(output_file_txt);
        fclose(output_file_bin);
    }
}


void open_binary(char group[20], char surname_name[50]) {
    int N = 0;
    double num = 0, *a;
    FILE *input_file_bin;
    input_file_bin = fopen(output_filename_bin, "r+b");
    if (input_file_bin == NULL) {
        printf("Error");
    } else {
        fread(&N, sizeof(int), 1, input_file_bin);

        int n = 2 * N;
        a = (double *) malloc(n * sizeof(double));
        for (int i = 0; i < n; i = i + 2) {
            fread(&num, sizeof(double), 1, input_file_bin);
            a[i] = num;

            fread(&num, sizeof(double), 1, input_file_bin);
            a[i + 1] = num;
        }
        fclose(input_file_bin);
        print_answer(a, N, group, surname_name);
        free(a);
    }
}

void print_answer(double *a, int N, char group[20], char surname_name[50]) {
    printf("\n**************************"
           "\n*  N  *  X  *  F(X)   *"
           "\n**************************"
           "\n+-----+-----+------------+");
    for (int i = 0; i < (2 * N); i = i + 2) {
        printf("\n|  %d  |%.2f  |%.2f |", (i / 2) + 1, a[i], a[i + 1]);
        printf("\n+-----+-----+------------+");
    }
    printf("\n%s%s", group, surname_name);

}