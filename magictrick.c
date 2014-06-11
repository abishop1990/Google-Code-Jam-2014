/*
 * cardmagic.c
 *
 * Solves the "Magic Trick" problem for Google Code Jam 2014 QR Problem 1
 *
 * "Problem
 *
 * Recently you went to a magic show. You were very impressed by one of the tricks, 
 * so you decided to try to figure out the secret behind it!
 *
 * The magician starts by arranging 16 cards in a square grid: 4 rows of cards, with 
 * 4 cards in each row. Each card has a different number from 1 to 16 written on the 
 * side that is showing. Next, the magician asks a volunteer to choose a card, and to 
 * tell him which row that card is in.
 *
 * Finally, the magician arranges the 16 cards in a square grid again, possibly in a 
 * different order. Once again, he asks the volunteer which row her card is in. With 
 * only the answers to these two questions, the magician then correctly determines 
 * which card the volunteer chose. Amazing, right?
 *
 * You decide to write a program to help you understand the magician's technique. The 
 * program will be given the two arrangements of the cards, and the volunteer's answers
 * to the two questions: the row number of the selected card in the first arrangement,
 * and the row number of the selected card in the second arrangement. The rows are 
 * numbered 1 to 4 from top to bottom.
 *
 * Your program should determine which card the volunteer chose; or if there is more than
 * one card the volunteer might have chosen (the magician did a bad job); or if there's 
 * no card consistent with the volunteer's answers (the volunteer cheated)."
 *
 *
 *
 * Written by Alan Bishop 4/11/2014
 */

#include <stdio.h>
#include <string.h>

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
    int i,r;
    int setup1[4][4];
    int setup2[4][4];
    int row1 = 0, row2 = 0;
    for(i=0; i<ncases; ++i)
    {
        printf("Case 1:\n");
        //Get the card's row (1)
        fscanf(fd,"%d\n",&row1);
        //printf("row1=%d\n",row1);
        //Get setup (1)
        for( r = 0; r < 4; ++r)
        {
                fscanf(fd,"%d %d %d %d\n",&setup1[r][0],&setup1[r][1],&setup1[r][2],&setup1[r][3]);
        }
        int j, k;
        printf("Arrangement 1 Row %d:\n",row1);
        j = row1-1;
        for(k=0;k<4;++k) { printf("%d ",setup1[j][k]); }
        printf("\n");
        

        //Get the card's row (2)
        fscanf(fd,"%d\n",&row2);
        //printf("row2=%d\n",row2);
        //Get setup (2)
        for(r=0;r<4;++r)
        {
                fscanf(fd,"%d %d %d %d\n",&setup2[r][0],&setup2[r][1],&setup2[r][2],&setup2[r][3]);
        }
        printf("Arrangement 2 Row %d:\n",row2);
        j = row2 -1;
        for(k=0;k<4;++k) { printf("%d ",setup2[j][k]) ;}
        printf("\n");
        

        //Do the magic
        row1--; row2--; //Humans and their non-zero based rows...
        int guess = 0;
        int multiple = 0;
        for(j=0;j<4;++j)
        {
            for(k=0;k<4;++k)
            {
                if(setup1[row1][j] == setup2[row2][k])
                {
                    if(guess != 0)  { multiple = 1; break; }
                    guess = setup1[row1][j];
                }
            }
                if(multiple == 1) break;
        }

        //Write output to buffer
        char line[50];
        sprintf(line,"Case #%d: ",i+1); //What no base 0?
        if(guess == 0) sprintf(line+strlen(line),"Volunteer cheated!\n");
        else if(multiple == 1) sprintf(line+strlen(line),"Bad magician!\n");
        else sprintf(line+strlen(line),"%d\n",guess);
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
