#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <limits.h>
typedef struct thread_data {    
     short m1_row;       
     short m1_col;        
     short m2_col;       
     int **matrix1;         
     int **matrix2;        
     int **result;        
     short cur_row;
    }Thread_data_t; 
void *thread_matrix(void *arg) {
    Thread_data_t *data = (Thread_data_t *)arg;
    
    for(int i = 0; i < data->m2_col; i++) {
        int result = 0;
        for (int j = 0; j < data->m2_col; j++) {
            result += data->matrix1[data->cur_row][j] * data->matrix2[j][i];
        }
        // Store the result in the result matrix
        data->result[data->cur_row][i] = result;
    }
    pthread_exit(NULL);
    return NULL;
}

int main(){

    int m1_row, m1_col, m2_row, m2_col;
    printf("Enter the number of rows and columns for the first matrix: ");
    scanf("%d %d", &m1_row, &m1_col);
    printf("Enter the number of rows and columns for the second matrix: ");
    scanf("%d %d", &m2_row, &m2_col);
    if (m1_col != m2_row) {
        printf("Matrix multiplication not possible.\n");
        return 1;
    }
    int **matrix1, **matrix2, **result;
    matrix1 = (int **)malloc(m1_row * sizeof(int *));
    matrix2 = (int **)malloc(m2_row * sizeof(int *));
    result = (int **)malloc(m1_row * sizeof(int *));
    for (int i = 0; i < m1_row; i++) {
        matrix1[i] = (int *)malloc(m1_col * sizeof(int));
    }
    for (int i = 0; i < m2_row; i++) {
        matrix2[i] = (int *)malloc(m2_col * sizeof(int));
    }
    for (int i = 0; i < m1_row; i++) {
        result[i] = (int *)malloc(m2_col * sizeof(int));
        for (int j = 0; j < m2_col; j++) {
            result[i][j] = 0; // Initialize result matrix
        }
    }

    printf("Enter elements of the first matrix:\n");
    for (int i = 0; i < m1_row; i++) {
        for (int j = 0; j < m1_col; j++) {
            scanf("%d", &matrix1[i][j]);
        }
    }
    printf("Enter elements of the second matrix:\n");
    for (int i = 0; i < m2_row; i++) {
        for (int j = 0; j < m2_col; j++) {
            scanf("%d", &matrix2[i][j]);
        }
    }

    pthread_t threads[m1_row];
    Thread_data_t thread_data[m1_row];
    for (int i = 0; i < m1_row; i++) {
        thread_data[i].m1_row = i;
        thread_data[i].m1_col = m1_col;
        thread_data[i].m2_col = m2_col;
        thread_data[i].matrix1 = (int **)matrix1;
        thread_data[i].matrix2 = (int **)matrix2;
        thread_data[i].result = (int **)result;
        thread_data[i].cur_row = i;

        pthread_create(&threads[i], NULL, thread_matrix, (void *)&thread_data[i]);
    }
    for (int i = 0; i < m1_row; i++) {
        pthread_join(threads[i], NULL);
    }
    printf("Resultant matrix:\n");
    for (int i = 0; i < m1_row; i++) {
        for (int j = 0; j < m2_col; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }
    // Free allocated memory
    for (int i = 0; i < m1_row; i++) {
        free(matrix1[i]);
    }
    for (int i = 0; i < m2_row; i++) {
        free(matrix2[i]);
    }
    for (int i = 0; i < m1_row; i++) {
        free(result[i]);
    }
    free(matrix1);
    free(matrix2);
    free(result);
    return 0;
    

}