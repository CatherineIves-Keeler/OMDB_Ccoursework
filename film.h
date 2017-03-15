/*****************************************************************************

File        : film.h

Date        : Sunday 30th October 2016

Description : Header file for implementation of a film struct

Author      : Catherine Ives-Keeler

******************************************************************************/

#ifndef FILM_H
#define FILM_H

enum ageEnum {PG_13 = 0, APPROVED, PASSED, PG, R, NOT_RATED, G, UNRATED, N_A, 
                                                                TV_14, M, X};

typedef struct Film //Film struct
{
    char *title; //pointers to character array
    int releaseYear;
    enum ageEnum ageRating;
    char *genre;
    int lengthMins;
    double starRating;
}Film;

/*****************************************************************************

Procedure   : film_new

Parameters  : char *title
              int release Year
              enum age Enum ageRating
              char *genre
              int length Mins
              double starRating

Returns     : film
 
Description : Goes through the film and points to all of the information needed
              to make a new film

 *****************************************************************************/

Film* film_new(char *title, int releaseYear, enum ageEnum ageRating, 
                            char *genre, int lengthMins, double starRating);

/*****************************************************************************

Procedure   : film_free

Parameters  : Film *aFilm

Returns     : none
 
Description : Frees the films information

 *****************************************************************************/

void film_free(Film *afilm);

/*****************************************************************************

Procedure   : film_getReleaseYear

Parameters  : Film *aFilm

Returns     : releaseYear
 
Description : Get function to return the current films year of release using
              using static inline to hint to the compiler to reduce 
              function overhead

 *****************************************************************************/

static inline int film_getReleaseYear(Film *aFilm) 
{
    return aFilm->releaseYear;
}

/*****************************************************************************

Procedure   : film_getGenre

Parameters  : Film *aFilm

Returns     : genre
 
Description : Get function to return the current films genre of the current 
              film using static inline to hint to the compiler to reduce 
              function overhead

 *****************************************************************************/

static inline char* film_getGenre(Film *aFilm)
{
    return aFilm->genre;
}

/*****************************************************************************

Procedure   : film_getLengthMins

Parameters  : Film *aFilm

Returns     : lengthMins
 
Description : Get function to return the length in minutes of the current film
              using static inline to hint to the compiler to reduce function
              overhead

 *****************************************************************************/

static inline int film_getLengthMins(Film *aFilm)
{
    return aFilm->lengthMins;
}

/*****************************************************************************

Procedure   : film_getRating

Parameters  : Film *aFilm

Returns     : starRating
 
Description : Get function to return the star rating of the current film
              using static inline to hint to the compiler to reduce 
              function overhead

 *****************************************************************************/

static inline double film_getRating(Film *aFilm)
{
    return aFilm->starRating;
}

/*****************************************************************************

Procedure   : film_getTitle

Parameters  : Film *aFilm

Returns     : title
 
Description : Get function to return the title of the current film using static
              inline to hint to the compiler to reduce function overhead

 *****************************************************************************/

static inline char* film_getTitle(Film *aFilm)
{
    return aFilm->title;
}

/*****************************************************************************

Procedure   : film_getStringAgeRating

Parameters  : Film *aFilm

Returns     : ageRateString
 
Description : Get function to return the age rating of the current film

 *****************************************************************************/

char* film_getStringAgeRating(Film *aFilm);

/*****************************************************************************

Procedure   : acendingYear

Parameters  : Film *a
              Film *b

Returns     : film_getReleaseYear(a) > film_getReleaseYear(b)
 
Description : Function that sorts two films at a time, going through the list
              of films comparing the year of release and sorting it in 
              acending order

 *****************************************************************************/

int acendingYear(Film *a, Film *b);

/*****************************************************************************

Procedure   : decendingTime

Parameters  : Film *a
              Film *b

Returns     : film_getLengthMins(a) < film_getLengthMins(b);
 
Description : Function that sorts two films at a time, going through the list
              of films comparing the length of the film and sorting them in 
              decending order

 *****************************************************************************/

int decendingTime(Film *a, Film *b);

/*****************************************************************************

Procedure   : decendingRating

Parameters  : Film *a
              Film *b

Returns     : film_getRating(a) < film_getRating(b);
 
Description : Function that sorts two films at a time, going through the list
              of films comparing the star rating of each films, sorting them
              in decending order

 *****************************************************************************/

int decendingRating(Film *a, Film *b);

/*****************************************************************************

Procedure   : titleLength
 * 
Parameters  : Film *a
              Film *b

Returns     : strlen(film_getTitle(a)) > strlen(film_getTitle(b))
 
Description : Function that sorts two films at a time, going through the list
              of films comparing the length of the titles of each film,
              sorting them in acending order, giving the shortest length first

 *****************************************************************************/

int titleLength(Film *a, Film *b);

/*****************************************************************************

Procedure   : film_print

Parameters  : Film *afilm

Returns     : none
 
Description : Gets all of the information from afilm pointing to each part of
              each film, and then printing it out in a line

 *****************************************************************************/

void film_print(Film *afilm);

/*****************************************************************************

Procedure   : film_getEnumFromString

Parameters  : char *eString

Returns     : ageRatingNum
 
Description : Returns the enum value of a rating, given string format

 *****************************************************************************/

enum ageEnum film_getEnumFromString(char *eString);

#ifdef __cplusplus
extern "C" {
#endif




#ifdef __cplusplus
}
#endif

#endif /* FILM_H */

