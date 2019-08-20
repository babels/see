/* simple hexdump */

#include <stdio.h>
#include <stdlib.h>
#define HEX_OFFSET    0
#define ASCII_OFFSET 51
#define NUM_CHARS    16


/* I modified this from some example */

void   hexdump    (char* prog_name, char * filename);

/* Clear the display line.  */
void   clear_line (char *line, int size);

/* Put a character (in hex format into the display line. */
char * hex   (char *position, int c);

/* Put a character (in ASCII format into the display line. */
char * ascii (char *position, int c);


main(int argc, char * argv[])
{
    char *prog_name="hexdump";

    if (argc != 2)
    {
        printf("\n\t%s syntax:\n\n", argv[0]);
        printf("\t\t%s filename\n\n", argv[0]);
        exit(0);
    }

    hexdump( argv[0], argv[1]);
}


void hexdump(char* prog_name, char * filename)
{
    int c='\0';                 /* Character read from the file */

    char * hex_offset;		/* Position of the next character in Hex     */

    char * ascii_offset;	/* Position of the next character in ASCII.      */

    FILE *ptr;			/* Pointer to the file.   */

    char line[81];		/* O/P line.      */

    /* Open the file */
    ptr = fopen(filename,"r");
    if ( ferror(ptr) )
    {
        printf("\n\t%s: Unable to open %s\n\n", prog_name, filename);
        exit(0);
    }


    while (c != EOF )
    {
        clear_line(line, sizeof line);
        hex_offset   = line+HEX_OFFSET;
        ascii_offset = line+ASCII_OFFSET;

        while ( ascii_offset < line+ASCII_OFFSET+NUM_CHARS
                &&(c = fgetc(ptr)) != EOF  )
        {
            /*  HEX    */
            hex_offset = hex(hex_offset, c);

            /* ASCII   */
            ascii_offset = ascii(ascii_offset, c);

        }
        printf("%s", line);
    }

    fclose(ptr);
}

void clear_line(char *line, int size)
{
    int count;

    for  (count=0; count < size; line[count]='\0', count++);
}

char * ascii(char *position, int c)
{
    /* If the character is NOT printable
     * replace it with a '.'  */
    if (!isprint(c)) c='.';

    sprintf(position, "%c", c);    /* Put the character to the line
                                    * so it can be displayed later */

    /* Return the position of the next
     * ASCII character.   */
    return(++position);
}

char * hex(char *position, int c)
{
    int offset=2;

    if( c == " " ) {
      return(++position+offset);
    }
    sprintf(position, "%02X", (unsigned char) c);


    return (position+offset);
}

