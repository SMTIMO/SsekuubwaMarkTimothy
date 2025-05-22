#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Book {
    char title[100];
    char author[100];
    float price;
};

int main() {
    struct Book b;

    printf("Enter title: ");
    fgets(b.title, sizeof(b.title), stdin);
    strtok(b.title, "\n");

    printf("Enter author: ");
    fgets(b.author, sizeof(b.author), stdin);
    strtok(b.author, "\n");

    printf("Enter price: ");
    scanf("%f", &b.price);

    FILE *fptr = fopen("book4.csv", "w");
    if (!fptr) return 1;
    fprintf(fptr, "%s,%s,%.2f\n", b.title, b.author, b.price);
    fclose(fptr);

    struct Book rb;
    char line[300];
    fptr = fopen("book4.csv", "r");
    fgets(line, sizeof(line), fptr);
    fclose(fptr);
    sscanf(line, "%99[^,],%99[^,],%f", rb.title, rb.author, &rb.price);

    printf("\nTitle: %s\nAuthor: %s\nPrice: %.2f\n", rb.title, rb.author, rb.price);
    return 0;
}
