/* DO NOT CHANGE THIS FILE */

#include<stdio.h>
#include<stdlib.h>

int transform_name(const char *name);

int** initialize_storage(int IA_size, int DA_size, int** DA_sizes);

void print_storage(int** storage, int IA_size, int* DA_sizes);

void insert(int** storage, int IA_size, const char* name, int* DA_sizes);

void insert2(int** storage, int IA_size, int name_code, int* DA_sizes);

void fill_new_storage(int** storage, int IA_size, int** new_storage, int *DA_sizes, int* new_DA_sizes);

void resize_IA(int*** storage, int* IA_size, int DA_size, int** DA_sizes);
