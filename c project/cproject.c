#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
void generatebillheader(char name[50],char date[30])
{
    printf("\n\n");
    printf("\t        ADV.RESTAURENT");           
    printf("\n---------------------------------------------------");
    printf("\nDate:%s",date);
    printf("\ninvoice to:%s",name);
    printf("\n");
    printf("--------------------------------------------------\n");
    printf("Items\t\t");
    printf("Quantity\t\t");
    printf("Total\t\t");
    printf("\n--------------------------------------------------");
    printf("\n\n");
}


void generatebillbody(char items[30],int qty, float price)
{

printf("%s\t\t",items);
printf("%d\t\t\t",qty);
printf("%.2f\t\t",qty*price);

printf("\n");
}

struct items{
char item[20];
float price;
int qty;
};

struct order{
    char customer[50];
    char date[50];
    int numofitems;
    struct items itm[50];
};





void generatebillfooter( float total)
{

printf("\n");
float dis=0.1*total;
float nettotal=total-dis;
float cgst=0.09*nettotal,grandtotal=nettotal + 2*cgst;
printf("--------------------------------------------------");
printf("\nsub total\t\t\t%.2f",total);
printf("\nDiscount@10%s\t\t\t%2.f\n","%",dis);
printf("--------------------------------------------------");
printf("\n net total\t\t\t%.2f",nettotal);
printf("\n cgst @9%s\t\t\t%2.f","%",cgst);
printf("\n sgst @9%s\t\t\t%2.f","%",cgst);
printf("\n--------------------------------------------------");
printf("\n Grannd total\t\t\t%.2f",grandtotal);
printf("\n--------------------------------------------------\n");
}

int main()
{
struct order ord;
struct order order;
int opt,n,i;

float total;
FILE *fp;
char saveBill='y',continueflag='y';
char name[50];
while(continueflag=='y'){
    float total=0;
    int invoicefound=0;
    printf("==================ADV.RESTAURENT==================");
    printf("\n\n plese select your prefered operation:\t");
printf("\n1.GENERATE INVOICE");
printf("\n2.SHOW ALL INVOICE");
printf("\n3.SEARCH INVOICE");
printf("\n4.EXIT");

printf("\nYOUR CHOICE\t");
scanf("%d",&opt);
fgetc(stdin);

switch(opt)
{

case 1:system("cls");
printf("PLEASE ENTER THE NAME OF THE CUSTOMER:\t");
        fgets(ord.customer,50,stdin);
        ord.customer[strlen(ord.customer)-1]=0;
        strcpy(ord.date,__DATE__);
        printf("Please enter the number of items:\t");
        scanf("%d",&n);
        ord.numofitems=n;
        for(i=0;i<n;i++)
        {
         fgetc(stdin);
         printf("\n\n");
         printf("Please enter the items:\t %d",i+1);
         fgets(ord.itm[i].item,20,stdin);
         ord.itm[i].item[strlen(ord.itm[i].item)-1]=0;
         printf("Please enter the quantity:");
         scanf("%d",&ord.itm[i].qty);
         printf("Please enter the unit of each piece:");
         scanf("%f",&ord.itm[i].price);
         total+=ord.itm[i].qty*ord.itm[i].price;

    }

generatebillheader(ord.customer,ord.date);
for(i=0;i<ord.numofitems;i++)
{

generatebillbody(ord.itm[i].item,ord.itm[i].qty,ord.itm[i].price);

}
generatebillfooter(total);
printf("\nDO TOU WANT TO SAVE BILL INVOICE[y/n]:");
scanf("%s",&saveBill);
if(saveBill=='y')
{

fp=fopen("Restaurentbill.dat","a+");
fwrite(&ord,sizeof(struct order),1,fp);
if(fwrite!=0)
{
    printf("\n succesfully saved");
}
else
{
    printf("\nerror in saving");
}
fclose(fp);

}
break;//case 1 khtm

case 2:system("cls");
fp=fopen("Restaurentbill.dat","r");
printf("\n*****your previous invoices*****\n");
while(fread(&order,sizeof(struct order),1,fp))
{
    float tot=0;
generatebillheader(order.customer,order.date);
for(i=0;i<order.numofitems;i++)
{
generatebillbody(order.itm[i].item,order.itm[i].qty,order.itm[i].price);
tot+=order.itm[i].qty*order.itm[i].price;

}
generatebillfooter(tot);
}
fclose(fp);
break;

case 3:
printf("\n ********enter name of the customer*******");
//fgetc(stdin);
fgets(name,50,stdin);
name[strlen(name)-1]=0;

system("cls");
fp=fopen("Restaurentbill.dat","r");
printf("\n*****invoice of %s*****\n",name);
while(fread(&order,sizeof(struct order),1,fp))
{
   float tot=0; 
   if(!strcmp(order.customer,name))
   {

generatebillheader(order.customer,order.date);
for(i=0;i<order.numofitems;i++)
{
generatebillbody(order.itm[i].item,order.itm[i].qty,order.itm[i].price);
tot+=order.itm[i].qty*order.itm[i].price;
}
generatebillfooter(tot);
invoicefound=1;
}
}
if(invoicefound!=1)
{
printf("sorry invoice not found for%s",name);



}
fclose(fp);
break;
case 4:
printf("\n BYE BYE ::)");
exit(0);
break;
default:printf("sorry invalid option kindly Recheck ");
break;







}
printf("Do you want to perform another operations?[y/n]");
scanf("%s",&continueflag);
}
printf("\n BYE BYE ::)");
printf("\n\n");
return 0;
}














