#include <stdlib.h>
#include <stdio.h>
#include "student.h"
int cmpStudent(const struct Student *pA, const struct Student *pB)
{
    return strncmp(pA->name, pB->name, sizeof(pA->name));
}

void writeStudent(const struct Student *pRecord)
{
    printf("%s has a score of %d\n",pRecord->name, pRecord->score);
}

int main(void)
{
    struct Student class[MAXSTUDENT];
    int i;

    for (i = 0; (i < MAXSTUDENT) && readStudent(&class[i]); ++i);
    selSort(class, i);
    while (i > 0)
    {
        writeStudent(&class[--i]);
    }
    return 0;
}
