# technicolor_random #

Generatore di password casuali per router technicolor

## Compilazione ##

Se si usa gcc, usare il parametro -std=c99

## Input/Output ##

Il programma prende da stdin il numero di password da calcolare, quindi restituisce su stdout le password e su stderr gli errori.

## Limiti ##

 * Possono essere calcolate al massimo ULONG_LONG_MAX password (vedere limits.h)
 * Se si salvano le password in un file, la dimensione sarà di npassword*11 byte (10 char per password+\n)
  
  
Aggiornamenti: [GitHub] (https://github.com/emanueleforestieri/linux_update/) 