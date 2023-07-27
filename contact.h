#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//#define MAX 1000
#define INIT 3
#define ADD 2
#define MAX_NAME 20
#define MAX_SEX 20
#define MAX_TELE 15
#define MAX_ADDR 25
enum option
{
	Exit,
	add,
	del,
	search,
	modify,
	show,
	sort
};
struct ContactInfo
{
	char name[MAX_NAME];
	int age;
	char sex[MAX_SEX];
	char tele[MAX_TELE];
	char addr[MAX_ADDR];
};
struct Contact
{
	int size;
	int capacity;
	struct ContactInfo *date;
};
void InitContact(struct Contact* ps);
void AddContact(struct Contact* ps);
void ShowContact(struct Contact* ps);
void DelContact(struct Contact* ps);
void SearchContact(struct Contact* ps);
void ModifyContact(struct Contact* ps);
void SortContact(struct Contact* ps);
void DextroyContact(struct Contact* ps);