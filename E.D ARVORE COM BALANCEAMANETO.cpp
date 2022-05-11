#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX(a,b) (((a)>(b))?(a):(b))

typedef struct Aluno {
	int id;
	char nome[50];
	int idade;
    char matricula[10];
    char naturalida[20];
	struct Aluno *esq;
	struct Aluno *dir;
} aluno;

aluno *raiz = NULL;

void imprimirTab(int n) {
	for (int i = 0; i < n; i++) {
		printf("\t");
	}
}

void imprimir(aluno *aux, int nivel) {
	if (aux != NULL) {
		imprimir(aux->dir, nivel + 1);
		imprimirTab(nivel);
		printf("%d-%s-%d-%s-%s\n",aux->id ,aux->nome, aux->idade,aux->matricula,aux->naturalida);
		imprimir(aux->esq, nivel + 1);
	}
}

aluno *criarAluno() {
	aluno *p = (aluno*) malloc(sizeof(aluno));
	printf("Digite a id do aluno: ");
	scanf("%d", &p->id);
	printf("Digite o nome do aluno: ");
	scanf("%s", p->nome);
	printf("Digite a idade do aluno: ");
	scanf("%d", &p->idade);
	printf("Digite a matricula do aluno: ");
	scanf("%s", p->matricula);
	printf("Digite a naturalidade do aluno: ");
	scanf("%s", p->naturalida);
	p->esq = NULL;
	p->dir = NULL;
	return p;
}

void inseriraluno(aluno *raiz,aluno *p) {
	
		if(raiz->id< p->id ){
			if(raiz->esq==NULL){
				raiz->esq=p;
			}else{
				 inseriraluno(raiz->esq,p);
			}
		}else{
			if(raiz->dir==NULL){
				raiz->dir=p;
			}else{
				inseriraluno(raiz->dir,p);
			}
		}
	
}

void inserir() {
	if (raiz == NULL) {
		raiz = criarAluno();
	} else {
		aluno* p = criarAluno();
		inseriraluno(raiz, p);
	}
}

aluno* remove_atual(aluno* atual){
	aluno *no1,*no2;
	if(atual->esq==NULL){
		no2=atual->dir;
		free(atual);
		return no2;
	}
	no1=atual;
	no2= atual->esq;
	while(no2->dir!=NULL){
		no1=no2;
		no2=no2->dir;
	}
	if(no1!=atual){
		no1->dir=no2->esq;
		no2->esq=atual->esq;
	}
	no2->dir=atual->dir;
	free(atual);
	return no2;
}

int remove_Aluno(aluno* raiz,int i){
	if(raiz==NULL){
		return 0;
	}
	aluno *ant;
	aluno* atual= raiz;
	while(atual!=NULL){
		if(i==atual->id){
			if(atual==raiz){
				raiz=remove_atual(atual);
			}else{
				if(ant->dir==atual){
					ant->dir=remove_atual(atual);
				}else{
					ant->esq=remove_atual(atual);
				}
			}
		}
		return 1;
	}
	ant=atual;
	if(i>atual->id){
		atual=atual->dir;
	}else{
		atual=atual->esq;
	}
}



void retirar() {
	if (raiz == NULL) {
		printf("Nao existem alunos cadastrados!\n");
	} else {
		int x;
		printf("Digite o id do aluno que voce deseja remover: ");
		scanf("%d",&x);
		remove_Aluno(raiz,x);
	}
}
aluno* buscar(aluno* aux,int valor) {
	aux = raiz;
	while (aux != NULL) {
		if (aux->id == valor) {
			return aux;
		}
		if (valor < aux->id) {
			if (aux->esq == NULL) {
				return NULL;
			} else {
				aux = aux->esq;
			}
		} else {
			if (aux->dir == NULL) {
				return NULL;
			} else {
				aux = aux->dir;
			}
		}
	}
	return 0;
}
void busca(){
	if (raiz == NULL) {
		printf("Nao existem alunos cadastrados!\n");
	} else {
		int x;
		printf("Digite o id do aluno que voce deseja encontar: ");
		scanf("%d",&x);
		aluno* p=buscar(raiz,x);
		if (p != 0) {
		printf("aluno %s encontrado\n",p->nome);
	} else {
		printf("aluno  nao encontrado\n");
	}
	}
}

int altura(aluno *aux) {
	if ((aux == NULL) || ((aux->esq == NULL) && (aux->dir == NULL))) {
		return 0;
	}
	return 1 + MAX(altura(aux->esq), altura(aux->dir));
}
void altura1() {
	if (raiz == NULL) {
		printf("Nao existem alunos cadastrados!\n");
	} else {
		printf("\n a altura da arvore eh %d",altura(raiz));
	}
}
int alt(aluno* no){
	if(no==NULL){
		return 0;
	}
	if((no->esq==NULL)&&(no->dir==NULL)){
		return 0;
	}
	return 1+(altura(no->esq),altura(no->dir));


}
int verificaaltura(){
	aluno *raiz;
     printf("\nA Altura2 da arvore eh %d",alt(raiz));
}



int fat_bal(aluno* aux) {
return (altura(aux->esq) - altura(aux->dir));
}
int main(int argc, char **argv) {

	

	int opt = 0;
	do {
		printf("\n|\t**********************************\t|\n");
		printf("|\t\t\tMENU\t\t\t|\n");
		printf("|\t1-Inserir Aluno\t\t\t\t|\n");
		printf("|\t2-Imprimir arvore\t\t\t|\n");
		printf("|\t3-Preencher vaga\t\t\t|\n");
		printf("|\t4-Bucar Aluno\t\t|\n");
		printf("|\t5-Altura da arvore Aluno\t\t|\n");
		printf("|\t6-Altura2 da arvore Aluno\t\t|\n");
		printf("|\t0-Sair\t\t\t\t\t|\n");
		printf("|\t**********************************\t|\n");
		printf("Digite a opcao desejada: ");
		scanf("%d", &opt);
		printf("\n");
		switch (opt) {
		case 1:
			inserir();
			break;
		case 2:
			imprimir(raiz, 0);
			break;
		case 3:
			retirar();
			break;
		case 4:
			busca();
			break;
			case 5:
			altura1();
			break;
			case 6:
			verificaaltura();
			break;
		case 0:
			break;
		default:
			printf("Opcao invalida\n");
			break;
		}

	} while (opt != 0);

}
