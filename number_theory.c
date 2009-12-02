/* A simple GMP test */

#include <stdio.h>
#include <gmp.h>

void seventh_fermat_number( void )
{
    mpz_t n;
    mpz_init( n );

    mpz_ui_pow_ui( n, 2, 128 );
    mpz_add_ui( n, n, 1);

    printf(" 2 ** 7 = 128\n");
    gmp_printf("2 ** (2 ** 7) + 1: %Zd\n", n);
}

void fast_fermat_alg( mpz_t n )
{ 
    mpz_t rem, k, y, fl_y, lhs, rhs;
    int d;

    mpz_init( rem );
    mpz_init( k );
    mpz_init( y );
    mpz_init( fl_y );
    mpz_init( lhs );
    mpz_init( rhs );    
    
    /* even number check*/
    mpz_mod_ui( rem, n, 2 );
    if (mpz_cmp_ui( rem, 0) == 0)
        gmp_printf( "%Zd is even\n", n );

    /* initialise bits */
    mpz_sqrt( k, n );
    mpz_add_ui( k, k, 1 );

    mpz_pow_ui( y, k, 2 );
    mpz_sub( y, y, n );

    d = 1;

    while ( 1 )
    {
        mpz_sqrt( fl_y, y );
        mpz_pow_ui(lhs, fl_y, 2 );
        mpz_pow_ui(lhs, lhs, 2 );
        mpz_pow_ui(rhs,    y, 2 );

        if ( mpz_cmp( lhs, rhs ) == 0 )
        {
            printf( "Have found factors:\n" );
            break;            
        }
        
        mpz_mul_si( lhs, k, 2 );
        mpz_add_ui( lhs, lhs, d );
        mpz_add( y, y, lhs );
        d = d + 2;

        mpz_cdiv_q_ui( rhs, n, 2 );
        if (mpz_cmp(fl_y, rhs) > 1)
        {
            printf( "No factor found\n" );
            return;
        }
    }

    mpz_add( k, n, y );
    mpz_sqrt( lhs, k );

    mpz_sqrt( rhs, y );
        
    gmp_printf( " the non-trivial factors of %Zd are\n", n );
    
    mpz_sub( k, lhs, rhs );
    gmp_printf( "%Zd and\n", k );
    
    mpz_add( k, lhs, rhs );
    gmp_printf( "%Zd\n", k );
}

int main (int argc, char const *argv[])
{
    mpz_t n;
    mpz_init( n );

#if 0
    /* set up 7th Fermat number */
    mpz_ui_pow_ui( n, 2, 128 );
    mpz_add_ui( n, n, 1);
#else
    /*mpz_set_ui( n, 3248523672894567297 );*/
    mpz_set_str( n, "3248523672894567297", 10 );
#endif

    /* try to factor it */
    fast_fermat_alg( n );

    return 0;
}
