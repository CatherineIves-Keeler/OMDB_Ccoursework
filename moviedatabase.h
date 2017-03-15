/*****************************************************************************

File        : moviedatabase.h

Date        : Sunday 30th October 2016

Description : Header file for implementation of a linked list and 
              functions used for the coursework tasks

Author      : Catherine Ives-Keeler

******************************************************************************/

#ifndef MOVIEDATABASE_H
#define MOVIEDATABASE_H

typedef struct Node //defining the linked list node
{
    Film *theFilm;
    struct Node *next;
    
}Node;

typedef struct movieList //struct for the list of films
{ 
    Node *first;
    Node *last;
    size_t length; 
    
}movieList;

/*****************************************************************************

Procedure   : movieDatabase_newList

Parameters  : none

Returns     : newList* - pointer to newly created list
 
Description : Creates a new list using the movieList struct, and calling
              malloc for dynamically assigned memory so the list can be freed 
              later on

 *****************************************************************************/

movieList *movieDatabase_newList();

/*****************************************************************************

Procedure   : film_add

Parameters  : Film *film
              movieList *list 

Returns     : void
 
Description : Calling malloc for dynamic memory for the node so it can be freed
              later on, adds the film to the end of the list and increments     
              the length

 *****************************************************************************/

void movieDatabase_add(Film *film, movieList *list);

/*****************************************************************************

Procedure   : film_insert

Parameters  : Film *film
              movieList *list

Returns     : void
 
Description : Calling malloc for dynamic memory for the node so it can be freed
              later on, adds the film to the start of the list and increments     
              the length

 *****************************************************************************/

void movieDatabase_insert(Film *film, movieList *list);

/*****************************************************************************

Procedure   : movieDatabase_length

Parameters  : movieList *list

Returns     : size_t - number of films in the list
 
Description : Determines the number of items currently stored in the
              linked list

 *****************************************************************************/

size_t movieDatabase_length(movieList *list);

/*****************************************************************************

Procedure   : movieDatabase_head

Parameters  : movieList *list

Returns     : theFilm - the first film in the list theFilm
 
Description : Points to the head of the list, pointing to theFilm which is      
              is the first in the list movieList

 *****************************************************************************/

Film *movieDatabase_head(movieList *list);

/*****************************************************************************

Procedure   : movieDatabase_tail

Parameters  : movieList *list

Returns     : theFilm - the last film in the list theFilm
 
Description : Points to the tail of the list, pointing to theFilm which is
              the last film in the list movieList

 *****************************************************************************/

Film *movieDatabase_tail(movieList *list);

/*****************************************************************************

Procedure   : movieDatabase_sort

Parameters  : movieList *list - list to sort
              int(*comparison)(Film*, Film*) - function pointer

Returns     : void
 
Description : This is the bubble sort function which will go through the list
              that compares each pair of adjacent items, it goes through the
              list as long as there is more than two items in the list. It
              will sort the items that are getting passed through while it 
              is not sorted. This is a sort function that was shown as part
              of a example in the lecture notes, but I have added in the
              int *comparison

 *****************************************************************************/

void movieDatabase_sort(movieList *list, int(*comparison)(Film*, Film*));

/*****************************************************************************

Procedure   : movieDatabase_clear

Parameters  : movieList *list

Returns     : void
 
Description : This function frees everything in the list that is  being passed 
              through

 *****************************************************************************/

void movieDatabase_clear(movieList *list);

/*****************************************************************************

Procedure   : movieDatabase_clearWithoutFilms

Parameters  : movieList *list

Returns     : void
 
Description : This function is to free everything apart from what is in the    
              film struct

 *****************************************************************************/

void movieDatabase_clearWithoutFilms(movieList *list);

/*****************************************************************************

Procedure   : film_freeNode

Parameters  : Node *node

Returns     : void
 
Description : Frees the node

 *****************************************************************************/

void movieDatabase_freeNode(Node *node);

/*****************************************************************************

Procedure   : movieDatabase_printFilms

Parameters  : const movieList *list

Returns     : void
 
Description : Prints the film that is being passed through the fuction from 
              the movieList

 *****************************************************************************/

void movieDatabase_printFilms(const movieList *list);

/*****************************************************************************

Procedure   : movieDatabase_getFilms

Parameters  : FILE *fp - A file containing films

Returns     : filmList - the films that have just been added to the list from  
              reading the file
 
Description : Gets the films being read in from the File using sscanf to read
              through the line, reading the information that is found between
              each " " in the list, ensuring the list will be printed out
              in the correct format, returns the filmList once it has iterated
              though the whole file

 *****************************************************************************/

movieList *movieDatabase_getFilms(FILE *fp);

/*****************************************************************************

Procedure   : movieDatabase_getFilmPosition

Parameters  : size_t position - the position of the film its looking for using
              size_t which is an unsigned int
              int (*comparison)(Film*)(Film*) - function pointer to compare by
              movieList *list - the list to compare
              char *genre - the given genre to sort

Returns     : found - the film the node is pointing to
 
Description : This takes in an argument passed through in main.c which will
              take the postion that you're looking for, what you want it to do,
              where to read it from and specifically which genre to look for.
              This can be used to answer question 2 and 3 as it sorts the list
              before it finds the position of the film its looking for

 *****************************************************************************/

Film* movieDatabase_getFilmPosition(size_t position, int(*comparison)(Film*,
                                        Film*), movieList *list, char *genre);

/*****************************************************************************

Procedure   : movieDatabase_getTopRated

Parameters  : int(*comparison)(Film*)(Film*) - function pointer to compare by
              movieList *list - list to compare

Returns     : found - the film the node is pointing to
 
Description : This takes in an argument passed through in main.c which will
              take the film from the movieList you point to depending on which
              order you want it in (eg. decending order of rating) unlike the
              getFilmPosition function, it does not sort the list first

 *****************************************************************************/

Film* movieDatabase_getTopRated(int(*comparison)(Film*,Film*), movieList *list);

/*****************************************************************************

Procedure   : movieDatabase_RemoveFilm

Parameters  : movieList *list
              enum ageEnum - using an enum as a way to find all the R rated 
              films to remove

Returns     : void
 
Description : This goes through the list, and when it comes to the arugment
              that is being passed in (eg. R rated film) it will free that 
              node so that it is no longer in the list, and keep iterating
              through the list until there are no more R rated films and 
              reduces the length of the movieList

 *****************************************************************************/

void movieDatabase_RemoveFilm(movieList *list, enum ageEnum);

#ifdef __cplusplus
extern "C" {
#endif




#ifdef __cplusplus
}
#endif

#endif /* MOVIEDATABASE_H */

