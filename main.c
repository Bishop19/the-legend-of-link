#include <stdio.h>
#include <stdlib.h>
#include "parser.h"

void print_header (){
	printf("Content-Type: text/html; charset=utf-8\n\n"); 
	printf("<header><title> Rogue.</title></header>\n");  
	printf("<body>\n");
	printf("<svg width=1000 height=600>\n");  
}
void print_footer (){
	printf("</svg>\n");
	printf("</body>\n");
}
 
int main () {
	print_header ();
	parser(); 
	print_footer ();
	return 0; 
}
