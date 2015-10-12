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

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <errno.h>

const char caratteri[]="0123456789ABCDEF"; /*usable characters in a password*/

void ehelp(char *nome) 
{
	fprintf(stderr, "Uso: %s numero_di_password\n", nome);
	exit(EXIT_FAILURE);
}

static inline short contac(register char *s,  char c) /*count how many times there is in the string s*/
{
	short n=0;
	while(*s) if(*s++==c) n++;
	return n;
}

static inline char *generapass(char *pass) /*It puts pass a valid password and returns its address*/
{

	short caratteriAF; /*counter*/

	/*generating random string*/
	nuovapass:;
	for(short i=0; i<10; i++) /*pass[10] has to be '\0', should not be changed!*/
		pass[i]=caratteri[rand()%16]; /*TODO: collo di bottiglia?*/

	/*Check the generated password, FUNCTIONS ORDER FOR SPEED*/

	/*There can be no more than two consecutive identical characters*/		    
	for(short i=0; i<8; i++)
	{
		if(pass[i]==pass[i+1])
		{
			i++;
			if(pass[i]==pass[i+1])
				goto nuovapass;
		}
	}
	
	/*There can be no more than three identical characters*/
	for(short i=0; i<16; i++)
		if(contac(pass, caratteri[i])>3)
			goto nuovapass;
	
	/*There can be no more than 5 characters A-F*/
	caratteriAF=0;
	for(short i=0; i<10; i++)
		if((pass[i]>='A')&&(pass[i]<='F'))
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
		printf("%s\n", generapass(pass));
		#else
		generapass(pass);
		#endif	

	return EXIT_SUCCESS;
}
