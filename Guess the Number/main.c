#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int generateNum(){
    srand(time(NULL));
    int random = 1 + rand()% 1000 + 1;
    return random;
}

int checkNum(int humanNum, int randomNum){
    if (humanNum < randomNum){
        printf("Your number is less than expected.\n");
    } else if (humanNum == randomNum){
        printf("You guessed the number.\n");
    } else printf("Your number is higher than expected.\n");
}


int main(){
    int humanNumber;
    int genNum = generateNum();
    while(1){
        printf("Put your number: ");
        scanf("%d",&humanNumber);
        checkNum(humanNumber, genNum);
        if (humanNumber == genNum) break;
    }
    return 0;
}