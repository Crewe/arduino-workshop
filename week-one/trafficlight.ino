#define FOUR_WAY 4
#define MAX_LIGHTS 4
#define GREEN_LIGHT 0
#define YELLOW_LIGHT 1
#define RED_LIGHT 2
#define PED_LIGHT 3

int array[FOUR_WAY][MAX_LIGHTS] = {{1, 2, 3, 4 },{5, 6, 7, 8},{9, 10, 11, 12},{13, 14, 15, 16}};

void printAll(int *array)
{
    int(*x)[MAX_LIGHTS] = array;
    for (; x != array + MAX_LIGHTS; ++x)
    {
        for (int *y = *x; y != *x + FOUR_WAY; ++y)
        {
            printf("%d\n", *y);
        }
    }
}

void printCol(int *array, int col)
{
    int *a = array + col;
    while (a != array + col + (MAX_LIGHTS * FOUR_WAY)) {
        printf("%d\n", *a);
        a += 4;
    }
}

int main()
{
    printAll(&array);
    printf("-----\n");
    printCol(&array, GREEN_LIGHT);
    printf("-----\n");
    printCol(&array, RED_LIGHT);

    return 0;
}