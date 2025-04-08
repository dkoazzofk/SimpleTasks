#include <stdio.h>
#include <windows.h>
#include <locale.h>


void createTask(){
    FILE *fp;
    char input[100];
    char name[] = "ToDoList.txt";
    if((fp = fopen(name,"a")) == NULL){
        perror("�� ������� ������� ����.\n");
        getchar();
        return;
    }
    printf("������� ������: ");
    scanf(" %99[^\n]", input);
    fprintf(fp, "%s\n", input);

    fclose(fp);
}

void showTask(){
    FILE *fp;
    char buffer[256];
    char name[] = "ToDoList.txt";
    if((fp = fopen(name,"r")) == NULL){
        perror("�� ������� ������� ����.\n");
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
        printf("-----������� ����-----\n");
        printf("1. �������� ������\n");
        printf("2. ������� ������\n");
        printf("3. ������ �����\n");
        printf("4. �����\n");
        printf("�������� ��������: ");
        scanf("%d", &choice);
        while(getchar() != '\n');
        switch (choice)
        {
        case 1:
            createTask();
            break;
        case 2:
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