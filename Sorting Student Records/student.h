#define MAXSTUDENT 30

struct Student
{
    char name[32];
    int score;
    struct Student *pLess;
    struct Student *pMore;
};

int readStudent(struct Student *pRecord);
int cmpStudent(const struct Student *pA, const struct Student *pB);
void writeStudent(const struct Student *pRecord);
void swapStudent(struct Student *pA, struct Student *pB);
int findMinIndex(struct Student *pClass, int numStudent);
void selSort(struct Student *pClass, int numStudent);
