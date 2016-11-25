// List.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <iostream>
using namespace std;

struct Film // Сотрудник
{
	char name[30]; // ФИО
	char genre[15]; // Дата рождения
	char director[20]; // Должность
	int rating; // Оклад
};

struct List // Список
{
	Film film; // Инф поле
	List *pNext; // Указательна следующий элемент
};

// Функция добавления элемента в начало списка
void addFirst(List *& pF, // Указатель на начало списка
	List* p) // Указатель на добавляемый элемент
{
	p->pNext = pF;
	pF = p;
}
// Удаление элемента из начала списка
List * delFirst(List *&pF) // Функция возвращает указатель на удаляемый элемент
{
	if (pF == 0) return 0;
	List *p = pF;
	pF = pF->pNext;
	return p;

}
// Добавление элемента перед заданным
bool add(List *&pF, List * pZad, List *p)
{
	// Функция возвращает true при нормальном завершении и false в случае ошибки
	if (pZad == pF) // Элемент будет первым
	{
		p->pNext = pF;
		pF = p;
		return true;
	}

	List *pPred = pF; // Указатель на предыдущий элемент перед pZad
	while (pPred->pNext != pZad && pPred->pNext)
		pPred = pPred->pNext;
	if (pPred->pNext == 0) return false; // Элемента pZad нет в списке
	p->pNext = pZad;
	pPred->pNext = p;
	return true;
}
// Удаление любого элемента p из списка
List * del(List*& pF, List *p) // Функция возвращает указатель на удаленный элемент
{
	if (pF == 0) return 0;
	if (pF == p) // Удаляем первый элемент
	{
		pF = pF->pNext;
		return p;
	}
	else
	{
		List *pPred = pF; // Указатель на предыдущий элемент перед p
		while (pPred->pNext != p && pPred->pNext)
			pPred = pPred->pNext;
		if (pPred->pNext == 0) return 0; // Элемента p нет в списке
		pPred->pNext = p->pNext;
		return p;
	}
	while (delFirst(pF)); // Очистка списка
}

int main(int argc, char* argv[])
{
	List *pF = 0; // Список пуст
	List *p;
	// Ввод списка
	char vv; // Переменная для ввода условия продолжения ввода
	do
	{
		p = (List *)malloc(sizeof(List)); // Выделяем память под элемент
		/*cin.get();*/
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
		addFirst(pF, p); // Добавляем элемент в начало списка
		cout << "For continue press Q or q else any key! " << endl;
		vv = _getche(); // Чтение кода клавиши с печатью символа
	} while (vv == 'Q' || vv == 'q');
	cout << endl;
	// Вывод спика
	for (List *pi = pF; pi; pi = pi->pNext) // Просмотр списка
		cout << pi->film.name <<" " << pi->film.genre << " " <<
		pi->film.director << " " << pi->film.rating << endl;
	cout << endl;
	// Сортировка списка
	for (List *pi = pF; pi->pNext;)
	{
		// Ищем минимальный элемент в списке
		int min = pi->film.rating;
		List *pmin = pi;
		for (List *pj = pi->pNext; pj; pj = pj->pNext)
			if (pj->film.rating<min)
			{
				min = pj->film.rating;
				pmin = pj;
			}
		if (pi != pmin) // Минимальный элемент делаем первым, он будет перед pi
		{
			del(pF, pmin);
			add(pF, pi, pmin);
		}
		else pi = pi->pNext;
	}
	// Печать списка после сортировки
	cout << "Srting:" << endl;
	for (List *pi = pF; pi; pi = pi->pNext) // Просмотр списка
		cout <<pi->film.name << " " << pi->film.genre << " " <<
			pi->film.director << " " << pi->film.rating << endl;
	cout << "For exit press any key ";
	system("pause"); // Останавливаем программу, ждем нажатия любой клавиши
	return 0;
}