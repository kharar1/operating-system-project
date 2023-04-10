#include <iostream>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <cstdlib>
#include <ctime>

using namespace std;

sem_t pen_sem, paper_sem, question_paper_sem, teacher_sem;
bool has_pen = false, has_paper = false, has_question_paper = false;
const int PEN = 0;
const int PAPER = 1;
const int QUESTION_PAPER = 2;

void *teacher(void *arg) {
    while (true) {
        sem_wait(&teacher_sem);
        int item1 = rand() % 3;
        int item2 = rand() % 3;
        while (item2 == item1) {
            item2 = rand() % 3;
        }
        switch (item1) {
            case PEN:
                switch (item2) {
                    case PAPER:
                        cout << "Teacher placed pen and paper on the table\n";
                        sem_post(&question_paper_sem);
                        break;
                    case QUESTION_PAPER:
                        cout << "Teacher placed pen and question paper on the table\n";
                        sem_post(&paper_sem);
                        break;
                }
                break;
            case PAPER:
                switch (item2) {
                    case PEN:
                        cout << "Teacher placed pen and paper on the table\n";
                        sem_post(&question_paper_sem);
                        break;
                    case QUESTION_PAPER:
                        cout << "Teacher placed paper and question paper on the table\n";
sem_post(&pen_sem);
break;
}
break;
case QUESTION_PAPER:
switch (item2) {
case PEN:
cout << "Teacher placed question paper and pen on the table\n";
sem_post(&paper_sem);
break;
case PAPER:
cout << "Teacher placed question paper and paper on the table\n";
sem_post(&pen_sem);
break;
}
break;
}
}
}

void *student(void *arg) {
    int student_id = *(int *)arg;
    while (true) {
        switch (student_id) {
            case PEN:
                sem_wait(&pen_sem);
                has_pen = true;
                break;
            case PAPER:
                sem_wait(&paper_sem);
                has_paper = true;
                break;
            case QUESTION_PAPER:
                sem_wait(&question_paper_sem);
                has_question_paper = true;
                break;
        }
        cout << "Student " << student_id << " has acquired necessary resource\n";
        usleep(rand() % 1000000);
        sem_wait(&teacher_sem);
        cout << "Student " << student_id << " entered teacher's critical section\n";
        if (has_pen && has_paper) {
            has_pen = false;
            has_paper = false;
            cout << "Student " << student_id << " has completed the assignment\n";
        } else if (has_paper && has_question_paper) {
            has_paper = false;
            has_question_paper = false;
            cout << "Student " << student_id << " has completed the assignment\n";
        } else if (has_question_paper && has_pen) {
            has_question_paper = false;
            has_pen = false;
            cout << "Student " << student_id << " has completed the assignment\n";
        }
        sem_post(&teacher_sem);
    }
}


int main() {
srand(time(NULL));
sem_init(&pen_sem, 0, 0);
sem_init(&paper_sem, 0, 0);
sem_init(&question_paper_sem, 0, 0);
sem_init(&teacher_sem, 0, 1);
pthread_t threads[4];
int ids[] = {PEN, PAPER, QUESTION_PAPER};

pthread_create(&threads[0], NULL, teacher, NULL);
pthread_create(&threads[1], NULL, student, &ids[0]);
pthread_create(&threads[2], NULL, student, &ids[1]);
pthread_create(&threads[3], NULL, student, &ids[2]);

for (int i = 0; i < 4; i++) {
    pthread_join(threads[i], NULL);
}

sem_destroy(&pen_sem);
sem_destroy(&paper_sem);
sem_destroy(&question_paper_sem);
sem_destroy(&teacher_sem);

return 0;
}

