/*****************************************************************************

File        : moviedatabase.c

Date        : Sunday 30th October 2016

Description : Source file for implementation of a linked list and
              functions used for the coursework tasks

Author      : Catherine Ives-Keeler

******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "film.h"
#include "moviedatabase.h"

movieList *movieDatabase_newList() 
{
    movieList *newList = (movieList*)malloc(sizeof(movieList));
    
    newList->first = NULL;
    newList->last = NULL;
    newList->length = 0;
    
    return newList;
}

void movieDatabase_add(Film *film, movieList *list) 
{ //to add a new film to the end of the movie list
    Node *node = (Node*)malloc(sizeof(Node));
    
    if (node == NULL)
    {
        fprintf(stderr, "Error: Unable to allocate memory in film_add()\n");
        
        exit(EXIT_FAILURE);
    }
    
    node->theFilm = film;
    node->next = NULL;
    
    if (list->last == NULL)
    {
        list->first = list->last = node;
    }
    else
    {
        list->last = list->last->next = node; //adds to the end
    }
    
    list->length++; //adding a new film increments the length of the list
    
}

void moviedatabase_insert(Film *film, movieList *list)
{ //to insert a film at the start of the movie list
    Node *node = (Node*)malloc(sizeof(Node));
    
    if (node == NULL)
    {
        fprintf(stderr, "Error: Unable to allocate memory in film_insert()\n");
        
        exit(EXIT_FAILURE);
    }
    
    node->next = list->first;
    node->theFilm = film;
    
    if (list->first == NULL)
    {
        list->first = list->last = node;
    }
    else
    {
        list->first = node;
    }
    
    list->length++;
}

size_t movieDatabase_length(movieList *list)
{
    return list->length; //returns the length of the movie list
}

Film *movieDatabase_head(movieList *list)
{ //points to the first film in the movie list
    if (list->first == NULL)
    {
        fprintf(stderr,"Error: attempt to return the head of an empty list.\n");
        
        exit(EXIT_FAILURE);
    }
    
    Film *theFilm = list->first->theFilm; 
    
    return theFilm;
}

Film *movieDatabase_tail(movieList *list)
{ //points to the last film in the movie list
    if (list->first == NULL)
    {
        fprintf(stderr, "Error: attempt to return the tail of empty list\n");
        
        exit(EXIT_FAILURE);
    }
    
    Film *theFilm = list->last->theFilm;
    
    return theFilm;
}

void movieDatabase_sort(movieList *list,int(*comparison)(Film*, Film*))
{ //bubble sort
    if (list->first != list->last) //list >= 2 items
    {
        int sorted;
        
        do
        {
            sorted = 1;
            
            for (Node *node = list->first; node->next != NULL;
                                                node = node->next)
            { //compares one film to the next film
                if (comparison(node->theFilm, node->next->theFilm))
                {
                    Film *temp            = node->theFilm;
                    node->theFilm       = node->next->theFilm;
                    node->next->theFilm = temp;
                    sorted              = 0;
                }
            }
        }
        while (!sorted); 
    }
}

void movieDatabase_clear(movieList *list) //to free everything
{
    while (list->first != NULL)
    {
        Node* node = list->first;
        list->first = node->next;
        film_free(node->theFilm);
        free(node);
    }
    list->last = NULL;
    free(list);
}

void movieDatabase_clearWithoutFilms(movieList* list) 
{ //frees everything apart from the film structs
    while (list->first != NULL)
    {
        Node *node = list->first;
        list->first = node->next;
        free(node);
    }
    list->last = NULL;
    free(list);
}

void movieDatabase_freeNode(Node *node)
{ //frees the film node
    film_free(node->theFilm);
    free(node);
}

void movieDatabase_printFilms(const movieList *list)
{ //prints film from movieList
    for (Node *node = list->first; node != NULL; node = node->next)
    {
        film_print(node->theFilm);
    }
}

movieList *movieDatabase_getFilms(FILE *fp)
{
    size_t buffer = 256;
    
    char title[buffer];
    int releaseYear;
    char ageRating[buffer];
    enum ageEnum ageRatingnum;
    char genre[buffer];
    int lengthMins;
    double starRating;
    
    movieList *filmList = movieDatabase_newList();
    
    if (fp == NULL)
    {
        printf("Error: file not found.\n");
        
        exit(EXIT_FAILURE);
    }
    
    char line[buffer];
    //using sscanf to read though the format of the line in the file
    while(fgets(line, buffer, fp))
    {
        sscanf(line, "\"%[^\"]\",%i,\"%[^\"]\",\"%[^\"]\",%i,%lf\n", title,
                &releaseYear, ageRating, genre, &lengthMins, &starRating);
        
        ageRatingnum = film_getEnumFromString(ageRating);
        
        Film *afilm = film_new(title, releaseYear, ageRatingnum, genre, 
                                                        lengthMins, starRating);
        
        movieDatabase_add(afilm, filmList);
    }
    
    return filmList;
}

Film *movieDatabase_getFilmPosition(size_t position, int(*comparison)(Film*,
                                        Film*), movieList* list, char* genre)
{
    movieList *genreList = movieDatabase_newList();
    //makes second list of films with specific genres
    for (Node *node = list->first; node != NULL; node = node->next)
    {
        if (strstr(node->theFilm->genre, genre))
        {
            movieDatabase_add(node->theFilm, genreList);
        }
    }
    movieDatabase_sort(genreList, comparison);
    //sorts the genre list before finding the film
    int i = 1;
    Node *node = genreList->first;
    
    while (i < position && node != NULL)
    {
        node = node->next;
        i++;
    }
    Film *found = node->theFilm;
    //clears the new genre list
    movieDatabase_clearWithoutFilms(genreList);
    
    return found;
}

Film *movieDatabase_getTopRated(int(*comparison)(Film*,Film*), movieList *list)
{ //using comparison to find the shortest title and the highest rated film
    Film *found = list->first->theFilm;
    //just compares the films, does not sort them first
    for (Node *node = list->first->next; node != NULL; node = node->next)
    {
        if(comparison(found, node->theFilm))
        {
            found = node->theFilm;
        }
    }
    return found;
}

void movieDatabase_RemoveFilm(movieList *list, enum ageEnum ageRate)
{
    Node *previous;
    Node *current = list->first;
    
    while (current != NULL)
    {
        if (current->theFilm->ageRating != ageRate)
        {
            previous = current;
            current = current->next;
        }
        else 
        { //if ratings match check that its the first node
            if (current == list->first)
            {
                list->first = current->next;
                //if it matches free the current node
                movieDatabase_freeNode(current); 
                current = list->first;
            }
            previous->next = current->next;
            movieDatabase_freeNode(current);
            current = previous->next;
            list->length --; //if node is freed then it reduces the length
        }
    }
}