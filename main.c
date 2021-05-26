#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct  processus proc;

struct processus
{
    char nom[4];
    int duree;
    proc *suivant;
};

typedef struct ordonnancement ord;
struct ordonnancement
{
    char nom[10];
    ord * suivant;
};


void affichage_ord(ord *o)
{
    printf("----ordonnancement-----\n");
    ord *current=(ord*)malloc(sizeof(*current));
    current=o;

    while(current!=NULL)
    {
        printf("%s->",current->nom);
        current=current->suivant;
    }
    printf("FIN\n");

}
void affichage_pro(ord *o)
{

    proc *current=(proc*)malloc(sizeof(*current));
    current=o;

    while(current!=NULL)
    {
        printf("%s,%d\n",current->nom,current->duree);
        current=current->suivant;
    }
    printf("FIN\n");



}

proc *insert_porcedure(proc *p,char * nom,int duree)
{
    proc *nouveau=(proc*)malloc(sizeof(*nouveau));
    proc *tmp=(proc*)malloc(sizeof(*tmp));

    strcpy(nouveau->nom,nom);
    nouveau->duree=duree;
    nouveau->suivant=NULL;
    if(p==NULL)
    {

        return nouveau;
    }
    else
    {
        tmp=p;
        while(tmp->suivant!=NULL)
        {
            tmp=tmp->suivant;
        }
        tmp->suivant=nouveau;

        return p;
    }
}


proc *read_file(proc *p)
{
    FILE *f=fopen("processus.txt","r");
    proc tmp;


    if(f==NULL)
    {
        fprintf(stderr,"\nError to open the file\n");
        exit(1);
    }

    while(fread(&tmp,sizeof(proc),1,f))
    {

        p= insert_porcedure(p,tmp.nom,tmp.duree);

    }




    fclose(f);
    return p;
}
void print_in_file(proc *p)
{
    FILE *f=fopen("processus.txt","w");
    if(f==NULL)
    {
        fprintf(stderr,"\nError to open the file\n");
        exit(1);
    }
    proc *tmp=(proc*)malloc(sizeof(*tmp));
    tmp=p;
    while(tmp!=NULL)
    {
        fwrite(tmp,sizeof(proc),1,f);
        tmp=tmp->suivant;
    }

    fclose(f);
}


ord *insert_ord(ord *rr,char * nom)
{
    ord *nouveau=(ord*)malloc(sizeof(*nouveau));
    ord *tmp=(ord*)malloc(sizeof(*tmp));

    strcpy(nouveau->nom,nom);
    nouveau->suivant=NULL;
    if(rr==NULL)
    {

        return nouveau;
    }
    else
    {
        tmp=rr;
        while(tmp->suivant!=NULL)
        {
            tmp=tmp->suivant;
        }
        tmp->suivant=nouveau;

        return rr;
    }
}


int exist_values(proc *p)
{
    int test=0;
    proc *tmp=(proc*)malloc(sizeof(*tmp));
    tmp=p;
    while(tmp!=NULL)
    {
        if(tmp->duree>0)
        {
            test=1;
            break;
        }
        tmp=tmp->suivant;
    }
    return test;
}
ord * scheduler(ord *rr,int q,proc *p)
{

    proc *tmp=(proc*)malloc(sizeof(*tmp));

while(exist_values(p)){
        tmp=p;
    while(tmp!=NULL)
    {
        if(tmp->duree>0)
        {
            rr=insert_ord(rr,tmp->nom);
            tmp->duree-=q;
        }
        tmp=tmp->suivant;

    }}
    return rr;

}
int main()
{
    proc *p1=NULL;
    int quantum=3;
    ord *round_robin=NULL;
    char c;

    int reponse=0;
    whil:while(reponse==0){
        puts("##########MENU############");
        puts("1-INSERE VALEUR IN FILE");
        puts("2-READ FROM FILE ");
        puts("3-ROUND_ROBIN /SHOW");
        puts("4-EXIT");
        puts("Answer:");
        scanf("%d",&reponse);
        if(reponse==1){
                int n;
                char name[3];
                int duree;
                printf("NUMBER OF PROCESS :");
                scanf("%d",&n);
                for(int i=0;i<n;i++){
                    printf("proccess %d\n:",i);
                    printf("nom: ");
                    scanf("%s",name);
                    printf("\nDuration:");
                    scanf("%d",&duree);
                    p1=insert_porcedure(p1,name,duree);
                }
                print_in_file(p1);
            system("cls");
            goto whil;
        }
        else if(reponse==2){
            system("cls");
            puts("File is readen");
            p1=read_file(p1);
            system("cls");
            reponse=0;
            goto whil;
        }
        else if(reponse==3){
            char d;
            system("cls");
            round_robin=scheduler(round_robin,quantum,p1);
            affichage_ord(round_robin);
            d=getchar();
            reponse=0;
            goto whil;
        }
        else if(reponse==4){
            exit(1);
        }
        else{
            system("cls");
            fprintf(stderr,"WRONG CHOICE!!\n");

            reponse=0;
            goto whil;
        }

    }



    return 0;
}
