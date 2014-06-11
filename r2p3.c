/*
 * r2.c 
 * Written by Alan Bishop 4/25/2014
 */

#include <stdio.h>
#include <string.h>

int generateTheLists(int * LIST, int N);

int main(int argc, char * argv [])
{
    char outbuf[100000]; 
    outbuf[0] = '\0';
    //Blah blah blah file open validation
    if(argc < 2) 
    {
        fprintf(stderr,"Error: No file specified\n");
        return 1;
    }
    FILE * fd = fopen(argv[1], "r");
    if(fd == NULL)
    {
        fprintf(stderr,"Error: Couldn't open file\n");
        return 2;
    }

    //Parse the input data 
    int ncases =  -1;
    fscanf(fd,"%d\n",&ncases);
    if(ncases == -1) 
    {
        printf("Error reading from the file: couldn't read ncases\n");
        return 3;
    }
    printf("%d cases:\n",ncases);
    int i;
    int numgood = 0;
    for(i = 0; i < ncases; ++i)
    {

        int N;
        fscanf(fd,"%d\n",&N);
        int LIST[1000];
        //LOGIC GOES HERE
        int j;
        for(j=0;j<N;++j)
        {
            if(j==N-1) fscanf(fd,"%d\n",&LIST[i]);
            else fscanf(fd,"%d\n",&LIST[j]);
        }        

        int blnIsGood =  generateTheLists(LIST,N);
        if(blnIsGood) ++numgood;
        //Write output to buffer
        char line[50];
        sprintf(line,"Case #%d: ",i+1); //What no base 0?
        if(blnIsGood) strcat(line,"GOOD\n");
        else strcat(line,"BAD\n");
        printf("%s",line);
        strcat(outbuf,line);
    }
    printf("Done numgood=%d\n",numgood);
    


    //Write output to file
    FILE * ofd = fopen("output.txt","w");
    if(ofd == NULL) printf("Oh shit!\n");
    fputs(outbuf,ofd);
    fclose(fd);
    fclose(ofd);

    return 0;
}

int generateTheLists(int * LIST, int N)
{
    //I would assume that the difference is in the BAD algorithm stuff is more likely to be IN PLACE 
    int i;
    int guessval = 0;
    for(i=0; i < N; ++i)
    {
        if(LIST[i] == i)
        {
            guessval++;
        }       
    }
    printf("guessval=%d\n",guessval);
    if(guessval > 0) return 0; //What 9000?
    return 1;
}
