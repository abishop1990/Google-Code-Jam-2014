/*
 * war.c
 *
 * Solves the "Deceitful War" problem for Google Code Jam QR Problem D
 *
 *
 * Written by Alan Bishop on 4/12/2014
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int playDeceitfulWar(float * Nb, float * Kb,int nblocks);
int playRealWar(float * Nb,  float * Kb,int nblocks);
float NMoveCheating(float * Nblocks, float * Kblocks, int nblocks);
float NMove(float * Nblocks,int nblocks);
float Kmove(float * Kblocks, int nblocks, float Nchosen);
void sortArray(float * arr, int size);


int main(int argc, char * argv [])
{
    char outbuf[10000];
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

    //Get data
    int ncases = -1;
    fscanf(fd,"%d\n",&ncases);
    if(ncases <= 0)
    {
        fprintf(stderr,"Invalid number of cases [%d]\n",ncases);
        return 3;
    }
    int i;
    for(i = 0; i < ncases; ++i)
    {
        int nblocks = -1;
        fscanf(fd,"%d\n",&nblocks);
        if(nblocks <= 0)
        {
            fprintf(stderr,"Invalid number of blocks [%d]\n",ncases);
            return 3;
        }
        //Get the blocks
        float Nblocks[nblocks],Kblocks[nblocks];
        int j;
        for(j = 0; j < nblocks; ++j)
        {
            if(j == nblocks-1) fscanf(fd,"%f\n",&Nblocks[j]);
            else fscanf(fd,"%f ",&Nblocks[j]);
        }
        for(j = 0; j < nblocks; ++j)
        {
            if(j == nblocks-1) fscanf(fd,"%f\n",&Kblocks[j]);
            else fscanf(fd,"%f ",&Kblocks[j]);
        }
        int rw = playRealWar(Nblocks,Kblocks,nblocks);
        int dw = playDeceitfulWar(Nblocks,Kblocks,nblocks);
        
        //Create line
        char line[50];
        sprintf(line,"Case #%d: %d %d\n",i+1,dw,rw);
        printf("%s",line);
        strcat(outbuf,line);
    }

    //Write output to file
    FILE * ofd = fopen("output.txt","w");
    fputs(outbuf,ofd);
    fclose(fd);
    fclose(ofd);

    return 0;
}


int playRealWar(float * Nb,float * Kb,int nblocks)
{
    float Nblocks[nblocks];
    float Kblocks[nblocks];
    memcpy(Nblocks,Nb,sizeof(float)*nblocks);
    memcpy(Kblocks,Kb,sizeof(float)*nblocks);
    //Sort the arrays
    sortArray(Nblocks,nblocks);
    sortArray(Kblocks,nblocks);

    int i;
    int Nscore = 0;
    for(i=0; i<nblocks; ++i)
    {
        float nb, kb;
        //Optimal for Naomi = lowest to score a point
        nb = NMove(Nblocks,nblocks);
        //Optimal for Ken = lowest to be > Naomi
        kb = Kmove(Kblocks,nblocks,nb);
        //printf("RW:Ken plays %f, Naomi plays %f\n",kb,nb);
        if(nb - kb > 0.00000000001) 
        {
            ++Nscore;
          //  printf("RW:Point for Naomi!\n");
        }
        //else printf("RW:Point for Ken!\n");
    }

    return Nscore;
}

int playDeceitfulWar(float * Nb,float * Kb,int nblocks)
{
    float Nblocks[nblocks];
    float Kblocks[nblocks];
    memcpy(Nblocks,Nb,sizeof(float)*nblocks);
    memcpy(Kblocks,Kb,sizeof(float)*nblocks);
    //Sort the arrays
    sortArray(Nblocks,nblocks);
    sortArray(Kblocks,nblocks);

    int i;
    int Nscore = 0;
    for(i=0; i<nblocks; ++i)
    {
        float nb, kb;
        //Mrs.Puff, I think I have cheated!!!
        nb = NMoveCheating(Nblocks,Kblocks,nblocks);
        //Optimal for Ken = lowest to be > Naomi
        kb = Kmove(Kblocks,nblocks,nb);
        printf("DW:Ken plays %lf, Naomi plays %lf\n",kb,nb);
        if(nb - kb > 0.00001) 
        {
            ++Nscore;
            printf("DW:Point for Naomi!\n");
        }
        else printf("DW:Point for Ken!\n");
    }
    
    return Nscore;
}


float NMoveCheating(float * Nblocks, float * Kblocks, int nblocks)
{
    float Nmove = 0.0;
    int i;
    //Start with the lowest block
    for(i=0; i <nblocks; ++i)
    {
        if(Nblocks[i] == 0.0) continue;
        else
        {
            Nmove = Nblocks[i];
            printf("Naomi actually playing %f\n",Nmove);
            Nblocks[i] = 0.0;
            break;
        }
    }
    //Check if this is greater than Ken's smallest, if so we can cheat
    int j;
    int cheat = 0;
    for(j=0;j<nblocks;++j)
    {
        if(Kblocks[j] == 0.0) continue;
        else if(Kblocks[j] < Nmove)
        {
            printf("CHEATING!\n");
            //Then let's cheat!
            cheat = 1;
            break;
        }
    }

    //Find the highest block in Kblocks
    for(j=nblocks-1; j >=0; --j)
    {
        if(Kblocks[j] == 0.0) continue;
        else if(cheat == 1)
        {
            Nmove = Kblocks[j] + 0.1;
            break;
        }
        else if(Kblocks[j] > Nmove)
        {
            Nmove = Kblocks[j] - 0.0001;
            break;
        }
        else break;
    }

    return Nmove;
}


float NMove(float * Nblocks,int nblocks)
{
    float Nmove = 0.0;
    int i;
    for(i=0;i<nblocks;++i)
    {
        //Smallest block first
        if(Nblocks[i] == 0.0) continue;
        else
        {
            Nmove = Nblocks[i];
            Nblocks[i] = 0.0;
            break;
        }
    }
    return Nmove;
}


float Kmove(float * Kblocks, int nblocks, float Nchosen)
{
    float Kmove = 0.0;
    int i;
    for(i=0;i<nblocks;++i)
    {
        //Find the smallest block > Naomi's (if possible)
        if(Kblocks[i] == 0.0) continue; //Skip these (been burned)
        if(Kblocks[i] > Nchosen)
        {
            //Use this block
            Kmove = Kblocks[i];
            Kblocks[i] = 0.0;
            break;
        }
    }
    if(Kmove == 0.0)
    {
        //Take the smallest possible block instead (yeah we lose a point, not possible to win)
        for(i = 0; i < nblocks; ++i)
        {
            if(Kblocks[i] == 0.0) continue;
            Kmove = Kblocks[i];
            Kblocks[i] = 0.0;
            break;
        }
    }
    return Kmove;
}

int comp(const void * a, const void * b)
{
    float ac = *(float *)a;
    float bc = *(float *)b;
    int retval;
    if(ac > bc) retval = 1;
    if(ac == bc) retval = 0;
    if(ac < bc) retval = -1;
    return retval;
}

void sortArray(float * arr, int size)
{
    qsort(arr,size,sizeof(float),comp);   
/*    //DEBUG CODE
    printf("Sorted: ");
    int i;
    for(i = 0; i <size; ++i)
    {
        printf("%f ",arr[i]);
    }
    printf("\n"); */
}
