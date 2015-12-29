#include <stdio.h>

int main(int argc, char* argv[])  {
    if (argc < 2) {
        return 1;
    }
    printf("%s %s %s %s", argv[4], argv[5], argv[6], argv[7]);
    return 0;
}
