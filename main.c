#include <stdio.h>
#include "memory.h"
int main() {
    pList memoryList;
    initList(&memoryList, 100);
    run(memoryList);
}
