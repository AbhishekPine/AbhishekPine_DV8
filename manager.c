#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_NAMES 5
#define NUM_FORMATIONS 3

char* names[NUM_NAMES] = {"John", "Mike", "Sarah", "David", "Emily"};
char* formations[NUM_FORMATIONS] = {"4-4-2", "3-5-2", "4-3-3"};

typedef struct {
    char* name;
    char* formation;
} Manager;

void initManager(Manager* manager) {
    srand(time(NULL));
    manager->name = names[rand() % NUM_NAMES];
    manager->formation = formations[rand() % NUM_FORMATIONS];
}

int main() {
    Manager manager;
    initManager(&manager);
    printf("Name: %s\n", manager.name);
    printf("Formation: %s\n", manager.formation);
    return 0;
}