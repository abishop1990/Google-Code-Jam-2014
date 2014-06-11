/*
 * r2.c 
 * Written by Alan Bishop 4/25/2014
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
    for(i = 0; i < ncases; ++i)
    {
        //LOGIC GOES HERE
        int N, L;
        fscanf(fd,"%d %d",N,L);
        int j;
        //I don't remember binary/bitwise, I suck :( 
        int devices[N][L];
        int flows[N][L];
        for(j = 0; j < N; ++j)
        {
            if(j < N-1) fscanf("%s ",flows[j]);
            else fscanf("%s",flows[j]);
        }
        for(j=0;j<N;++i)
        {
            if(j < N-1) fscanf("%s",devices[j]);
            else fscanf("%s",devices[j]);
        }

        int n = getNumSwitches(devices,flows,N,L);


        //Write output to buffer
        char line[50];
        sprintf(line,"Case #%d: ",i+1); //What no base 0?
        char line2[20];
        if(n < 0) sprintf(line2,"NOT POSSIBLE\n");
        else sprintf(line2,"%d\n",n);
        strcat(line,line2);
    }

    


    //Write output to file
    FILE * ofd = fopen("output.txt","w");
    fputs(outbuf,ofd);
    fclose(fd);
    fclose(ofd);

    return 0;
}

int getNumSwitches(char ** devices, char ** flows, int N, int L)
{
    int i;
    for(i = 0; i < L; ++i)
    {
        //Generate a solution
        int j;
        for(j = 0; j < N; ++j)
        {
            
        }
    }
}
