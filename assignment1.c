#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CITIES 30
#define MAX_NAME_LEN 50


char cities[MAX_CITIES][MAX_NAME_LEN];
int city_count = 0;
int distances[MAX_CITIES][MAX_CITIES];


struct Vehicle {
    char name[20];
    int capacity;
    int rate_per_km;
    int avg_speed;
    int fuel_efficiency;
};


struct Vehicle vehicles[3] = {
    {"Van", 1000, 30, 60, 12},
    {"Truck", 5000, 40, 50, 6},
    {"Lorry", 10000, 80, 45, 4}
};

void init_distances() {
    for (int i = 0; i < MAX_CITIES; i++) {
        for (int j = 0; j < MAX_CITIES; j++) {
            if (i == j) {
                distances[i][j] = 0;
            } else {
                distances[i][j] = -1;
            }
        }
    }
}

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


void set_distance() {
    if (city_count < 2) {
        printf("Need at least 2 cities to set distance!\n");
        return;
    }

    display_cities();

    int from, to, dist;
    printf("Enter source city number: ");
    scanf("%d", &from);
    printf("Enter destination city number: ");
    scanf("%d", &to);

    from--; to--;

    if (from < 0 || from >= city_count || to < 0 || to >= city_count) {
        printf("Invalid city numbers!\n");
        return;
    }

    if (from == to) {
        printf("Source and destination cannot be same!\n");
        return;
    }

    printf("Enter distance (km): ");
    scanf("%d", &dist);


    distances[from][to] = dist;
    distances[to][from] = dist;

    printf("Distance set successfully!\n");
}


void display_distances() {
    if (city_count == 0) {
        printf("No cities available!\n");
        return;
    }

    printf("\n.... Distance Table ....\n");
    printf("%-15s", "Cities");
    for (int i = 0; i < city_count; i++) {
        printf("%-10s", cities[i]);
    }
    printf("\n");

    for (int i = 0; i < city_count; i++) {
        printf("%-15s", cities[i]);
        for (int j = 0; j < city_count; j++) {
            if (distances[i][j] == -1) {
                printf("%-10s", "N/A");
            } else {
                printf("%-10d", distances[i][j]);
            }
        }
        printf("\n");
    }
}
void display_vehicles() {
    printf("\n=== Available Vehicles ===\n");
    printf("%-5s %-10s %-12s %-12s %-12s %-15s\n",
           "No.", "Type", "Capacity(kg)", "Rate/km(LKR)", "Speed(km/h)", "Efficiency(km/l)");
    printf("--------------------------------------------------------------------\n");

    for (int i = 0; i < 3; i++) {
        printf("%-5d %-10s %-12d %-12d %-12d %-15d\n",
               i + 1, vehicles[i].name, vehicles[i].capacity,
               vehicles[i].rate_per_km, vehicles[i].avg_speed, vehicles[i].fuel_efficiency);
    }
    printf("\n");
}
void distance_menu() {
    int choice;

    while (1) {
        printf("\n=== Distance Management ===\n");
        printf("1. Set Distance\n");
        printf("2. Display Distance Table\n");
        printf("3. Back to Main Menu\n");
        printf("Choose option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                set_distance();
                break;
            case 2:
                display_distances();
                break;
            case 3:
                return;
            default:
                printf("Invalid choice!\n");
        }
    }
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
display_vehicles();
    printf("Welcome to Logistics Management System\n");

    while (1) {
        printf("\n... MAIN MENU ...\n");
        printf("1. City Management\n");
        printf("2. Distance Management\n");
        printf("2. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                city_menu();
                break;
            case 2:
                distance_menu();
            case 3:
                printf("you exit!\n");
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
