#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
struct Book {
    char name[100];
    char author[30];
    int number_of_pages;
    int year_of_publication;
};
struct Node {
    struct Book data;
    struct Node *next;
    struct Node *down;
};
typedef struct Node node_t;
void random_filling(struct Book *array, int size) {
    struct AuthorBooks {
        char author[30];
        char books[3][100];
    };
    struct AuthorBooks catalog[] = {
        {"Толстой", {"Война и мир", "Анна Каренина", "Воскресение"}},
        {"Достоевский", {"Преступление и наказание", "Идиот", "Братья"}},
        {"Пушкин", {"Евгений Онегин", "Капитанская дочка", "Дубровский"}},
        {"Чехов", {"Вишневый сад", "Чайка", "Дядя Ваня"}},
        {"Булгаков", {"Мастер и Маргарита", "Собачье сердце", "Белая гвардия"}},
        {"Маркес", {"Сто лет", "Любовь во время чумы", "Полковнику никто"}},
        {"Оруэлл", {"1984", "Скотный двор", "Дочь священника"}},
        {"Хемингуэй", {"Старик и море", "Прощай, оружие", "По ком звонит"}},
        {"Ремарк", {"Три товарища", "На западном фронте", "Арка"}},
        {"Брэдбери", {"451 градус", "Вино из одуванчиков", "Марс"}}
    };
    int author_count = sizeof(catalog) / sizeof(catalog[0]);
    for (int i = 0; i < size; i++) {
        int author_index = rand() % author_count;
        strcpy(array[i].author, catalog[author_index].author);
        strcpy(array[i].name, catalog[author_index].books[rand() % 3]);
        array[i].number_of_pages = 100 + rand() % 500;  
        array[i].year_of_publication = 1900 + rand() % 125;  
    }
}
node_t *new_node(struct Book data) {
    node_t *new_n = malloc(sizeof(node_t));
    new_n->data = data;
    new_n->next = NULL;
    new_n->down = NULL;
    return new_n;
}

node_t* insert_end(node_t *head, struct Book data) {
    node_t *new_item = new_node(data);
    node_t *curr = head;
    while (curr->next != NULL) {
        curr = curr->next;
    }
    curr->next = new_item;
    return head;
}

node_t* complex_list(struct Book *books, int n, int k, node_t **lower_head) {
    node_t *upper_head = NULL; //верх
    *lower_head = NULL; //низ
    node_t *last_upper = NULL; // последний верх
    node_t *last_lower = NULL; // последниц низ
    for (int i = 0; i < n; i++) {
        node_t *current = new_node(books[i]);
        if (upper_head == NULL) {
            upper_head = current;
        } else {
            last_upper->next = current;
        }
        last_upper = current;
    }
    
    for (int i = n; i < n + k; i++) {
        node_t *current = new_node(books[i]);
        if (*lower_head == NULL) {
            *lower_head = current;
        } else {
            last_lower->next = current;
        }
        last_lower = current;
    }
    node_t *up = upper_head;
    node_t *low = *lower_head;
    int min_length = (n < k) ? n : k;
    
    for (int i = 0; i < min_length; i++) {
        up->down = low;
        up = up->next;
        low = low->next;
    }
    
    return upper_head;
}
void print_all(node_t *S_up, node_t *S_low, node_t *current) {
    node_t *temp;
    int count;
    printf("Ряд N\n");
    count = 2;
    temp = S_up;
    while (temp != NULL) {
        if (temp == current) printf("> "); else printf("  ");
        printf("%d %s %s %d %d\n", 
               count, temp->data.name, temp->data.author, 
               temp->data.number_of_pages, temp->data.year_of_publication);
        printf("------------------------------------------------------------\n");
        count += 2;
        temp = temp->next;
    }
    printf("Ряд K\n");
    count = 1;
    temp = S_low;
    while (temp != NULL) {
        if (temp == current) printf("> "); else printf("  ");
        printf("%d %s %s %d %d\n", 
               count, temp->data.name, temp->data.author, 
               temp->data.number_of_pages, temp->data.year_of_publication);
        printf("------------------------------------------------------------\n");
        count += 2;
        temp = temp->next;
    }
}


void menu(node_t *S_up, node_t *S_low) {
    node_t *current = S_up; 
    char choice;

    while (1) {
        print_all(S_up, S_low, current);
        
        printf("R в начало | Q Выход\n");
        
        if (scanf(" %c", &choice) != 1) break;
        if (choice == 'q') break;

        switch (choice) {
            case 'd': case '6': 
                if (current->next) current = current->next;
                else printf("\a!! Конец ряда.\n"); 
                break;
            case 's': case '2': 
                if (current->down) current = current->down;
                else printf("\a!! Пути вниз нет.\n");
                break;
            case 'r':
                current = S_up;
                break;
        }
    }
}

void free_simple_list(node_t *head) {
    while (head != NULL) {
        node_t *temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    srand(time(NULL));
    int n, k;
    printf("Введите N и K: ");
    scanf("%d %d", &n, &k);

    struct Book *array_struct = malloc((n + k) * sizeof(struct Book));
    random_filling(array_struct, n + k);

    node_t *S_lower = NULL;
    node_t *S_upper = complex_list(array_struct, n, k, &S_lower);
    menu(S_upper, S_lower);

    free_simple_list(S_upper); 
    free_simple_list(S_lower);
    free(array_struct);
}
