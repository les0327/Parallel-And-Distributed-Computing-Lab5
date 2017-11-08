//
// Created by Foresstt on 28-Oct-17.
//

#include "functions.h"
#include <stdio.h>
#include <limits.h>

#define n   3
#define nxn 9

const int num = 1;

void printVector(int *A) {
    for (int i = 0; i < n; i++)
        printf("%d ", A[i]);
    printf("\n");
}

void printMatrix(int *A) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%d ", A[i*n + j]);
        printf("\n");
    }
    printf("\n");
}

void fillVector(int num, int *A) {
    for (int i = 0; i < n; i++)
        A[i] = num;
}

void fillMatrix(int num, int *A) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            A[i*n + j] = num;
}

/**
 * Multiplication matrix A and B
 * @param A - matrix
 * @param B - matrix
 * @param C=A*B - matrix
 */
int * matrixMultiplication(int *A, int *B) {
    static int C[nxn];
    int buf;
    for (int i = 0; i < n; i++ ) {
        for (int j = 0; j < n; j++) {
            buf = 0;
            for (int k = 0; k < n; k++) {
                buf += A[i*n + k] * B[k*n + j];
            }
            C[i*n + j] = buf;
        }
    }
    return C;
}

/**
 * Multiplication vector A with matrix B
 * @param A - vector
 * @param B - matrix
 * @param C=A*B - vector
 */
int * vectorMatrixMultiplication(int *A, int *B) {
    static int C[n];
    int buf;
    for (int i = 0; i < n; i++ ) {
        buf = 0;
        for (int j = 0; j < n; j++) {
            buf += A[j] * B[j*n + i];
        }
        C[i] = buf;
    }
    return C;
}

/**
 * Calculate scalar of A with B
 * @param A - vector
 * @param B - vector
 * @param scalar=A*B - number
 */
int scalar(int *A, int *B) {
    int scalar = 0;
    for (int i = 0; i < n; i++) {
        scalar += A[i] * B[i];
    }
    return scalar;
}


/**
 * Add matrix A and B
 * @param A - matrix
 * @param B - matrix
 * @param C=A+B
 */
int * matrixAddition(int *A, int *B) {

    static int C[nxn];
    for (int i = 0; i < n; i++ ) {
        for (int j = 0; j < n; j++) {
            C[i*n + j] = A[i*n + j] + B[i*n + j];
        }
    }
    return C;
}

/**
 * Multiplication vector A with number num
 * @param num
 * @param A
 * @param B=num*A - vector
 */
int * numberVectorMultiplication(int num, int *A) {
    static int B[n];
    for (int i = 0; i < n; i++)
        B[i] = A[i] * num;
    return B;
}

/**
 * Find max element from matrix
 * @param A - matrix
 * @param max element
 */
int matrixMax(int *A) {
    int max = INT_MIN;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (A[i*n + j] > max)
                max = A[i*n + j];
    return max;
}

/**
 * Sort matrix A
 * @param A - matrix
 */
int * matrixSort(int *A) {
    int index = 0;
    int max   = 0;
    for (int line = 0; line < n; line++) {
        for (int i = 0; i < n; i++) {
            index = i;
            max   = A[line*n + i];
            for (int j = i + 1; j < n; j++) {
                if (A[line*n + j] > max) {
                    index = j;
                    max   = A[line*n + j];
                }
            }
            A[line*n + index] = A[line*n + i];
            A[line*n + i]     = max;
        }
    }
    return A;
}

/**
  * F1: e = (A*B) + (C*(D*(MA*MD)))
  */
void threadFunction1() {
    printf("Thread1 start\n");
    int MA[nxn];
    int MD[nxn];
    int a[n];
    int b[n];
    int c[n];
    int d[n];

    fillVector(num, a);
    fillVector(num, b);
    fillVector(num, c);
    fillVector(num, d);
    fillMatrix(num, MA);
    fillMatrix(num, MD);

    int e = scalar(a, b) + scalar(c, vectorMatrixMultiplication(b, matrixMultiplication(MA, MD)));

    if (n < 7) {
        printf("T1: e = %d\n", e);
    }

    printf("Thread1 finish\n");
}

/**
  * F2: ML = SORT(MF + MG*MH)
  */
void threadFunction2() {
    printf("Thread2 start\n");
    int MF[nxn];
    int MG[nxn];
    int MH[nxn];

    fillMatrix(num, MF);
    fillMatrix(num, MG);
    fillMatrix(num, MH);

    int *ML = matrixSort(matrixAddition(MF, matrixMultiplication(MG, MH)));

    if (n < 7) {
        printf("T2: ML =\n");
        printMatrix(ML);
    }


    printf("Thread2 finish\n");
}

/**
  * F3: O = MAX(MP*MR)*T
  */
void threadFunction3() {
    printf("Thread3 start\n");
    int MP[nxn];
    int MR[nxn];
    int T[n];

    fillMatrix(num, MP);
    fillMatrix(num, MR);
    fillVector(num, T);

    int *O = numberVectorMultiplication(matrixMax(matrixMultiplication(MP, MR)), T);

    if (n < 7) {
        printf("T3: O = ");
        printVector(O);
    }

    printf("Thread3 finish\n");
}