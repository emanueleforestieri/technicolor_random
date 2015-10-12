# technicolor_random #

Random password generator for technicolor routers

## Compilation ##

When using gcc, use the parameter -std=c99 

## Input/Output ##

The program takes from stdin the number of passwords to be calculated, then returns password on stdout and errors on stderr.

## Limits ##

 * Can be calculated at the maximum ULONG_LONG_MAX passwords (see limits.h)
 * If you save your password in a file, the size will be npassword * 11 bytes (10 char password to + \n)
  
  
Updates: [GitHub] (https://github.com/emanueleforestieri/technicolor_random)

Donations: [Paypal] (https://www.paypal.me/emanueleforestieri)
