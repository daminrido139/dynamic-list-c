#include <stdio.h>
#include <stdlib.h>

#define INIT_SIZE 2

typedef struct
{
    size_t capacity;
    size_t size;
    int *array;
} DynamicList;

DynamicList *create_list();
void insert(DynamicList *arr_ptr, int num);
void display(DynamicList *arr);
void delete_at(DynamicList *arr, size_t index);
void free_list(DynamicList *arr);

int main()
{
    DynamicList *array = create_list();
    printf("\n# Inserting elements\n\n");
    for (int i = 1; i <= 20; ++i)
    {
        insert(array, i * 10);
        display(array);
    }
    printf("\n# Deleting 2 elements from the beginning\n\n");
    for (int i = 0; i < 2; ++i)
    {
        delete_at(array, 0);
        display(array);
    }

    printf("\n# Freeing the list\n\n");
    free_list(array);
    array = NULL;
    return 0;
}

DynamicList *create_list()
{
    DynamicList *temp = (DynamicList *)malloc(sizeof(DynamicList));
    if (temp == NULL)
    {
        printf("Memory Allocation failed!");
        exit(1);
    }
    temp->array = (int *)malloc(sizeof(int) * INIT_SIZE);
    if (temp->array == NULL)
    {
        printf("Memory Allocation failed!");
        free_list(temp);
        exit(1);
    }
    temp->capacity = INIT_SIZE;
    temp->size = 0;
    return temp;
}

void insert(DynamicList *arr, int num)
{
    if (arr == NULL)
        return;
    if (arr->size == arr->capacity)
    {
        arr->capacity <<= 1;
        int *temp = (int *)realloc(arr->array, sizeof(int) * arr->capacity);
        if (temp == NULL)
        {
            printf("Memory Allocation failed!");
            free_list(arr);
            exit(1);
        }
        arr->array = temp;
    }
    arr->array[arr->size++] = num;
}

void display(DynamicList *arr)
{
    if (arr == NULL)
        return;
    for (size_t i = 0; i < arr->size; ++i)
    {
        printf("%d ", arr->array[i]);
    }
    printf("\n");
}

void delete_at(DynamicList *arr, size_t index)
{
    if (arr == NULL || index >= arr->size)
        return;
    for (size_t i = index + 1; i < arr->size; ++i)
        arr->array[i - 1] = arr->array[i];
    --(arr->size);
}

void free_list(DynamicList *arr)
{
    if (arr == NULL)
        return;
    if (arr->array != NULL)
        free(arr->array);
    free(arr);
}