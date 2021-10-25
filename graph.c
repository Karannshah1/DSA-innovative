#include <stdio.h>
#include <stdlib.h>

struct nodeL{
    int data;
    int w1; // time/length
    int w2; // cost/totalNode
    struct nodeL *next;
    struct nodeL *prev;
};

struct Graph{
    struct nodeL *Gamma;
};

void NewNodeL(struct nodeL **u,int Data, int wTime , int wCost){
    (*u) = (struct nodeL *) malloc(sizeof(struct nodeL));
    (*u)->data = Data;
    (*u)->w1 = wTime;
    (*u)->w2 = wCost;
    (*u)->next = NULL;
    (*u)->prev = NULL;
}

void CreateGraph(struct Graph *g,int size){
    g->Gamma = (struct nodeL*) malloc((size+1)*sizeof(struct nodeL));
    //initialize with default value
    for (int i=0;i<=size;i++){
        struct nodeL *info = g->Gamma + i;
        info->data = i; //u of {u,v}
        info->next = NULL; //initialize with NULL
        info->prev  = info->next; //middle pointer
        info->w1 = 0; //length
        info->w2 = size; //max nodes
    }
}

void Insert(struct Graph *g, int u, int v, int wTime , int wCost){
    // {u,v}
    struct nodeL *nn;
    NewNodeL(&nn,v,wTime,wCost);
    struct nodeL *p = g->Gamma + u; // p is in gamma area
    if (p->w1 == 0){
        p->next = nn;
        nn->prev = p;
        p->w1++; //lenght
        p->prev = nn; // last pointer
        nn->next = p->prev;
    }
    else{
        struct nodeL *last= p->prev;
        struct nodeL *first = p->next;
        if(first->data > v ){
            p->next = nn;
            nn->prev = p;
            first ->prev = nn;
            nn->next = first;
            p->w1++;
            // no need to change last  pointer
        }
        else if (last->data < v){
            last->next = nn;
            nn->prev = last;
            p->prev = nn;
            p->w1++;
            nn->next = p;
        }
        else{
            while(first->next->data < v) first = first->next;
            struct nodeL *temp;
            temp = first->next; // temp->data > v
            first->next = nn;
            nn->prev = first;
            nn->next  = temp;
            temp->prev = nn;
            p->w1++;
        }
    }
}
void Mega_Insert(struct Graph *g, int u, int v, int wTime , int wCost){
    Insert(g,u,v,wTime,wCost);
    Insert(g,v,u,wTime,wCost);
}

void PrintGraphAdjList(struct Graph *g){
    int n = g->Gamma ->w2;
    for (int i=1;i<=n;i++){
        struct nodeL *t = (g->Gamma + i); // t is in gamma domain
        struct nodeL *p = t->next; // p is in list
        int m = t->w1;
        for (int j=1;j<=m;j++){
            printf("{%d,%d} , %d ,%d\n",t->data,p->data,p->w1,p->w2);
            p = p->next;
        }
    }
}
 void lakshit_test(){
    struct Graph MG;
    CreateGraph(&MG,4);
    //{1,2}
    Mega_Insert(&MG,1,2,12,21);
    //{2,3}
    Mega_Insert(&MG,2,3,23,32);
    //{2,4}
    Mega_Insert(&MG,2,4,24,42);

    PrintGraphAdjList(&MG);
}

int main(){
    lakshit_test();
    return 0;
}
