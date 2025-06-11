
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define FILENAME "employees.dat"

struct Employee {
    int id;
    char name[50];
    char department[50];
    float rating;
};

struct Employee employees[MAX];
int n = 0;

void swap(struct Employee *a, struct Employee *b) {
    struct Employee temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int low, int high) {
    float pivot = employees[high].rating;
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (employees[j].rating >= pivot) {
            i++;
            swap(&employees[i], &employees[j]);
        }
    }
    swap(&employees[i + 1], &employees[high]);
    return i + 1;
}

void quickSort(int low, int high) {
    if (low < high) {
        int pi = partition(low, high);
        quickSort(low, pi - 1);
        quickSort(pi + 1, high);
    }
}

void merge(int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    struct Employee L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = employees[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = employees[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (strcmp(L[i].department, R[j].department) <= 0) {
            employees[k] = L[i];
            i++;
        } else {
            employees[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        employees[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        employees[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(l, m);
        mergeSort(m + 1, r);
        merge(l, m, r);
    }
}

void selectionSort() {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++)
            if (employees[j].id < employees[min_idx].id)
                min_idx = j;
        swap(&employees[min_idx], &employees[i]);
    }
}

void findEmployeesByRating(float threshold) {
    quickSort(0, n - 1);
    printf("Employees with rating >= %.2f:\n", threshold);
    for (int i = 0; i < n; i++) {
        if (employees[i].rating >= threshold) {
            printf("ID: %d, Name: %s, Rating: %.2f\n", employees[i].id, employees[i].name, employees[i].rating);
        }
    }
}

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

void addEmployee() {
    if (n >= MAX) {
        printf("Employee list is full!\n");
        return;
    }
    printf("Enter Employee ID: ");
    scanf("%d", &employees[n].id);
    printf("Enter Employee Name: ");
    scanf("%s", employees[n].name);
    printf("Enter Employee Department: ");
    scanf("%s", employees[n].department);
    printf("Enter Employee Rating: ");
    scanf("%f", &employees[n].rating);
    n++;
}

void displayAllEmployees() {
    selectionSort();
    printf("All employees:\n");
    for (int i = 0; i < n; i++) {
        printf("ID: %d, Name: %s, Department: %s, Rating: %.2f\n", employees[i].id, employees[i].name, employees[i].department, employees[i].rating);
    }
}

void saveToFile() {
    FILE *fp = fopen(FILENAME, "wb");
    if (fp == NULL) {
        printf("Error saving to file!\n");
        return;
    }
    fwrite(&n, sizeof(int), 1, fp);
    fwrite(employees, sizeof(struct Employee), n, fp);
    fclose(fp);
    printf("Data saved to file successfully.\n");
}

void loadFromFile() {
    FILE *fp = fopen(FILENAME, "rb");
    if (fp == NULL) {
        printf("No previous data found.\n");
        return;
    }
    fread(&n, sizeof(int), 1, fp);
    fread(employees, sizeof(struct Employee), n, fp);
    fclose(fp);
    printf("Data loaded from file successfully.\n");
}

void searchByID() {
    int id;
    printf("Enter Employee ID to search: ");
    scanf("%d", &id);
    for (int i = 0; i < n; i++) {
        if (employees[i].id == id) {
            printf("Employee found - ID: %d, Name: %s, Department: %s, Rating: %.2f\n", employees[i].id, employees[i].name, employees[i].department, employees[i].rating);
            return;
        }
    }
    printf("Employee with ID %d not found.\n", id);
}

void updateEmployee() {
    int id;
    printf("Enter Employee ID to update: ");
    scanf("%d", &id);
    for (int i = 0; i < n; i++) {
        if (employees[i].id == id) {
            printf("Enter new Name: ");
            scanf("%s", employees[i].name);
            printf("Enter new Department: ");
            scanf("%s", employees[i].department);
            printf("Enter new Rating: ");
            scanf("%f", &employees[i].rating);
            printf("Employee record updated.\n");
            return;
        }
    }
    printf("Employee with ID %d not found.\n", id);
}

void deleteEmployee() {
    int id;
    printf("Enter Employee ID to delete: ");
    scanf("%d", &id);
    for (int i = 0; i < n; i++) {
        if (employees[i].id == id) {
            for (int j = i; j < n - 1; j++) {
                employees[j] = employees[j + 1];
            }
            n--;
            printf("Employee with ID %d deleted.\n", id);
            return;
        }
    }
    printf("Employee with ID %d not found.\n", id);
}

int main() {
    int option;
    loadFromFile();

    do {
        printf("\n******* Menu ********\n");
        printf("1 => Add a new record\n");
        printf("2 => Search record from employee ID\n");
        printf("3 => List Employee of particular department\n");
        printf("4 => Display all employees\n");
        printf("5 => Update record of an employee\n");
        printf("6 => Delete record of particular employee\n");
        printf("7 => Find Employees by Rating\n");
        printf("8 => GCD of Employee IDs\n");
        printf("0 => Exit\n");
        printf("Enter your option: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                addEmployee();
                break;
            case 2:
                searchByID();
                break;

            case 3: {
                char department[50];
                printf("Enter department name: ");
                scanf("%s", department);

    printf("Employees in the %s department:\n", department);
    for (int i = 0; i < n; i++) {
        if (strcmp(employees[i].department, department) == 0) {
            printf("ID: %d, Name: %s,Rating: %.2f", employees[i].id, employees[i].name, employees[i].rating);
        }
    }
    break;
}

            case 4:
                displayAllEmployees();
                break;
            case 5:
                updateEmployee();
                break;
            case 6:
                deleteEmployee();
                break;
            case 7: {
                float threshold;
                printf("Enter rating threshold: ");
                scanf("%f", &threshold);
                findEmployeesByRating(threshold);
                break;
            }
            case 8: {
                int id1, id2;
                printf("Enter first Employee ID: ");
                scanf("%d", &id1);
                printf("Enter second Employee ID: ");
                scanf("%d", &id2);
                printf("GCD of %d and %d is %d\n", id1, id2, gcd(id1, id2));
                break;
            }
            case 0:
                saveToFile();
                printf("Exiting and saving data.\n");
                break;
            default:
                printf("Invalid option. Please try again.\n");
        }
    } while (option != 0);

    return 0;
}
