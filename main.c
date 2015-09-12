/*
 * Copyright 2015 Emanuele Forestieri <forestieriemanuele@gmail.com>
 * Copyright 2015 Matteo Alessio Carrara <sw.matteoac@gmail.com> 
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */

/*TODO: Wtf non funziona con -O1/-O2/-O3*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <limits.h>

const char caratteri[]="0123456789ABCDEF"; /*caratteri utilizzabili in una password*/

void ehelp(char *nome) 
{
    fprintf(stderr, "Uso: %s numero_di_password\n", nome);
	exit(EXIT_FAILURE);
}

static inline short contac(register char *s,  char c) /*conta quante volte c è nella stringa s*/
{
    short n=0;
    while(*s) if(*s++==c) n++;
    return n;
}


static inline char *generapass(char *pass) /*mette in pass una password valida e restituisce il suo indirizzo*/
{

	short caratteriAF; /*contatore*/

	/*generazione stringa casuale*/
	nuovapass:;
	for(short i=0; i<10; i++) /*pass[10] deve essere '\0', non va modificato!*/
		pass[i]=caratteri[rand()%16]; /*TODO: collo di bottiglia?*/

	/*Verifica della password generata*/

	/*Non possono esserci più di due caratteri uguali consecutivi*/		    
	for(short i=0; i<8;)
    	if(pass[i]==pass[++i]) /*warning: operation on ‘i’ may be undefined [-Wsequence-point]*/
			if(pass[i]==pass[++i])
				goto nuovapass;
	
	/*Non possono esserci più di tre caratteri A-F uguali*/
	for(short i=10; i<16; i++) /*caratteri[10..15] sono A..F*/
		if(contac(pass, caratteri[i])>3)
			goto nuovapass;

	/*Non possono esserci più di due numeri uguali*/
	for(short i=0; i<10; i++)
		if(contac(pass, caratteri[i])>2)
			goto nuovapass;
	
	/*Non possono esserci più di 5 caratteri A-F*/
	caratteriAF=0;
	for(short i=0; i<10; i++)
		if ((pass[i]>='A')&&(pass[i]<='F'))
			caratteriAF++;
		if(caratteriAF>5)
			goto nuovapass;

	return pass;
}

int main(int argc, char **argv)
{
	#define help() ehelp(*argv)
	
    unsigned long long passcnt=0, npass;
	char pass[10+1]="xxxxxxxxxx";
	
    if (argc!=2)
        help();
	if (!strncmp(argv[1], "-h", 2) || !strncmp(argv[1], "--help", 6) || !strncmp(argv[1], "-?", 2))
		help();

	npass=strtoull(argv[1],NULL,0); /*atoi*/
	if(errno)
	{
		perror("Errore nella conversione del numero di password da stringa a ulong, strtoull()");
		exit(EXIT_FAILURE);
	}
	
    srand(time(NULL));

    for(; passcnt<npass; passcnt++)
			#ifndef BENCHMARK
            printf("%s\n", generapass(pass))
			#endif
			;

    return EXIT_SUCCESS;
}
