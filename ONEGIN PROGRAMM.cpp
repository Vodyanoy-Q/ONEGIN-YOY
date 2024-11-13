#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void ArraysCount(int * arr_count, int * symbols_counter);
void MaxArraySize(int * arr_count, int * max_arr_size);
void GetText(char * text, int * symbols_counter);
void GetArrayAddres(char * text, int * array_addres, int * symbols_counter);

int main()
{
    int arr_count = 0;
    int max_arr_size = 0;
    int symbols_counter = 0;

    ArraysCount(&arr_count, &symbols_counter);

    int * array_addres = (int*)calloc(arr_count, sizeof(int));

    MaxArraySize(&arr_count, &max_arr_size);

    char * text = (char*)calloc(symbols_counter, sizeof(char));
    char * sorted_text = (char*)calloc(symbols_counter, sizeof(char));

    GetText(text, &symbols_counter);
    GetArrayAddres(text, array_addres, &symbols_counter);

    for (int i = 0; i < arr_count; i++)
    {
        printf("%d\n", array_addres[i]);
    }

    for (int i = 0; i < symbols_counter; i++)
    {
        printf("%c", text[i]);
    }

    return 0;
}

void ArraysCount(int * arr_count, int * symbols_counter)
{
    assert(arr_count);

    FILE * ONEGIN = fopen("ONEGIN.txt", "r");  //w

    int ch = 0;

    do
    {
        ch = getc(ONEGIN);

        if (ch == '\n' || ch == EOF)
        {
            * arr_count = * arr_count + 1;
        }
        * symbols_counter = * symbols_counter + 1;
    }
    while (ch != EOF);

    fclose(ONEGIN);
}

void MaxArraySize(int * arr_count, int * max_arr_size)
{
    assert(arr_count);
    assert(max_arr_size);

    FILE * ONEGIN = fopen("ONEGIN.txt", "r");

    int ch = 0;
    int slash_n_counter = 0;

    do
    {
        ch = getc(ONEGIN);

        if (ch == '\n' || ch == EOF)
        {
            if (slash_n_counter > * max_arr_size)
            {
                * max_arr_size = slash_n_counter;
            }
            slash_n_counter = 0;
        }
        else
        {
            slash_n_counter++;
        }
    }
    while(ch != EOF);

    fclose(ONEGIN);
}

void GetText(char * text, int * symbols_counter)
{
    assert(text);
    assert(symbols_counter);

    FILE * ONEGIN = fopen("ONEGIN.txt", "r");

    for(int i = 0; i < * symbols_counter; i++)
    {
        text[i] = getc(ONEGIN);
    }
    fclose(ONEGIN);
}

void GetArrayAddres(char * text, int * array_addres, int * symbols_counter)
{
    assert(text);

    int slash_n_counter = 0;
    int addres_counter = 1;

    array_addres[0] = int(text);

    for(int i = 0; i < * symbols_counter; i++)
    {
        if (text[i] == '\n')
        {
            array_addres[addres_counter] = (int(text) + slash_n_counter * sizeof(char));
            slash_n_counter++;
            addres_counter++;
        }
        else
        {
            slash_n_counter++;
        }
    }
}
