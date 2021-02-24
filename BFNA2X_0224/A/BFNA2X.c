#include <stdio.h>

int main() {
	FILE *fp = fopen("Meszaros.txt", "w");
	fprintf(fp, "Meszaros Akos\nMernok Informatikus\nBFNA2X");
	fclose(fp);

	char s[100];
	fp = fopen("Meszaros.txt", "r");

	while (fgets(s, 100, fp) != NULL)
		printf("%s", s);

	fclose(fp);

	return 0;
}