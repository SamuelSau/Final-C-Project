/*
Samuel Sau
This program allows users to enter t-shirt information into a database
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tshirt.h"
#include "readline.c"

void help() {
	printf("List of operation codes:\n");
	printf("\t'a' for adding a t-shirt to the inventory;\n");
	printf("\t'h' for help;\n");
	printf("\t'o' for searching t-shirts by organization;\n");
	printf("\t's' for searching t-shirts by size;\n");
	printf("\t'p' for printing the inventory;\n");
	printf("\t'q' for quit.\n");
}

struct tshirt * add_to_inventory(struct tshirt *inventory) {

	 struct tshirt *new_node;
	 struct tshirt *p = inventory; //temporary pointer that will compare values

     //initialization of variables to compare with inventory
     char org_name[ORG_NAME_LEN+1];
     char size[SIZE_LEN+1];

     //user input
	 printf("Enter student organization name: ");
	 read_line(org_name, ORG_NAME_LEN);

	 printf("Enter t-shirt size: ");
	 read_line(size, SIZE_LEN);

    while(p != NULL)
    {
        if(strcmp(p->org_name, org_name)==0 && strcmp(p->size, size)==0) //comparing if inventory found or not
        {
            printf("T-shirt size already exist in this student organization.");
            return inventory;
        }
        p = p->next; //iterate through inventory
    }
    //allocating memory to new_node
    new_node = malloc(sizeof(struct tshirt));

    new_node->next = NULL;

    if(new_node == NULL) //check to see if heap exhausted or malloc cannot generate
    {
        printf("Malloc has failed in add_to_inventory.");
        return 0;
    }

        //Copying values into new_node
        strcpy(new_node->org_name, org_name);
        strcpy(new_node->size, size);

        //User input
        printf("Enter price of t-shirt: ");
        scanf("%lf", &new_node->price);

        printf("Enter quantity: ");
        scanf("%d", &new_node->quantity);

        if(inventory==NULL) //if inventory is empty
        {
            inventory = new_node; //assigns new_node as the head of inventory
        }
        else if(inventory->next==NULL)
        //logic to add linked list if we only have one starting node
        {
            if(strcmp(new_node->org_name, org_name) < 0)
            {
                new_node->next = inventory;
                inventory = new_node;
            }

            else if(strcmp(new_node->org_name, org_name)> 0)
            {
                inventory->next = new_node;
            }

            else if(strcmp(new_node->org_name, org_name)==0)
            {
                if(strcmp(new_node->size, size)<0)
                {
                    new_node->next = inventory;
                    inventory = new_node;
                }
                else
                {
                    inventory->next = new_node;
                }
            }
            return inventory;
        }

        prev = p = inventory; //important to declare the pointers as equal so that we can iterate through after each update for inventory.

        //logic for if inventory contains more than one node

        while(strcmp(new_node->org_name, p->org_name) > 0 && p->next !=NULL) //iterate through entire inventory and stop before we hit null
        {
            prev = p;
            p=p->next;
        }

        if(strcmp(new_node->org_name, p->org_name) > 0)
        {
            new_node->next = p->next;
            p->next = new_node;
        }

        else if(strcmp(new_node->org_name, p->org_name)<0 && p==inventory) //if p is pointing to inventory, which means it can be pointing to null
        {
            new_node->next = p;
            inventory = new_node;
        }

        else if(strcmp(new_node->org_name, p->org_name)<0)
        {
            new_node->next = p;
            prev->next = new_node;
        }

        else if(strcmp(new_node->org_name, p->org_name)==0) //if our org names matches, then we check conditions for the sizes and order them
        {
            while(strcmp(new_node->size, p->size)> 0 && strcmp(new_node->org_name, p->org_name)==0 && p->next!=NULL)
            {
                prev = p;
                p=p->next;
            }

            if(strcmp(new_node->size, p->size)>0)
            {
                p->next = new_node;
            }

            else
            {
                prev->next = new_node;
                new_node->next = p;
            }
        }

        return inventory; //returns back to list

    return 0;
}

void search_by_organization(struct tshirt *inventory) {

	char org_name[ORG_NAME_LEN+1];

	if(!inventory) //checks if its empty or there's no match with name
    {
        printf("No tshirt found!\n");
    }
    else
    {
        printf("Enter name of organization: ");
        read_line(org_name,ORG_NAME_LEN);

        struct tshirt *p = inventory;

        for(p=inventory; p!=NULL; p=p->next)
        {
            if(strcmp(p->org_name, org_name)==0) //checks if there's organization name match with user input. If so, display all relevant content
            {
                printf("|----------------------------------------------------|-----|-------|------|\n");
                printf("| Student organization                               | Sz. | Price | Qty. |\n");
                printf("|----------------------------------------------------|-----|-------|------|\n");
                printf("| %-50s | %-3s | %5.2f | %4d |\n", p->org_name, p->size, p->price, p->quantity);
                printf("|----------------------------------------------------|-----|-------|------|\n");
            }
        }
    }
}

void search_by_size(struct tshirt *inventory) {

	char size[SIZE_LEN+1];

	if(!inventory)
    {
        printf("No t-shirt found!\n");
    }
    else
    {
        printf("Enter size: ");
        read_line(size, SIZE_LEN);

        struct tshirt *p = inventory;

        for(p=inventory; p!=NULL; p=p->next)
        {
            if(strcmp(p->size, size)==0)
            {
                printf("|----------------------------------------------------|-----|-------|------|\n");
                printf("| Student organization                               | Sz. | Price | Qty. |\n");
                printf("|----------------------------------------------------|-----|-------|------|\n");
                printf("| %-50s | %-3s | %5.2f | %4d |\n", p->org_name, p->size, p->price, p->quantity);
                printf("|----------------------------------------------------|-----|-------|------|\n");
            }
        }
    }
}

void print_inventory(struct tshirt *inventory) {

	struct tshirt *p;

	for(p=inventory; p!=NULL; p=p->next)
    {
        printf("|----------------------------------------------------|-----|-------|------|\n");
        printf("| Student organization                               | Sz. | Price | Qty. |\n");
        printf("|----------------------------------------------------|-----|-------|------|\n");
        printf("| %-50s | %-3s | %5.2f | %4d |\n", p->org_name, p->size, p->price, p->quantity);
        printf("|----------------------------------------------------|-----|-------|------|\n");
	}
}

void clear_inventory(struct tshirt *inventory) {

	struct tshirt *p = inventory;
	struct tshirt *q = p;

	while(p != NULL) //iterate through inventory and free each one
    {
        p = p->next;
        free(q); //clears every pointer
        q = p;
    }
}


