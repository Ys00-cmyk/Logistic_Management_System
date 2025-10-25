#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CITIES 30
#define MAX_NAME_LEN 50
#define MAX_DELIVERIES 50

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


int find_shortest_path(int from, int to, int path[]) {
    if (from == to) return 0;


    int dist[MAX_CITIES][MAX_CITIES];
    int next[MAX_CITIES][MAX_CITIES];


    for (int i = 0; i < city_count; i++) {
        for (int j = 0; j < city_count; j++) {
            if (i == j) {
                dist[i][j] = 0;
                next[i][j] = -1;
            } else if (distances[i][j] != -1) {
                dist[i][j] = distances[i][j];
                next[i][j] = j;
            } else {
                dist[i][j] = INF;
                next[i][j] = -1;
            }
        }
    }


    for (int k = 0; k < city_count; k++) {
        for (int i = 0; i < city_count; i++) {
            for (int j = 0; j < city_count; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF &&
                    dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = next[i][k];
                }
            }
        }
    }

    if (dist[from][to] == INF) {
        return -1;
    }

    int current = from;
    int path_length = 0;
    path[path_length++] = current;

    while (current != to) {
        current = next[current][to];
        if (current == -1) break;
        path[path_length++] = current;
    }
    return dist[from][to];
}
void calculate_delivery_cost() {
    if (city_count < 2) {
        printf("Need at least 2 cities for delivery calculation!\n");
        return;
    }
void process_delivery_with_optimization() {
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


    int path[MAX_CITIES];
    int shortest_distance = find_shortest_path(from, to, path);

    if (shortest_distance == -1) {
        printf("No route available between these cities!\n");
        return;
    }

    int direct_distance = distances[from][to];

    printf("\n--- Route Analysis ---\n");
    if (direct_distance != -1) {
        printf("Direct distance: %d km\n", direct_distance);
    } else {
        printf("No direct route available\n");
    }
    printf("Optimized distance: %d km\n", shortest_distance);

    if (direct_distance != -1 && shortest_distance < direct_distance) {
        printf("Optimized route saves: %d km\n", direct_distance - shortest_distance);
    }


    int distance = shortest_distance;
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
    printf("DELIVERY COST ESTIMATION (OPTIMIZED ROUTE)\n");
    printf("------------------------------------------------------\n");
    printf("From: %s\n", cities[from]);
    printf("To: %s\n", cities[to]);
    printf("Minimum Distance: %d km\n", distance);
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

void view_delivery_history() {
    if (delivery_count == 0) {
        printf("No deliveries recorded yet!\n");
        return;
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
    if (delivery_count == 0) {
        printf("No deliveries recorded yet! Cannot generate reports.\n");
        return;
    }
    int total_distance = 0;
    float total_revenue = 0.0;
    float total_profit = 0.0;
    float total_time = 0.0;
    int shortest_distance = deliveries[0].distance;
    int longest_distance = deliveries[0].distance;
    int shortest_index = 0;
    int longest_index = 0;

    for (int i = 0; i < delivery_count; i++) {
        total_distance += deliveries[i].distance;
        total_revenue += deliveries[i].customer_charge;
        total_profit += (deliveries[i].cost * 0.25);
        total_time += deliveries[i].time;

        if (deliveries[i].distance < shortest_distance) {
            shortest_distance = deliveries[i].distance;
            shortest_index = i;
        }
        if (deliveries[i].distance > longest_distance) {
            longest_distance = deliveries[i].distance;
            longest_index = i;
        }
    }
    float avg_delivery_time = total_time / delivery_count;

    printf("\n===============================================\n");
    printf("PERFORMANCE REPORTS\n");
    printf("===============================================\n");
    printf("Total Deliveries Completed: %d\n", delivery_count);
    printf("Total Distance Covered: %d km\n", total_distance);
    printf("Average Delivery Time: %.2f hours\n", avg_delivery_time);
    printf("Total Revenue: %.2f LKR\n", total_revenue);
    printf("Total Profit: %.2f LKR\n", total_profit);
    printf("-----------------------------------------------\n");
    printf("Shortest Route: %s -> %s (%d km)\n",
           cities[deliveries[shortest_index].from_city],
           cities[deliveries[shortest_index].to_city],
           shortest_distance);
    printf("Longest Route: %s -> %s (%d km)\n",
           cities[deliveries[longest_index].from_city],
           cities[deliveries[longest_index].to_city],
           longest_distance);
    printf("===============================================\n");
}
void remove_city() {
    if (city_count == 0) {
        printf("No cities available to remove!\n");
        return;
    }

    display_cities();

    int city_num;
    printf("Enter city number to remove (1-%d): ", city_count);
    scanf("%d", &city_num);

    if (city_num < 1 || city_num > city_count) {
        printf("Invalid city number!\n");
        return;
    }

    int index_to_remove = city_num - 1;
    char city_name[MAX_NAME_LEN];
    strcpy(city_name, cities[index_to_remove]);

    for (int i = index_to_remove; i < city_count - 1; i++) {
        strcpy(cities[i], cities[i + 1]);
    }


    for (int i = index_to_remove; i < city_count - 1; i++) {
        for (int j = 0; j < city_count; j++) {
            distances[i][j] = distances[i + 1][j];
        }
    }

    for (int j = index_to_remove; j < city_count - 1; j++) {
        for (int i = 0; i < city_count; i++) {
            distances[i][j] = distances[i][j + 1];
        }
    }

    city_count--;
    printf("City '%s' removed successfully!\n", city_name);


    for (int i = 0; i < delivery_count; i++) {
        if (deliveries[i].from_city == index_to_remove || deliveries[i].to_city == index_to_remove) {
            printf(" Delivery record %d referenced removed city!\n", i + 1);
        }

        if (deliveries[i].from_city > index_to_remove) {
            deliveries[i].from_city--;
        }
        if (deliveries[i].to_city > index_to_remove) {
            deliveries[i].to_city--;
        }
    }

    save_cities_and_distances();
}

void rename_city() {
    if (city_count == 0) {
        printf(" No cities available to rename!\n");
        return;
    }

    display_cities();

    int city_num;
    printf("Enter city number to rename (1-%d): ", city_count);
    scanf("%d", &city_num);

    if (city_num < 1 || city_num > city_count) {
        printf(" Invalid city number!\n");
        return;
    }

    char old_name[MAX_NAME_LEN];
    strcpy(old_name, cities[city_num - 1]);

    printf("Enter new name for %s: ", old_name);
    scanf("%s", cities[city_num - 1]);

    printf("City renamed from '%s' to '%s' successfully!\n", old_name, cities[city_num - 1]);
    save_cities_and_distances();
}
void reports_menu() {
    int choice;

    while (1) {
        printf("\n=== Reports ===\n");
        printf("1. Generate Performance Report\n");
        printf("2. Back to Main Menu\n");
        printf("Choose option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                generate_reports();
                break;
            case 2:
                return;
            default:
                printf("Invalid choice!\n");
        }
    }
}

void delivery_menu() {
    int choice;

    while (1) {
        printf("\n=== Delivery Management ===\n");
        printf("1. View Vehicles\n");
        printf("2. Calculate Delivery Cost\n");
        printf("3. View Delivery History\n");
        printf("4. Back to Main Menu\n");
        printf("Choose option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                display_vehicles();
                break;
            case 2:
                process_delivery_with_optimization();
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
        printf("3. Rename City\n");
        printf("4. Remove City \n");
        printf("5. Back to Main Menu\n");
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
                rename_city();
            case 4:
                remove_city();
            case 5:
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
    printf("Now with route optimization!\n");
    while (1) {
        printf("\n=== MAIN MENU ===\n");
        printf("1. City Management\n");
        printf("2. Distance Management\n");
        printf("3. Delivery Management\n");
        printf("4. Reports\n");
        printf("5. Exit\n");
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
                reports_menu();
                break;
            case 5:
                printf("Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
