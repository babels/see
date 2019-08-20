/* a simple P-Box as implemented by DES
   AKA Transpositional Cipher */


#include <time.h>

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#include <string.h>

#include <sys/syscall.h>
#include <linux/random.h>


#define KSZ 64
static uint32_t ky[KSZ-1];


void
shuffle
  (array, n)
     int *array;
     size_t n;
{
  /* randome shuffle array */

  struct timespec nan;
  if (n > 1) {
     size_t i;
     for (i = 0; i < n - 1; i++) {

       clock_gettime(CLOCK_MONOTONIC, &nan);
       srand(nan.tv_nsec);

       size_t j  =  i + rand() / (RAND_MAX / (n - i) + 1);
       int t     =  array[j];
       array[j]  =  array[i];
       array[i]  =  t;
     }
  }
}


void
pbyd
  (buf, div)
     char *buf;		// character buffer
       int div;		// line split on int( delimiter )
{
  /* print buffer by divsor */

  printf("BUFFER\n");
  int k = 0;

  //  size_t bfl = strlen( buf );
  while( k  <  KSZ ) {
    if ( k % div == 0 ) {
      printf("\n");
    }

    char tk = buf[k];
    printf("%x\t", tk);

    k = k + 1;
  }
  printf("\n\n");

  return;
}


void
pitd
  (dig, div)
     unsigned int dig[];
       int div;
{
  /* print key  */

  printf("KEY\n");
  int k = 0;
  while( k  <=  KSZ-1 ) {

    if ( k % div == 0 ) {
      printf("\n");
    }

    int tk = dig[k];
    printf("%d\t", tk);

    k = k + 1;
  }
  printf("\n\n");

  return;
}



char
*rbuf
   (buf)
     char *buf;
{
  /* random hex buffer */

  int i;
  for(i = 0; i < KSZ; i++) {
    sprintf(buf + i, "%x", rand() % 16);
  }

  return buf;
}


char
*zecr
   (bff, zbf, ky, ze)
     char *bff;
     char *zbf;
     unsigned int ky[];
     short ze;
{
  /* pbox */

  int i=0;
  while( i < KSZ ) {
     int dx = ky[i];

     if( ze == 1 ) {		// encrypt
        char c = bff[dx];
        sprintf(zbf + i, "%c", c);

     } else {			// decrypt
        char c = bff[i];
        char tk[1] = "";
        sprintf(tk, "%c", c);
        memmove(zbf +dx,  tk, 1);
     }

     i++;
  }

  return zbf;
}


int
main
   (void)
{
  char buf[KSZ-1];		// origional buffer
  char nbf[KSZ-1];		// encrypted buffer
  char dbf[KSZ-1];		// decrypted buffer

  for( int k=0; k<KSZ; k++ ) {
     memmove(dbf +k, "A", 1);	// escape null terminator
  }

  int i=0;

  for( i=0;  i<KSZ; i++ ) {	// load range < key
     ky[i] = i;
  }

  shuffle(ky, i);		// key = rand( key )
  pitd(ky, 10);

  rbuf(buf);			// random hex buffer
  pbyd( buf, 10 );


  zecr(buf, nbf, ky, 1);	// encrypt
  pbyd( nbf, 10 );

  zecr(nbf, dbf, ky, 0);	// decrypt
  pbyd( dbf, 10 );

  size_t dln = strlen( dbf );

  //printf("random %s\n", buf);
  return 0;
}
