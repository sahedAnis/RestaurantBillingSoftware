#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <errno.h>
#include <string.h>

#define SIZE 1<<10

struct item{
    char name[100];
    int qty;
    float uprice;
};

struct orders{
    char name[100];
    char date[50];
    int numberOfItems;
    struct item items[SIZE];
};

int selectOperation(){
    
    char selection[SIZE];

    printf("\t\tPlease select one operation : \n\n");
    printf("\t\t1. Create invoice\n");
    printf("\t\t2. Show all invoices\n");
    printf("\t\t3. Search invoice\n");
    printf("\t\t4. Exit\n\n");

    printf("\t\tYour choice : ");
    scanf("%s", selection);
    printf("\n");
    fgetc(stdin);
    while(atoi(selection) != 1 &&  atoi(selection) != 2 && atoi(selection) != 3 && atoi(selection) != 4){
        printf("\t\tWrong entry! Please retry\n");
        printf("\t\tSelect 1, 2, 3 or 4 :\n\n");

        printf("\t\t1. Create invoice\n");
        printf("\t\t2. Show all invoices\n");
        printf("\t\t3. Search invoice\n");
        printf("\t\t4. Exit\n\n");

        printf("\t\tYour choice : ");
        scanf("%s", selection);
        printf("\n");
        fgetc(stdin);
        
    }

    return atoi(selection);
}

int invoiceHeader(const char* date, const char* name){

    printf("\n\t\t\t\t\t\t\t   SAHED Restaurant \n");
    printf("\t\t\t\t\t\t\t  ------------------\n");

    printf("\t\tDate : %s\n", date);
    printf("\t\tInvoice to : Mr. %s\n", name);

    printf("\t\t---------------------------------------------------------\n");
    printf("\t\tItems");
    printf("\t\t\tQty");
    printf("\t\t\t    Total\n");
    printf("\t\t---------------------------------------------------------\n");

    return 0;
}


char invoiceBody(int nbitems, struct orders* ord){
    float total = 0;
    char save;
    printf("\n");
    for(int i = 0; i < nbitems; i++){
        total = total + ord->items[i].qty * ord->items[i].uprice;
        printf("\t\t%s", ord->items[i].name);
        printf("\t\t\t%d", ord->items[i].qty);
        printf("\t\t\t    %2.f\n", ord->items[i].qty * ord->items[i].uprice);
    }
    printf("\n");
    printf("\t\t---------------------------------------------------------\n");
    printf("\t\tSub total\t\t\t\t\t    %2.f\n", total);
    printf("\t\tDiscount @10%%\t\t\t\t\t    %.2f\n", total*0.1);

    printf("\t\t\t\t\t\t\t\t---------\n");
    printf("\t\tAmount before tax\t\t\t\t    %.2f\n", total-(total*0.1));
    printf("\t\tTVA @20%%\t\t\t\t\t    %.2f\n", (total-(total*0.1))*0.2);
    printf("\t\t---------------------------------------------------------\n");
    printf("\t\tTotal after tax\t\t\t\t\t    %.2f\n", (total-(total*0.1))+((total-(total*0.1))*0.2));
    printf("\t\t---------------------------------------------------------\n");
    return 0;
}

int choiceOne(struct orders ord, struct orders ord2){
    system("clear");
    int choice = 0;
    size_t written;
    FILE* fd = 0;
    char save;

        
    strcpy(ord.date, __DATE__);

    printf("\n\t\tPlease enter the number of items : ");
    scanf("%d", &ord.numberOfItems);
        
    for(int i = 0; i < ord.numberOfItems; i++){
        fgetc(stdin);
        printf("\n\t\tPlease enter the item %d : ", i+1);
        fgets(ord.items[i].name, 100, stdin);
        ord.items[i].name[strlen(ord.items[i].name)-1] = 0;

        printf("\t\tPlease enter the unit price : ");
        scanf("%f", &ord.items[i].uprice);

        printf("\t\tPlease enter the quantity : ");
        scanf("%d", &ord.items[i].qty);
    }
    printf("\n");

    invoiceHeader(ord.date, ord.name);
    invoiceBody(ord.numberOfItems, &ord);
    printf("\n\t\tDo you want to save the invoice? (y/n) ");
    scanf("%s", &save);
    fgetc(stdin);

    if (save == 'y'){
        fd = fopen("RestaurantBills.dat", "a+");
        written = fwrite(&ord, sizeof(struct orders), 1, fd);
        if(written != 0){
            printf("\t\tSuccesfully saved!, written : %d\n", fd);
            printf("\n\t\tWant to create another invoice? Please put 1.\n");
            printf("\t\tSee your previous invoices ? Please put 2.\n");
            printf("\t\tSearch for an invoice by name ? Please put 3.\n");
            printf("\t\tExit ? Please put 4.\n");
            printf("\n\t\tYour choice : ");
            scanf("%d", &choice);
            if (choice == 1){
                choice = choiceOne(ord, ord2);
                while(choice == 1){
                    choice = choiceOne(ord, ord2);
                }
                while(choice == 2){
                    choice = choiceTwo(ord2, ord);
                }
                while(choice == 3){
                    choice = choiceThree(ord2, ord);
                }
            }

            if (choice == 2){
                choice = choiceTwo(ord2, ord);
                while(choice == 1){
                    choice = choiceOne(ord, ord2);
                }
                while(choice == 2){
                    choice = choiceTwo(ord2, ord);
                }
                while(choice == 3){
                    choice = choiceThree(ord2, ord);
                }
            }

            if (choice == 3){
                choice = choiceThree(ord2, ord);
                while(choice == 1){
                    choice = choiceOne(ord, ord2);
                }
                while(choice == 2){
                    choice = choiceTwo(ord2, ord);
                }
                while(choice == 3){
                    choice = choiceThree(ord2, ord);
                }

            }

            if(choice == 4){
                printf("\n\t\tProgram exit...\n");
                sleep(1);
                printf("\n\t\tThank you! See you soon!\n");
                exit(0);
            }
        }
    }
    else if (save == 'n'){
        printf("\t\tYou have chosen not to save the invoice.\n");
        printf("\n\t\tWant to create another invoice? Please put 1.\n");
        printf("\t\tSee your previous invoices ? Please put 2.\n");
        printf("\t\tSearch for an invoice by name ? Please put 3.\n");
        printf("\t\tExit ? Please put 4.\n");
        printf("\n\t\tYour choice : ");
        scanf("%d", &choice);
        if (choice == 1){
            choice = choiceOne(ord, ord2);
            while(choice == 1){
                choice = choiceOne(ord, ord2);
            }
            while(choice == 2){
                choice = choiceTwo(ord2, ord);
            }
            while(choice == 3){
                choice = choiceThree(ord2, ord);
            }
        }

        if (choice == 2){
            choice = choiceTwo(ord2, ord);
            while(choice == 1){
                choice = choiceOne(ord, ord2);
            }
            while(choice == 2){
                choice = choiceTwo(ord2, ord);
            }
            while(choice == 3){
                choice = choiceThree(ord2, ord);
            }
        }

        if (choice == 3){
            choice = choiceThree(ord2, ord);
            while(choice == 1){
                choice = choiceOne(ord, ord2);
            }
            while(choice == 2){
                choice = choiceTwo(ord2, ord);
            }
            while(choice == 3){
                choice = choiceThree(ord2, ord);
            }
        }

        if(choice == 4){
            printf("\n\t\tProgram exit...\n");
            sleep(1);
            printf("\n\t\tThank you! See you soon!\n");
            exit(0);
        }
        fclose(fd);
        
    }
    else{
        printf("\n\t\tERROR SAVING THE INVOICE...\n");
        exit(0);
    }
    return choice;
}
    

int choiceTwo(struct orders ord, struct orders ord2){
    system("clear");
    int choice = 0;
    FILE* fd;
    fd = fopen("RestaurantBills.dat", "r");
    printf("\t\t****Your previous invoices****\n");
    while(fread(&ord, sizeof(struct orders), 1, fd)){
        invoiceHeader(&ord.date, &ord.name);
        invoiceBody(ord.numberOfItems, &ord);
    }
    printf("\n\t\tWant to create another invoice? Please put 1.\n");
    printf("\t\tSee your previous invoices ? Please put 2.\n");
    printf("\t\tSearch for an invoice by name ? Please put 3.\n");
    printf("\t\tExit ? Please put 4.\n");
    printf("\n\t\tYour choice : ");
    scanf("%d", &choice);
    close(fd);
    if (choice == 1){
        choice = choiceOne(ord, ord2);
        while(choice == 1){
            choice = choiceOne(ord, ord2);
        }
        while(choice == 2){
            choice = choiceTwo(ord2, ord);
        }
        while(choice == 3){
            choice = choiceThree(ord2, ord);
        }
    }

    if (choice == 2){
        choice = choiceTwo(ord2, ord);
        while(choice == 1){
            choice = choiceOne(ord, ord2);
        }
        while(choice == 2){
            choice = choiceTwo(ord2, ord);
        }
        while(choice == 3){
            choice = choiceThree(ord2, ord);
        }
    }

    if (choice == 3){
        choice = choiceThree(ord2, ord);
        while(choice == 1){
            choice = choiceOne(ord, ord2);
        }
        while(choice == 2){
            choice = choiceTwo(ord2, ord);
        }
        while(choice == 3){
            choice = choiceThree(ord2, ord);
        }
    }

    if(choice == 4){
        printf("\n\t\tProgram exit...\n");
        sleep(1);
        printf("\n\t\tThank you! See you soon!\n");
        exit(0);
    }

    return choice;
}

int choiceThree(struct orders ord, struct orders ord2){
    FILE* fd;
    int choice;    
    int found = 0;
    char name[50];
    system("clear");
    fd = open("RestaurantBills.dat", O_RDONLY);
    printf("\n\t\tPlease put a name : ");
    scanf("%s", &name);
    int cmp = -1;
    while(read(fd, &ord, sizeof(struct orders)) && found != 1){
        cmp = strcmp(name, ord.name);
        if(cmp == 0){
            invoiceHeader(&ord.date, &ord.name);
            invoiceBody(ord.numberOfItems, &ord);
            found = 1;
        }
    }
    if (found == 0){
        printf("\t\tInvoice for the name %s does not exists.\n", name);
    }
    printf("\n\t\tWant to create another invoice? Please put 1.\n");
    printf("\t\tSee your previous invoices ? Please put 2.\n");
    printf("\t\tSearch for an invoice by name ? Please put 3.\n");
    printf("\t\tExit ? Please put 4.\n");
    printf("\n\t\tYour choice : ");
    scanf("%d", &choice);
    if (choice == 1){
        choice = choiceOne(ord, ord2);
        while(choice == 1){
            choice = choiceOne(ord, ord2);
        }
        while(choice == 2){
            choice = choiceTwo(ord2, ord);
        }
        while(choice == 3){
            choice = choiceThree(ord2, ord);
        }
    }

    if (choice == 2){
        choice = choiceTwo(ord2, ord);
        while(choice == 1){
            choice = choiceOne(ord, ord2);
        }
        while(choice == 2){
            choice = choiceTwo(ord2, ord);
        }
        while(choice == 3){
            choice = choiceThree(ord2, ord);
        }
    }

    if (choice == 3){
        choice = choiceThree(ord2, ord);
        while(choice == 1){
            choice = choiceOne(ord, ord2);
        }
        while(choice == 2){
            choice = choiceTwo(ord2, ord);
        }
        while(choice == 3){
            choice = choiceThree(ord2, ord);
        }
    }

    if(choice == 4){
        printf("\n\t\tProgram exit...\n");
        sleep(1);
        printf("\n\t\tThank you! See you soon!\n");
        exit(0);
        }
    close(fd);
    return choice;
}


int main(){
    int choice;
    struct orders order1;
    struct orders savedorders;
    char name[50]; 

    printf("\n\t\t\t\t\t\t========== WELCOME ===========\n\n");

    printf("\t\tPlease enter your customer's name : ");
    fgets(order1.name, 100, stdin);
    
        
    order1.name[strlen(order1.name)-1] = 0;
    printf("\n\t\tWelcome %s!\n", order1.name);
    sleep(1);

    choice = selectOperation();

    if (choice == 1){
        choiceOne(order1, savedorders);
    }

    if (choice == 2){
        choiceTwo(savedorders, order1);
    }

    if (choice == 3){
        choiceThree(savedorders, order1);
    }

    if(choice == 4){
        printf("\n\t\tProgram exit...\n");
        sleep(1);
        printf("\n\t\tThank you! See you soon!\n");
        exit(0);
    }
}