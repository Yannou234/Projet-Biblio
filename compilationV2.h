#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#define TA 10

#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_RESET   "\x1b[0m"

typedef struct{
	char title[100];
	char author[100];
	int category;
	int identification_number;
	int disponibility;
	}Book;
typedef struct{
	char name[30];
	char role;
	int pin;
	Book livre[4];
}User;

int Verify_User(User **u,User tabusers[],int nbU);//this fonction will verify if the name exist in this file and compare if it's exist the pin code affiliate with the name
int Creer_liste_uti(User tab[],int taille);
void connexion();
void write_users(User user);//this fonction will create a profil for each new user in this file name liste_utilisateurs.txt wich contain all the informations about each user
void fichier_livres(Book tab[], int ta);
void display_list1();
void display_list2(User user, int nbo);
char borrow_book(User *user, User tab[], Book tab1[],int nbo, int nbUser);
char return_book(User *user,Book tab2[], int nbBook);
int tabbook(Book **ptTab);
void fichier_utilisateur(User *user, int ta);
int ajout_livre(User user, Book* tab[],int nbo);

User Create_users_list();
void write_users(User user);
void connexion();
int tabuti1(User **ptTab);

