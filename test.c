#include <stdio.h>

int main() {
    char buffer[100];
    printf("Enter data (stops at comma): ");
    scanf("%99[^,]", buffer); // Reads up to 99 chars, stopping at ','
    printf("You entered: %s\n", buffer);
    return 0;
}