#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CITIES 30
#define MAX_NAME_LEN 50


char cities[MAX_CITIES][MAX_NAME_LEN];
int city_count = 0;
int distances[MAX_CITIES][MAX_CITIES];


struct DeliveryRecord {
    int from_city;
    int to_city;
    int weight;
    int vehicle_type;
    int distance;
    float cost;
    float time;
    float fuel_cost;
    float customer_charge;
};


struct DeliveryRecord deliveries[MAX_DELIVERIES];
int delivery_count = 0;

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

    printf("\n--- Distance Table ---\n");
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


void calculate_delivery_cost() {
    if (city_count < 2) {
        printf("Need at least 2 cities for delivery calculation!\n");
        return;
    }

    display_cities();
void process_delivery() {
    if (city_count < 2) {
        printf("Need at least 2 cities for delivery calculation!\n");
        return;
    }

    if (delivery_count >= MAX_DELIVERIES) {
        printf("Maximum delivery limit reached!\n");
        return;
    }

    display_cities();

    int from, to, weight, vehicle_type;
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

    if (distances[from][to] == -1) {
        printf("Distance not set between these cities!\n");
        return;
    }

    printf("Enter weight (kg): ");
    scanf("%d", &weight);

    display_vehicles();
    printf("Select vehicle type (1-3): ");
    scanf("%d", &vehicle_type);
    vehicle_type--;

    if (vehicle_type < 0 || vehicle_type > 2) {
        printf("Invalid vehicle type!\n");
        return;
    }

    if (weight > vehicles[vehicle_type].capacity) {
        printf("Weight exceeds vehicle capacity!\n");
        return;
    }


    int distance = distances[from][to];
    float base_cost = distance * vehicles[vehicle_type].rate_per_km * (1 + (float)weight / 10000);
    float delivery_time = (float)distance / vehicles[vehicle_type].avg_speed;
    float fuel_used = (float)distance / vehicles[vehicle_type].fuel_efficiency;
    float fuel_cost = fuel_used * 310;
    float total_operational_cost = base_cost + fuel_cost;
    float profit = base_cost * 0.25;
    float customer_charge = total_operational_cost + profit;


    deliveries[delivery_count].from_city = from;
    deliveries[delivery_count].to_city = to;
    deliveries[delivery_count].weight = weight;
    deliveries[delivery_count].vehicle_type = vehicle_type;
    deliveries[delivery_count].distance = distance;
    deliveries[delivery_count].cost = base_cost;
    deliveries[delivery_count].time = delivery_time;
    deliveries[delivery_count].fuel_cost = fuel_cost;
    deliveries[delivery_count].customer_charge = customer_charge;

    delivery_count++;


    printf("\n======================================================\n");
    printf("DELIVERY COST ESTIMATION\n");
    printf("------------------------------------------------------\n");
    printf("From: %s\n", cities[from]);
    printf("To: %s\n", cities[to]);
    printf("Distance: %d km\n", distance);
    printf("Vehicle: %s\n", vehicles[vehicle_type].name);
    printf("Weight: %d kg\n", weight);
    printf("------------------------------------------------------\n");
    printf("Base Cost: %.2f LKR\n", base_cost);
    printf("Fuel Used: %.2f L\n", fuel_used);
    printf("Fuel Cost: %.2f LKR\n", fuel_cost);
    printf("Operational Cost: %.2f LKR\n", total_operational_cost);
    printf("Profit: %.2f LKR\n", profit);
    printf("Customer Charge: %.2f LKR\n", customer_charge);
    printf("Estimated Time: %.2f hours\n", delivery_time);
    printf("======================================================\n");

    printf("Delivery record saved successfully!\n");
}

printf("\n=== Delivery History ===\n");
    printf("%-5s %-15s %-15s %-10s %-10s %-12s %-12s\n",
           "No.", "From", "To", "Vehicle", "Weight(kg)", "Distance(km)", "Charge(LKR)");
    printf("--------------------------------------------------------------------------------\n");

    for (int i = 0; i < delivery_count; i++) {
        printf("%-5d %-15s %-15s %-10s %-10d %-12d %-12.2f\n",
               i + 1,
               cities[deliveries[i].from_city],
               cities[deliveries[i].to_city],
               vehicles[deliveries[i].vehicle_type].name,
               deliveries[i].weight,
               deliveries[i].distance,
               deliveries[i].customer_charge);
    }
    printf("\n");
}
void generate_reports() {
    int total_distance = 0;
    float total_revenue = 0.0;
    float total_profit = 0.0;
    float total_time = 0.0;
    int shortest_distance = deliveries[0].distance;
    int longest_distance = deliveries[0].distance;
    int shortest_index = 0;
    int longest_index = 0;
}
void delivery_menu() {
    int choice;

    while (1) {
        printf("\n=== Delivery Management ===\n");
        printf("1. View Vehicles\n");
        printf("2. Calculate Delivery Cost\n");
        printf("3. Back to Main Menu\n");
        printf("Choose option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                display_vehicles();
                break;
            case 2:
                calculate_delivery_cost();
                break;
            case 3:
                view_delivery_history();
                break;
            case 4:
                return;
            default:
                printf("Invalid choice!\n");
        }
    }
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
        printf("\n=== City Management ===\n");
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

    init_distances();

    printf("Welcome to Logistics Management System\n");

    while (1) {
        printf("\n=== MAIN MENU ===\n");
        printf("1. City Management\n");
        printf("2. Distance Management\n");
        printf("3. Delivery Management\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                city_menu();
                break;
            case 2:
                distance_menu();
                break;
            case 3:
                delivery_menu();
                break;
            case 4:
                printf("Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
