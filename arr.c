#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

/* pythonic split, who needs constant structs */


/* TODO: in each query type, ensure that newline, return, and zero
function as both delimiter and last character of element by checking for the the other two
terminators at the end of each line, adjust string size and manually insert a null term */

int elm;			// number of elements in array

typedef void (*fptr) ();

// ptr[0] will hold the total number of elements
struct array {
   int  pnt;			// pointer on arr from 1 = ele[len]
   int  psz;			// length of element
   int  pos;			// starting position on origional array
}; struct array splt[1024];	// return element + max_size


void
Fatal
   (err)
     char* err;
{
  printf("FATAL:  %s\n", err);
  exit(1);
}

void
something
   (buf)
     char* buf;
{
  printf("buff %s\n",buf);
//  free(buf);
  return;
}

void
logfp
   (txt)
     char *txt;         // text buffer
{
  /* writes text buffer to log path */

  FILE *fd;

  fd = fopen("log.txt", "a");

  fprintf(fd, "%s\n", txt);
  fclose(fd);

  return;
}


char*
concat
   (rbf,fp)
     char* rbf;
     char* fp;
{
   // read text file to buffer
   int string_size, read_size;
   FILE *fd = fopen(fp, "r");

   if (fd) {
       fseek(fd, 0, SEEK_END);
       string_size = ftell(fd);
       rewind(fd);

       rbf = (char*) malloc(sizeof(char) * (string_size + 1) );
       read_size = fread(rbf, sizeof(char), string_size, fd);
       rbf[string_size] = '\0';

       if (string_size != read_size) {
           free(rbf);
           rbf = NULL;
       }
       fclose(fd);
    }
    return rbf;
}


void
loadar
   (wrds)
     char* wrds;
{
  // load buffer to structure
  int i=1; 				// element pointer, iterator > while
  int k=0; 				// character pointer
  char* lim = " ";			// delimiter

  int ll = strlen(lim);			// delimiter length
  int wl = strlen(wrds);		// in buffer length

  char* nwd = realloc(NULL,0);		// copy origional leaving intact
  nwd = realloc(nwd, wl);
  memmove(nwd,wrds,wl);

  char* ele = strtok(nwd, lim);


  while ( ele != NULL ) {

     int eln = strlen( ele );
     splt[i].pnt = i;			// element pointer
     splt[i].psz = eln;		// element length
     splt[i].pos = k;			// element
     elm = i;
     printf("element %d  length  %d  position  %d\n", i, eln, k);

  i++;					// math

  k = k + eln + ll;			// position next pointer at end of last
  ele = strtok(NULL, lim);		// increment element
  }

  splt[0].pnt = i;			// first element as max element count
  return;
}



void
split
  (pew, ptr, wrds)
     fptr  pew;				// out function
     int   ptr;				// in  index
     char *wrds;			// in  buffer
{
  /* splits character buffer(wrds) by index(ptr) & pass' each element to the function pew */

  int i;
  int wl = strlen(wrds) +1;

  char* nwrd = realloc(NULL, 0);        // initialize copy
  char* bff  = realloc(NULL, 0);	// initialize return buuffer

  nwrd = realloc(nwrd, wl);		// copy origional leaving intact
  memmove(nwrd, wrds, wl);


  int rt;				// element number
  rt = splt[ptr].pnt-1;
  int lst = splt[0].pnt-1;

  if ( ptr > lst )
     Fatal("index out of bounds");

  int tr = splt[0].pnt;			// last element
  if ( ptr == 0 ) {			// assumes we dont need to size just index
     printf("we have all\n");
     for( i=1; i<tr; i++) {

       int ln = splt[i].psz;		// element length
       int ps = splt[i].pos;		// buffer position
       printf(" length %d position %d\n,", ln,ps);

       char* ele = realloc(NULL,0);
       ele = realloc( ele, ln );

       memmove(ele, nwrd+ps, ln);
       memmove(ele+ln, "\0", 1);

       pew(ele);
       free(ele);    }
    return;
  }

  if ( ptr < 0 )
    rt = lst + ptr + 1;			// negetive index  lst +(-ptr) +1;

  if ( ptr == -1 )
    rt = lst;				// last index

  int esz = splt[rt].psz;		// size of element at ptr
  int wrd = splt[rt].pos;		// character position on origional buffer
  bff = realloc(bff, esz);		// allocate memory to return buffer
  memmove(bff, nwrd+wrd, esz);		// move date into buffer
  memmove(bff+esz, "\0", 1);		// ensure nullterm, see todo

  pew(bff);
  return;
}


void
main
   (void)
{
  //  char* fp   = "txt.txt";		// in file path
  //  char* wrds = concat(wrds, fp);	// in text buffer

  char *wrds = "I am the very model of a modern major general";
  int   prog = something;               // function to pass to element(s)

  loadar(wrds);                         // in struct array

  int sze = splt[0].pnt-1;
  int i=1;

  while(i<=sze) {
     char *tik = realloc(NULL, 0);
     char *tok=NULL;
     tok = realloc(NULL ,sizeof(tok));                  // array element

     int tsz = splt[i].psz;             // token size
     int pos = splt[i].pos;             // array position
     int pnt = splt[i].pnt;             // buffer position

     tok = realloc(tok, tsz +1);

     memmove(tok, wrds+pos, tsz);
     memmove(tok+tsz, "\0", 1);

     printf("size %d\nposition %d\ntoken %s\n", tsz,pos,tok);
     something(tok);

     memset(tok, '\0', sizeof(tok));
     logfp(tok);
     free(tok);
     i++;
  }
     printf("size %d\nposition %d\ntoken %s\n", tsz,pos,tok);
     something(tok);

     memset(tok, '\0', sizeof(tok));
     logfp(tok);
     free(tok);
     i++;
  }


////  split(prog, -1, wrds);	// last element
//  split(prog,  5, wrds);	// fifth element
    split(prog,  0, wrds);	// all
//  split(prog, -5, wrds);	// fifth from last


  return;
}
