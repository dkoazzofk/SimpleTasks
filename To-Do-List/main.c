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
        
        default:
            break;
        }
    } while (choice != 4);
    
    return 0;
}