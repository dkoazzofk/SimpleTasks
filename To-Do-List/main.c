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

void deleteTask(){
    FILE *fp;
    char input[1024];
    char search[1024];
    int flag = 0;
    char name[] = "ToDoList.txt";
    if((fp = fopen(name, "r")) == NULL){
        perror("Не удалось открыть файл.\n");
        getchar();
        return;
    }
    printf("Введите номер задачи, которую хотите удалить: ");
    scanf(" %99[^\n]", search);

    char tempName[] = "tempFile.txt";
    FILE *temp;
    if((temp = fopen(tempName, "w")) == NULL){
        perror("Не удалось открыть временный файл.\n");
        getchar();
        return;
    }
    while(fgets(input, sizeof(input), fp) != NULL){
        if(strstr(input, search) == input){
            flag = 1;
            continue;
        }
        fputs(input, temp);
    }
    fclose(fp);
    fclose(temp);

    if(flag){
        remove(name);
        rename(tempName, name);
    } else{
        remove(tempName);
    }
}

void showTask(){
    FILE *fp;
    char buffer[256];
    char name[] = "ToDoList.txt";
    if((fp = fopen(name,"r")) == NULL){
        perror("Не удалось открыть файл.\n");
        getchar();
        return;
    }
    if(fp){
        while(fgets(buffer, 256, fp) != NULL){
            printf("%s", buffer);
        }
        fclose(fp);
    }
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
        case 2:
            deleteTask();
            break;
        case 3:
            showTask();
            break;
        default:
            break;
        }
    } while (choice != 4);
    
    return 0;
}