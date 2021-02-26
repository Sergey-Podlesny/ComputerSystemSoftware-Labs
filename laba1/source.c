//
// Created by s3rp0d on 20/02/2021.
//

#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void setData(struct Men* men, double regionalCost, double localCost, double currentMoneyCount)
{
    (*men).telephone = (struct Telephone*)malloc(sizeof(struct Telephone));
    (*(*men).telephone).regionalCost = regionalCost;
    (*(*men).telephone).localCost = localCost;
    (*men).currentMoneyCount = currentMoneyCount;
}

void pushMoney(struct Men* men, double count)
{
    (*men).currentMoneyCount += count;
}

int regionalCall(struct Men* men, double minute)
{
    if(!(*men).telephone || (*men).currentMoneyCount < (*(*men).telephone).regionalCost * minute)
    {
        return 0;
    }
    else
    {
        (*men).currentMoneyCount -= (*(*men).telephone).regionalCost * minute;
        return 1;
    }
}

int localCall(struct Men* men, double minute)
{
    if(!(*men).telephone || (*men).currentMoneyCount < (*(*men).telephone).localCost * minute)
    {
        return 0;
    }
    else
    {
        (*men).currentMoneyCount -= (*(*men).telephone).localCost * minute;
        return 1;
    }
}

void debug(struct Men* men)
{
    puts("\nINFO");
    printf("curMon: %lf \nlocalCost: %lf \nregCost: %lf\n\n", (*men).currentMoneyCount, (*(*men).telephone).localCost, (*(*men).telephone).regionalCost);
}


void menu()
{
    struct Men* men;
    men = (struct Men*)malloc(sizeof (struct Men));
    setData(men, 0.7, 0.3, 10);
    int numChoice;
    double countOfMinute;
    double countOfMoney;
    debug(men);
    do {
        puts("1. Local call");
        puts("2. Regional call");
        puts("3. Push money call");
        puts("4. Exit");
        scanf("%i", &numChoice);
        switch (numChoice) {
            case 1:
                printf("Count of minute: ");
                scanf("%lf", &countOfMinute);
                if(localCall(men, countOfMinute))
                {
                    puts("Successfully!");
                }
                else
                {
                    puts("Not successfully!");
                }
                debug(men);
                break;
            case 2:
                printf("Count of minute: ");
                scanf("%lf", &countOfMinute);
                if(regionalCall(men, countOfMinute))
                {
                    puts("Successfully!");
                }
                else
                {
                    puts("Not successfully!");
                }
                debug(men);
                break;
            case 3:
                printf("Count of money: ");
                scanf("%lf", &countOfMoney);
                pushMoney(men, countOfMoney);
                debug(men);
                break;
        }
    } while(numChoice != 4);
    exit(1);
}



