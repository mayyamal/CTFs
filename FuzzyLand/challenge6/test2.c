#include <stdio.h>
void dummy() {
char s[] = "XXj0TYX45Pk13VX40473At1At1qu1qv1qwHcyt14yH34yhj5XVX1FK1FSH3FOPTj0X40PP4u4NZ4jWSEW18EF0V";
((size_t*)s)[15] = s;
}
int main() {
printf("No suspicious stuff in this application...\n");
dummy();
return 0;
}