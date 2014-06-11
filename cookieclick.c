/*
 * cookieclick.c
 *
 * "In this problem, you start with 0 cookies. You gain cookies at a rate of 2 cookies 
 * per second, by clicking on a giant cookie. Any time you have at least C cookies, you 
 * can buy a cookie farm. Every time you buy a cookie farm, it costs you C cookies and 
 * gives you an extra F cookies per second.
 *
 * Once you have X cookies that you haven't spent on farms, you win! Figure out how long 
 * it will take you to win if you use the best possible strategy.
 *
 * Example:
 * Suppose C=500.0, F=4.0 and X=2000.0. Here's how the best possible strategy plays out:
 * You start with 0 cookies, but producing 2 cookies per second.
 * After 250 seconds, you will have C=500 cookies and can buy a farm that produces F=4 
 * cookies per second.
 * After buying the farm, you have 0 cookies, and your total cookie production is 6 cookies 
 * per second.
 * The next farm will cost 500 cookies, which you can buy after about 83.3333333 seconds.
 * After buying your second farm, you have 0 cookies, and your total cookie production is 10 
 * cookies per second.
 * Another farm will cost 500 cookies, while you can buy after 50 seconds.
 * After buying your third farm, you have 0 cookies, and your total cookie production is 14 
 * cookies per second.
 * Another farm would cost 500 cookies, but it actually makes sense not to buy it: instead 
 * you can just wait until you have X=2000 cookies, which takes about 142.8571429 seconds.
 *
 * Total time: 250 + 83.3333333 + 50 + 142.8571429 = 526.1904762 seconds.
 *
 * Notice that you get cookies continuously: so 0.1 seconds after the game starts you'll 
 * have 0.2 cookies, and π seconds after the game starts you'll have 2π cookies." 
 *
 *
 * Written by Alan Bishop 4/11/2014
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TIMESLICE_QUICK 0.001
#define TIMESLICE 0.0000001 //0.0000001

/*struct OutcomeT
{
    long double cookies;
    int farms;
    struct OutcomeT * next;
};*/


long double bruteForce(double F, double C, double X);
long double getTime(double F, double C, double X, int nfarms);
//double CookieSimulation(double F, double C, double X);

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
        //Get our initial  values
        double F = 0.0, C = 0.0, X = 0.0;
        fscanf(fd,"%lf %lf %lf\n",&C,&F,&X);
        //Simulate
        long double result = bruteForce(F,C,X); //CookieSimulation(F,C,X);
        
        //Output result
        char line[50];
        sprintf(line,"Case #%d: %.7Lf\n",i+1,result);
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

#define MAX_FARMS 100000

//Okay let's try this....
long double bruteForce(double F, double C, double X)
{
    long double t = 999999999.0;
    long double times[MAX_FARMS]; //Array of times [0 = built 0 farms, 100 = built 100 farms)
    int i;
    //Initalize the array
    for(i = 0; i < MAX_FARMS; ++i) { times[i] = 0.0; }
    for(i = 0; i < MAX_FARMS; ++i)
    {
        times[i] = getTime(F,C,X,i);
        if(t > times[i]) t = times[i];
    }
    return t;
}



long double getTime(double F, double C, double X, int nfarms)
{
    long double t = 0.0;
    int i;
    for(i = 0; i < nfarms; ++i)
    {
        t+=  C/(2.0 + F*i);
    }
    t += X/(2.0 + F*nfarms);
    return t;
}


/*
//We've estimated the best options, so let's get the more specific time
long double timeWithXFarms(double F, double C, double X, int f)
{
    long double t = 0.0;
    struct OutcomeT outcome;
    outcome.cookies = 0.0;
    outcome.farms = 0;
    while(outcome.cookies < X)
    {
        t += TIMESLICE;
        outcome.cookies += (2.0 + (long double)outcome.farms *F)*TIMESLICE;
        if(f > 0)
        {
            long double change = C - outcome.cookies;
            long double tinc = change/(2.0 + (long double)outcome.farms *F);
            t += tinc;
            outcome.cookies = 0;
            --f;
            outcome.farms++;
        }
    }
    return t;
}

double CookieSimulation(double F, double C, double X)
{
    long double t = 0.0;
    struct OutcomeT outcomes;
    struct OutcomeT * cur;
    outcomes.cookies = 0.0;
    outcomes.farms = 0;
    outcomes.next = NULL;
    while(1)
    {
        t += TIMESLICE_QUICK; //Requested Google granularity

        cur = &outcomes;
        while(cur->next != NULL)
        {
            cur->cookies += (2.0 + (long double)cur->farms *F)*TIMESLICE_QUICK;
            //printf("cookies=%lf,farms=%d\n",cur->cookies,cur->farms);
            if(cur->cookies >= X) 
            { 
                printf("farms=%d\n",cur->farms); 
                //Break it down to get the real time
                return timeWithXFarms(F,C,X,cur->farms); 
            }
            cur = cur->next;
        }
        cur->cookies += (2.0 + (long double)cur->farms *F)*TIMESLICE_QUICK;
        if(cur->cookies >= X) 
        { 
            printf("farms=%d\n",cur->farms); 
            //Break it down to get the real time
            return timeWithXFarms(F,C,X,cur->farms); 
        }
        if(cur->cookies >= C)
        {
            //Create a new outcome possibility, buy a farm!
            cur->next = malloc(sizeof(struct OutcomeT));
            cur->next->cookies = cur->cookies - C;
            cur->next->farms = cur->farms + 1;
            cur->next->next = NULL; //Just being explicit
        }
        
    }
    return t; //Shuts the compiler up (Yeah, breaking coding standard ooooh rebel)
}*/
