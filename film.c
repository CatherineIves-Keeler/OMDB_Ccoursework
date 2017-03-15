/*****************************************************************************

File        : film.c

Date        : Sunday 30th October 2016

Description : Source file for implementation of functions that directly
              interact with a film from the list

Author      : Catherine Ives-Keeler

******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "film.h"
#include "moviedatabase.h"

#define ENUMSIZE (12)

char *ageRateString[ENUMSIZE] = {"PG-13", "APPROVED", "PASSED", "PG", "R",
                        "NOT RATED", "G", "UNRATED", "N/A", "TV-14", "M", "X"};

Film *film_new(char *title, int releaseYear, enum ageEnum ageRating, 
                                char *genre, int lengthMins, double starRating)
{
    Film *film = (Film*)malloc(sizeof(Film));
    //memory management for film information for char*
    film->title = malloc(sizeof(char)*strlen(title)+1);
    strncpy(film->title, title, sizeof(char)*strlen(title)+1);
    
    film->releaseYear = releaseYear;
    
    film->ageRating = ageRating;
    
    film->genre = malloc(sizeof(char)*strlen(genre)+1);
    strncpy(film->genre, genre, sizeof(char)*strlen(genre)+1);
    
    film->lengthMins = lengthMins;
    film->starRating = starRating;
    
    return film;
}

void film_free(Film *afilm) //function to free film information
{
    free(afilm->title);
    free(afilm->genre);
    free(afilm);
}

char* film_getStringAgeRating(Film *aFilm)
{
    return ageRateString[aFilm->ageRating];
}

int acendingYear(Film *a, Film *b)
{
    return film_getReleaseYear(a) > film_getReleaseYear(b);
}

int decendingTime(Film *a, Film *b)
{
    return film_getLengthMins(a) < film_getLengthMins(b);
}

int decendingRating(Film *a, Film *b)
{
    return film_getRating(a) < film_getRating(b);
}

int titleLength(Film *a, Film *b)
{
    return strlen(film_getTitle(a)) > strlen(film_getTitle(b));
}

void film_print(Film *afilm) //prints out the list of film information
{
   printf("%s, %i, %s, %s, %i, %.1f\n", afilm->title, afilm->releaseYear,
         film_getStringAgeRating(afilm), afilm->genre, afilm->lengthMins,
                                                    afilm->starRating); 
}

enum ageEnum film_getEnumFromString(char *eString)
{
    int found = 0;
    int i = 0;
    enum ageEnum ageRatingnum;
        
    while (!found && i < ENUMSIZE)
        {
            if (!strcmp(ageRateString[i], eString))
            {
                found = 1;
                ageRatingnum = i;
            }
            i++;
        }
    return ageRatingnum;
}