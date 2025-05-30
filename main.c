#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CARS 100
#define MAX_STRING_LENGTH 50

typedef struct 
{
    char brand[MAX_STRING_LENGTH];
    char number[MAX_STRING_LENGTH];
    char color[MAX_STRING_LENGTH];
    float price;
} Car;

int main() 
{
    system("chcp 65001");
    Car cars[MAX_CARS];
    int n;
    char search_brand[MAX_STRING_LENGTH];
    float max_price;
    FILE *output_file;

    printf("Введіть кількість автомобілів: ");
    scanf("%d", &n);
    getchar();

    for (int i = 0; i < n; i += 1) 
    {
        printf("\nАвтомобіль #%d\n", i + 1);
        
        printf("Марка: ");
        fgets(cars[i].brand, MAX_STRING_LENGTH, stdin);
        cars[i].brand[strcspn(cars[i].brand, "\n")] = '\0';
        
        printf("Номер: ");
        fgets(cars[i].number, MAX_STRING_LENGTH, stdin);
        cars[i].number[strcspn(cars[i].number, "\n")] = '\0';
        
        printf("Колір: ");
        fgets(cars[i].color, MAX_STRING_LENGTH, stdin);
        cars[i].color[strcspn(cars[i].color, "\n")] = '\0';
        
        printf("Вартість: ");
        scanf("%f", &cars[i].price);
        getchar();
    }

    printf("\nВведіть марку для пошуку: ");
    fgets(search_brand, MAX_STRING_LENGTH, stdin);
    search_brand[strcspn(search_brand, "\n")] = '\0';
    
    printf("Введіть максимальну вартість: ");
    scanf("%f", &max_price);

    output_file = fopen("filtered_cars.txt", "w");
    if (output_file == NULL) 
    {
        printf("Помилка відкриття файлу!\n");
        return 1;
    }

    fprintf(output_file, "Автомобілі марки '%s' дешевші за %.2f:\n", search_brand, max_price);
    int found = 0;
    
    for (int i = 0; i < n; i += 1) 
    {
        if (strcmp(cars[i].brand, search_brand) == 0 && cars[i].price < max_price) 
        {
            fprintf(output_file, "\nАвтомобіль #%d\n", i + 1);
            fprintf(output_file, "Марка: %s\n", cars[i].brand);
            fprintf(output_file, "Номер: %s\n", cars[i].number);
            fprintf(output_file, "Колір: %s\n", cars[i].color);
            fprintf(output_file, "Вартість: %.2f\n", cars[i].price);
            found = 1;
        }
    }

    if (!found) 
    {
        fprintf(output_file, "Не знайдено автомобілів, які відповідають критеріям.\n");
    }

    fclose(output_file);
    printf("\nРезультати збережено у файлі 'filtered_cars.txt'\n");

    return 0;
}