#include <stdio.h>
#include <stdlib.h>

#define N 4
#define M 15

typedef struct student {
    char name;
    char task;
    int mark;
} student;

int **allocate_mem1(int x, int y);
struct student **allocate_mem2(int x, int y);
void free_mem(void (**p), int x);
void create_marks_arr1(int (**p), int d[N][M]);
void print_marks(int (**p), int x, int y, int (*t), char (**names));
int *create_tasks_arr(int d[N][M], int n);
int in_arr(int num, const int arr[]);
int find_hardest_task(int (**p), int x, int y, double *res);
void create_marks_arr2(struct student(**p), int d[N][M], char (**names));

int main() {
    int arr[N][M] = {
            {4, 0, 7, 7, 10, 1, -7, 9, -6, 10, -9, 2, -4, 9, -4},
            {104, 100, 102, 104, 108, 108, 106, 102, 104, 100, 100, 106, 102, 108, 106},
            {15, 20, 5, 4, 37, 32, 26, 35, 8, 15, 5, 23, 24, 39, 9},
            {0, 0, 0, 1, 0, 1, 0, 1, 2, 1, 2, 1, 2, 2, 2}
    };

    char *names[] = {"Wyll", "Toony", "Lucca"};
    int s_num = 3, t_num = 5, hard_i;
    double hard_res;

    int **marks = allocate_mem1(s_num, t_num);
    struct student** marks_s = allocate_mem2(s_num, t_num);

    create_marks_arr1(marks, arr);
    create_marks_arr2(marks_s, arr, names);

    int *tasks = create_tasks_arr(arr, t_num);

    print_marks(marks, s_num, t_num, tasks, names);

    printf("\n");
    hard_i = find_hardest_task(marks, s_num, t_num, &hard_res);
    printf("Task %d was the hardest and its average result was: %.2lf\n", tasks[hard_i], hard_res);

    free_mem((void**)marks, s_num);
    free_mem((void**)marks_s, s_num);
    free(tasks);
}

void create_marks_arr2(struct student(**p), int d[N][M], char (**names)) {
    int points, student, task;
    struct student new_s;

    for (int j = 0; j < M; j++) {
        task = d[1][j];
        points = d[2][j] / 40. * 100;  // ocena
        student = d[3][j];  // 0 1 2

        new_s.name = *names[student];
        new_s.task = task;
        new_s.mark = points;

        p[student][task] = new_s;
    }
}

struct student **allocate_mem2(int x, int y) {
    struct student** p = NULL;
    p = (struct student**) malloc(sizeof(struct student *) * x);
    if (!p) {
        printf("memory error");
        exit(1);
    }

    for (int i = 0; i < x; i++) {
        p[i] = (struct student *) malloc(sizeof(struct student) * y);
        if (!p[i]) {
            printf("memory error");
            exit(1);
        }
    }

    return p;
}

int find_hardest_task(int (**p), int x, int y, double *res) {
    int index = 0, sum;
    *res = 100.;
    double avg;

    for (int j = 0; j < y; j++) {
        sum = 0;
        for (int i = 0; i < x; i++) {
            sum += p[i][j];
        }
        avg = sum / 3.;

        if (avg < *res) {
            *res = avg;
            index = j;
        }
    }

    return index;
}

int in_arr(int num, const int arr[]) {
    int res = 0, i = 0;
    while (arr[i]) {
        if (arr[i] == num) {
            res = 1;
            return res;
        }
        i++;
    }
    return res;
}

int *create_tasks_arr(int d[N][M], int n) {
    int * arr = (int *) malloc(sizeof(int) * n);
    int task;

    for (int i = 0; i < M; i++) {
        task = d[1][i];
        if (!in_arr(task, arr)) {
            arr[(task - 100) / 2] = task;
        }
    }
    return arr;
}

void print_marks(int (**p), int x, int y, int (*t), char (**names)) {
    printf("marks\t");
    for (int i = 0; i < y; i++) {
        printf("%d\t", t[i]);
    }
    printf("\n");

    for (int i = 0; i < x; i++) {
        printf("%s\t", names[i]);
        for (int j = 0; j < y; j++) {
            printf("%d\t", p[i][j]);
        }
        printf("\n");
    }
}

void create_marks_arr1(int (**p), int d[N][M]) {
    int points, student, task;
    for (int j = 0; j < M; j++) {
        task = (d[1][j] - 100) / 2;  // 0 1 2 3 4
        points = d[2][j] / 40. * 100;  // ocena
        student = d[3][j];  // 0 1 2
        p[student][task] = points;
    }
}

int **allocate_mem1(int x, int y) {
    int** p = NULL;
    p = (int **) malloc(sizeof(int *) * x);
    if (!p) {
        printf("memory error");
        exit(1);
    }

    for (int i = 0; i < x; i++) {
        p[i] = (int *) malloc(sizeof(int) * y);
        if (!p[i]) {
            printf("memory error");
            exit(1);
        }
    }

    return p;
}

void free_mem(void (**p), int x) {
    for (int i = 0; i < x; i++) {
        free(p[i]);
    }
    free(p);
}
