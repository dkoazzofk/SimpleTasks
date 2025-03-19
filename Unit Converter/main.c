#include <stdio.h>
#define MILES 0.621371
#define KILOMETRS 1.609

int convertKilometrsToMiles(double kilo){
    printf("Result: %.3lf", kilo * MILES);
}

int convertMilesToKilometrs(double mile){
    printf("Result: %.3lf", mile * KILOMETRS);
}

int convertCelsiumToFahr(double celsium){
    printf("Result: %.2lf", celsium * 1.8 + 32);
}

int convertFahrToCelsium(double fahr){
    printf("Result: %.2lf", (fahr - 32) / 1.8);
}

int main(){
    int choice;
    double number;
    for (;;){
        printf("\nWhat you want to convert?\n");
        printf("1. Kilometrs to Miles\n2. Miles to Kilometrs\n3. Celsium to Fahr\n4. Fahr to Celsium\n5. Exit\n");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Put Kilometrs: ");
            scanf("%lf",&number);
            convertKilometrsToMiles(number);
            break;
        case 2:
            printf("Put Miles: ");
            scanf("%lf", &number);
            convertMilesToKilometrs(number);
            break;
        case 3:
            printf("Put Celsium: ");
            scanf("%lf", &number);
            convertCelsiumToFahr(number);
            break;
        case 4:
            printf("Put Fahr: ");
            scanf("%lf", &number);
            convertFahrToCelsium(number);
        case 5:
            break;
        }
    }
    return 0;
}