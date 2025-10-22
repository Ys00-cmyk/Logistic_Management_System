#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CITIES 30
#define MAX_NAME_LEN 50


char cities[MAX_CITIES][MAX_NAME_LEN];
int city_count = 0;


void add_city() {
    if (city_count >= MAX_CITIES) {
        printf("Cannot add more cities. Maximum limit reached.\n");
        return;
    }

    printf("Enter city name: ");
    scanf("%s", cities[city_count]);
    city_count++;
    printf("City added successfully!\n");
}

void display_cities() {
    printf("\n--- Current Cities ---\n");
    for (int i = 0; i < city_count; i++) {
        printf("%d. %s\n", i + 1, cities[i]);
    }
    printf("\n");
}

void city_menu() {
    int choice;

    while (1) {
        printf("\n... City Management ...\n");
        printf("1. Add City\n");
        printf("2. Display Cities\n");
        printf("3. Back to Main Menu\n");
        printf("Choose option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_city();
                break;
            case 2:
                display_cities();
                break;
            case 3:
                return;
            default:
                printf("Invalid choice!\n");
        }
    }
}

int main() {
    int choice;

    printf("Welcome to Logistics Management System\n");

    while (1) {
        printf("\n... MAIN MENU ...\n");
        printf("1. City Management\n");
        printf("2. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                city_menu();
                break;
            case 2:
                printf("you exit!\n");
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
