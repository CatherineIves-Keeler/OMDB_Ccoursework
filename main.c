/*****************************************************************************

File        : main.c

Date        : Sunday 30th October 2016

Description : Main source file for implementation of a linked list that 
              contains the tasks for the coursework

Author      : Catherine Ives-Keeler

******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "film.h"
#include "moviedatabase.h"

int main(int argc, char** argv) {
    
    //reads the list of films from the films.txt file
    FILE *fp = fopen("films.txt", "r");
    movieList *filmList = movieDatabase_getFilms(fp);
    fclose(fp);
    
    //sorts all films in the film list in acending order
    movieDatabase_sort(filmList, acendingYear); 
    printf("*************************************************");
    printf("\n\n 1.) Films sorted in acending order of year: \n");
    movieDatabase_printFilms(filmList);
    
    //Sorts the Film-Noir films and gets the film in the 3rd highest position
    Film *noirFilm = movieDatabase_getFilmPosition(3, decendingTime, filmList,
                                                                "Film-Noir");
    printf("\n*************************************************");
    printf("\n\n 2.) Third longest Film-Noir film: \n");
    film_print(noirFilm);
    
    //Sorts the Sci-Fi films and gets the film in the 10th highest position
    Film *sciFilm = movieDatabase_getFilmPosition(10, decendingRating, 
                                                        filmList, "Sci-Fi");
    printf("\n*************************************************");
    printf("\n\n 3.) Tenth highest rated Sci-Fi film: \n");
    film_print(sciFilm);
    
    //Gets the highest rated film out of the whole list
    Film *ratedFilm = movieDatabase_getTopRated(decendingRating, filmList);
    printf("\n*************************************************");
    printf("\n\n 4.) Highest rated film: \n");
    film_print(ratedFilm);
    
    //Gets the films with the shortest film title
    Film *topFilm = movieDatabase_getTopRated(titleLength, filmList);
    printf("\n*************************************************");
    printf("\n\n 5.) Shortest Title: \n");
    film_print(topFilm);
    
    //gets the original length of the list
    size_t length = movieDatabase_length(filmList);
    printf("\n*************************************************");
    printf("\n\n 6.)Total number of films: %lu\n", length);
    
    //Returns the length of the list after all R rated films have been removed
    movieDatabase_RemoveFilm(filmList, R);
    size_t lengthAfter = movieDatabase_length(filmList);
    printf("Total number of films after removing all R rated films: %lu\n",
                                                                lengthAfter);
    printf("\n*************************************************\n");
    
    //clears the film list
    movieDatabase_clear(filmList);
    
    return (EXIT_SUCCESS);
}

