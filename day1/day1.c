#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

int compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

void part1(int *left_num, int *right_num, int entry_cnt);
void part2(int *left_num, int *right_num, int entry_size);

int main(void)
{
    printf("Advent of Code 2024 day one :)\n");
    // setup arrays
    int array_size = 50;
    int entry_cnt = 0;

    int *left_num = malloc(array_size * sizeof(int));
    int *right_num = malloc(array_size * sizeof(int));

    // open file
    FILE *fp = fopen("./input1.txt", "r");
    if (fp == NULL)
    {
        printf("error opening file!\n");
        return 1;
    }

    // setup to read line by line
    size_t buff_size = 256;
    ssize_t bytes;
    char *line_buff;

    // Setup to extract int from lines
    char *token = " ";
    char *tokenized;

    // read line by linw
    while ((bytes = getline(&line_buff, &buff_size, fp)) != EOF)
    {

        // bulk allocation for arrays
        if (entry_cnt + 1 > array_size)
        {
            array_size *= 2;
            left_num = (int *)realloc(left_num, array_size * sizeof(int));
            right_num = (int *)realloc(right_num, array_size * sizeof(int));
        }

        // extract int and save in array
        tokenized = strtok(line_buff, token);
        left_num[entry_cnt] = atoi(tokenized);
        tokenized = strtok(NULL, token);
        right_num[entry_cnt] = atoi(tokenized);
        entry_cnt++;
    }
    // realloc to correct size
    left_num = (int *)realloc(left_num, entry_cnt * sizeof(int));
    right_num = (int *)realloc(right_num, entry_cnt * sizeof(int));

    part1(left_num, right_num, entry_cnt);
    part2(left_num, right_num, entry_cnt);

    fclose(fp);

    return 0;
}

void part1(int *left_num, int *right_num, int entry_cnt)
{
    // sort arrays
    qsort(left_num, entry_cnt, sizeof(int), compare);
    qsort(right_num, entry_cnt, sizeof(int), compare);

    // calculate aboslute difference
    int difference = 0;
    for (int i = 0; i < entry_cnt; i++)
    {
        difference += abs(left_num[i] - right_num[i]);
    }
    printf("total distance is %d\n", difference);
}

void part2(int *left_num, int *right_num, int entry_size)
{
    // too lazy to implement my own hashmap :)

    // find max for array size
    int max = -1;
    for (int i = 0; i < entry_size; i++)
    {
        if (left_num[i] > max)
        {
            max = left_num[i];
        }
        if (right_num[i] > max)
        {
            max = right_num[i];
        }
    }

    // create  dictionary
    int *left_dic = malloc((max + 1) * sizeof(int));
    int *right_dic = malloc((max + 1) * sizeof(int));
    for (int i = 0; i < entry_size; i++)
    {
        left_dic[left_num[i]]++;
        right_dic[right_num[i]]++;
    }

    // calculate similiary score
    int sim_score = 0;
    for (int i = 0; i < max + 1; i++)
    {
        sim_score += left_dic[i] * right_dic[i] * i;
    }
    printf("similarity score is %d\n", sim_score);
}