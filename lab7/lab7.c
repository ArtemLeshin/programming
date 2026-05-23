#include <stdio.h>
#include <string.h>

int main() {
    char text[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";
    int len = strlen(text);
    for (int i = len - 1; i >= 0; i--) {
        if (i == 0 || text[i-1] == ' ') {
            for (int j = i; j < len && text[j] != ' '; j++) {
                printf("%c", text[j]);
            }
            printf(" ");
        }
    }
    
}

