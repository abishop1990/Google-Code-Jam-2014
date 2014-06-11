#include <stdio.h>

int main(int argc, char * argv [])
{

    //Blah blah blah file open validation
    if(argc < 2) 
    {
        fprintf(stderr,"Error: No file specified\n");
        return 1;
    }
    int fd = fopen(argv[1], "r");
    if(fd == NULL)
    {
        fprintf(stderr,"Error: Couldn't open file\n");
        return 2;
    }


    //Do the stuff


    //Write output to file
    char * outbuf;
    int ofd = fopen("output.txt","w");
    fputs(outbuf,ofd);
    fclose(ofd);

    return 0;
}
