#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define BUFSIZE 100

//Create structure (Cup) to hold cup information and declare Cup mug
struct Cup
{
    int espresso;
    int milkSteam;
    int milkFoam;
    int remaining;
};

//Functions outside of main()
void add(struct Cup *ptr);
void draw(struct Cup *ptr);
void ratio(struct Cup *ptr);

int main(int argc, char *argv[])
{
    //Allocate space in heap for mug contents
    struct Cup *mug = malloc(sizeof(struct Cup));

    //Use command line arguments to specify ingredients amounts if user does not wish to go through CLI / UI
    if (argc > 2)
    {
        mug->espresso = atoi(argv[1]);
        mug->milkSteam = atoi(argv[2]);
        mug->milkFoam = atoi(argv[3]);

        ratio(mug);
    }
    else
    {
        //Initialize mug amounts
        mug->espresso = mug->milkSteam = mug->milkFoam = 0;
        mug->remaining = 250;

        printf("\n\nWelcome, in this application you will incrementally add coffee (espresso), steamed milk, and foamed milk to a mug in order to create one of many \nconcoctions...upon completion, the application will tell you which drink \nyour creation most closely resembles. Press enter when ready to proceed.\n");

        //Get input to continue
        char c[BUFSIZE];
        fgets(c, BUFSIZE, stdin);

        //Allow method for stopping loop of adding ingredients
        int active = 0;
        while (active != 1)
        {
            add(mug);
            if (mug->remaining < 0)
                break;
            printf("Finished? Enter '1', or press enter to continue.");
            char continueNum[BUFSIZE];
            fgets(continueNum, BUFSIZE, stdin);
            active = continueNum[0] - '0';
        }

        ratio(mug);
    }
}

//Function for adding ingredient (and specifying amount to add) to mug
void add(struct Cup *ptr)
{
    int d;
    printf("\nYou have %d mls of mug space to work with\n", ptr->remaining);
    printf("What would you like to add?\nenter 'e' for espresso or 'm' for milk\n");

    char c[BUFSIZE];
    fgets(c, BUFSIZE, stdin);

    if ((c[0] == 'e') || (c[0] == 'E'))
    {
        printf("How many shots of espresso would you like to add?\nEnter 1, 2, or 3\n");
        char c2buf[BUFSIZE];
        fgets(c2buf, BUFSIZE, stdin);
        int c2 = c2buf[0] - '0';
        switch (c2)
        {
        case 1:
            ptr->espresso += 35;
            ptr->remaining -= 35;
            break;
        case 2:
            ptr->espresso += 70;
            ptr->remaining -= 70;
            break;
        case 3:
            ptr->espresso += 105;
            ptr->remaining -= 105;
            break;
        default:
            break;
        }
    }
    else if ((c[0] == 'm') || (c[0] == 'M'))
    {
        printf("What type of milk would you like to add?\nenter 's' for steamed or 'f' for foam\n");
        char c3[BUFSIZE];
        fgets(c3, BUFSIZE, stdin);
        if ((c3[0] == 's') || (c3[0] == 'S'))
        {
            printf("How many mls of steamed milk would you like to add?\nEnter a whole number between 1 and 100\n");
            char mlsMilkbuf[BUFSIZE];
            fgets(mlsMilkbuf, BUFSIZE, stdin);
            int mlsMilk = atoi(mlsMilkbuf);
            ptr->milkSteam += mlsMilk;
            ptr->remaining -= mlsMilk;
        }
        else if ((c3[0] == 'f') || (c3[0] == 'f'))
        {
            printf("How many mls of milk foam would you like to add?\nEnter a whole number between 1 and 100\n");
            char mlsMilkbuf[BUFSIZE];
            fgets(mlsMilkbuf, BUFSIZE, stdin);
            int mlsMilk = atoi(mlsMilkbuf);
            ptr->milkFoam += mlsMilk;
            ptr->remaining -= mlsMilk;
        }
    }

    printf("Your mug now has:\n %d mls of espresso\n %d mls of steamed milk\n %d mls of milk foam\n", ptr->espresso, ptr->milkSteam, ptr->milkFoam);
}

//Function for drawing graphic of filled cup
void draw(struct Cup *ptr)
{
    int amountEspresso = ptr->espresso * 10 / 250;
    int remainderEspresso = ptr->espresso - (amountEspresso * 250 / 10);
    int amountSteamedMilk = ptr->milkSteam * 10 / 250;
    int remainderSteamed = ptr->milkSteam - (amountSteamedMilk * 250 / 10);
    int amountFoamMilk = ptr->milkFoam * 10 / 250;
    int remainderFoam = ptr->milkFoam - (amountFoamMilk * 250 / 10);
    int sum = amountEspresso + amountSteamedMilk + amountFoamMilk;
    int remainderTotal = 10 - sum;

    char coffeeSymbol[11] = "xxxxxxxxxx\0";
    char steamedMilkSymbol[11] = "----------\0";
    char foamedMilkSymbol[11] = "~~~~~~~~~~\0";
    char emptySymbol[11] = "          \0";

    char *symbolArray[10];

    int i = 0;
    while (remainderTotal > 0)
    {
        symbolArray[i] = emptySymbol;
        i++;
        remainderTotal--;
    }

    while (amountFoamMilk > 0)
    {
        symbolArray[i] = foamedMilkSymbol;
        i++;
        amountFoamMilk--;
    }

    while (amountSteamedMilk > 0)
    {
        symbolArray[i] = steamedMilkSymbol;
        i++;
        amountSteamedMilk--;
    }

    while (amountEspresso > 0)
    {
        symbolArray[i] = coffeeSymbol;
        i++;
        amountEspresso--;
    }

    printf("\n\n|%s|\n|%s|\n|%s||||||\n|%s|     ||\n|%s|       |\n|%s|     ||\n|%s||||||\n|%s|\n|%s|\n|%s|\n------------\n\n", symbolArray[0], symbolArray[1], symbolArray[2], symbolArray[3], symbolArray[4], symbolArray[5], symbolArray[6], symbolArray[7], symbolArray[8], symbolArray[9]);
    printf("__________________________________________________________\n|KEY: x = espresso | - = steamed milk  | ~  = foamed milk|\n----------------------------------------------------------\n\n");
}

//Function for determining which coffee drink the user's concoction most closely resembles
void ratio(struct Cup *ptr)
{

    float milk2coffee = ((float)ptr->milkFoam + (float)ptr->milkSteam) / (float)ptr->espresso;
    float steam2foam = (float)ptr->milkFoam / (float)ptr->milkSteam;

    if (milk2coffee > 2.5)
    {
        printf("\nNice looking latte.\n\n");
        draw(ptr);
    }
    else if (milk2coffee > 1.5)
    {
        if ((steam2foam > .7) && (steam2foam < 1.3))
        {
            printf("\nCappucino time, baby!\n\n");
            draw(ptr);
        }
        else
        {
            printf("\nHmmmm...strong latte?\n\n");
            draw(ptr);
        }
    }
    else if (milk2coffee > .7)
    {
        char continueNum[BUFSIZE];
        int selection;
        while ((selection != 1) && (selection != 2))
        {
            printf("\nWhere are you? Press 1 for Gibraltar or 2 for Oceania...\n");
            fgets(continueNum, BUFSIZE, stdin);
            selection = continueNum[0] - '0';
            if ((selection != 1) && (selection != 2))
            {
                printf("\nTry again hot shot...\n");
            }
        }
        if (selection == 1)
        {
            printf("\nCortado...you got it.\n\n");
            draw(ptr);
        }
        else if (selection == 2)
        {
            printf("\nFlat white all day, mate.\n\n");
            draw(ptr);
        }
    }
    else if (milk2coffee > 0)
    {
        printf("\nEnjoy your macchiato.\n\n");
        draw(ptr);
    }
    else
    {
        printf("\nStraight espressso...i like it.\n\n");
        draw(ptr);
    }
}
