#include <stdio.h>
#include <stdlib.h>

#define HASH_TABLE_SIZE 10000
int hashArray[HASH_TABLE_SIZE];

struct node {
    int data;
    struct node *next;
};

struct node *chain[HASH_TABLE_SIZE];

void init()
{
    for(int i=0; i<HASH_TABLE_SIZE; i++)
        chain[i] = NULL;
}

int hashCode(int value)
{
   return value % HASH_TABLE_SIZE;
}

int search(int value)
{
	int hashIndex = hashCode(value);
    struct node *temp = chain[hashIndex];
    while(temp)
    {
        if(temp->data == value)
            return 1;			//search found
        temp = temp->next;
    }
    return 0;					//no search found
}

int insert(int value)
{
	int cnt=0;

    //create a newnode with value
    struct node *newNode = malloc(sizeof(struct node));
    newNode->data = value;
    newNode->next = NULL;

	int hashIndex = hashCode(value);

    //if chain[hashIndex] is empty then insert. No Collision
    if(chain[hashIndex] == NULL) {
        chain[hashIndex] = newNode;
    }
    else	// Collision
    {
        //add the node at the end of chain[key].
        struct node *temp = chain[hashIndex];
        while(temp->next)
        {
            temp = temp->next;
        }
        temp->next = newNode;
		cnt++;
    }
    return cnt;
}


int main(int argc, char *argv[]) {

  int input_data, search_cnt=0, collision_cnt=0;
  char in_command[20];
  int n;

  FILE* in_file = fopen(argv[1], "r");				// read only mode
  //FILE* in_file  = fopen("input_file.dat", "r"); 		// Debug mode only

  if (in_file == NULL)  {			//Error reading File
  	  fclose(in_file);
	  return 1;
  }

  while ( fscanf(in_file, "%s %d", in_command, &input_data) != EOF ) 
  //while (!feof(in_file))
  {
    //fscanf(in_file, "%s %d", in_command, &input_data);
    switch(in_command[0])     //checking 1st char of the in_command
    {
        case 'i':
                n = insert(input_data);	// storing input_number
    			if(n!=0) {
					collision_cnt++;
   				}
   				break;
       	case 's':
   				n = search(input_data);
    			if(n!=0) {
					search_cnt++;
   				}
   				break;
        default:
            	break;
    }
  }

  //printf("Collision: %d\n", collision_cnt);
  printf("%d\n", collision_cnt);
  //printf("Successful Searches: %d\n", search_cnt);
  printf("%d\n", search_cnt);

  fclose(in_file);
  return 0;
}