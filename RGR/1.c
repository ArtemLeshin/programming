#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

#define MAX_TEXT_LEN 256
#define MAX_LEADERS 5
#define MAX_NAME 50

// Структура для таблицы лидеров
typedef struct {
    char name[MAX_NAME];
    int wpm;
    float accuracy;
    int score;
} Leader;

Leader leaders[MAX_LEADERS];
int leader_count = 0;

// Список предложений
const char *sentences[] = {
    "The quick brown fox jumps over the lazy dog",
    "Programming in C is fun and challenging",
    "Practice makes perfect when learning to type",
    "Speed and accuracy are both important metrics",
    "Dynamic mode changes text automatically over time",
    "Snake mode increases difficulty after each success"
};
const int sentence_count = sizeof(sentences) / sizeof(sentences[0]);

// Слова для режима "слова"
const char *words[] = { "keyboard", "typing", "speed", "accuracy", "practice", "skill", "master", "train" };
const int word_count = sizeof(words) / sizeof(words[0]);

// Уровни сложности
typedef struct {
    int min_len;
    int max_len;
    const char *name;
} Difficulty;

Difficulty difficulties[] = {
    {10, 30, "Easy"},
    {30, 70, "Medium"},
    {70, 150, "Hard"}
};
int diff_count = 3;

// ========== Функции для работы с клавиатурой (UNIX/macOS) ==========
int kbhit(void) {
    struct termios oldt, newt;
    int ch;
    int oldf;
    
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
    
    ch = getchar();
    
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    
    if (ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }
    return 0;
}

char getch(void) {
    struct termios oldt, newt;
    char ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

void clear_screen() {
    printf("\033[2J\033[1;1H"); // ANSI escape codes для очистки экрана
}

void wait_key() {
    printf("\nНажмите Enter для продолжения...");
    getchar();
    getchar(); // для очистки буфера
}

// Генерация случайного текста
void generate_text(char *buffer, int mode, int difficulty_level) {
    buffer[0] = '\0';
    int len = 0;
    int target_len = rand() % (difficulties[difficulty_level].max_len - difficulties[difficulty_level].min_len + 1)
                     + difficulties[difficulty_level].min_len;
    
    if (mode == 1) {
        while (len < target_len) {
            int idx = rand() % word_count;
            if (len > 0) strcat(buffer, " ");
            strcat(buffer, words[idx]);
            len = strlen(buffer);
        }
    } else {
        int idx = rand() % sentence_count;
        strcpy(buffer, sentences[idx]);
    }
}

// Вычисление точности
float calculate_accuracy(const char *original, const char *input) {
    int correct = 0, total = strlen(original);
    for (int i = 0; i < total && input[i] != '\0'; i++) {
        if (original[i] == input[i]) correct++;
    }
    return (total > 0) ? (correct * 100.0f / total) : 0;
}

// Сохранение в таблицу лидеров
void save_leaderboard(const char *name, float accuracy, int wpm, int score) {
    leaders[leader_count].wpm = wpm;
    leaders[leader_count].accuracy = accuracy;
    leaders[leader_count].score = score;
    strcpy(leaders[leader_count].name, name);
    leader_count++;
    
    for (int i = 0; i < leader_count - 1; i++) {
        for (int j = i + 1; j < leader_count; j++) {
            if (leaders[i].score < leaders[j].score) {
                Leader temp = leaders[i];
                leaders[i] = leaders[j];
                leaders[j] = temp;
            }
        }
    }
    if (leader_count > MAX_LEADERS) leader_count = MAX_LEADERS;
}

// Показать таблицу лидеров
void show_leaderboard() {
    clear_screen();
    printf("======= ТАБЛИЦА ЛИДЕРОВ =======\n");
    printf("Место | Имя                | Очки | WPM  | Точность\n");
    printf("------+--------------------+------+------+---------\n");
    for (int i = 0; i < leader_count; i++) {
        printf("%4d  | %-18s | %4d | %4d | %6.1f%%\n",
               i + 1, leaders[i].name, leaders[i].score, leaders[i].wpm, leaders[i].accuracy);
    }
    if (leader_count == 0) printf("Нет записей. Пройдите тест!\n");
    wait_key();
}

// ========== РЕЖИМ 1: Обычный тест ==========
void mode_normal() {
    clear_screen();
    printf("=== РЕЖИМ: СЛУЧАЙНОЕ ПРЕДЛОЖЕНИЕ ===\n\n");
    
    int idx = rand() % sentence_count;
    const char *original = sentences[idx];
    printf("Текст для ввода:\n%s\n\n", original);
    printf("Нажмите Enter и начинайте печатать...");
    getchar();
    
    char input[MAX_TEXT_LEN];
    printf("\n\nВаш ввод:\n");
    fgets(input, MAX_TEXT_LEN, stdin);
    input[strcspn(input, "\n")] = '\0';
    
    int correct = 0, errors = 0;
    for (int i = 0; original[i] != '\0'; i++) {
        if (input[i] == original[i]) correct++;
        else if (input[i] != '\0') errors++;
        else errors++;
    }
    
    printf("\nРезультат:\n");
    printf("Правильно: %d\n", correct);
    printf("Ошибок: %d\n", errors);
    wait_key();
}

// ========== РЕЖИМ 2: Пользовательские настройки ==========
void mode_custom() {
    int text_type, time_limit, difficulty;
    printf("Выберите тип текста (1-слова, 2-предложения): ");
    scanf("%d", &text_type);
    printf("Выберите уровень сложности (0-Easy, 1-Medium, 2-Hard): ");
    scanf("%d", &difficulty);
    printf("Время теста (секунд): ");
    scanf("%d", &time_limit);
    
    clear_screen();
    char original[MAX_TEXT_LEN];
    generate_text(original, text_type, difficulty);
    printf("Текст:\n%s\n\n", original);
    printf("У вас %d секунд. Нажмите Enter для старта...", time_limit);
    getchar();
    getchar();
    
    char input[MAX_TEXT_LEN] = {0};
    time_t start = time(NULL);
    int pos = 0;
    
    while (time(NULL) - start < time_limit) {
        if (kbhit()) {
            char ch = getch();
            if (ch == '\n') break;
            if (ch == 127 && pos > 0) { // backspace
                pos--;
                input[pos] = '\0';
            } else if (ch >= 32 && ch <= 126 && pos < MAX_TEXT_LEN - 1) {
                input[pos++] = ch;
                input[pos] = '\0';
            }
            printf("\rВаш ввод: %s    ", input);
            fflush(stdout);
        }
        usleep(50000);
    }
    
    float accuracy = calculate_accuracy(original, input);
    printf("\n\nТочность: %.1f%%\n", accuracy);
    wait_key();
}

// ========== РЕЖИМ 3: Динамический ==========
void mode_dynamic() {
    clear_screen();
    printf("=== ДИНАМИЧЕСКИЙ РЕЖИМ ===\n");
    int interval = 5;
    int duration = 30;
    printf("Текст будет меняться каждые %d сек в течение %d сек.\n", interval, duration);
    printf("Нажмите Enter для старта...");
    getchar();
    getchar();
    
    time_t start = time(NULL);
    int total_correct = 0, total_errors = 0, rounds = 0;
    
    while (time(NULL) - start < duration) {
        char original[MAX_TEXT_LEN];
        generate_text(original, 1, 0);
        clear_screen();
        printf("Раунд %d. Введите: %s\n", rounds + 1, original);
        printf("Ваш ввод: ");
        
        char input[MAX_TEXT_LEN];
        fgets(input, MAX_TEXT_LEN, stdin);
        input[strcspn(input, "\n")] = '\0';
        
        for (int i = 0; original[i] != '\0'; i++) {
            if (original[i] == input[i]) total_correct++;
            else if (input[i] != '\0') total_errors++;
            else total_errors++;
        }
        rounds++;
        if (time(NULL) - start + interval > duration) break;
        sleep(interval);
    }
    
    printf("\nДинамический режим завершён!\n");
    printf("Всего символов правильно: %d\n", total_correct);
    printf("Ошибок: %d\n", total_errors);
    wait_key();
}

// ========== РЕЖИМ 4: Змейка ==========
void mode_snake() {
    clear_screen();
    printf("=== РЕЖИМ ЗМЕЙКА ===\n");
    printf("При правильном вводе сложность растёт. При ошибке — падает.\n");
    printf("Нажмите Enter для старта...");
    getchar();
    getchar();
    
    int level = 0;
    int score = 0;
    char input[MAX_TEXT_LEN];
    
    while (level < 5 && level >= 0) {
        char text[MAX_TEXT_LEN];
        int len = 10 + level * 5;
        for (int i = 0; i < len; i++) {
            text[i] = 'a' + (rand() % 26);
        }
        text[len] = '\0';
        
        clear_screen();
        printf("Уровень %d | Очки: %d\n", level + 1, score);
        printf("Текст: %s\n", text);
        printf("Ваш ввод: ");
        fgets(input, MAX_TEXT_LEN, stdin);
        input[strcspn(input, "\n")] = '\0';
        
        if (strcmp(text, input) == 0) {
            printf("✅ Верно!\n");
            score += 100 * (level + 1);
            level++;
            sleep(1);
        } else {
            printf("❌ Ошибка!\nПравильно: %s\n", text);
            if (level > 0) level--;
            sleep(2);
        }
    }
    
    if (level >= 5) printf("\n🎉 ПОБЕДА! Очки: %d\n", score);
    else printf("\nИгра окончена. Очки: %d\n", score);
    
    wait_key();
}

// ========== РЕЖИМ 5: Тренировка клавиш ==========
void mode_key_practice() {
    clear_screen();
    printf("=== ТРЕНИРОВКА КЛАВИШ ===\n");
    printf("Вводите появляющиеся символы.\n");
    printf("Нажмите Enter...");
    getchar();
    getchar();
    
    int correct = 0, total = 0;
    char target;
    
    for (int i = 0; i < 20; i++) {
        target = "abcdefghijklmnopqrstuvwxyz1234567890"[rand() % 36];
        printf("\nВведите: %c\n", target);
        char ch = getch();
        printf("%c\n", ch);
        if (ch == target) {
            printf("✅\n");
            correct++;
        } else {
            printf("❌ (было: %c)\n", target);
        }
        total++;
    }
    
    printf("\nТочность: %.1f%%\n", (correct * 100.0f / total));
    wait_key();
}

// ========== ГЛАВНОЕ МЕНЮ ==========
int main() {
    srand(time(NULL));
    leader_count = 0;
    
    int choice;
    do {
        clear_screen();
        printf("============= ТРЕНАЖЁР ПЕЧАТИ =============\n");
        printf("1. Обычный тест (случайное предложение)\n");
        printf("2. Пользовательские настройки\n");
        printf("3. Динамический режим\n");
        printf("4. Режим 'Змейка'\n");
        printf("5. Тренировка отдельных клавиш\n");
        printf("6. Таблица лидеров\n");
        printf("0. Выход\n");
        printf("============================================\n");
        printf("Выберите: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: mode_normal(); break;
            case 2: mode_custom(); break;
            case 3: mode_dynamic(); break;
            case 4: mode_snake(); break;
            case 5: mode_key_practice(); break;
            case 6: show_leaderboard(); break;
            case 0: printf("До свидания!\n"); break;
            default: printf("Неверный выбор!\n"); wait_key();
        }
    } while (choice != 0);
    
    return 0;
}