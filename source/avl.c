#include "avl.h"

int specialCompare(char* wordItem1, char* wordItem2){
   char * splited1;
   char * splited2;
   char iitem[500];
   char hitem[500];
   int compareOccorrences;
   strcpy(iitem,wordItem1);
   strcpy(hitem,wordItem2);
   splited1=strtok(iitem,"#");
   splited2=strtok(hitem,"#");
   compareOccorrences = strcmp(wordItem2,wordItem1);
   if(compareOccorrences==0){
       splited1=strtok(NULL,"#");
       splited2=strtok(NULL,"#");
       return strcmp(splited1,splited2);

   }else
       return compareOccorrences;
}

link NEW(Item item, link l, link r)
{
    link x = (link)malloc(sizeof(struct STnode));
    x->item = item;
    x->l = l;
    x->r = r;
    x->height=1;
return x; 
}

int height(link h){
    if (h == NULL) return 0;
    return h->height;
}

void STinit(link*head)
{
*head = NULL;
}

void STinsert(link*head, Item item)
{
    *head = insertR(*head, item);
}


link max(link h) {
  if (h==NULL || h->r==NULL) return h;
  else return max(h->r);
}

link min(link h) {
  if (h==NULL || h->l==NULL) return h;
  else return min(h->l);
}

link rotL(link h)
{
    int height_left, height_right;
    link x = h->r;
    h->r = x->l;
    x->l = h;
  height_left = height(h->l); height_right = height(h->r);
  h->height = height_left > height_right ?  height_left + 1 :
  height_right + 1;
  height_left = height(h->l); height_right = height(x->r);
  x->height = height_left > height_right ?  height_left + 1 :
  height_right + 1;
  return x;
}


link AVLbalance(link h) {
    int balanceFactor;
    if (h==NULL) return h;
    balanceFactor= Balance(h);
    if(balanceFactor>1) {
        if (Balance(h->l)>=0) h=rotR(h);
        else                 h=rotLR(h);
    }
    else if(balanceFactor<-1){
        if (Balance(h->r)<=0) h = rotL(h);
        else                 h = rotRL(h);
} else{
        int height_left = height(h->l); int height_right = height(h->r);
        h->height = height_left > height_right ?  height_left + 1 :
   height_right + 1;
}

return h; }

/*
link deleteR(link h, Key k)
{
    if (h==NULL) return h;
    else if (less(key(h->item),k)) h->l=deleteR(h->l,k);
    else if (less(k,key(h->item))) h->r=deleteR(h->r,k) ;
    else {
        if (h->l !=NULL && h->r !=NULL){
            link aux=max(h->l);
            {Item x; x=h->item; h->item=aux->item; aux->item=x; }
            h->l= deleteR(h->l, key(aux->item));
        } else { 
            link aux=h;
            if ( h->l == NULL && h->r == NULL ) h=NULL;
            else if (h->l==NULL) h=h->r;
            else h=h->l;
            deleteItem(aux->item);
            free(aux);
        }
    }
    h=AVLbalance(h);
    return h;
}*/


link deleteR(link h, Key k)
{
    char * splited1;
    char achas[500];
    char reptostr[20];
    if (h!=NULL){
        strcpy(achas,k);
        splited1=strtok(achas,"#");
        sprintf(reptostr, "%d", h->item->rep);
        printf("Rep:%s splited1:%s Item: %s k:%s \n",reptostr,splited1,h->item->item,k);
        //printf("%s %s\n",reptostr,splited1);
        //splited1=strtok(NULL,"#");
        //printf("%s %s\n",h->item->hashtag,splited1);
    }
    if (h==NULL) return h;
    else if (less(reptostr,splited1)) {
            //splited1=strtok(NULL,"#");
            printf("Q:%d QQ:%s\n",h->item->rep,splited1);
            h->l=deleteR(h->l,k) ;
    }
    else if (greater(reptostr,splited1)) {
            //splited1=strtok(NULL,"#");
            printf("R:%d RR:%s\n",h->item->rep,splited1);
            h->r=deleteR(h->r,k) ;


    }

    else {
        splited1=strtok(NULL,"#");
        if(less(h->item->hashtag,splited1))
            h->r=deleteR(h->r,k) ;
        else if(greater(h->item->hashtag,splited1))
            h->l=deleteR(h->l,k) ;
        else
        if (h->l !=NULL && h->r !=NULL && eq(h->item->hashtag,splited1)){
                link aux=max(h->r);
                {Item x; x=h->item; h->item=aux->item; aux->item=x;}
                h->r= deleteR(h->r, key(aux->item));
        } 
        else 
        { 
            link aux=h;
            if (h->l == NULL && h->r == NULL) h=NULL;
            else if (h->l==NULL) h=h->r;
            else h=h->l;
            deleteItem(aux->item);
            free(aux);
        }
    }
    h=AVLbalance(h);
    return h;
}

/*
link deleteR(link h, Key k) {
    char * splited1;
    char achas[500];
    char reptostr[20];
    if (h!=NULL){
        strcpy(achas,k);
        splited1=strtok(achas,"#");
        sprintf(reptostr, "%d", h->item->rep);
        //printf("A:%s k:%s\n",reptostr,splited1);
        
        printf("B:%s :%s\n",h->item->hashtag,k);
    }
    if (h==NULL) return h;
    else if (greater(splited1,reptostr)) h->l=deleteR(h->l,k);
    else if (less(splited1, reptostr)) h->r=deleteR(h->r,k) ;
    else{
        splited1=strtok(NULL,"#");

        if (h->l !=NULL && h->r !=NULL){
            if(greater(splited1,h->item->hashtag)){
                link aux=max(h->l);
                {Item x; x=h->item; h->item=aux->item; aux->item=x;}
                h->l= deleteR(h->l, key(aux->item));
            }
            else{
                link aux=max(h->r);
                {Item x; x=h->item; h->item=aux->item; aux->item=x;}
                h->r= deleteR(h->r, key(aux->item));
            }
        }else {
            link aux=h;
            if (h->l == NULL && h->r == NULL) h=NULL;
            else if (h->l==NULL) h=h->r;
            else h=h->l;
            deleteItem(aux->item);
            free(aux);
        }
    }
    h=AVLbalance(h);
    return h;
}
*/
link rotR(link h)
{
    int height_left, height_right;
    link x = h->l;
    h->l = x->r;
    x->r = h;


 height_left = height(h->l); height_right = height(h->r);
 h->height = height_left > height_right ?  height_left + 1 :
height_right + 1;
 height_left = height(x->l); height_right = height(h->r);
 x->height = height_left > height_right ?  height_left + 1 :
height_right + 1;
return x;
}

link rotLR(link h) /*rotação dupla esquerda direita*/
{
    if (h==NULL) return h;
    h->l=rotL(h->l);
    return rotR(h);
}
link rotRL(link h) /*rotação dupla direita esquerda*/
{
    if (h==NULL) return h;
    h->r=rotR(h->r);
    return rotL(h);
}
int Balance(link h) {/*Balance factor*/
    if(h == NULL) return 0;

    return height(h->l)-height(h->r);
}

int count(link h){
    if (h==NULL) return 0;
    else return count(h->r)+count(h->l)+1;
}

int STcount(link head){
    return count(head);
}
void STdelete(link*head, Key k){
    *head = deleteR(*head, k);
}


//specialCompare(h->item->item,item->item)
link insertR(link h, Item item)
{
   if (h == NULL)
       return NEW(item, NULL, NULL);
   if (h->item->rep < item->rep)
       h->l = insertR(h->l, item);
   else if (h->item->rep > item->rep){
       h->r = insertR(h->r, item);
   }
   else{
       if (greater(h->item->hashtag, item->hashtag)){
           h->l = insertR(h->l, item);   
       }
       else
           h->r = insertR(h->r, item);   
   }
   h=AVLbalance(h);

return h; }


void sortR(link h, void (*visit)(Item))
{
    if (h == NULL)
        return;
    sortR(h->l, visit);
    visit(h->item);
    sortR(h->r, visit);
}
void STsort(link head, void (*visit)(Item))
{
    sortR(head, visit);
}


link freeR(link h)
{
    if (h==NULL)
        return h;
    h->l=freeR(h->l);
    h->r=freeR(h->r);
    return deleteR(h,key(h->item));
}
void STfree(link*head)
{
    *head=freeR(*head);
}