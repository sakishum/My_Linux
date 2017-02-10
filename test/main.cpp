#include <cstdio> 
int main() { 
	const char *s= "int main() { char *s=%c%s%c; printf(s,34,s,34); }"; 
	printf(s,34,s,34); 
 }
