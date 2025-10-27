#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    char name[50];
    char category[30];
    float price;
    int quantity;
} Product;

Product products[MAX];
int count = 0;

void WelcomeMessage() { // ประกาศ Function WelcomeMessage, และ มีการใช้ ASCII Art มาร่วมด้วยเพื่อความสวยงาม
    printf(" .--.      .--.     .-''-.     .---.          _______        ,-----.     ,---.    ,---.     .-''-.   \n");
    printf(" |  |_     |  |   .'_ _   \\    | ,_|         /   __  \\     .'  .-,  '.   |    \\  /    |   .'_ _   \\  \n");
    printf(" | _( )_   |  |  / ( ` )   ' ,-./  )        | ,_/  \\__)   / ,-.|  \\ _ \\  |  ,  \\/  ,  |  / ( ` )   ' \n");
    printf(" |(_ o _)  |  | . (_ o _)  | \\  '_ '`)    ,-./  )        ;  \\  '_ /  | : |  |\\_   /|  | . (_ o _)  | \n");
    printf(" | (_,_) \\ |  | |  (_,_)___|  > (_)  )    \\  '_ '`)      |  _`,/ \\ _/  | |  _( )_/ |  | |  (_,_)___| \n");
    printf(" |  |/    \\|  | '  \\   .---. (  .  .-'     > (_)  )  __  : (  '\\_/ \\   ; | (_ o _) |  | '  \\   .---. \n");
    printf(" |  '  /\\  `  |  \\  `-'    /  `-'`-'|___  (  .  .-'_/  )  \\ `\"/  \\  ) /  |  (_,_)  |  |  \\  `-'    / \n");
    printf(" |    /  \\    |   \\       /    |        \\  `-'`-'     /    '. \\_/``\".'   |  |      |  |   \\       /  \n");
    printf(" `---'    `---`    `'-..-'     `--------`    `._____.'       '-----'     '--'      '--'    `'-..-'   \n");
    printf("\n                      Welcome to our warehouse,Press Enter to continue...\n");
    getchar(); // รอผู้ใช้กด Enter
}


// --------------------------- ฟังก์ชัน Merge Sort ---------------------------
void merge(Product arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    Product L[n1], R[n2];

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i].price <= R[j].price)
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(Product arr[], int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// --------------------------- ฟังก์ชันหลักของโปรแกรม ---------------------------
void displayAll() {
    if (count == 0) {
        printf("\nNo products in inventory.\n");
        return;
    }

    printf("\n%-20s %-15s %-10s %-10s\n", "Name", "Category", "Price", "Qty");
    printf("-------------------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%-20s %-15s %-10.2f %-10d\n",
               products[i].name,
               products[i].category,
               products[i].price,
               products[i].quantity);
    }
}

void addProduct() {
    if (count >= MAX) {
        printf("Inventory full!\n");
        return;
    }

    Product p;
    printf("\nEnter product name: ");
    scanf(" %[^\n]", p.name);
    printf("Enter category (mouse/keyboard/monitor/cpu): ");
    scanf(" %[^\n]", p.category);

    do {
        printf("Enter price: ");
        scanf("%f", &p.price);
        if (p.price < 0)
            printf("Error: Price cannot be negative! Please enter again.\n");
    } while (p.price < 0);

    do {
        printf("Enter quantity: ");
        scanf("%d", &p.quantity);
        if (p.quantity < 0)
            printf("Error: Quantity cannot be negative! Please enter again.\n");
    } while (p.quantity < 0);

    products[count++] = p;
    printf("Product added successfully!\n");
}


void deleteProduct() {
    if (count == 0) {
        printf("No products to delete.\n");
        return;
    }

    char name[50];
    displayAll();
    printf("\nEnter product name to delete: ");
    scanf(" %[^\n]", name);

    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(products[i].name, name) == 0) {
            found = 1;
            for (int j = i; j < count - 1; j++)
                products[j] = products[j + 1];
            count--;
            printf("Product deleted successfully!\n");
            break;
        }
    }

    if (!found) printf("Product not found.\n");
}

void sortByCategory() {
    if (count == 0) {
        printf("No products to sort.\n");
        return;
    }

    char cat[30];
    printf("\nEnter category to sort (mouse/keyboard/monitor/cpu): ");
    scanf(" %[^\n]", cat);

    // เก็บสินค้าที่อยู่ในหมวดนั้นชั่วคราว
    Product temp[MAX];
    int tempCount = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(products[i].category, cat) == 0) {
            temp[tempCount++] = products[i];
        }
    }

    if (tempCount == 0) {
        printf("No products found in this category.\n");
        return;
    }

    mergeSort(temp, 0, tempCount - 1);

    printf("\nSorted products in category '%s' by price (ascending):\n", cat);
    printf("%-20s %-15s %-10s %-10s\n", "Name", "Category", "Price", "Qty");
    printf("-------------------------------------------------------------\n");
    for (int i = 0; i < tempCount; i++) {
        printf("%-20s %-15s %-10.2f %-10d\n",
               temp[i].name,
               temp[i].category,
               temp[i].price,
               temp[i].quantity);
    }
}

void saveToFile() {
    FILE *fp = fopen("warehouse.txt", "w");
    if (fp == NULL) {
        printf("Error saving file.\n");
        return;
    }

    fprintf(fp, "Name                 Category        Price      Qty\n");
    fprintf(fp, "-------------------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        fprintf(fp, "%-20s %-15s %-10.2f %-10d\n",
                products[i].name,
                products[i].category,
                products[i].price,
                products[i].quantity);
    }

    fclose(fp);
    printf("Data saved to 'warehouse.txt' successfully!\n");
}


// --------------------------- main ---------------------------
int main() {
    int choice;
    WelcomeMessage(); // เรียกใช้ function  WelcomeMessage


    do {
        printf("\n===== ELECTRONIC WAREHOUSE SYSTEM =====\n");
        printf("1. Display all products\n");
        printf("2. Add product\n");
        printf("3. Delete product\n");
        printf("4. Sort products by price (by category)\n");
        printf("5. Save to file\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: displayAll(); break;
            case 2: addProduct(); break;
            case 3: deleteProduct(); break;
            case 4: sortByCategory(); break;
            case 5: saveToFile(); break;
            case 6: printf("Exiting program...\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 6);

    return 0;
}
