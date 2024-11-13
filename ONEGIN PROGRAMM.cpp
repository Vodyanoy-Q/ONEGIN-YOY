#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

struct str_info
{
    const char * str;
    size_t len;
};

size_t GetFileSize(FILE * ONEGIN);
int StrCounter(char * text, size_t symbols);
void GetStrAddres(char * text, size_t symbols, str_info * str_data, str_info ** str_data_addres);
void BubbleSort(void ** data_addres, const int addres_data_size, int Comparator(void * data_1, void * data_2));
int StrComparator(void * addres_1, void * addres_2);
int ReverseStrComparator(void * addres_1, void * addres_2);

int main()
{
    FILE * ONEGIN = fopen("ONEGIN.txt", "rb");

    assert(ONEGIN);

    size_t symbols = GetFileSize(ONEGIN);

    char * text = (char*)calloc(symbols + 1, sizeof(char));

    fread((void*)text, sizeof(char), symbols, ONEGIN);

    assert(fclose(ONEGIN) == 0);

    const int str_counter = StrCounter(text, symbols);

    str_info * str_data = (str_info*)calloc(str_counter + 1, sizeof(str_info));
    str_info ** str_data_addres = (str_info**)calloc(str_counter + 1, sizeof(str_info*));

    GetStrAddres(text, symbols, str_data, str_data_addres);

//    for(int i = 0; i < str_counter; i++)
//    {
//        printf("%d %s\n", str_data[i].len, str_data[i].str);
//    }

    printf("=============\n"
           "ORIGINAL TEXT\n"
           "=============\n");

    for(int i = 0; i <= str_counter - 1; i++)
    {
        printf("%s\n", (*str_data_addres[i]).str);
    }

    printf("=============\n"
           " SORTED TEXT\n"
           "=============\n");
    BubbleSort((void**)str_data_addres, str_counter, StrComparator);

    free(text);
    free(str_data_addres);
    free(str_data);

    return 0;
}

size_t GetFileSize(FILE * ONEGIN)
{
    assert(ONEGIN);

    fseek(ONEGIN, 0L, SEEK_END);

    size_t symbols = ftell(ONEGIN);

    rewind(ONEGIN);

    return symbols;
}

int StrCounter(char * text, size_t symbols)
{
    assert(text);

    int counter = 0;

    size_t i = 0;

    for (i = 0; i < symbols; i++)
    {
        if (text[i] == '\r')
        {
            text[i] = '\0';
            text[i + 1] = '\0';
            counter++;
        }
    }

    return counter;
}

void GetStrAddres(char * text, size_t symbols, str_info * str_data, str_info ** str_data_addres)
{
    assert(text);
    assert(str_data);

    int str_counter = 0;

    str_info data = {(const char*)text, strlen((const char*)text)};

    str_data[0] = data;

    str_data_addres[0] = &str_data[0];

    for(size_t i = 0; i < symbols; i++)
    {
        if (text[i] == '\0')
        {
            data = {(const char*)(text + i + 2), strlen((const char*)(text + i + 2))};

            str_counter += 1;

            str_data[str_counter] = data;

            str_data_addres[str_counter] = &str_data[str_counter];

            i++;
        }
    }
}

void BubbleSort(void ** data_addres, const int addres_data_size, int Comparator(void * data_1, void * data_2))
{
    assert(data_addres);

    void * switcher = 0;

    for(int j = 0; j < addres_data_size - 1; j++)
    {
        for(int i = 0; i < addres_data_size - 1; i++)
        {
            if (Comparator(data_addres[i], data_addres[i + 1]) > 0)
            {
                assert(data_addres[i]);
                assert(data_addres[i + 1]);

                switcher = data_addres[i + 1];

                data_addres[i + 1] = data_addres[i];

                data_addres[i] = switcher;
            }
        }
    }

    for(int i = 0; i <= addres_data_size - 1; i++)
    {
        printf("%s\n", (*(str_info*)(data_addres[i])).str);
    }
}

int StrComparator(void * addres_1, void * addres_2)
{
    assert(addres_1);
    assert(addres_2);

    size_t i = 0;
    size_t j = 0;

    str_info str_data_1 = *(str_info*)addres_1;
    str_info str_data_2 = *(str_info*)addres_2;

    /*while (!isalpha(str_data_1.str[i]))
    {
        i++;
    }


    while (!isalpha(str_data_2.str[j]))
    {
        j++;
    }

    while (str_data_1.str[i] == str_data_2.str[j])
    {
        i++;
        j++;
    }   */

    while(1)
    {
        assert(str_data_1.str[i]);       //             СЁ
        assert(str_data_2.str[j]);

        if(i == str_data_1.len)
        {
            return 0;
        }

        if(j == str_data_2.len)
        {
            return 1;
        }

        if (!isalpha(str_data_1.str[i]))
        {
            i++;
            continue;
        }

        if (!isalpha(str_data_2.str[j]))
        {
            j++;
            continue;
        }

        if (tolower(str_data_1.str[i]) == tolower(str_data_2.str[j]))
        {
            i++;
            j++;
            continue;
        }

        if (tolower(str_data_1.str[i]) > tolower(str_data_2.str[j]))
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    return 0;
}

int ReverseStrComparator(void * addres_1, void * addres_2)
{
    assert(addres_1);
    assert(addres_2);

    str_info str_data_1 = *(str_info*)addres_1;
    str_info str_data_2 = *(str_info*)addres_2;


    size_t i = str_data_1.len - 1;
    size_t j = str_data_2.len - 1;


    while(1)
    {
        assert(str_data_1.str[i]);       //             СЁ
        assert(str_data_2.str[j]);                                        //

        if(i == 0)
        {
            return 0;
        }

        if(j == 0)
        {
            return 1;
        }

        if (!isalpha(str_data_1.str[i]))
        {
            i--;
            continue;
        }

        if (!isalpha(str_data_2.str[j]))
        {
            j--;
            continue;
        }

        if (tolower(str_data_1.str[i]) == tolower(str_data_2.str[j]))
        {
            i--;
            j--;
            continue;
        }

        if (tolower(str_data_1.str[i]) > tolower(str_data_2.str[j]))
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    return 0;
}

