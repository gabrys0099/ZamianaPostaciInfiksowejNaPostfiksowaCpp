//============================================================================
//                  Algorytmy i Struktury Danych
// Zadanie 4.1
// Zamiana postaci infiksowej funkcji na posta� postfiksowa 
//
//  WCY21IY1S1  Go��biowski Gabriel
//============================================================================
#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <fstream>

using namespace std;

//Zdefiniowanie struktury stosu
typedef struct stos
 {
 	char znak;
 	int priority;
 	struct stos *next;   
 	struct stos *prev;
 }node;
 
//Funkcja dodaj�ca element Na koniec stosu przypisuj�c mu priorytet

node *DodajOgon(node *head , int priority, char znak)
{
	node *newNode =(node *)malloc(sizeof(node));
	newNode->znak=znak;
	newNode->priority=priority;
	newNode->next=NULL;
	newNode->prev=NULL;
	if(head==NULL)
	{
		head=newNode;
	}
	else
	{
		node *tmp=head;
		while(tmp->next !=NULL)
		{
			tmp=tmp->next;
		}
		tmp->next=newNode;
		newNode->prev=tmp;
	}
	return head;
}

//Funkcja usuwaj�ca z ogona elementy z wi�kszym priorytetem ni� ten przs�any w argumencie funkcji

node *UsunOgon(node *head, int priority)
{
	if(head!=NULL)
	{
		while(head!=NULL)
		{
		node *tmp1=head, *tmp2=head;
		while(tmp1->next !=NULL)
		{
			tmp2=tmp1;
			tmp1=tmp1->next;
		}
		if(tmp1->priority>=priority)
		{
			if(tmp1==head)
			{	
				cout<<tmp1->znak;
				free(head);
				head=NULL;
			}
			else
			{
				tmp2->next=NULL;
				cout<<tmp1->znak;
				free(tmp1);
			}
		}
		else
		{
			return head;
		}
		}
	}
	return head;;
}

//Funkcja wypisuj�ca i usuwaj�ca ze stosu elementy a� do odczytania znaku (

node * znakNawiasu(node *head)
{
	node *tmp1=head, *tmp2=head;
	while(tmp1->next!=NULL)
	{
		tmp2=tmp1;
		tmp1=tmp1->next;
	}
	while(tmp1->znak!='(')//usuni�cie i wypisanie wszystkiego a� nie odczytany zostanie nawias
	{
		node *tmp2=tmp1;
		if(tmp1==head)
		{
			cout<<head->znak;
			free(head);
			head=NULL;
			return head;
		}
		else
		{
			cout<<tmp1->znak;
			tmp1=tmp1->prev;
			tmp1->next=NULL;
			free(tmp2);
		}
	}
	
	//usuni�cie nawiasu
	node *tmp3=tmp1;
	tmp3=tmp3->prev;
	if(tmp3==head)
	{
		tmp3->next=NULL;
		free(tmp1);
	}	
	else if(tmp1==head)
	{
		free(head);
		head=NULL;
	}
	else
	{
		tmp3->next=NULL;
		free(tmp1);
	}
	
	return head;
}

//Zdj�cie ca�ego stosu od ko�ca na koniec

node *ZdjecieStosu(node *head)
{
	if(head!=NULL)
	{
		
		node *tmp1=head, *tmp2=head;
		
		while(tmp1->next!=NULL)
		{
			tmp2=tmp1;
			tmp1=tmp1->next;
		}
		
		if(tmp1==head)
		{
			if(tmp1->znak=='(')
			{
				free(head);
				head=NULL;
			}
			else
			{
				cout<<head->znak;
				free(head);
				head=NULL;
			}
		}
		else
		{
			if(tmp1->znak=='(')
			{
				tmp2->next=NULL;
				free(tmp1);
			}
			else
			{
				tmp2->next=NULL;
				cout<<tmp1->znak;
				free(tmp1);
			}
		}
		return head;
	}
}

int main()
{
	node *head=NULL;
	string tab;
	int a;
	cout<<"podaj 1 jezeli chcesz wczytac wyrazenie z pliku lub 2 jezeli z klawiatury: ";
	cin>>a;
	switch(a)
 	{
 		case 1:
 			{
 			ifstream plik("we.txt");
 			while(!plik.eof())
 			{
			 plik>>tab;	
			}
			cout<<"podane wyrazenie: "<<tab<<endl;
			plik.close();
			break;
			}
		
		case 2:
			cout<<"Podaj ciag znakow w notacji infiksowej(bez spacji): ";
			cin>>tab;
				break;
 			
	}
    cout<<"postac postfiksowa: ";
    int j=0;
    for(int i=0;i<tab.length();i++)
    {
    	if(tab[i]=='*' || tab[i]=='/' || tab[i]=='%')
    	{
    		head=DodajOgon(head, 2, tab[i]);//wywo�anie funkcji dodania elementu na stos
		}
		else if(tab[i]=='+' || tab[i]=='-')
		{
			head=UsunOgon(head, 1);//Funkcja usuwaj�ca elementy ze stosu o priorytecie wiu�kszym ni� 1
			head=DodajOgon(head, 1, tab[i]);//Funkcja dodaj�ca element na koniec stosu
		}
		else if(tab[i]=='(')
		{
			head=DodajOgon(head, 0, tab[i]);//Funkcja dodaj�ca element na koniec stosu
		}
		else if(tab[i]==')' )
		{
			head=znakNawiasu(head);//wywo�anie funkcji wypisania i usuni�cia wszystkich element�w do nawiasu otwieraj�cego
			
		}
		else if(tab[i]=='=')//zako��zenie odczytu r�wnania
		{
			break;
		}
		else
		{
			cout<<tab[i];
		}
	}
	
	while(head!=NULL)
	{
		head=ZdjecieStosu(head);
		
	}
	
	return 0;
}
