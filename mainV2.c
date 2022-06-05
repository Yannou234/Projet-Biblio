#include"compilationV2.h"


User Create_users_list(){//this function will write in the file the informations given by the users
	User user;
	int i;
		printf("Quel est votre identifiant?\n");
		scanf("%s",user.name);
		do{
		printf("Rôle: e-étudiant/p-professeur?\n");
		scanf("%c",&user.role);
		}while(user.role !='e' && user.role !='p');
		printf("Choissisez un code PIN\n");
		scanf("%d",&user.pin);
		for(i=0;i<5;i++){
			user.livre[i].title[0]=' ';
		}
	return user;
}

int tabuti1(User **ptTab){//this function extract the data from file liste_utilisateurs and put it in a table to facilitate comparaison  
	FILE* fichier = NULL;
	fichier = fopen("liste_utilisateurs.txt", "r");
	if(fichier == NULL){		
		printf("Ouverture du fichier impossible\n");
		printf("code d'erreur = %d \n", errno);
		printf("Message d'erreur = %s \n", strerror(errno));
		exit(1); 
	}	
	int nbu=0;
	int c=fgetc(fichier);
	while(c !=EOF){
		if(c == '\n'){
			nbu++;
		}
		c=fgetc(fichier);
	}
	//nbu++;
	
	User *tab=malloc(nbu*sizeof(User));
	if(tab==NULL){
		printf("Erreur\n");
		printf("code d'erreur = %d \n", errno);
		printf("Message d'erreur = %s \n", strerror(errno));
	}
	rewind(fichier);
	int i=0;
	while(!feof(fichier)){
		fscanf(fichier, "%s %c %d", tab[i].name,&tab[i].role,&tab[i].pin);
		for(int k = 0; k < 4; k++){
			fgetc(fichier);
			if(fgetc(fichier) == ' '){
				tab[i].livre[k].title[0] = ' ';
			}else{
				fseek(fichier, -2, SEEK_CUR);
				fscanf(fichier, "%s", tab[i].livre[k].title);
			}
			
		}
		i++;
 	}
 	*ptTab=tab;
 	return nbu;		
}

int Verify_User(User **u, User tabusers[], int nbU){//It's used to verify if the informations given by the users exist in the file. tabusers is the table wich contains all the informations of connexion of the users. nbU is the number of users in data base.
	int n,i;
	/*User user;
	printf("Quel est votre identifiant de connexion?\n");
	scanf("%s",user.name);
	printf("Quel est votre code PIN?\n");
	scanf("%d",&user.pin);*/
	for(i=0;i<nbU;i++){
		if((strcmp(tabusers[i].name,(*u)->name)==0)&&(tabusers[i].pin==(*u)->pin)){
			*u = (tabusers+i);
			return '0';
		}
	}
}



int action(User *user, User tabUser[],int nbUser,Book tab1[], int nbo){//this function is used to direct the user to the action he wants to do
	char a,b,c;
	User u;
	printf("Que souhaitez vous faire?\n	1/Emprunter un livre.\n	2/Rendre un livre.\n	3/Changer d'utilisateur.\n	4/Créer un livre.\n	5/Quitter.\n");
	do{
		scanf("%c",&a);
	}while(a!='1' && a!='2' && a!='3' && a!='4' && a!='5');
	if(a=='1'){
		c=borrow_book(user, tabUser, tab1,nbo,nbUser);
		if(c=='0'){
			printf("Ce livre est emprunté :)\n");
			action(user,tabUser,nbUser,tab1,nbo);
		}
		else if(c=='1'){
			printf("Ce livre ne peut pas être emprunté :(\n");
			action(user,tabUser,nbUser,tab1,nbo);
		}
		else{
			printf("Ce livre ne peut pas être emprunté :(\n");
			action(user,tabUser,nbUser,tab1,nbo);
		}
	}
	else if(a=='2'){
		c=return_book(user, tab1, nbo);
		if(c=='0'){
			printf("Ce livre est bien rendu :)\n");
			fichier_utilisateur(tabUser, nbUser);
			action(user,tabUser,nbUser,tab1,nbo);
		}
		else{
			printf("Vous ne possédez pas ce livre :(\n");
			action(user,tabUser,nbUser,tab1,nbo);
		}
	}
	else if(a=='3'){
		connexion();
	}
	else if(a=='4'){
			printf("Création d'un livre\n");
			int value = ajout_livre(*user, &tab1,nbo);
			
			if(value == -1){
				printf("Vous ne pouvez pas ajouter de livre, vous n'en avez pas le droit.");
			}else{
				nbo = value;
			}
			
			action(user,tabUser,nbUser,tab1,nbo);
	}
	else if(a=='5'){
		printf("Vous quittez le programme\n");
		exit(1);
	}
	else if(a!='1' && a!='2' && a!='3' && a!='4' && a!='5'){
		action(user,tabUser,nbUser,tab1,nbo);
	}
}

void connexion(){//this function is used 
	char a,b,c;
	User u;
	Book* tab1;
	int nbo=tabbook(&tab1);
	printf("|======================================|\n");
	printf("|		Bienvenue              |\n");
	printf("|======================================|\n");
	printf("\n1/Connexion\n2/Créer un compte\n3/Quitter\n");
	do{
		scanf("%c",&a);
	}while( a!='1' && a!= '2' && a!= '3');
	printf("\n");
	User* tabu;
	int nbUser = tabuti1(&tabu);
	User user;
	User* ptUser = &user;
	if(a=='1'){
		printf("Quel est votre identifiant de connexion?\n");
		scanf("%s",user.name);
		printf("Quel est votre code PIN?\n");
		scanf("%d",&user.pin);
		b=Verify_User(&ptUser,tabu, nbUser);
			if(b=='0'){
				printf(COLOR_GREEN "Le code est bon. Vous êtes connecté ! :)\n\n"COLOR_RESET);
				action(ptUser,tabu,nbUser,tab1,nbo);
			}
			else{
				printf("Saisie incorrecte\nVoulez-vous:\n1/Réessayer\n2/Quitter le programme \n");
				do{
					scanf("%c",&c);
				}while( c!='1' && c!= '2');
				printf("\n");
				if(c=='1'){
					connexion();
				}
				else if(c=='2'){
					printf("Vous quittez le programme\n");
					exit(1);
				}
			}
	}
	else if(a=='2'){
		u=Create_users_list();
		write_users(u);
		printf("Votre compte a bien été créé. Veuillez vous connecter.\n");
		connexion();
	}
	else if(a=='3'){
		printf("Vous quittez le programme\n");
		exit(1);
	}
	else if(a!='1' && a!='2' && a!='3'){
		connexion();
	}
}
	
void write_users(User user){//this function 
	int i;
	FILE* fichier = NULL;
	fichier = fopen("liste_utilisateurs.txt", "a");
	if(fichier == NULL) {
		printf("Ouverture du fichier impossible\n");
		printf("code d'erreur = %d\n", errno);
		printf("Message d'erreur = %s\n", strerror(errno));
		exit(1);
	}
	fseek(fichier,0,SEEK_END);
	fprintf(fichier, "%s %c %d",user.name, user.role, user.pin);
	
	for(i = 0; i < 4; i++){
		if(user.livre[i].title[0] = ' '){
			fprintf(fichier, "  ");
		}else{
			fprintf(fichier, " %s", user.livre[i].title);
		}
	}
	fprintf(fichier, "\n");
	fclose(fichier);
}
	
/*int timer_e(int i) {
    printf("patientez\n");
    sleep(120);
    printf("temps écoulé\n");
    return 0;
} //student 3 books

int timer_p(int i) {
    printf("patientez\n");
    sleep(180);
    printf("temps écoulé\n");
    return 0;
}//max 5 books teacher*/

int main(){//Commentary needed
	User *liste_uti;
	int n;
	int i;
	User p;
	User* t;
	n=tabuti1(&t);
	liste_uti=malloc(n*sizeof(User));
	if(liste_uti ==NULL){
		printf("la liste_uti est vide, on ne peut pas l'afficher !\n");
		exit(0);
	}
	connexion();
	free(liste_uti);
	return 0;
}


