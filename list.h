#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string.h>
#include<string>
#include<stdio.h>
using namespace std;
struct Node {
    char word[40];  // слово
    int	 count;     // счетчик повторений
    Node* next;     // ссылка на следующий элемент
};
typedef Node* PNode;
PNode CreateNode(char NewWord[])
{
    PNode NewNode = (Node*)malloc(sizeof(Node));
    strcpy(NewNode->word, NewWord);
    NewNode->count = 1;
    NewNode->next = NULL;
    return NewNode;
}
void AddFirst(PNode& Head, PNode NewNode)
{
    NewNode->next = Head;
    Head = NewNode;
}
void AddAfter(PNode p, PNode NewNode)
{
    NewNode->next = p->next;
    p->next = NewNode;
}
void AddLast(PNode& Head, PNode NewNode)
{
    PNode q = Head;
    if (Head == NULL) {
        AddFirst(Head, NewNode);
        return;
    }
    while (q->next) q = q->next;
    AddAfter(q, NewNode);
}
void AddBefore(PNode p, PNode NewNode)
{
    Node temp;
    temp = *p; *p = *NewNode;
    *NewNode = temp;
    p->next = NewNode;
}
PNode Find(PNode Head, char NewWord[])
{
    PNode q = Head;
    while (q && strcmp(q->word, NewWord))
        q = q->next;
    return q;
}
PNode FindPlace(PNode Head, char NewWord[])
{
    PNode q = Head;
    while (q && strcmp(NewWord, q->word) > 0)
        q = q->next;
    return q;
}
void DeleteNode(PNode& Head, PNode p)
{
    PNode q = Head;
    if (Head == p)
        Head = p->next;
    else {
        while (q && q->next != p)
            q = q->next;
        if (q == NULL) return;
        q->next = p->next;
    }
    delete p;
}
int ListLength(PNode Head)
{
    PNode p = Head;
    int len = 0;
    while (p != NULL)
    {
        len++;
        p = p->next;
    }
    return len;
}
void PrintToFile(PNode Head)
{
    FILE* output = fopen("list.txt", "w+");
    fprintf(output, "%i\n", ListLength(Head));
    PNode p = Head;
    while (p != NULL)
    {
        fprintf(output, "%s %i\n", p->word, p->count);
        p = p->next;
    }
    fclose(output);
}
void ReadFromFile(PNode& Head)
{
    FILE* input = fopen("list.txt", "r");
    int n, cou;
    char word[40];
    fscanf(input, "%i", &n);
    PNode p = Head, newNode;
    for (int i = 0; i < n; i++)
    {
        fscanf(input, "%s %d", word, &cou);
        newNode = CreateNode(word);
        newNode->count = cou;
        if (p != NULL)
            AddAfter(p, newNode);
        else
            AddFirst(Head, newNode);
    }
    fclose(input);
}
