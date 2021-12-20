#include <stdio.h>
#include <stdlib.h>
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
    printf("\t\tItems\t\t\tQty\t\t\t    Total\n");
    printf("\t\t---------------------------------------------------------\n");

    return 0;
}


char invoiceBody(int nbitems, struct orders* ord){
    float total = 0;
    char save;
    printf("\n");
    for(int i = 0; i < nbitems; i++){
        total = total + ord->items[i].qty * ord->items[i].uprice;
        printf("\t\t%s\t\t\t%d\t\t\t   %2.f\n", ord->items[i].name, ord->items[i].qty, ord->items[i].qty * ord->items[i].uprice);
    }
    printf("\n");
    printf("\t\t---------------------------------------------------------\n");
    printf("\t\tSub total\t\t\t\t\t   %2.f\n", total);
    printf("\t\tDiscount @10%%\t\t\t\t\t   %.2f\n", total*0.1);

    printf("\t\t\t\t\t\t\t\t---------\n");
    printf("\t\tAmoout before tax\t\t\t\t   %.2f\n", total-(total*0.1));
    printf("\t\tTVA @20%%\t\t\t\t\t   %.2f\n", (total-(total*0.1))*0.2);
    printf("\t\t---------------------------------------------------------\n");
    printf("\t\tTotal after tax\t\t\t\t\t   %.2f\n", (total-(total*0.1))+((total-(total*0.1))*0.2));
    printf("\t\t---------------------------------------------------------\n");
    printf("\t\tDo you want to save the invoice? (y/n)");
    scanf("%s", &save);
    printf("\n");
    return save;
}

int main(){
    int choice;
    struct orders order1;
    int items = 0;
    char save;

    printf("\n\t\t\t\t\t\t========== WELCOME ===========\n\n");
    choice = selectOperation();

    if (choice == 1){
        printf("\t\tPlease enter your customer's name : ");
        fgets(order1.name, 100, stdin);
        
        order1.name[strlen(order1.name)-1] = 0;
        
        printf("\n\t\tWelcome %s!\n", order1.name);
        
        strcpy(order1.date, __DATE__);

        printf("\n\t\tPlease enter the number of items : ");
        scanf("%d", &items);
        
        for(int i = 0; i < items; i++){
            fgetc(stdin);
            struct item itm;
            printf("\n\t\tPlease enter the item %d : ", i+1);
            fgets(itm.name, 100, stdin);
            itm.name[strlen(itm.name)-1] = 0;

            printf("\t\tPlease enter the unit price : ");
            scanf("%f", &itm.uprice);

            printf("\t\tPlease enter the quantity : ");
            scanf("%d", &itm.qty);

            order1.items[i] = itm;
        }
        printf("\n");

        invoiceHeader(order1.date, order1.name);
        save = invoiceBody(items, &order1);

        if (save == 'y'){
            printf("\t\tAzulaaa");
        }
    
    }
}