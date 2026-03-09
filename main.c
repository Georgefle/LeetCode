#include <stdio.h>
#include <stdlib.h>

void hash(int a, int b, char* odd, char* even) {
    if (rand() % 2) {
        if (a % 2) {
            odd[0] = 'a';
            odd++;
        }
        else {
            even[0] = 'a';
            even++;
        }
        if (b % 2) {
            odd[0] = 'b';
        }
        else {
            even[0] = 'b';
        }
    }
    else {
        if (b % 2) {
            odd[0] = 'b';
            odd++;
        }
        else {
            even[0] = 'b';
            even++;
        }
        if (a % 2) {
            odd[0] = 'a';
        }
        else {
            even[0] = 'a';
        }
    }
}

int find_a(int a, char* odd, char* even) {
    if (a % 2) {
        if (odd[0] == 'a') return 1;
        return 2;
    }
    if (even[0] == 'a') return 1;
    return 2;
}

int main(void) {
    int count = 0;
    for (int i = 1; i <= 2000; i++) {
        int a = rand();
        int b = rand();
        char odd_slot[2];
        char even_slot[2];
        hash(a, b, odd_slot, even_slot);
        int find_times = find_a(a, odd_slot, even_slot);
        count += find_times;
    }
    printf("%f", count / 2000.0);

}