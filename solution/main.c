#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include <sys/wait.h>

int main(int argc, char** argv) {
    int pid;

    if (argc != 4) {
        printf("Usage: %s <input file> <number of TAs> <minimum pass grade>\n", argv[0]);
        return 1;
    }

    FILE* file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    int N = atoi(argv[2]);
    int minPassGrade = atoi(argv[3]);
    int totalStudents = 0;

    fscanf(file, "%d", &totalStudents);

    int studentGrades[totalStudents];

    for (int i = 0; i < totalStudents; i++) {
        int finalGrade, midGrade;
        fscanf(file, "%d %d", &finalGrade, &midGrade);
        studentGrades[i] = (finalGrade + midGrade);
    }

    fclose(file);

    int start, end;
    for (int i = 0; i < N; i++) {
        start = i * (totalStudents / N);
        end = (i + 1) * (totalStudents / N);
        if (i == N - 1) {
            end = totalStudents;
        }
        
        pid = fork();
        if (pid == 0) {
            break;
        }
    }

    if (pid == -1) {
        perror("error in fork");
    } else if (pid == 0) { // Child
        int totalPassed = 0;

        for (int i = start; i < end; i++) {
            int grade = studentGrades[i];
            if (grade >= minPassGrade) {
                totalPassed++;
            }
        }
        printf("%d ", totalPassed);
    } else {
        sleep(1);
        printf("\n");
    }

    return 0;
}