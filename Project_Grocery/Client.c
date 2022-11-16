#include "Client.h"

/*function to alocate a client*/
struct client* createClient() 
{
	struct client* temp = (struct client*)calloc(1, sizeof(struct client));
	if (temp == NULL)
	{
		printf("allocation failed!");
	}
	return temp;
}

/*Function to free memory from specific client*/
void freeClient(struct client* client)
{
	free(client->firstName);
	free(client->lastName);
	free(client->ID);
	free(client->phone);
	free(client);

	client = NULL;                    // The pointer of client refering now to a NULL.
}

/*Function to free memory from all the list*/
void freeList(struct list* List)
{
	struct client* client;

	while (client = List->head)
	{
		List->head = List->head->next;
		freeClient(client);
	}
	free(List);
	List = NULL;
}