#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define SIZE 4

void print_matrix(int matrix[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int matrix1[SIZE][SIZE] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };

    int matrix2[SIZE][SIZE] = {
        {16, 15, 14, 13},
        {12, 11, 10, 9},
        {8, 7, 6, 5},
        {4, 3, 2, 1}
    };

    int result[SIZE][SIZE] = {0};

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork gagal");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Proses anak: Lakukan perkalian matriks
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < SIZE; k++) {
                    result[i][j] += matrix1[i][k] * matrix2[k][j];
                }
            }
        }
        exit(EXIT_SUCCESS); // Keluar dari proses anak setelah perhitungan selesai
    } else {
        // Proses induk: Tunggu proses anak selesai
        wait(NULL);

        // menampilkan hasil perkalian matriks
        print_matrix(result);
    }

    return 0;
}
