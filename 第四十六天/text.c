#include"contact.h"
void Pause()
{
	printf("����󷵻���ҳ��\n");
	Sleep(3000);
	system("cls");
}
void menu()
{
	printf("**************************\n");
	printf("***1.add      2.del    ***\n");
	printf("***3.search   4.modify ***\n");
	printf("***5.show     6.sort  ***\n");
	printf("***0.exit              ***\n");
	printf("**************************\n");
}
int main()
{
	int  input = 0;	
	struct Contact con = {0};
	InitContact(&con);	
	do
	{	
		menu();
		printf("��ѡ�񡪡�> ");
		scanf("%d", &input);
		switch (input)
		{
		case add:
			AddContact(&con);
			Pause();
			break;
		case del:			
			DelContact(&con);
			Pause();
			break;
		case search:
			SearchContact(&con);
			Pause();
			break;
		case modify:
			ModifyContact(&con);
			Pause();
			break;
		case show:
			ShowContact(&con);
			break;
		case sort:
			SortContact(&con);
			Pause();
			break;
		case save:
			SaveContact(&con);
			Pause();
			break;
		case Exit:
			SaveContact(&con);
			DextroyContact(&con);
			printf("�˳��ɹ���");
			break;
		default:
			printf("�����������������룡");
			break;
		}				
	} while (input);
	return 0;
}