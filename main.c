/*
 * Copyright 2015 Emanuele Forestieri <forestieriemanuele@gmail.com>
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
#include <time.h>
#include <string.h>
#define ULONG_MAX 4294967295
void help()//visualizza l'helper 
{
    printf("\nUso: ./technicolor_random [NUMERO_DI_PASSWORD/OPZIONI]");
    printf("\n\nOpzioni:");
    printf("\n-h, --help        mostra questa schermata ed esce");
    printf("\n\nEsempi:");
    printf("\n./technicolor_random 500000");
    printf("\n./technicolor_random 1000000");
    printf("\n./technicolor_random 2000000\n\n");
}
unsigned short verifica(unsigned char *s,unsigned char c)//conta caratteri uguali
{
    unsigned short n=0;
    while(*s)
    {
        if(*(s++)==c)
            n++;
    }
    return n;
}
bool controlla(unsigned char *s,unsigned char *c,unsigned short start,unsigned short end,unsigned short q)//controlla determinati caratteri
{
    bool t=1;
    for(unsigned short i=start;i!=end;i++)
        if(verifica(s,*(c+i))>q)
        {
            t=0;
            break;
        }
    return t;
}
bool tripli(unsigned char *s,unsigned char *c)//controlla caratteri consecutivi 
{
    bool t=1;
    while(*s)
        if(*(s++)==*s)
            if(*(s++)==*s)
            {
                t=0;
                break;
            }
    return t;
}
unsigned short cinque(unsigned char *s,unsigned char *c)//controlla caratteri
{
    unsigned short n=0;
    while(*s)
    {
        c+=9;
        while(*c)
            if(*s==*(c++))
                n++;
        s++;
    }
    return n;   
}
void genera(unsigned char *s,unsigned char *c)//genera stringa
{
    while(*s)
        *(s++)=*(c+rand()%+16);
}
int main(int argc,char** argv)//funzione principale
{
    if (argc!=2||strcmp(argv[1],"-h")==0||strcmp(argv[1],"--help")==0||strtoul(argv[1],NULL,0)>ULONG_MAX)
    {
        help();
        exit(EXIT_FAILURE);
    }
    srand(time(NULL));
    unsigned char s[11]="XXXXXXXXXX\0",c[17]="0123456789ABCDEF\0";
    register unsigned long cnt=0;
    while(cnt!=strtoul(argv[1],NULL,0))
    {
        genera(s,c);
        if(controlla(s,c,0,10,2)&&controlla(s,c,10,16,3)&&tripli(s,c)&&cinque(s,c)<5)
        {
            printf("%s\n",s);
            cnt++;
        }       
    }
    return EXIT_SUCCESS;
}
