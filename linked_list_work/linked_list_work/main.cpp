//
//  main.cpp
//  linked_list_work
//
//  Created by ibrahim dağcı on 25.02.2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct Node{
    char foodName[30];
    int foodGramaj;
    float foodCost;
    Node *next;
    
}Node;

 Node *head=NULL;
 Node *temp=NULL;
 Node *tempPrev = NULL;
 Node *tail=NULL;


void linkedList(char name[30],int gramaj,float cost){
    
    int strlegth = (int)strlen(name);
    if (head==NULL) {
        Node *space=(Node*)malloc(1*sizeof(Node));
        head=tail=space;
        for(int i=0;i<strlegth;i++){
            head->foodName[i]=name[i];
        }
        head->foodGramaj = gramaj;
        head->foodCost = cost;
        tail->next=head;
    }
    else{
        Node *space=(Node*)malloc(1*sizeof(Node));
        for(int i=0;i<strlegth;i++){
            space->foodName[i]=name[i];
        }
        space->foodGramaj = gramaj;
        space->foodCost = cost;
        if(space->foodCost<head->foodCost){
            space->next = head;
            head = space;
            tail->next = head;
        }
        else if (space->foodCost>tail->foodCost){
            tail->next = space;
            tail=space;
            tail->next = head;
        }
        else{
            
            temp = head->next;
            tempPrev = head;
            while(temp!=head){
                if(space->foodCost<=temp->foodCost && space->foodCost>=tempPrev->foodCost){
                    tempPrev->next = space ;
                    space->next = temp;
                    break;
                }
                else{
                    tempPrev = tempPrev->next;
                    temp = temp->next;
                }
            }
        }
    }
}

void freee(){
    temp=head;
    Node *nowTemp;
    while (temp->next!=head) {
        nowTemp=temp;
        temp=temp->next;
        free(nowTemp);
    }
}

void readText(FILE *fFile ){
    rewind(fFile);
    char foodName[30];
    int Gr;
    float Cst;
    while (!feof(fFile)) {
        fscanf(fFile,"%s %d %f",foodName,&Gr,&Cst);
        
        linkedList(foodName,Gr,Cst);
    }
}

int deleteFood(char willDeleteFood[30]){
    int strlegth = (int)strlen(willDeleteFood);
    int counter = 0;
    Node *prevsPrev=NULL;
    temp = head;
    tempPrev = tail;
    while(temp->next!=head){
        for(int i=0;i<strlegth;i++){
            if(temp->foodName[i]==willDeleteFood[i]){
                counter++;
            }
        }
        if(counter==strlegth) {
            if(temp==head){
                if (head==tail) {
                    free(temp);
                    head = NULL;
                    tail = NULL;
                    printf("*****");
                }else{
                    head=temp->next;
                    tail->next = head;
                    free(temp);
                }
                
            }else{
                tempPrev->next = temp->next;
                free(temp);
            }
            return 1;
        }
        counter = 0;
        temp = temp->next;
        tempPrev = tempPrev->next;
        if(temp->next->next==head){
            prevsPrev=temp;
        }
    }
    for(int i=0;i<strlegth;i++){
        if(tail->foodName[i]==willDeleteFood[i]){
            counter++;
        }
    }
    if(counter==strlegth){
        
        if (head->next!=NULL) {
            tail=prevsPrev;
        }
        
        if (head!=NULL) {
            tail->next = head;
        }else{
            tail = NULL;
        }
        
        free(temp);
        return 1;
    }
    else{
        return 0;
    }
    
    
}

void foodMenuList(){
    if (head==NULL) {
        printf("Listelenecek kayıt yok!!!");
    }else{
        temp = head;
        while (temp->next != head) {
            for(int i=0;i<strlen(temp->foodName);i++){
                printf("%c",temp->foodName[i]);
            }
            printf("\n");
            temp = temp->next;
        }
        printf("%s\n",tail->foodName);
    }
    
}

void chooseFood(){
    printf("Yemek seçimi için 1\nBir sonraki yemeğe geçmek için 2\nana menuye donmek icin 3\n");
    int choose;
    temp = head;
    while (1) {
        printf("%s:(1/2/3)",temp->foodName);
        scanf("%d",&choose);
        switch (choose) {
            case 1:
                printf("%s sectiniz \nsiparisiniz en kısa sürede teslim edilecektir\nAfiyet Olsun :)\n",temp->foodName);
                choose = 3;
                break;
            default:
                break;
        }
        if (choose==3) {
            break;
        }
        temp=temp->next;
    }
}

void userMenu(){
    int chooseIndex,cikis=1;
    
    while (cikis==1) {
        printf("Lütfen yapmak istediğiniz işlemi seçin\n1-> Yemek menüsü\n2-> Yemek Seçimi\n3-> Yemek Silme\n4-> Yemek ekleme\n0->Çıkış\n");
        char food[30];
        int  Gr;
        float price;
        int check = 0 ;
        scanf("%d",&chooseIndex);
        switch (chooseIndex) {
            case 1:
                foodMenuList();
                break;
            case 2:
                chooseFood();
                break;
            case 3:
                
                printf("silmek istediginiz yemegin adını boşluk bırakmadan giriniz\n");
                scanf("%s",food);
                check = deleteFood(food);
                if (check) {
                    printf("yemek silindi\n");
                }
                else{
                    printf("bu yemek listede yok\n");
                }
                break;
            case 4:
                printf("eklemek istediginiz yemegin adını boşluk bırakmadan giriniz\n");
                scanf("%s",food);
                printf("eklemek istediginiz yemegin gramajını  giriniz\n");
                scanf("%d",&Gr);
                printf("eklemek istediginiz yemegin fiyatını boşluk bırakmadan giriniz\n");
                scanf("%f",&price);
                linkedList(food, Gr, price);
                printf("başarıyla eklendi\n");
                break;
            
            default:
                cikis = 0;
                break;
        }
        
    }
}



int main (){
    FILE *foodFile=fopen("/Users/ibrahimdagci/Desktop/DataStructure/data_structure_work1/foodlist.txt","r+");
    readText(foodFile);
    userMenu();
    freee();
    free(tail);
    fclose(foodFile);
    return 0;
}
