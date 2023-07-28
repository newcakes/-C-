#include"contact.h"
void Check_Capacity(struct Contact* ptr);
void LandContact(struct Contact* ps)
{
	FILE* pfread = fopen("contact.dat", "rb");
	if (pfread==NULL)
	{
		printf("LandContact::%s\n", strerror(errno));
	}
	struct ContactInfo temp;
	while (fread(&temp, sizeof(struct ContactInfo), 1, pfread))
	{
		Check_Capacity(ps);
		ps->date[ps->size] = temp;
		ps->size++;
	}
}
void InitContact(struct Contact* ps)
{
	ps->date = (struct ContactInfo*)calloc(INIT, sizeof(struct ContactInfo));
	ps->size = 0;
	ps->capacity = INIT;
	LandContact(ps);
}
void Check_Capacity(struct Contact* ptr)
{
	if (ptr->size==ptr->capacity)
	{
		struct ContactInfo* temp = (struct ContactInfo*)realloc(ptr->date, (ptr->capacity + ADD) * sizeof(struct ContactInfo));
		if (temp==NULL)
		{
			return;
		}
		else
		{	
			ptr->date=temp;
			ptr->capacity += ADD;
			printf("增容成功！\n");
		}		
	}
}
void AddContact(struct Contact* ps)
{
	Check_Capacity(ps);
	printf("请输入姓名：");
	scanf("%s", ps->date[ps->size].name);
	printf("请输入年龄：");
	scanf("%d", &ps->date[ps->size].age);
	printf("请输入性别：");
	scanf("%s", ps->date[ps->size].sex);
	printf("请输入电话：");
	scanf("%s", ps->date[ps->size].tele);
	printf("请输入地址：");
	scanf("%s", ps->date[ps->size].addr);
	ps->size++;
	printf("添加成功！\n");
}
void ShowContact(struct Contact* ps)
{
	if (ps->size==0)
	{
		printf("通讯录为空！\n");
	}
	else
	{
		printf("%-20s\t%-4s\t%-20s\t%-15s\t%-25s\n", "姓名：", "年龄：", "性别：", "电话：", "地址");
		for (int i = 0; i < ps->size; i++)
		{
			printf("%-20s\t%-4d\t%-20s\t%-15s\t%-25s\n", ps->date[i].name,
				ps->date[i].age,
				ps->date[i].sex,
				ps->date[i].tele,
				ps->date[i].addr);
		}
	}	
}
static int FindByName( const struct Contact* ps)
{
	char retname[MAX_NAME] = { 0 };
	printf("请输入相应的的姓名：");
	scanf("%s", retname);
	for (int i = 0; i < ps->size; i++)
	{
		if (strcmp(ps->date[i].name, retname) == 0)
		{
			return i;
		}
	}	
	return -1;
}
void DelContact(struct Contact* ps)
{	
	int pos = FindByName(ps);
	if (pos == -1)
	{
		printf("查找不到该联系人！请核对后再来输入\n");
	}
	else
	{
		for (int j = pos; j < ps->size - 1; j++)
		{
			ps->date[j] = ps->date[j + 1];			
		}
		ps->size--;
		printf("删除成功！\n");
	}	
}
void SearchContact(const struct Contact* ps)
{
	int pos = FindByName(ps);
	if (pos == -1)
	{
		printf("查找不到该联系人！请核对后再来输入\n");
	}
	else
	{
		printf("%-20s\t%-4s\t%-20s\t%-15s\t%-25s\n", "姓名：", "年龄：", "性别：", "电话：", "地址");
		printf("%-20s\t%-4d\t%-20s\t%-15s\t%-25s\n", 
			ps->date[pos].name,
			ps->date[pos].age,
			ps->date[pos].sex,
			ps->date[pos].tele,
			ps->date[pos].addr);
	}
}
void ModifyContact(struct Contact* ps)
{
	int pos = FindByName(ps);
	if (pos == -1)
	{
		printf("查找不到该联系人！请核对后再来输入\n");
	}
	else
	{
		printf("请输入姓名：");
		scanf("%s", ps->date[pos].name);
		printf("请输入年龄：");
		scanf("%d", &ps->date[pos].age);
		printf("请输入性别：");
		scanf("%s", ps->date[pos].sex);
		printf("请输入电话：");
		scanf("%s", ps->date[pos].tele);
		printf("请输入地址：");
		scanf("%s", ps->date[pos].addr);
		printf("修改成功！");
	}
}
static void swap(char* buf1, char* buf2, int width)
{
	for (int i = 0; i < width; i++)
	{
		char temp = *buf1;
		*buf1 = *buf2;
		*buf2 = temp;
		buf1++;
		buf2++;
	}
}
static int cmp(void* e1, void* e2)
{
	return strcmp((char*)e1, (char*)e2);
}
static void bubblesort(void* base, int sz, int width, int (*cmp)(void* e1, void* e2))
{
	for (int i = 0; i < sz - 1; i++)
	{
		for (int j = 0; j < sz - 1 - i; j++)
		{
			if (cmp((char*)base + j * width, (char*)base + (j + 1) * width) > 0)
			{
				swap((char*)base + j * width, (char*)base + (j + 1) * width, width);
			}
		}
	}
}
void SortContact(struct Contact* ps)
{	
	bubblesort(ps->date, ps->size, sizeof(ps->date[0]), cmp);
	printf("排序完成！\n");
}
void DextroyContact(struct Contact* ps)
{
	free(ps->date);
	ps->date = NULL;
}
void SaveContact(struct Contact* ps)
{
	FILE* pfwrite = fopen("contact.dat", "wb");
	if (pfwrite==NULL)
	{
		printf("SaveContact::%s\n", strerror(errno));
		return;
	}
	for (int i = 0; i < ps->size; i++)
	{
		fwrite(&(ps->date[i]), sizeof(struct ContactInfo), 1, pfwrite);
	}
	fclose(pfwrite);
	pfwrite = NULL;
}