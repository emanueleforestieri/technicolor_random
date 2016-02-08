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
#include <string.h>
#include <errno.h>
#include <time.h>

#define byte char

const char characters[]="0123456789ABCDEF"; /*usable characters in a password*/

void ehelp(char *name) 
{
	fprintf(stderr, "Use: %s [password_number]\n", name);
	exit(1);
}

static inline byte contac(register char *s,  char c) /*count how many times there is in the string s*/
{
	byte n=0;
	while(*s) if(*s++==c) n++;
	return n;
}

static inline char *generatepass(char *pass) /*It puts pass a valid password and returns its address*/
{

	/*generating random string*/
	newpass:;
	for(byte i=0; i<10; i++) /*pass[10] has to be '\0', should not be changed!*/
		pass[i]=characters[rand()%16]; /*TODO: collo di bottiglia?*/

	/*Check the generated password, FUNCTIONS ORDER FOR SPEED*/

	/*There can be no more than two consecutive identical characters*/		    
	for(byte i=0; i<8; i++)
	{
		if(pass[i]==pass[i+1])
		{
			i++;
			if(pass[i]==pass[i+1])
				goto newpass;
		}
	}
	
	/*There can be no more than three identical characters*/
	for(byte i=0; i<16; i++)
		if(contac(pass, characters[i])>3)
			goto newpass;
	
	/*There can be no more than 5 characters A-F or 9 numbers*/
	short charactersAF=0,numbers=0; /*counters*/
	for(byte i=0; i<10; i++)
		(pass[i]>='A' && pass[i]<='F') ? charactersAF++ : numbers++;
	if((charactersAF>5)||(numbers>9))
		goto newpass;
		
	return pass;
}

int main(int argc, char **argv)
{
	#define help() ehelp(*argv)
	
	unsigned long long npass;
	char pass[10+1]="xxxxxxxxxx";
	
	if (argc!=2)
		help();
	if (!strncmp(argv[1], "-h", 2) || !strncmp(argv[1], "--help", 6) || !strncmp(argv[1], "-?", 2))
		help();

	npass=strtoull(argv[1],NULL,0); /*ascii to unsigned long long*/
	if(errno)
	{
		perror("Error in the conversion of the number of password from string to ulong, strtoull()");
		exit(1);
	}
	
	srand(time(NULL));

	for(unsigned long long passcnt=0; passcnt<npass; passcnt++)
		#ifndef BENCHMARK
		printf("%s\n", generatepass(pass));
		#else
		generatepass(pass);
		#endif	

	return 0;
}
