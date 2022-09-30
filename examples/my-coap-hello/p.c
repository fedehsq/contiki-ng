#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int main()
{
    char *buf = (char *)calloc(300, sizeof(char));
    sprintf(buf, "Temperature: %d, Humidity: %d, Battery Level: %d", 1, 2, 3);
    memset(buf, 0, 64);
    printf("%s", buf);
}