/*Trabalho de Estruturas de Dados SIN 211
Professora: Rachel Reis
Alunos:Jhonatha Cordeiro 5984, Lincoln Dandson Sousa Morais 5993 , Ludmyla Caroline Ferreira Marques 552 */
//bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//estruturas de dados
typedef struct sRemedio{ // cria a estrutura que vai alocar horarios e medicamentos a tomar
	char nome[20]; // variavel para armazenar o nome do medicamento 
	int hora,minuto,soma; // variaveis para armazenar o horario e soma 
}remedio;

typedef struct sCELULA{ // cria a estrutura que vai alocar informações de medicamentos e proxima celula
	remedio info; // informacao no no da lista
	struct sCELULA *next; // ponteiro aponta para o proximo elemento
}celula;
//funcao para inicializar a lista
void inicializar_lista(celula **lista){ // inicializa a lista 
	*lista=NULL; // inicializa a lista com null
}
//funcao para verificar se a lista esta vazia
int lista_vazia(celula **lista){ // verifica se a lista esta vazia
	if(*lista==NULL){
		return 1; // se estiver vazia retorna verdadeiro 
	}else{
		return 0; // se não estiver vazia retorna falso
	}
}
// funcoes criar e excluir elemento
celula* getnode(){ // funcao aloca um novo nó na memoria 
	return (celula*)malloc(sizeof(celula));
}
void freenode(celula *q){ //funcao remove um nó na memoria 
	free(q);
}
//funcoa para printar lista
int print_lista(celula **lista){ // funcao para printar os elementos da lista
	celula *aux,*aux2; // cria ponteiros auxiliares
	int i=1;// variavel auxiliar para contador
	if(lista_vazia(lista)){ // verifica se a lista esta vazia 
		printf("\nErro - Lista de medicamentos vazia\n");
		return 0;
	}else{ 
		aux=(*lista)->next; // aux recebe o primeiro elemento da lista
		printf("\n.:lista de medicamentos:.\n");
		printf("--------------------------\n");
		do{
			printf("\nMedicamento %d:%s horario:%d:%d\n",i,aux->info.nome,aux->info.hora,aux->info.minuto);//printa o elemento
			aux2=aux; // aux2 recebe aux
			aux=aux->next; // aux aponta para o proximo elemento
			freenode(aux2); // remove o elemento anterior a aux
			i++; // conta a quantidade de medicamentos
		}while(aux!=(*lista)->next); // verifica se a lista ainda tem elementos
		inicializar_lista(lista); // chama a funcao para inicializar a lista para ser usada novamente
	}
}
// funcoes de insercao
int inserir_ordenado(celula **lista,remedio elem){
	celula *q,*aux,*anterior=NULL; // cria ponteiros auxiliares
	q=getnode(); // cria novo nó
	if(q==NULL){// verifica se o novo nó foi criado 
		printf("\nERRO AO ALOCAR");
		return 0;
	}
	q->info=elem; // insere elementos no novo nó 
	if(*lista==NULL){ // verifica se a lista esta vazia
		q->next=q; //q aponta para ele mesmo
		*lista=q; // lista recebe q 
		return 0;
	}
	aux=(*lista)->next; // aux recebe o primeiro elemento da lista
	anterior=(*lista);// ponteiro auxiliar recebe ultimo elemento da lista
	if(((q->info).soma)<=((aux->info).soma)){ //verifica se o horario a inserir e menor que o horario do primeiro no
		inserir_inicio(lista,q); //chama a funcao inserir no inicio
		return 0;
	}
	do{
		if((aux->info).soma>=(q->info).soma){ //verifica se o horario do no atual e maior ou igual que o novo no a ser inserido
			break;
		}else{
			anterior=aux; //anterior recebe o no atual
			aux=aux->next; // aux aponta para o proximo no
		}
	}while(aux!=(*lista)->next); // verifica se o existe elemento na lista
	if(aux==(*lista)->next){// verifica se o elemento deve ser inserido no fim
		inserir_fim(lista,q); // chama a funcao inserir no fim
		return 0;
	}else{ // insere o elemento no meio da lista
		q->next=aux; // q aponta para o aux(elemento seguinte)
		anterior->next=q; //no anterior aponta para o novo elemento(q)
		return 0;
	}
}

int inserir_inicio(celula **lista,celula *q){ //funcao para inserir elemento no inicio da lista
	if(lista_vazia(lista)){ // verifica se a lista esta vazia 
		q->next=q; // q aponta para ele mesmo
		*lista=q; //lista recebe q
		return 0;
	}else{
		q->next=(*lista)->next; // q next aponta para o antigo primeiro elemento
		(*lista)->next=q; // lista next aponta para o primeiro elemento
	}
	return 0;
}

int inserir_fim(celula **lista,celula *q){ //funcao para inserir elemento no fim da lista
	if(lista_vazia(lista)){ // verifica se a lista esta vazia
		q->next=q; // q aponta para ele mesmo
		*lista=q; // lista recebe o ponteiro auxiliar
		return 0;
	}else{ 
		q->next=(*lista)->next; //q next aponta para o primeiro elemento da lista
		(*lista)->next=q; //lista aponta para o q(ultimo elemento)
		*lista=q; // lista recebe q 
	}
	return 0;
}
// funcoes de pesquisa
int pesquisar(celula **lista,remedio elem){ // funcao para pesquisar um elemento por horario
	celula *aux; // cria ponteiro auxiliar
	int x=0,i=1; // variaveis auxiliares
	if(lista_vazia(lista)){//verifica se a lista esta vazia
		printf("Erro lista de medicamentos vazia\n");
		return 0;
	}else{
		aux=*lista; //aux recebe lista
		do{
			if(elem.soma==aux->info.soma){	// verifica se o elemento se encontra na lista
				printf("\nMedicamento %d:%s Horario:%d:%d\n",i,aux->info.nome,aux->info.hora,aux->info.minuto);
				x++; // verifica se foi encontrado o medicamento
				i++; // contador de medicamentos encontrados
			}
			aux=aux->next; // aux aponta para o proximo elemento
		}
		while(aux!=*lista);	// verifica se a lista chegou ao fim
	}
	if(x==0){ // caso nao encontre o elemento apresenta a mensagem abaixo 
		printf("\nMedicamento nao encontrado\n");
	}
	return 0;
}
int pesquisar_nome(celula **lista,char nome[20]){
	celula *aux; // cria ponteiro auxiliar
	int x=0,i=1,z; // variaveis auxiliares
	if(lista_vazia(lista)){//verifica se a lista esta vazia
		printf("Erro lista de medicamentos vazia\n");
		return 0;
	}else{
		aux=*lista; //aux recebe lista
		do{
			z=strcmp((aux->info.nome),nome); // verifica se a duas strings sao iguais
			if(z==0){// verifica se o retorno de z e igual a 0 , se sim as duas strings sao iguais
				printf("\nMedicamento %d:%s Horario:%d:%d\n",i,aux->info.nome,aux->info.hora,aux->info.minuto);
				x++; // verifica se foi encontrado o medicamento
				i++; // contador de medicamentos encontrados
			}
			aux=aux->next; // aux aponta para o proximo elemento
		}
		while(aux!=*lista);	// verifica se a lista chegou ao fim
	}
	if(x==0){ // caso nao encontre o elemento apresenta a mensagem abaixo 
		printf("\nMedicamento nao encontrado\n");
	}
	return 0;
}
// funcoes de remocao
int remover(celula **lista,char nome[20]){
	celula *aux,*anterior; // cria ponteiro auxiliar
	int z; //variavel auxiliar 
	if(lista_vazia(lista)){ // verifica se a lista esta vazia 
		printf("Erro lista de medicamentos vazia\n");
		return 0;
	}else{
		aux=(*lista)->next; // aux recebe o primeiro elemento da lista
		while(aux!=*lista){ // verifica se a lista esta no fim
			z=strcmp((aux->info.nome),nome); // verifica se as strings sao iguais
			if(z==0){ // verifica se o retorno de z e igual a 0 , se sim as duas strings sao iguais
				if(aux==(*lista)->next){
					(*lista)->next=aux->next; // lista aponta para o proximo elemento (aux next)
					freenode(aux);
				}else if(aux==(*lista)){
					anterior->next=aux->next; //anterior aponta para inicio da lista 
					*lista=anterior; // lista recebe elemento anterior
					freenode(aux); // chama funcao para remover elemento da lista
				}else{ // remove um elemento no meio da lista
					anterior->next=aux->next; // anterior next aponta para o aux next 
					freenode(aux); //chama a funcao para remover aux 
				}
				break; //encerra while
			}
			anterior=aux; // anterior recebe o elemento atual(aux)
			aux=aux->next; // aux recebe o proximo elemento
		}
	}
	return 0;
}
int remover_inicio(celula **lista){ // funcao para remover elemento do inicio da lista
	celula *aux; // cria ponteiro auxiliar
	if(lista_vazia(lista)){ // verifica se a lista esta vazia 
		printf("Erro lista de medicamentos vazia\n");
		return 0;
	}else{ 
		aux=(*lista)->next; // aux recebe a lista
		if(*lista==(*lista)->next){ // verifica se existe apenas um no na lista
			*lista=NULL; // lista recebe null
			return 0;
		}
		(*lista)->next=aux->next; // lista recebe o proximo elemento (aux next)
		freenode(aux); //chama a funcao para remover o elemento da lista
	}
	return 0;
}
int remover_final(celula **lista){ // funcao pare remover elemento do final da lista
	celula *aux,*anterior; // cria ponteiros auxiliares 
	if(lista_vazia(lista)){ // verifica se a lista esta vazia
		printf("Erro lista de medicamentos vazia\n");
		return 0;
	}else{
		aux=(*lista)->next; // faz ponteiro auxiliar receber a lista 
		while(aux!=*lista){ // procura o ultimo elemento da lista 
			anterior=aux; //anterior recebe aux
			aux=aux->next;//aux recebe aux next
		}
		if(aux==(*lista)->next){ // verifica se a lista so tem um elemento
			remover_inicio(lista); // chama funcao remover do inicio
			return 0;
		}else{ // caso a funcao tenha mais de um elemento
			anterior->next=aux->next; //anterior aponta para inicio da lista 
			*lista=anterior; // lista recebe elemento anterior
			freenode(aux); // chama funcao para remover elemento da lista
		}
	}
	return 0;
}
//funcoes de menu
void menu(){ // funcao menu
	system("pause"); //pausa o programa
	system("cls || clear"); // limpa a tela do usuario
	printf("\n====================================");
	printf("\n=     Lembrete de medicamentos     =");
	printf("\n====================================");
	printf("\n* 1-Inserir medicamento            *");
	printf("\n* 2-Remover medicamento            *");
	printf("\n* 3-Mostrar medicamentos inseridos *");
	printf("\n* 4-Pesquisar medicamento          *");
	printf("\n* 5-Como usar?                     *");
	printf("\n* 6-Sair                           *");
	printf("\n====================================");
	printf("\nDigite a opcao desejada:");
}
void menu_dois(){
	system("pause"); //pausa o programa
	system("cls || clear");// limpa a tela
	printf("\n====================================");
	printf("\n=     Lembrete de medicamentos     =");
	printf("\n====================================");
	printf("\n* 1-Pesquisar por nome             *");
	printf("\n* 2-Pesquisar por horario          *");
	printf("\n* 3-Retornar ao menu               *");
	printf("\n====================================");
	printf("\nDigite a opcao desejada:");
}
void menu_tres(){
	system("pause"); //pausa o programa
	system("cls || clear");// limpa a tela
	printf("\n====================================");
	printf("\n=     Lembrete de medicamentos     =");
	printf("\n====================================");
	printf("\n* 1-Remover medicamento por nome   *");
	printf("\n* 2-Remover primeiro medicamento   *");
	printf("\n* 3-Remover ultimo medicamento     *");
	printf("\n* 4-Retornar ao menu               *");
	printf("\n====================================");
	printf("\nDigite a opcao desejada:");
}
void intro(){// funcao de introducao ao usuario
	system("cls || clear");// limpa a tela
	printf("--------------------------------------------\n");
	printf("*  Boas vindas ao Lembrete de Medicamentos *");
	printf("\n--------------------------------------------\n");
	printf("Como usar?\n");
	printf("\n   O programa(Lembrete de Medicamentos) consiste em cria uma lista em que\no usuario(a) consiga gravar seus medicamentos diarios a serem tomados\nevitando esquecimentos e demais danos a saude.\n");
	printf("\nOpcao 1: Selecionando a opcao 1, o usuario podera inserir medicamentos,\ninserindo nome e horario, gravando os medicamentos na lista.\n");
	printf("\nOpcao 2: Selecionando a opcao 2, o usuario podera remover elementos por nome, do inicio e fim da lista.\n");
	printf("\nOpcao 3: Selecionando a opcao 3, o usuario mostra todos os elementos inseridos na lista.\n");
	printf("\nOpcao 4: Selecionando a opcao 4, o usuario pesquisa medicamentos na lista por nome ou horario.\n");
	printf("\nOpcao 5: Selecionando a opcao 5, o usuario volta para este tutorial.\n");
	printf("\nOpcao 6: Selecionando a opcao 6, o usuario encerra o programa.\n");
}
int main(){
	celula *ptr; // cria o ponteiro externo da lista
	remedio elem; // cria uma copia da estrutura remedio
	char nome[20]; // cria variavel auxiliar
	int x=-1,y; // variavel x controla o loop dentro do menu, y a opção desejada
	inicializar_lista(&ptr); // inicializa a lista
	intro(); // chama a funcao de introducao
	while(x!=0){ // estrutura d repeticao que controla o menu do programa
		do{
			menu(); // chama a função menu 
			scanf("%d",&y);
			if(y<1 || y>6){ // verifica se o numero digitado e um numero valido
				printf("\nOpcao invalida, por favor digite uma opcao valida\n");
			}	
		}while(y<1 || y>6); // faz a verificacao se o numero em que o usuario digitou e um numero valido
		switch(y){ 
			case 1: // opcao 1 inserir medicamento
				printf("\nDigite o nome do remedio:");
				fflush(stdin); // limpa o buffer
				gets(elem.nome); //ler nome do medicamento 
				fflush(stdin); // limpa o buffer
				do{
					printf("\nDigite as horas a tomar o remedio:");
					scanf("%d",&elem.hora); // ler as horas
					if(elem.hora>24 || elem.hora<1){
						printf("\nHorario invalido\n"); //apresenta mensagem de horario invalido caso o usuario digite um horario invalido
					}
				}while(elem.hora>24 || elem.hora<1); // faz a verificao do horario digitado, se e valido ou nao
				do{
					printf("\nDigite os minutos a tomar o remedio:"); 
					scanf("%d",&elem.minuto);	// ler os minutos
					if(elem.minuto>60 || elem.minuto<0){ 
						printf("\nHorario invalido\n"); // apresenta mensagem de horario invalido caso o usuario digite os minutos invalido
					}
				}while(elem.minuto>60 || elem.minuto<0);// faz a verificao dos minutos digitado, se e valido ou nao
				elem.soma=((elem.hora*100)+elem.minuto); // multiplica as horas por 100 e soma com os minutos, para facilitar a verificao ao inserir
				inserir_ordenado(&ptr,elem); // chama a funcao para inserir os elementos
				break; // encerra o case 1
			case 2:
				do{
					menu_tres(); // chama a funcao menu tres
					scanf("%d",&y); // le a opcao do usuario
					if(y<1 || y>4){ // verifica se a opcao digitada e valida
						printf("\nOpcao invalida, por favor digite uma opcao valida\n");				
					}
				}while(y<1 || y>4); // verifica se a opcao digitada e valida
				switch(y){
					case 1:
						printf("Digite o nome do medicamento a remover:");
						fflush(stdin); // limpa o buffer
						gets(nome); // ler o nome a pesquisar
						fflush(stdin); // limpa o buffer
						remover(&ptr,nome); // chama funcao remover
						break; //encerra o case
					case 2:
						remover_inicio(&ptr); // chama funcao remover do inicio
						break; //encerra o case
					case 3:
						remover_final(&ptr); // chama funcao remover do final
						break; //encerra o case
					case 4:
						break; // encerra a funcao
				}
				break; // encerra o case
			case 3:
				print_lista(&ptr);// chama a funcao print lista
				break; // encerra o case
			case 4:
				do{
					menu_dois(); //chama a funcao menu dois 
					scanf("%d",&y); // ler do usuario a opcao
					if(y<1 || y>3){ // verifica se a opcao digitada e valida 
						printf("\nOpcao invalida, por favor digite uma opcao valida\n");				
					}
				}while(y<1 || y>3); // verifica se a opcao digitada e valida
				switch(y){
					case 1:
						printf("Digite o nome do medicamento a pesquisar:");
						fflush(stdin); //limpa buffer
						gets(nome); // ler o nome a pesquisar
						fflush(stdin); // limpa o buffer
						pesquisar_nome(&ptr,nome); // chama a funcao pesquisar por nome
						break; // encerra o case
					case 2:	
						printf("\nDigite o horario a pesquisar:");
						do{
							printf("\nHoras:");
							scanf("%d",&elem.hora);//ler as horas
							if(elem.hora>24 || elem.hora<1){ //apresenta mensagem de horario invalido caso o usuario digite um horario invalido
								printf("\nHorario invalido\n");
							}
						}while(elem.hora>24 || elem.hora<1); // faz a verificao se o horario digitado e valido
						do{
							printf("\nMinutos:");
							scanf("%d",&elem.minuto);// ler os minutos
							if(elem.minuto>60 || elem.minuto<0){ // apresenta mensagem de horario invalido caso o usuario digite os minutos invalido
								printf("\nHorario invalido\n");
							}
						}while(elem.minuto>60 || elem.minuto<0); //faz a verificao se o horario digitado e valido
						elem.soma=((elem.hora*100)+elem.minuto); // multiplica as horas por 100 e soma com os minutos, para facilitar a verificao ao inserir
						pesquisar(&ptr,elem);// chama a funcao pesquisar
						break;// encerra o case
					case 3:
						break;// encerra o case
				}	
				break;// encerra o case
			case 5:
				intro(); //chama  funcao intro
				break; // encerra o case
			case 6: // encerra o programa
				x=0; //x=0 encerra o while que controla o menu
				break; // encerra o case
		}
	}
	return 0;
}

