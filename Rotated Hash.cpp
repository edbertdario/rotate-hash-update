#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define TABLE_SIZE 10

struct node
{
	char data[100];
	struct node *next;
}*hashTable[26], *curr;

// First Character
int hashFuction(char data[])
{
	int hashKey = -1;
	char firstChar;
	
	// Ambil karakter pertama
	firstChar = data[0];
	// A -> a (97) - 97 = 0;
	hashKey = tolower(firstChar) - 97;
	return hashKey;
}

// METHOD DIVISION
int divHash(int key)
{
	return key % TABLE_SIZE;
}

// METHOD FOLDING
int foldingHash(int key)
{
	int part1 = key / 1000; // Ambil 4 digit pertama
	int part2 = key % 1000; // Ambil 4 digit terakhir
	
	return (part1 + part2) % TABLE_SIZE;
}

int rotatingHash(int key)
{
	char keyStr[10];
	sprintf(keyStr, "%d", key);
	int len = strlen(keyStr);
	if (len > 1)
	{
		
		char rotatedStr[10];
		strcpy(rotatedStr, keyStr + 1);
		rotatedStr[len - 1] = keyStr[0];
		rotatedStr[len] = '\0';
		return atoi(rotatedStr) % TABLE_SIZE;
	}
	return key;
}


int rehash(int key)
{
	return (key + 1) % TABLE_SIZE;
}

void viewHashTable()
{
	// Akses semua index
	for(int i = 0; i < 26; i++)
	{
		// Cek index null atau tidak
		if(hashTable[i] != NULL)
		{
			printf("Hash Table Index [%d] :\n", i);
			curr = hashTable[i];
			while(curr != NULL)
			{
				printf("%s ", curr->data);
				curr = curr->next;
			}
			printf("\n");
		}
	}
}

void pushBack(int hashKey, char data[])
{
	struct node *newNode = (struct node*)malloc(sizeof(struct node));
	strcpy(newNode->data, data);
	newNode->next = NULL;
	
	// Jika index kosong
	while (hashTable[hashKey] != NULL) {
		hashKey = rehash(hashKey);
	}
	
	hashTable[hashKey] = newNode;
}

int main()
{
	char data[100];
	int originalHash, rotatedHash;
	
	do
	{
		printf("Input Data: ");
		scanf("%s", data); getchar();
		
		if(strcmpi(data, "exit") == 0) break;
		
		originalHash = hashFuction(data);
		rotatedHash = rotatingHash(originalHash);
		
		printf("Hash awal : %d, Rotated Hash: %d\n", originalHash, rotatedHash);
		pushBack(rotatedHash, data);
		
	} while(1);
	
	viewHashTable();
	getchar();
	
	return 0;
}

