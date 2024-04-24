#include <stdio.h>
#include <stdlib.h>

#include "student.h"
#include "io.h"

typedef struct {
    double avg_mark; // Средний балл
    int group; // Группа
} StudentStatistics; // Статистика студента

double avg_mark(Student *s) // Функция для вычисления среднего балла
{
    if (s->gender == 'F'){ // Проверяем гендер
        return (s->dm + s->ma + s->la + s->cs + s->hi) / 5.0;
    }
    else {
        return -1; // Отметаем студентов мужского пола
    }
}

// Using qsort is better, but requires proficiency with pointers :)
void sort(int arr[], int length) // Сортировка массива
{
    int tmp;
    for (int i = 1; i < length; ++i) {
        for (int j = i; j > 0 && arr[j - 1] > arr[j]; --j) {
            tmp = arr[j];
            arr[j] = arr[j - 1];
            arr[j - 1] = tmp;
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Использование:\n\t./execute DB_FILE\n"); // Предполагается использование
        exit(0);
    }

    FILE *in = fopen(argv[1], "r");
    if (!in) {
        printf("Ошибка ввода-вывода: не удается открыть файл.\n"); // Ошибка ввода-вывода: не удается открыть файл
        exit(1);
    }

    double max_avg = -1.0; // Изначально устанавливаем максимальный балл как отрицательное значение
    int max_group = -1; // Изначально устанавливаем группу с максимальным баллом как -1

    Student student;

    while (student_read_bin(&student, in)) { // Считываем студентов из файла
        double avg = avg_mark(&student); // Вычисляем средний балл
        if (avg > max_avg) { // Если текущий средний балл больше максимального
            max_avg = avg; // Обновляем максимальный балл
            max_group = student.group; // Обновляем группу с максимальным баллом
        }
    }

    fclose(in);

    if (max_group != -1) { // Если найдена группа с максимальным баллом
        printf("Group with MAX: %d\n", max_group);
    } else {
        printf("NO DATA! LOL.\n"); // Если не найдено студенток
    }

    return 0;
}
