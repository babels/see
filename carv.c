#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

/* A Hex Compiler, Reads in Hex ASCII output binary */

//to hex,asci:  hexdump -C curl.exe | cut -c11-58|tr -d '\n'| tr -d ' '
char asci[] = "000102030405060708090A0B0C0D0E0F101112131415161718191A1B1C1D1E1F202122232425262728292A2B2C2D2E2F303132333435363738393A3B3C3D3E3F404142434445464748494A4B4C4D4E4F505152535455565758595A5B5C5D5E5F606162636465666768696A6B6C6D6E6F707172737475767778797A7B7C7D7E7F808182838485868788898A8B8C8D8E8F909192939495969798999A9B9C9D9E9FA0A1A2A3A4A5A6A7A8A9AAABACADAEAFB0B1B2B3B4B5B6B7B8B9BABBBCBDBEBFC0C1C2C3C4C5C6C7C8C9CACBCCCDCECFD0D1D2D3D4D5D6D7D8D9DADBDCDDDEDFE0E1E2E3E4E5E6E7E8E9EAEBECEDEEEFF0F1F2F3F4F5F6F7F8F9FAFBFCFDFEFF";


int
usage()
{
  printf("Usage:\n\t./carv in.hex out.bin\n");
  return 1;
}


int
fatal
   (err)
     char *err;
{
  printf("[!] FATAL:  %s\n", err);
  return 1;
}


int
hex2asci
   (hx)
     char *hx;
{

  int q, j, k;

  // cmp asci tble every 2 chars
  for( k=0; k<256; k++) {

     j = k*2; // nib's are real.. they eat nybles
     q = j+1;

     // TODO: endianess
     if( asci[j] == hx[0] ) {
       if( asci[q] == hx[1] ) {

          return k;
       }
     }

  }

  return 0;
}



void
carv
   (ifd, ofd)
     FILE *ifd;
     FILE *ofd;
{

  // read line by line extracting nib, converting to asci, write to hex

  const size_t line_size = 3;
  char* line = malloc(line_size);

  int i=0;
  int r,d;

  while (fgets(line, line_size, ifd) != NULL)  {

     if( i % 2 ==  0 ) {
       r = hex2asci(line);
     } else {
       d = hex2asci(line);

        fprintf(ofd,"%c",r);
        fprintf(ofd,"%c",d);

        // to stdout
        //printf(fd,"%X",d);
        //printf(fd,"%X",d);

     }
     i++;

  }
  free(line);

  return;
}


int
main
   (argc, argv)
     int argc;
     char **argv;
{

  char *ifp, *ofp;
  FILE *ifd, *ofd;

  if( argc < 3 )
     return usage();

  ifp = argv[1];
  ofp = argv[2];

  ifd = fopen(ifp,"r");
  ofd = fopen(ofp,"ab");

  if( ifd == NULL || ofd == NULL )
     return fatal("Error opening file");

  carv( ifd, ofd );

  printf("you got it\n");

  fclose(ifd);
  fclose(ofd);

  return 0;
}
