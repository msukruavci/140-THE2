#include <stdio.h>
#include <stdlib.h>
int transform_name(const char *name) {
    int i, sum = 0;
    for (i = 0; name[i] != '\0'; i++)
        sum += (i + 1) * (i + 1) * ((int)name[i]);
    return sum;
}
int** initialize_storage(int IA_size, int DA_size, int** DA_sizes) {
    int **storage,i;
    *DA_sizes = (int *)malloc(IA_size * sizeof(int));
    storage = (int **)malloc(IA_size * sizeof(int *));
    for (i = 0; i < IA_size; i++) {
        storage[i] = (int *)calloc(DA_size, sizeof(int));
        (*DA_sizes)[i] = DA_size;
    }
    return storage;
}
void print_storage(int** storage, int IA_size, int* DA_sizes) {
    int i, j;
    for (i = 0; i < IA_size; i++) {
        printf("%d ->", i);
        for (j = 0; j < DA_sizes[i]; j++)
            printf(" %d", storage[i][j]);
        printf("\n");
    }
}
void insert(int** storage, int IA_size, const char* name, int* DA_sizes) {
    int * new_DA,name_code, index, current_DA_size, i, new_DA_size;

    name_code = transform_name(name);
    index = name_code % IA_size;
    current_DA_size = DA_sizes[index];

    for (i = 0; i < current_DA_size; i++) {
        if (storage[index][i] == 0) {
            storage[index][i] = name_code;
            return;
        }
    }
    new_DA_size = current_DA_size * 2;
    new_DA = (int*)malloc(new_DA_size * sizeof(int));
    for (i = 0; i < new_DA_size; i++) {
        if (i < current_DA_size) {
            new_DA[i] = storage[index][i];
        } else {
            new_DA[i] = 0;
        }
    }
    free(storage[index]);
    storage[index] = new_DA;
    storage[index][current_DA_size] = name_code;
    DA_sizes[index] = new_DA_size;
}
void insert2(int** storage, int IA_size, int name_code, int* DA_sizes) {
    int * new_DA,index, current_DA_size, new_DA_size, i;
    index = name_code % IA_size;
    current_DA_size = DA_sizes[index];
    for (i = 0; i < current_DA_size; i++) {
        if (storage[index][i] == 0) {
            storage[index][i] = name_code;
            return;
        }
    }
    new_DA_size = current_DA_size * 2;
    new_DA = (int*)malloc(new_DA_size * sizeof(int));
    for (i = 0; i < new_DA_size; i++) {
        if (i < current_DA_size) {
            new_DA[i] = storage[index][i];
        } else {
            new_DA[i] = 0;
        }
    }
    free(storage[index]);
    storage[index] = new_DA;
    storage[index][current_DA_size] = name_code;
    DA_sizes[index] = new_DA_size;
}
void fill_new_storage(int** storage, int IA_size, int** new_storage, int* new_DA_sizes) {
    int * old_DA_sizes,new_IA_size, i, j, DA_size;
    new_IA_size = IA_size * 2;
    old_DA_sizes = (int*)malloc(sizeof(int) * IA_size);
    for (i = 0; i < IA_size; i++) {
        old_DA_sizes[i] = new_DA_sizes[i];
    }
    DA_size = new_DA_sizes[i];
    for (i = 0; i < new_IA_size; i++){
        new_DA_sizes[i] = DA_size;
    }
    for (i = 0; i < IA_size; i++) {
        for (j = 0; j < old_DA_sizes[i]; j++) {
            if (storage[i][j] != 0) {
                insert2(new_storage, new_IA_size, storage[i][j], new_DA_sizes);
            }
        }
    }
    free(old_DA_sizes);
}
void resize_IA(int*** storage, int* IA_size, int DA_size, int** DA_sizes) {
    int ** new_storage,* new_DA_sizes,i, total_data_size = 0, new_IA_size;
    for (i = 0; i < *IA_size; i++) {
        total_data_size += (*DA_sizes)[i];
    }
    if (total_data_size >= (*IA_size * DA_size * 1.5)) {
        new_IA_size = *IA_size * 2;
        new_storage = initialize_storage(new_IA_size, DA_size, &new_DA_sizes);
        for (i = 0; i < *IA_size; i++) {
            new_DA_sizes[i] = (*DA_sizes)[i];
        }
        for(i = *IA_size ; i < new_IA_size; i++){
            new_DA_sizes[i] = DA_size;
        }
        fill_new_storage(*storage, *IA_size, new_storage, new_DA_sizes);

        for (i = 0; i < *IA_size; i++) {
            free((*storage)[i]);
        }
        free(*storage);
        free(*DA_sizes);
        *DA_sizes = new_DA_sizes;
        *storage = new_storage;
        *IA_size = new_IA_size;
    }
}