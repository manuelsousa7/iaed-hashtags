/******************************************************************************************
* File Name:   main.c
* Author:      Goncalo Marques (84719) / Manuel Sousa (84740)
* Revision:
* NAME:        Hashtags - IST/IAED - 2015/2016 2º Semestre
* SYNOPSIS:    #include <stdio.h>
	       #include <string.h>  - strdup
	       #include <stdlib.h>  - qsort
	       #include <stdbool.h> - bool's
	       #include "avl.h" - toda a estrura da Arvore AVL
	       #include "auxiliares.h" - funcoes auxiliares a main 
* DESCRIPTION: funcao main
* DIAGNOSTICS: tested
* USAGE:       make clean
	       make all
	       make run
*****************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "avl.h"
#include "auxiliares.h"

#define MAXCHAR 142

/******************************************************************************************
* main()
*
* Arguments: nenhum
* Returns: 0
* Description: 	menu de comandos - processa informacao e insere na AVL (estrutura de dados utilizada)	   
*****************************************************************************************/
int main(){
	link avl;
	bool le_hashtag = false;
	int len_mensagem = 0, indice = 0, contador = 0, conta_repeticoes = 0;
	char c, palavra[MAXCHAR];
	Item aux, max_hashtag=NULL;
	AVLinicializa(&avl);

	while (1){
		c = getchar();
		switch (c){
			case 'a':
				c = getchar();
				len_mensagem = 0;
				
				while((c = getchar()))
				{ 
					len_mensagem++;
					
					if(e_caracter_branco(c) && le_hashtag){
						le_hashtag = false;
						palavra[indice] = '\0';
						indice = 0;
						aux = AVLprocura(avl, palavra);

						if (aux == NULLitem){
							contador++;
							conta_repeticoes++;

							AVLinsere(&avl, NOVOItem(palavra, 1));

							if (max_hashtag != NULL){
								//verifica a hashtag mais popular
								if (1 == max_hashtag->repeticoes && strcmp(palavra, max_hashtag->hashtag) < 0){
									max_hashtag = AVLprocura(avl, palavra);
								}
							}
							else
								max_hashtag = AVLprocura(avl, palavra);
						}
						else{
							aux->repeticoes++;

							//verifica a hashtag mais popular
							if (aux->repeticoes > max_hashtag->repeticoes){
								max_hashtag = aux;
							} else if (aux->repeticoes == max_hashtag->repeticoes && strcmp(palavra, max_hashtag->hashtag) < 0){
								max_hashtag = aux;
							}

							conta_repeticoes++;
						}
					}
					if(le_hashtag){
						if (c >= 65 && c <= 90)
							palavra[indice++] = tolower(c);
						else
							palavra[indice++] = c;
					}

					if (c == '#' && !(le_hashtag)){
						le_hashtag = true;
					}
					if (c == '\n' || len_mensagem == MAXCHAR)
						break;
				}
				break;

			case 's':
				printf("%d %d\n", contador, conta_repeticoes);
				break;

			case 'm':
				if (max_hashtag != NULL)
					printf("#%s %d\n", max_hashtag->hashtag, max_hashtag->repeticoes);
				break;

			case 'l':
			{
				Item *vetor;
				int i=0,a=0;
				vetor=(Item*)malloc(sizeof(Item)*contador);
				AVL_para_array(avl,vetor,&a);
				qsort(vetor, contador, sizeof(Item), ordenaHashtags); //Ordena com QuickSort ~(N log N)~
				for(i=0;i<contador;i++){
					printf("#%s %d\n",vetor[i]-> hashtag,vetor[i]->repeticoes);
				}
				free(vetor);
				break;
			}
		}
		if (c == 'x'){
			AVLliberta(&avl);
			return 0;
		}
	}
	return 0;
}
