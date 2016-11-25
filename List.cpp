// List.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <iostream>
using namespace std;

struct Film 
{
	char name[30]; 
	char genre[15]; 
	char director[20]; 
	int rating; 
};

struct List 
{
	Film film; 
	List *pNext; 
};


void addFirst(List *& pF, 
	List* p) 
{
	p->pNext = pF;
	pF = p;
}
List * delFirst(List *&pF) 
{
	if (pF == 0) return 0;
	List *p = pF;
	pF = pF->pNext;
	return p;

}

bool add(List *&pF, List * pZad, List *p)
{
	
	if (pZad == pF) 
	{
		p->pNext = pF;
		pF = p;
		return true;
	}

	List *pPred = pF; 
	while (pPred->pNext != pZad && pPred->pNext)
		pPred = pPred->pNext;
	if (pPred->pNext == 0) return false; 
	p->pNext = pZad;
	pPred->pNext = p;
	return true;
}

List * del(List*& pF, List *p) 
{
	if (pF == 0) return 0;
	if (pF == p) 
	{
		pF = pF->pNext;
		return p;
	}
	else
	{
		List *pPred = pF; 
		while (pPred->pNext != p && pPred->pNext)
			pPred = pPred->pNext;
		if (pPred->pNext == 0) return 0; 
		pPred->pNext = p->pNext;
		return p;
	}
	while (delFirst(pF)); 
}

int main(int argc, char* argv[])
{
	List *pF = 0;
	List *p;
	
	char vv; 
	do
	{
		p = (List *)malloc(sizeof(List)); 
		
		cout << "Name: ";
		cin.get();
		fflush(stdin); 
		cin.getline(p->film.name, 29);
		cout << endl;
		cout << "Genre: ";
		fflush(stdin); 
		cin.getline(p->film.genre, 14);
		cout << endl;
		cout << "Director: ";
		fflush(stdin); 
		cin.getline(p->film.director, 19);
		cout << endl;
		cout << "Rating: ";
		fflush(stdin); 
        cin >> p->film.rating;
		cout << endl;
		addFirst(pF, p); 
		cout << "For continue press Q or q else any key! " << endl;
		vv = _getche(); 
	} while (vv == 'Q' || vv == 'q');
	cout << endl;
	
	for (List *pi = pF; pi; pi = pi->pNext) 
		cout << pi->film.name <<" " << pi->film.genre << " " <<
		pi->film.director << " " << pi->film.rating << endl;
	cout << endl;
	
	for (List *pi = pF; pi->pNext;)
	{
		
		int min = pi->film.rating;
		List *pmin = pi;
		for (List *pj = pi->pNext; pj; pj = pj->pNext)
			if (pj->film.rating<min)
			{
				min = pj->film.rating;
				pmin = pj;
			}
		if (pi != pmin) 
		{
			del(pF, pmin);
			add(pF, pi, pmin);
		}
		else pi = pi->pNext;
	}
	
	cout << "Srting:" << endl;
	for (List *pi = pF; pi; pi = pi->pNext) 
		cout <<pi->film.name << " " << pi->film.genre << " " <<
			pi->film.director << " " << pi->film.rating << endl;
	cout << "For exit press any key ";
	system("pause"); 
	return 0;
}