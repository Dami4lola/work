
/* 
File name is linked_list_hospital.c
 Purpose: file contains functions for manipulating singly linked list
 
 Revisions
 Doron Nussbaum 2022 File created

 
 
 
 
 
 Copyright 2022 Doron Nussbaum
 
 */

/******************************************************************/
// INCLUDE 

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "linked_list_hospital.h"
#include "patient.h"


/************************************************************************/
// Define 

//helper functions
/*
int addNode(ListNode **head, Employee *data)
{
	ListNode *p = NULL;
	p = (ListNode*) malloc(sizeof(ListNode));
    if (p == NULL){
        return (1);
    }
	p->data = data;
	p->next = head;
    *head = p;
    return(0);

}

void printList(ListNode *head)
{
        printf("\n\nList elements are - \n");
        while(head != NULL){
            printf("%d", head->data);

            if (head->next != NULL){
                printf("------>");
            } else {
                printf("\n");
                head = head->next;
            }
        }


}

void printListRecursive(ListNode *head)
{
    while(head != NULL){
            printf("%d", head->data);
            if (head->next != NULL){
                printf("------>");
            } else {
                printf("\n");
                head = head->next;
            }
        }
}

int compare(ListNode *head){
    int n1, n2;
    n1 = *(int *)head;
    n2 = *(int *)head->next;
    if (n1 < n2){
        return 1;
    }
    if (n2 < n1){
        return -1;
    }
    return (0);
}

void printListInReverse(ListNode *head){
	while(head != NULL){
            printf("%d", head->data);
            if (head->next != NULL){
                printf("------>");
            } else {
                printf("\n");
                head = head->next;
            }
        }

}

void deleteNode(ListNode **head, Employee **data){
	ListNode *currNode, *prevNode;
    *data = (*head)->data;
    prevNode = NULL;
    currNode = *head;
    while(currNode != NULL){
        if (strcmp(currNode->data, *data) == 0){
            break;
        }
        prevNode = currNode;
        currNode = currNode->next;
    }
    if (currNode == NULL){
        printf("Data Not Found");
    }

    if (prevNode == NULL){
        *head = currNode->next;
    } else {
        prevNode->next = currNode->next;
    }
    free(currNode->data);
    free(currNode);
}

*/






/************************************************************************/

/*
Purpose: insert a new node into the list as the first element
input
patient - the patient record

input/output
head - head of linked list

return
A pointer to the node that was allocated.  

NULL - if the operation was not successful

*/

ListNode *insertToList(ListNode **head, PatientInfo *patient){
	// add code
	ListNode *p = NULL;// initialize node to null
	p = (ListNode*) malloc(sizeof(ListNode));//allocate memeory 
    if (p == NULL){//check is list is empty
        return NULL;
    }
	p->patient = *patient;//set patient data
	p->next = *head;
    *head = p;
    return p;
}


/************************************************************************/
/*
Purpose: insert a new node into the list after the given node  

Input
input
patient - the patient record


return
A pointer to the node that was allocated.  

NULL - if the operation was not successful

*/


ListNode *insertAfter(ListNode *node, PatientInfo *patient)
{
	// add code 
	//check if the given prev_node is NULL
    if (node == NULL) {
        printf("the given patient does not exist ");
        return NULL;
    }
    
    ListNode *new_node = NULL;// set nnode to null
    
    new_node =(ListNode*) malloc(sizeof(ListNode));// allocate memory
    
    new_node->patient = *patient;

    new_node->next = node->next;    //Make next of new node as next of prev_node 

    node->next = new_node;    //move the next of prev_node as new_node 
    
    return new_node;
}




/************************************************************************/
/*
Purpose: search for the first patient with the matching priority
Input
head - the head of the list
priority - first priority of the patient

output
patient - the patient record

return
a pointer to the node that was found.
NULL - if no node was found or list empty

*/


ListNode * searchFirstPatientByPriority(ListNode *head, unsigned char priority, PatientInfo *patient){
	// add code 
	
   ListNode *current = head; // Initialize current
   
   while (current != NULL) { // loop throught list whilee its nnot empty  
	   if (current->patient.priorityLevel == priority){//check priotiy level of patienntss
			*patient = current->patient;
		   return current;
		   
	   }else current = current->next;
	   }

	return NULL;
}

/************************************************************************/
/*
Purpose: search for the first patient with the matching criteria.  The criteria is determined
by the comparison function 
Input
head - the head of the list
findPatient -  a function pointer that returns a 0 if the patient's record matches that criteria

output
patient - the patient record

return
a pointer to the node that was found.
NULL - if no node was found or list empty

*/


ListNode * searchNextPatient(ListNode *head, int (*findPatient)(PatientInfo *), PatientInfo *patient)
{
	// add code 
	ListNode *p = NULL;
	p = head; // Initialize node
   
	while (p != NULL) {// loop through the list
		if (findPatient(&p->patient) == 0){  // if wanted node found
			*patient = p->patient;
			return p;
		}else p = p->next;
	}

	return NULL;
	   
	return p;
	

}

/***************************************************************/

/*
Purpose: delete the first node from the list
Input
head - the head of the list

output
head - the head of the list
patient - the patient record


return

0 if node was deleted
1 if node was not deleted or list is empty

*/


int deleteFromList(ListNode **head, PatientInfo *patient){
	if(*head == NULL){//check if node is empty
		return 1;
	}
	
	for(ListNode *curr = *head; curr->next!=NULL;curr=curr->next){
		PatientInfo *y=&curr->next->patient;
		if(y == patient){
			ListNode *remove = curr->next;
			curr->next=curr->next->next;
			free(remove);}
	}
	
	
return 0;
}


/***************************************************************/

/*
Purpose: Retrieve the first node that matches the priority.  When found the node is deleted and the patient
information is provided. 

Input
head - the head of the list

output
head - the head of the list
patient - the patient record


return

0 if node was deleted  
1 if node was not found or list is empty 

*/


int retrieveNextPatientByPriority(ListNode **head, unsigned char priority, PatientInfo *patient){
 
	
    // add code 
    int rc = 0;
	
	
	if(*head == NULL){// check if the list is empty
		return 1;
	}
	
	//check if the head is the node we want to delete
	if((*head)->patient.priorityLevel == priority){
		//Create a pointer that points to head
		ListNode *temp = *head;
		//set head to the next item in the list
		*patient = temp->patient;
		*head = (*head)->next;
		free(temp);
		temp = NULL;
	}
	
	//Loop through the list
	for(ListNode *curr= *head; curr->next != NULL; curr = curr->next){
		//if current node is what we want to delete
		if(curr->next->patient.priorityLevel == priority){
			//Create a pointer that points to the node
			ListNode *temp = curr->next;
			//remove the unwanted node
			curr->next = curr->next->next;
			//store the patient info
			*patient = temp->patient;
			//free memory
			free(temp);
			temp = NULL;
			return 0;
		}
	}
	return 1;
 
}

/***************************************************************/

/*
Purpose: Retrieve the patient with the highest criteria to be treated.  The maximum criteria is determined by 
a comparePatients function.  Once the patient is found it is deleted from the list and its information is 
returned. 

Input
head - the head of the list
comparePatients - this function takes two paitent records and compares them.  
				It returns, -1, 0 or 1 if p1 < p2, p1 == p2, or p1 > p2, respectively. 

output
head - the head of the list
patient - the patient record


return
0 if  patient was found and the node was deleted  
1 if no paitent was found or the list is empty 


Algorithm:
The function first finds the patient with the hights criteria by comparing all the patients records and 
finding the first patient with the maximum criteria to be treated.  It then deletes the patient and returns
its information. 
*/


int retrieveNextPatientByCriteria(ListNode **head, int (*comparePatients)(PatientInfo *p1, PatientInfo *p2, int currentTime), int currentTime, PatientInfo *patient){

    // add code 
 

    // check if list is empty
	if (*head == NULL){
		return 1;
	}
 	// otherwise 
 	// find next patient (similar to find a maximum value)
 	ListNode *highest_node= *head;
	for(ListNode *curr= *head; curr->next != NULL; curr = curr->next){
		
		if(comparePatients(&curr->patient,&highest_node->patient,currentTime) == 1){
			highest_node = curr;
		}
	} 

    // remove next patient from the list
    // if it is first node 


    // else it is somewhere in the list

	


	//printPatient(&highest_node->patient);
	int x = retrieveNextPatientByPriority(head,highest_node->patient.priorityLevel,patient);
	return 0;


  
 
}



/************************************************************************/
/*
Purpose: deletes all nodes from the list
input/output
head - the head of the list


*/


void deleteList(ListNode **head)
{
	// add code 

    ListNode *nextItem=*head;
  
  	while(head != NULL) {//loop while head is not empty
		nextItem = nextItem->next;
		free(head);
		head = &nextItem;
    }
    
}



/************************************************************************/
/*
Purpose: prints all the records in the list

input
head - the head of the list
myPrint - a function pointer for print the patient information. 
*/


void printList(ListNode *head, void (*myPrint)(PatientInfo *patient))
{
	// add code 
	while (head != NULL) {
		myPrint(&head->patient);
        head = head->next;
    }
 
}


/************************************************************************/
/*
Purpose: counts the number of patients that are waiting to be treted
input
head - the head of the list

return 
the number of registered patients

*/


int numPatientsInEmergency(ListNode *head)
{
	// add code 
	int count = 0; // Initialize count
    ListNode* current = head; // Initialize current
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
 

}

/************************************************************************/
/*
Purpose: counts the number of patients with a matching priority
input
head - the head of the list


return 
the number of patients with a matching priority


*/


int countPatients(ListNode *head, unsigned char priority)
{
// add code 
	int count = 0; // Initialize count
    ListNode *current = head; // Initialize current
    
    while (current != NULL) {
	    if (current->patient.priorityLevel == priority){
		    count++;
		    current = current->next;
		    }else current = current->next;
		}
    return count;
}






/************************************************************************/
/*

Purpose: store all the patients records in the file by printing out the information i.e., in ASCII readable format. 


input
filename - the name of the file to be used for storing the data
head - the head of the  list

Algorithm:
use the '$' character as a delimeter between the fields
For example:
Miya                 $Bronson                 $ 9700    $ 20  $ 2 $ Broken Bone 
*/

// Backup Functions
int createAsciiBackup(char *fileName, ListNode *head)

{
	// add code 

	// open the file

	// store each patient records in the file

	// close the file

    return(0);
}

/************************************************************************/
/*

Purpose: store all the patients records in the file in their binary format. 


input
filename - the name of the file to be used for storing the data
head - the head of the  list



*/

int createBinaryBackup(char *fileName, ListNode *head)
{
	// add code 

	// open the file

	// store each patient records in the file

	// close the file

    return(0);
}

////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

// BONUS SECTION



/************************************************************************/
/*

Purpose: removes all Patients with priority less than or equal to the given priority 
(remove all patients with priorityLevel <= priority).   


input
head - the head of the  list

Ouput
head - the head of the list where all patients with priorityLevel < priority are removed 

*/

int releasePatients(ListNode **head, unsigned char priority)

/* code */
{
	// add code 
	ListNode* curr = *head;

	if (*head == NULL || head == NULL){
	printf ("List is empty");
	return 1;
	}

	// remove all patients that head is pointing to and meet the criteria
	while(curr->next != NULL){
		if (curr-> patient.priorityLevel <= priority) {
		free(curr);
	} else{
	curr = curr-> next;}
	}

	// remove all other patients that meet the crieria
	


	return(0);

}

/************************************************************************/
/*
Purpose: prints all the patients' records in the list in reverse order using recursion

input
head - the head of the list
*/


void printListReverse(ListNode *head, void (*myPrint)(PatientInfo *patient))
{
	// add code 
	if(head == NULL){
		return;}
	printListReverse(head->next,myPrint);
    	myPrint(&head->patient);
 
}





/*****************************************************************************/

/************************************************************************/
/*
Purpose: Reverse the list such that the last node in the list becomes the first node and the first node in the list becomes the last node.  

Restrictions:
1.	This operation must be achieved using recursive calls
2.	No memory is to be allocated or released at any time during the execution of the function



input
head - the head of the list


Returns:
the head of the new list
*/

ListNode *reverse(ListNode *head){
	/* Add code */
	if(head == NULL){
		return NULL;}
	
	if(head->next == NULL){
		return head;
	}
	
	ListNode *reversed = reverse(head->next) ;
	head->next->next = head;
	head->next = NULL;
	
	return reversed;

}






