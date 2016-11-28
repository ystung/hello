#include <stdio.h>
#include <time.h>
#include <sys/time.h>

int main(void){
char text[100];
time_t now = time(NULL);
struct tm *t = localtime(&now);


strftime(text, sizeof(text)-1, "%Y-%m-%d %H:%M:%S", t);
printf("Current Date: %s", text);
}

