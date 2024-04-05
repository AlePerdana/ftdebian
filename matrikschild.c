#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#define SIZE 4

// Fungsi untuk melakukan perkalian matriks
void multiply_matrices(int mat1[SIZE][SIZE], int mat2[SIZE][SIZE], int result[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            result[i][j] = 0;
            for (int k = 0; k < SIZE; k++) {
                result[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
}

int main(void) {
    pid_t child_pid;
    int status;
    pid_t wait_result;

    // Inisialisasi matriks
    int mat1[SIZE][SIZE] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };

    int mat2[SIZE][SIZE] = {
        {16, 15, 14, 13},
        {12, 11, 10, 9},
        {8, 7, 6, 5},
        {4, 3, 2, 1}
    };

    int result[SIZE][SIZE];

    // Membuat proses anak
    child_pid = fork();

    if (child_pid == 0) { // Proses anak
        // Melakukan perkalian matriks
        multiply_matrices(mat1, mat2, result);
        printf("Hasil perkalian matriks:\n");
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                printf("%d ", result[i][j]);
            }
            printf("\n");
        }
        exit(0); // Keluar dari proses anak
    } else if (child_pid > 0) { // Proses induk
        // Menunggu proses anak selesai
        wait_result = wait(&status);
        if (wait_result == child_pid) {
            printf("Proses anak selesai dengan status %d\n", WEXITSTATUS(status));
        } else {
            printf("Proses anak tidak ditemukan\n");
        }
    } else { // Jika fork gagal
        printf("Gagal membuat proses anak\n");
        return 1;
    }

    return 0;
}
