#include "compilationV2.h"

void display_list1(){ //affiche fichier dans terminal//
	char c;
	FILE* file= NULL;
	file= fopen("biblio.txt","r");
	if(file == NULL) {
		printf("Ouverture du fichier impossible\n");
		printf("code d'erreur = %d \n", errno);
		printf("Message d'erreur = %s \n", strerror(errno));
		exit(1);
	}
	c=fgetc(file);
	while(c!=EOF){
		printf("%c",c);
		c=fgetc(file);
		}
	fclose(file);
}

void display_list2(User user,int nbe){ //affiche fichier dans terminal//
	int i;
	for(i=0;i<nbe;i++){
		printf("%d titre : %s\n",i,user.livre[i].title);
	}
}

char borrow_book(User *user, User tab[], Book tab1[], int nbo, int nbUser){ //the user choose the book he wants to borrow.The book selected information will change specificaly the disponibility number
	int choice;
	int i,j;
	display_list1();
	do{
		printf("\n quel livre voulez-vous emprunter?\n");
		scanf("%d",&choice);
	}while(choice>nbo);	
	for(i=0;i<nbo;i++){	
		if((tab1[i].identification_number==choice)&&(tab1[i].disponibility==0)){
			for(j=0;j<4;j++){
				if(user->livre[j].title[0]==' '){
					tab1[i].disponibility=1;
					fichier_livres(tab1,nbo-1);
					
					strncpy(user->livre[j].title, tab1[i].title, 100);
					strncpy(user->livre[j].author, tab1[i].author, 100);
					user->livre[j].category=tab1[i].category;
					user->livre[j].identification_number=tab1[i].identification_number;
					user->livre[j].disponibility=tab1[i].disponibility;
					fichier_utilisateur(tab,nbUser);
					return '0'; 
				}
			//return ('1'); il faut stocker les informations dans le fichier utilisateur
			}
		}
	}
	return('1');
}

/*the user put num_identification of the book
and return_book update disponibility in the books table.*/

char return_book(User *user,Book tab2[], int nbBook){//tab2??
	char choice = -1;
	int i;
	int nbe = 0;
	while(nbe != 4 && user->livre[nbe].title[0] != ' '){
		nbe++;
	}
	printf("\n");
	display_list2(*user,nbe);
	do{
		printf("\nquel livre voulez-vous rendre?\n");
		scanf("%c",&choice);
	}while((choice-'0')>nbe || !('0' <= choice && choice <= '4'));
	choice = choice-'0';
	for(i=0;i<nbBook;i++){
		if(strcmp(user->livre[choice].title, tab2[i].title) == 0){
			tab2[i].disponibility=0;
			fichier_livres(tab2, nbBook-1);
			
			user->livre[choice].title[0] = ' ';
			
			for(int k = choice+1; k < 4; k ++){
				if(user->livre[k].title[0] != ' '){
					strncpy(user->livre[k-1].title, user->livre[k].title, 100);
					user->livre[k].title[0] = ' ';
				}
			}
			
			return ('0');
			
		}
	}
	return ('1');//s'éxecute mal : il ne donne pas d'informations vu que le livre ne s'enregistre pas dans le fichier
	//fichier_livres(tab2, nbo);
}
void fichier_livres(Book tab[], int ta){//this function is used 
	int i;
	char category[50];
	FILE* fichier = NULL;
	fichier = fopen("biblio.txt", "w+");
	if(fichier == NULL) {
		printf("Ouverture du fichier impossible\n");
		printf("code d'erreur = %d \n", errno);
		printf("Message d'erreur = %s \n", strerror(errno));
		exit(1);
	}
	for(i=0;i<ta;i++){
		fprintf(fichier,"[%d	",tab[i].identification_number);
		fprintf(fichier,"%s	",tab[i].title);
		fprintf(fichier,"%s	",tab[i].author);
		if(tab[i].category==1){
			fprintf(fichier,"sciences	");
		}
		else if(tab[i].category==2){
			fprintf(fichier,"histoire	");
		}
		else if(tab[i].category==3){
			fprintf(fichier,"litterature	");
		}
		if(tab[i].disponibility==0){
			fprintf(fichier,"dispo]");
		}
		else if(tab[i].disponibility==1){
			fprintf(fichier,"indispo]");
		}
		fprintf(fichier,"\n");
	}
	fclose(fichier);
} 
void fichier_utilisateur(User *user, int ta){//this function is used 
	int i;
	char category[50];
	FILE* fichier = NULL;
	fichier = fopen("liste_utilisateurs.txt", "w");
	if(fichier == NULL) {
		printf("Ouverture du fichier impossible\n");
		printf("code d'erreur = %d \n", errno);
		printf("Message d'erreur = %s \n", strerror(errno));
		exit(1);
	}
	for(i=0;i<ta;i++){
		fprintf(fichier, "%s %c %d",user[i].name, user[i].role, user[i].pin);
		for(int k = 0; k < 4; k++){
			if(user[i].livre[k].title[0] == ' '){
				fprintf(fichier, "  ");
			}else{
				fprintf(fichier, " %s", user[i].livre[k].title);
			}
		}
		fprintf(fichier, "\n");
	}
	fclose(fichier);
} 
int tabbook(Book **ptTab){//this function extract the data from file biblio and put it in a table to facilitate comparaison  	
	FILE* fichier = NULL;
	fichier = fopen("biblio.txt", "r");
	if(fichier == NULL) {
		printf("Ouverture du fichier impossible\n");
		printf("code d'erreur = %d \n", errno);
		printf("Message d'erreur = %s \n", strerror(errno));
		exit(1);
	}
	int nbo=0;
	int c=fgetc(fichier);
	while(c !=EOF){
		if(c == ']'){
			nbo++;
		}
		c=fgetc(fichier);
	}
	nbo++;
	
	Book *tab=malloc(nbo*sizeof(Book));
	if(tab==NULL){
		printf("Erreur\n");
		printf("code d'erreur = %d \n", errno);
		printf("Message d'erreur = %s \n", strerror(errno));
	}
	rewind(fichier);
	//essayer de faire avec une boucle while
	int i=0;
	while(!feof(fichier)){
		char category[30] = {0};
		char disponi[30] = {0}; 
		fgetc(fichier);
		fscanf(fichier, "%d", &tab[i].identification_number);
		fscanf(fichier, "%s", tab[i].title);
		fscanf(fichier, "%s", tab[i].author);
		fscanf(fichier, "%s", category);
		
		if(strcmp("litterature", category) == 0){
			tab[i].category = 3;
		}
		else if(strcmp("sciences", category) == 0){
			tab[i].category = 1;
		}
		else{
			tab[i].category = 2;
		}
		
		fscanf(fichier, "%s", disponi);
		if(strcmp("dispo]", disponi) == 0){
			tab[i].disponibility = 0;
		}
		else{
			tab[i].disponibility = 1;
		}
		fgetc(fichier);
		i++;
 	}
 	*ptTab=tab;
 	return nbo;		
}
int ajout_livre(User user, Book** tab,int nbo){
	int i;
	int d=0;
	int n=nbo++;
	(*tab) = realloc(*tab, n*sizeof(Book));
	if(*tab == NULL){
		printf("Erreur dans la mémoire :(");
		exit(1);
	}

	Book* tabVal = *tab;
	if(user.role=='p'){
		tabVal[n-1].identification_number=n-1;
		printf("Titre?\n");
		scanf("%s", tabVal[n-1].title);
		printf("Auteur?\n");
		scanf("%s", tabVal[n-1].author);
		printf("Catégorie? 1.sciences 2.histoire 3.litterature\n");
		scanf("%d", &tabVal[n-1].category);
		tabVal[n-1].disponibility = 0;
		fichier_livres(tabVal, n);
		
		return n;
	}
	
	return -1;
}
