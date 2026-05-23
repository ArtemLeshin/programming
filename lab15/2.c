#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

struct Employee {
    char name[100];
    char id[20];
    char level[20];
};

void print_compression_report() {
    struct stat stat_before, stat_after;
    double size_before, size_after, compression_percent;
    
    // размер исходного файла
    if (stat("database.dat", &stat_before) != 0) {
        printf("Ошибка: не удалось получить размер database.dat\n");
        return;
    }
    
    // размер сжатого файла
    if (stat("database.rle", &stat_after) != 0) {
        printf("Ошибка: не удалось получить размер database.rle\n");
        return;
    }
    size_before = stat_before.st_size / 1024.0;
    size_after = stat_after.st_size / 1024.0;
    
    if (size_before > 0) {
        compression_percent = (1 - (size_after / size_before)) * 100;
    } else {
        compression_percent = 0;
    }
    
    printf("Размер до: %.2f Кб, Размер после: %.2f Кб, Сжатие: %.2f%%\n", size_before,size_after,compression_percent);
}
void compress() {
    FILE *input_file;
    FILE *output_file;
    struct Employee current, next;
    int count;
    int records_read;
    
    // бинарный файл для чтения
    input_file = fopen("database.dat", "rb");
    if (input_file == NULL) {
        printf("Ошибка: не удалось открыть database.dat\n");
        return;
    }
    
    // сжатый файл для записи
    output_file = fopen("database.rle", "wb");
    if (output_file == NULL) {
        printf("Ошибка: не удалось создать database.rle\n");
        fclose(input_file);
        return;
    }
        
    records_read = fread(&current, sizeof(struct Employee), 1, input_file);
    
    while (records_read == 1) {
        count = 1;
        while (fread(&next, sizeof(struct Employee), 1, input_file) == 1) {
            if (strcmp(current.name, next.name) == 0 &&
                strcmp(current.id, next.id) == 0 &&
                strcmp(current.level, next.level) == 0) {
                count++;
            } else {
                fseek(input_file, -sizeof(struct Employee), SEEK_CUR);
                break;
            }
        }
        fwrite(&count, sizeof(int), 1, output_file);
        fwrite(&current, sizeof(struct Employee), 1, output_file);
        records_read = fread(&current, sizeof(struct Employee), 1, input_file);
    }    
    fclose(input_file);
    fclose(output_file);
    printf("\nСодержимое database.rle:\n");
    
    output_file = fopen("database.rle", "rb");
    if (output_file == NULL) {
        printf("Ошибка: не удалось открыть database.rle\n");
        return;
    }
    
    while (fread(&count, sizeof(int), 1, output_file) == 1) {
        if (fread(&current, sizeof(struct Employee), 1, output_file) == 1) {
            printf("[%d] ", count);
            printf("%s;%s;%s\n", current.name, current.id, current.level);
        }
    }
    
    fclose(output_file);
}

void decompress() {
    FILE *input_file;
    FILE *output_file;
    struct Employee emp;
    int count;
    int i;
    
    // открываем сжатый файл для чтения
    input_file = fopen("database.rle", "rb");
    if (input_file == NULL) {
        printf("Ошибка: не удалось открыть database.rle\n");
        return;
    }
    printf("\ndatabase_restored.dat\n");
    // создаем восстановленный 
    output_file = fopen("database_restored.dat", "wb");
    if (output_file == NULL) {
        printf("Ошибка: не удалось создать database_restored.dat\n");
        fclose(input_file);
        return;
    }
    printf("-----------------------------------\n");
    printf("|  Имя сотрудника |  ID  | Уровень |\n");
    printf("|----------------------------------|\n");    
    while (fread(&count, sizeof(int), 1, input_file) == 1) {
        if (fread(&emp, sizeof(struct Employee), 1, input_file) == 1) {
            for (i = 0; i < count; i++) {
                fwrite(&emp, sizeof(struct Employee), 1, output_file);
                printf("| %-15s | %-4s | %-7s |\n", emp.name, emp.id, emp.level);
            }
        }
    }
    
    fclose(input_file);
    fclose(output_file);
}

void search_employee() {
    FILE *file;
    struct Employee emp;
    char search_id[20];
    int found = 0;
    
    file = fopen("database.dat", "rb");
    if (file == NULL) {
        printf("Ошибка: не удалось открыть database.dat\n");
        return;
    }
    
    printf("Введите ID сотрудника: ");
    fgets(search_id, sizeof(search_id), stdin);
    search_id[strcspn(search_id, "\n")] = '\0';    
    while (fread(&emp, sizeof(struct Employee), 1, file)) {
        if (strcmp(emp.id, search_id) == 0) {
            printf("Имя: %s\n", emp.name);
            printf("ID: %s\n", emp.id);
            printf("Уровень: %s\n", emp.level);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Сотрудник с ID %s не найден\n", search_id);
    }
    fclose(file);
}
int main(int argc, char *argv[]) {
    FILE *file;
    FILE *binary_file;

    char line[256];
    char *name;
    char *id;
    char *level;
    struct Employee emp;

    if (argc != 2) {
        printf("Ошибка: не указано имя файла\n");
        return 1;
    }
    
    file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Ошибка: не удалось открыть файл\n");
        return 1;
    }

    binary_file = fopen("database.dat", "wb");
    if (binary_file == NULL) {
        printf("Ошибка: не удалось создать database.dat\n");
        fclose(file);
        return 1;
    }
    printf("-----------------------------------\n");
    printf("|  Имя сотрудника |  ID  | Уровень |\n");
    printf("|----------------------------------|\n");

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0';
        name = strtok(line, ";");
        id = strtok(NULL, ";");
        level = strtok(NULL, ";");
        strcpy(emp.name, name);
        strcpy(emp.id, id);
        strcpy(emp.level, level);
        fwrite(&emp, sizeof(struct Employee), 1, binary_file);
        printf("| %-15s | %-4s | %-7s |\n", name, id, level);
    }
    printf("------------------------------------\n");
    fclose(file);
    fclose(binary_file);
    search_employee();
    compress();
    decompress();
    print_compression_report();
    return 0;
}