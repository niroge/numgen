#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

void scan_check_num(int *);
void write_file(char *, int);
void get_linefeed();

int main(void)
{
	int nmin, nmax, gen, ins, tent = 0;
	char nome[128];
	memset(nome, '\0', sizeof nome);
	
	printf("Numero minimo: ");
	scan_check_num(&nmin);

	printf("Numero massimo: ");
	scan_check_num(&nmax);

	if (nmax <= nmin) {
		fprintf(stderr, "[-] Excuse me what the fuck?\n");
		exit(4);
	}

	get_linefeed();
	printf("Nome utente: ");
	fgets(nome, sizeof nome, stdin);
	strtok(nome, "\n");

	if (nome[127] != '\0') {
		fprintf(stderr, "Overflow detected, go fund yourself\n");
		exit(2);
	}

	srand(time(0));
	gen = random();
	gen %= nmax;
	gen += nmin;

	printf("Numero casuale: %d\n", gen);

	while (ins != gen) {
		fprintf(stdout, "Numero: ");
		scan_check_num(&ins);
		tent++;

		if (ins < gen)
			fprintf(stdout, "Più grande\n");

		else if (ins > gen)
			fprintf(stdout, "Più piccolo\n");
	}

	write_file(nome, tent);
	
	exit(0);
}

void scan_check_num(int *number)
{
	if (scanf("%d", number) != 1) {
		fprintf(stderr, "[-] Fucking retard\n");
		exit(1);
	}
}

void check_null(int num) {
	if (num == NULL) {
		fprintf(stderr, "Cannot do that!\n");
		exit(0);
	}
}


void write_file(char *nome, int numero)
{
	int fd = open("database.txt", O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
	check_null(fd);
	char output[512];

	memset(output, '\0', sizeof output);
	sprintf(output, "%s:%d", nome, numero);
	strcat(output, "\n");

	write(fd, output, sizeof output);

	check_null(close(fd));
}
		
void get_linefeed()
{
	char a;
	scanf("%c", &a);
}
