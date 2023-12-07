#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//Define our list node
/**********************************************************/
/* You can not modify the code in this block */
/* You can not modify the code in this block */
/* You can not modify the code in this block */
struct ListNode {
	int val;
 	struct ListNode *next;
};
struct ListNode* append_node(struct ListNode* head, int val);
struct ListNode* delete_node(struct ListNode* head, int position);
struct ListNode* insertionSortList(struct ListNode* head);
/**********************************************************/

int main(int argc, char const *argv[])
{
	//Given array
	int int_arr[6] = {5,4,3,1,2,6};
	struct ListNode *head = NULL; 
	//transform array to linked list
    for(int i = 0; i < 6; i++){
		head = append_node(head, int_arr[i]);
	}
    //printf("Before sorting:\n");
    //insertion sort
    head = insertionSortList(head);
    //printf("After sorting:\n");
    //Print the list
    /*
     The output should be
     1
     2
     3
     4
     5
     6
     */
	struct ListNode *node = head, *tmp;
	while(node != NULL){
		printf("%d\n",node->val);
		tmp = node;
		node = node->next;
		free(tmp);
	}
	return 0;
}

struct ListNode* append_node(struct ListNode* head, int val){
	if(head == NULL){
		struct ListNode *newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
		newNode->val = val;
		newNode->next = NULL;
		head = newNode;
		return head;	
	}else { 
		struct ListNode *newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
		struct ListNode *tail = head;
		while(tail->next != NULL)tail = tail->next; 
		newNode->val = val;
		tail->next = newNode;
		newNode->next = NULL;
	}
	return head;
}

//Insertion sort
/**********************************************************/
/* You don't have to modify the code in this block */
struct ListNode* insertionSortList(struct ListNode* head) {
    if(head == NULL)return NULL;

    struct ListNode *node = head->next, *pre = head; 
    while(node != NULL){
        struct ListNode *tmp = node;
        //handle head
        if(tmp->val < head->val){
            pre->next = node->next;
            node->next = head;
            head = node;
        } else {
            struct ListNode *j = head->next, *jpre = head;
            while(j != node){
                if(tmp->val < j->val){
                    pre->next = node->next;
                    jpre->next = node;
                    node->next = j;
                    break;
                }
                jpre = j;
                j = j->next;
            }
        }
	    pre = tmp;
        node = tmp->next;
        
    }
    return head;
}
/**********************************************************/
