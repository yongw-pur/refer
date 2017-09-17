//clist incomplement list.h
//change the clist_s para to adapt to other application


//#include "syn_clist.h"
#include <stdlib.h>
#include <stdio.h>
struct list_head {
	struct list_head *next, *prev;
};

typedef struct
{
    struct list_head clist;
    unsigned char ether_addr[6];//ETH_ALEN
    unsigned int ip_addr;
}clist_s;
#define clist_entry(link, type, member) \
	((type *)((char *)(link)-(unsigned long)(&((type *)0)->member)))

#define for_each_clist(pelem, phead) \
    for(pelem = clist_entry(((phead)->clist).next, clist_s, clist); \
        pelem != phead; \
        pelem = clist_entry((pelem->clist).next, clist_s, clist))
//############head######################################

#define clist_for_each_safe(pos, n, head) \
	for (pos = (head)->next, n = pos->next; pos != (head); \
		pos = n, n = pos->next)
    
static inline void INIT_LIST_HEAD(struct list_head *list)
{
    list->next = list;
    list->prev = list;
}

static inline int list_empty(struct list_head *head)
{
	return head->next == head;
}

static inline void list_add(struct list_head *new, struct list_head *head)
{
	head->next->prev = new;
    new->next = head->next;
    new->prev = head;
    head->next = new;
}

static inline void list_del (struct list_head *elem)
{
  elem->next->prev = elem->prev;
  elem->prev->next = elem->next;
}


int model_init_clist(clist_s *plist)
{
    INIT_LIST_HEAD(&(plist->clist));
}

int model_add_clist(clist_s *pelem, clist_s *phead)
{
    list_add(&(pelem->clist), &(phead->clist));
}

int model_delete_clist(clist_s *pelem)
{
    list_del(&(pelem->clist));
    free(pelem); 
    pelem = NULL;
}

int model_free_clist(clist_s *phead)
{
    clist_s *p_del;
    struct list_head*tlist, *nlist;
    clist_for_each_safe(tlist, nlist, &(phead->clist))  
    {  
        list_del(tlist);  
        p_del = clist_entry(tlist, clist_s, clist);  
        free(p_del); 
        printf("free addr %p\n", p_del);
        p_del = NULL;
    }
    
    list_empty(&(phead->clist));
}

void main()
{
	int c;
	//the elemet is the head of list
	//it supply list_head,and other field in this elem has little effect
	clist_s clist;
	clist_s *plist;
	model_init_clist(&clist);
	for(c = 0 ; c < 5; c++)
	{
	    plist = (clist_s *)malloc(sizeof(clist_s));
	    printf("malloc addr %p\n", plist);
	    model_add_clist(plist, &clist);
	}
	for_each_clist(plist, &clist)
	{
	    printf("for each addr %p\n", plist);
	}
	model_free_clist(&clist);	
}