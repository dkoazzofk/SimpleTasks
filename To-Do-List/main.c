#include <stdio.h>
#include <windows.h>
#include <locale.h>


void createTask(){
    FILE *fp;
    char input[100];
    char name[] = "ToDoList.txt";
    if((fp = fopen(name,"a")) == NULL){
        perror("Не удалось открыть файл.\n");
        getchar();
        return;
    }
    printf("Введите задачу: ");
    scanf(" %99[^\n]", input);
    fprintf(fp, "%s\n", input);

    fclose(fp);
    
}

int main(){
    setlocale(LC_ALL, "ru");
    SetConsoleOutputCP(1251);
    int choice;
    do
    {
        printf("-----Главное Меню-----\n");
        printf("1. Добавить задачу\n");
        printf("2. Удалить задачу\n");
        printf("3. Список задач\n");
        printf("4. Выход\n");
        printf("Выберите действие: ");
        scanf("%d", &choice);
        while(getchar() != '\n');
        switch (choice)
        {
        case 1:
            createTask();
            break;
        
        default:
            break;
        }
    } while (choice != 4);
    
    return 0;
}