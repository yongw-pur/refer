#include <malloc.h>
#include <stdio.h>
#include <stddef.h> //offsetof
/*
#undef offsetof
#define offsetof(type, member) ((size_t) &((type *)0)->member)
*/

typedef struct node{
	struct node *next; 
	struct node *prev;
} ListNode;

#define INIT_HEAD(field) do {\
      (field).next = &(field);               \
      (field).prev = &(field);               \
   } while (0)

#define HEAD_INIT(name) { &(name), &(name) }

/*Create head and init*/
#define LIST_HEAD(name) \
	struct node name = HEAD_INIT(name)

static inline int list_empty(const struct node *head)
{
	return ((head->next == head) && (head->prev == head));
}

static inline void list_append(struct node *new, struct node *cur)
{
   cur->next->prev = new;

   new->next = cur->next;
   new->prev = cur;

   cur->next = new;
}

static inline void list_prepend(struct node *new, struct node *cur)
{
   cur->prev->next = new;

   new->next = cur;
   new->prev = cur->prev;

   cur->prev = new;
}

static inline void list_unlink(struct node *entry)
{
   entry->next->prev = entry->prev;
   entry->prev->next = entry->next;

	entry->next = 0;
	entry->prev = 0;
}

#define container_of(ptr, type, member) ({			\
        const typeof( ((type *)0)->member ) *__mptr = (ptr);	\
        (type *)( (char *)__mptr - offsetof(type,member));})

/*已知结构体某个成员的地址，得到结构体的地址*/
#define list_entry(ptr, type, member) \
	container_of(ptr, type, member)

#define list_for_each_entry(pos, head, member)				\
	for (pos = list_entry((head)->next, typeof(*pos), member);	\
	     &pos->member != (head); 					\
	     pos = list_entry(pos->member.next, typeof(*pos), member))

#define list_for_each_entry_safe(pos, tmp, head, member)				\
        for (pos = list_entry((head)->next, typeof(*pos), member),\
             tmp = list_entry(pos->member.next, typeof(*pos), member); \
             &pos->member != (head);                    \
             pos = tmp, tmp = list_entry(pos->member.next, typeof(*pos), member))

typedef struct
{
    int stuNum;
    ListNode stuList; //keep student info list head;
}Ctx;

typedef struct
{
    int number;
    char *name;
    ListNode _list;
}Student;

void Stu_Free(Student **stu)
{
    Student *pstu;
    pstu = *stu;
    list_unlink(&pstu->_list);

    free(pstu);
    pstu = NULL; //并不会变stu的地址
    return;
}

void main()
{
    Ctx ctx;
    INIT_HEAD(ctx.stuList);

    Student *pstu = malloc(sizeof(Student));
    list_prepend(&pstu->_list, &ctx.stuList);
    pstu->number = 1234;
    Student *stu, *temp;
    list_for_each_entry_safe(stu, temp, &ctx.stuList, _list)
    {
        printf("stu->_list %p, stu->list.next %p\n", stu->_list, stu->_list.next);
        Stu_Free(&conn);
    }  
}   
             
