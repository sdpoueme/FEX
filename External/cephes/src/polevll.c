/*							polevll.c
 *							p1evll.c
 *
 *	Evaluate polynomial
 *
 *
 *
 * SYNOPSIS:
 *
 * int N;
 * float128_t x, y, coef[N+1], polevl[];
 *
 * y = polevll( x, coef, N );
 *
 *
 *
 * DESCRIPTION:
 *
 * Evaluates polynomial of degree N:
 *
 *                     2          N
 * y  =  C  + C x + C x  +...+ C x
 *        0    1     2          N
 *
 * Coefficients are stored in reverse order:
 *
 * coef[0] = C  , ..., coef[N] = C  .
 *            N                   0
 *
 *  The function p1evll() assumes that coef[N] = 1.0 and is
 * omitted from the array.  Its calling arguments are
 * otherwise the same as polevll().
 *
 *
 * SPEED:
 *
 * In the interest of speed, there are no checks for out
 * of bounds arithmetic.  This routine is used by most of
 * the functions in the library.  Depending on available
 * equipment features, the user may wish to rewrite the
 * program in microcode or assembly language.
 *
 */


/*
Cephes Math Library Release 2.2:  July, 1992
Copyright 1984, 1987, 1988, 1992 by Stephen L. Moshier
Direct inquiries to 30 Frost Street, Cambridge, MA 02140
*/
#include "mconf.h"


/* Polynomial evaluator:
 *  P[0] x^n  +  P[1] x^(n-1)  +  ...  +  P[n]
 */
float128_t cephes_f128_polevll( float128_t x, void *PP, int n )
{

struct softfloat_state state = {};
register float128_t y;
float128_t *P;

P = (float128_t *) PP;
y = *P++;
do
	{
	y = f128_add(&state, f128_mul(&state, y, x), *P++);
	}
while( --n );
return(y);
}



/* Polynomial evaluator:
 *  x^n  +  P[0] x^(n-1)  +  P[1] x^(n-2)  +  ...  +  P[n]
 */
float128_t cephes_f128_p1evll( float128_t x, void *PP, int n )
{
struct softfloat_state state = {};
register float128_t y;
float128_t *P;

P = (float128_t *) PP;
n -= 1;
y = f128_add(&state, x, *P++);
do
	{
	y = f128_add(&state, f128_mul(&state, y, x), *P++);
	}
while( --n );
return( y );
}
