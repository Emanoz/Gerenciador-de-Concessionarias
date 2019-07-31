//Emanuel M.lourencon 
//Luiza Helena Camargo 

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct endereco {
	char logradouro[80];
	char bairro[15];
	char CEP[10];
	char cidade[15];
	char estado[3];
	char fone[12];
	char email[40];
} endereco;

typedef struct infocarro {
	char sigla;
	int regcarro;
} infocarro;

typedef union dadoscarro {
	char sigla;
	infocarro reservado;
} dadoscarro;

typedef struct loja {
	int regloja; //gerar automático
	char nome[30];
	char CNPJ[19];
	endereco end;
	int sold;
	int reserved;
	dadoscarro tabela[3];
} loja;

typedef struct infoloja {
	char sigla;
	char CNPJ[19];
} infoloja;

typedef union dadosloja {
	char sigla;
	infoloja reserva;
} dadosloja;

typedef struct montadora
{
	int regcarro; //gerar automático
	char modelo[20];
	char cor[10];
	float valor;
	dadosloja status;
} montadora;

void cad_endereco(loja *p);
void cad_loja(loja *p);
void aloca_loja(loja **p, int tam);
void cad_montadora(montadora *car);
void grava(loja *p);
int verifica(char *op);
void consultar_loja(loja *p, char *cnpj);
void grava_carro(montadora *p);
void cad_carro(montadora *carro);
void aloca_carro(montadora **p, int tam);
void consulta_carro(montadora *p, int op);
void reserva_carro(loja *p_loja, montadora *p_carro, char *cnpj);
void termino(montadora *p_carro, loja *p_loja);
int busca(loja *p_loja, char *cnpj);

int main()
{
	loja *p_loja = NULL;
	montadora *p_carro = NULL;
	int i, opcao, opp;
	char op, aux[19];
	 
	aloca_loja(&p_loja, 1);
	aloca_carro(&p_carro, 1);
	
	do
	{
		system("cls");
		printf("[1] - Cadastrar concessionaria\n[2] - Cadastrar carro\n[3] - Reserva de carros\n[4] - Terminar reserva\n[5] - Consulta concessionaria\n[6] - Consulta carro\n[0] - Sair\n\nInforme a opcao desejada: ");
		scanf("%i", &opcao);
		system("cls");
		
		switch(opcao)
		{
			case 1: cad_loja(p_loja);
					break;
			case 2: cad_carro(p_carro);
					break;
			case 3: printf("Informe o CNPJ da concessionaria para a reserva de carro: ");
					fflush(stdin);
					gets(aux);
					reserva_carro(p_loja, p_carro, aux);
					break;
			case 4: termino(p_carro, p_loja);
					break;
			case 5: printf("Informe o CNPJ da concessionaria a ser consultada: ");
					fflush(stdin);
					gets(aux);
					consultar_loja(p_loja, aux);
					break;
			case 6: system("cls");
					do{
					printf("\n[1] - Total\n[2] - Parcial\n[3] - Modelo\n\nOpcao desejada: ");
					scanf("%i", &opp);
					if(opp > 0 && opp < 4)
						consulta_carro(p_carro, opp);
					else
						printf("\nOpcao invalida!\n\n");
					}while (opp<1 || opp > 3);
					break;
			case 0: exit(1);
					break;
			default: printf("Esta opcao nao existe! Tente novamente\n");
					 break;					
		}
		printf("\n\nDeseja retomar ao menu <S/N>: ");
		fflush(stdin);
		scanf("%c", &op);
	} while(op == 's' || op == 'S');
	
	return 0;
}

void aloca_loja(loja **p, int tam)
{
	if((*p = (loja *) realloc(*p, tam * sizeof(loja))) == NULL)
		exit(1);
}		

void cad_loja(loja *p)
{
	int tam = verifica("concessionaria"), i;
	
	if(tam < 5)
	{
		printf("Registro: %i\n", tam+1);
		p->regloja = tam+1;
		printf("Nome: ");
		fflush(stdin);
		gets(p->nome);
		printf("CNPJ: ");
		fflush(stdin);
		gets(p->CNPJ);
		printf("Logradouro: ");
		fflush(stdin);
		gets(p->end.logradouro);
		printf("Bairro: ");
		fflush(stdin);
		gets(p->end.bairro);
		printf("CEP: ");
		fflush(stdin);
		gets(p->end.CEP);
		printf("Cidade: ");
		fflush(stdin);
		gets(p->end.cidade);
		printf("Estado: ");
		fflush(stdin);
		gets(p->end.estado);
		printf("Fone: ");
		fflush(stdin);
		gets(p->end.fone);
		printf("Email: ");
		fflush(stdin);
		gets(p->end.email);
		p->sold = 0;
		p->reserved = 0;
		for(i = 0; i < 3; i++)
			p->tabela[i].sigla = 'L';
		grava(p);
		printf("Registro cadastrado com sucesso!");
	}
	else
		printf("O limite maximo de concessionarias cadastradas ja foi excedido!");
}

void cad_endereco(loja *p)
{
	
}

void grava(loja *p)
{	
	FILE *fptr=NULL;
	
	if((fptr=fopen("concessionaria.bin","ab"))==NULL)
		printf("Erro ao abrir o arquivo.");
	else
		fwrite(p,sizeof(loja),1,fptr);
	fclose(fptr);
	
}

void consultar_loja(loja *p, char *cnpj)
{
	FILE *fptr = NULL;
	int tam = verifica("concessionaria"), i, j;
	if((fptr = fopen("concessionaria.bin", "rb")) == NULL)
		exit(1);
	else
	{
		for(i = 0; i < tam; i++)
		{
			fseek(fptr, i*sizeof(loja), 0);
			fread(p, sizeof(loja), 1, fptr);
			if(strcmp(cnpj, p->CNPJ) == 0)
			{
				printf("Nome: %s\nVendido: %i\nReservado: %i\n", p->nome, p->sold, p->reserved);
				for(j = 0; j < 3; j++)
				{
					if(p->tabela[j].sigla != 'L')
						printf("\n%c - %i", p->tabela->reservado.sigla, p->tabela->reservado.regcarro);

				}
			}
			printf("\n");		
		}
		fclose(fptr);
	}
}

int verifica(char *op)
{
	long int count = 0;
	FILE *fptr = NULL;
	
	if(strcmp(op, "concessionaria") == 0)
	{
		if((fptr = fopen("concessionaria.bin", "rb")) != NULL)
		{
			fseek(fptr, 0, 2);
			count = ftell(fptr) / sizeof(loja);
			fclose(fptr);
		}
	}
	else
	{
		if((fptr = fopen("carro.bin", "rb")) != NULL)
		{
			fseek(fptr, 0, 2);
			count = ftell(fptr) / sizeof(montadora);
			fclose(fptr);
		}
	}
	return count;
}

void cad_carro(montadora *p)
{
	FILE *fptr = NULL;
	int tam = verifica("carro");
	
	if(tam < 50)
	{
		p->regcarro = tam+1;
		printf("Registro: %i\n", p->regcarro);
		printf("Modelo: ");
		fflush(stdin);
		gets(p->modelo);
		printf("Cor: ");
		fflush(stdin);
		gets(p->cor);
		printf("Preco: ");
		scanf("%f", &p->valor);
		p->status.sigla = 'L';
		
		grava_carro(p);
		printf("cadastrado com sucesso!");
	}
	else
		printf("Limite maximo de carros cadastrados atingido!");
	
}

void grava_carro(montadora *p)
{
	FILE *fptr = NULL;
	
	if((fptr = fopen("carro.bin", "ab")) == NULL)
		printf("Erro ao abrir o arquivo 'carro.bin'");
	else
		fwrite(p, sizeof(montadora), 1, fptr);
	fclose(fptr);
}

void aloca_carro(montadora **p, int tam)
{
	if((*p = (montadora *) realloc(*p, tam * sizeof(montadora))) == NULL)
		exit(1);
}

void consulta_carro(montadora *p, int op)
{
	FILE *fptr = NULL;
	int tam = verifica("carro"), i;
	char opp, modelo[20];
	
	if((fptr = fopen("carro.bin", "rb")) == NULL)
		printf("Nao foi possivel abrir o arquivo 'carro.bin'");
	else
	{
		if(op == 2)
		{
			printf("Informe a opcao de consulta <R/L>: ");
			fflush(stdin);
			scanf("%c", &opp);
		}
		else if(op == 3)
		{
			printf("Escolha o modelo: ");
			fflush(stdin);
			gets(modelo);
		}
		for(i = 0; i < tam; i++)
		{
			fseek(fptr, i*sizeof(montadora), 0);
			fread(p, sizeof(montadora), 1, fptr);
			if(op == 1) //total
			{
				printf("Registro: %i\nModelo: %s\nCor: %s\nValor: %.2f\nStatus: ", p->regcarro, p->modelo, p->cor, p->valor);
				if(p->status.sigla == 'L')
					printf("L\n");
				else 
					printf("%c - %s\n", p->status.reserva.sigla, p->status.reserva.CNPJ);
			}
			else if(op == 2)
			{
				if(opp == 'L' && p->status.sigla == 'L')
					printf("Registro: %i\nModelo: %s\nCor: %s\nValor: %.2f\nStatus: %c\n", p->regcarro, p->modelo, p->cor, p->valor,p->status.sigla);
				else if(opp == 'R' && p->status.sigla == 'R')
					printf("Registro: %i\nModelo: %s\nCor: %s\nValor: %.2f\nStatus: %c - %s\n", p->regcarro, p->modelo, p->cor, p->valor, p->status.reserva.sigla, p->status.reserva.CNPJ);
			}
			else if(op == 3)
			{
				if(strcmp(modelo, p->modelo) == 0)
				{
					printf("Registro: %i\nModelo: %s\nCor: %s\nValor: %.2f\nStatus: ", p->regcarro, p->modelo, p->cor, p->valor);
					if(p->status.sigla == 'L')
						printf("L\n");
					else
						printf("%c - %s\n", p->status.reserva.sigla, p->status.reserva.CNPJ);
				}
			}
			printf("\n\n");
		}
		fclose(fptr);
	}
}

void reserva_carro(loja *p_loja, montadora *p_carro, char *cnpj)
{	
	int i, tam_loja = verifica("concessionaria"), tam_carro = verifica("carro"), reg, j, k;
	FILE *fptr_loja= NULL, *fptr_carro = NULL;
	
	if((fptr_loja = fopen("concessionaria.bin", "rb+")) == NULL)
		printf("Erro ao abrir o arquivo 'concessionaria.bin'");
	else
	{
		for(i = 0; i < tam_loja; i++)
		{
			fseek(fptr_loja, i*sizeof(loja), 0);
			fread(p_loja, sizeof(loja), 1, fptr_loja);
			if(strcmp(p_loja->CNPJ, cnpj) == 0)
			{
				if(p_loja->reserved < 3)
				{
					consulta_carro(p_carro, 1);
					printf("Informe o numero do registro do carro a ser reservado: ");
					scanf("%i", &reg);
					if((fptr_carro = fopen("carro.bin", "rb+")) == NULL)
						printf("Erro ao abrir o arquivo 'carro.bin'");
					else
					{
						for(j = 0; j < tam_carro; j++)
						{
							fseek(fptr_carro, j*sizeof(montadora), 0);
							fread(p_carro, sizeof(montadora), 1, fptr_carro);
							if(reg == p_carro->regcarro)
							{
								if(p_carro->status.sigla == 'L')
								{
									p_carro->status.reserva.sigla = 'R';
									strcpy(p_carro->status.reserva.CNPJ, cnpj);
									for(k = 0; k < 3; k++)
									{
										if(p_loja->tabela[k].sigla == 'L')
										{
											p_loja->tabela[k].reservado.sigla = 'R';
											p_loja->tabela[k].reservado.regcarro = reg;
											break;
										}
									}
									p_loja->reserved += 1;
									
									fseek(fptr_loja, i*sizeof(loja), 0);
									fwrite(p_loja, sizeof(loja), 1, fptr_loja);
									fseek(fptr_carro, j*sizeof(montadora), 0);
									fwrite(p_carro, sizeof(montadora), 1, fptr_carro);
									
									printf("Carro reservado.\n");
								}
								else
									printf("Este carro nao esta disponivel!");
							}
						}
						fclose(fptr_carro);
					}
				}
				else
					printf("Limite de carros reservados excedido");
			}
				
		}
		fclose(fptr_loja);
	}
}

void termino(montadora *p_carro, loja *p_loja)
{
	FILE *fptr_carro = NULL, *fptr_loja = NULL;
	int i , tam_carro = verifica("carro"), reg, op, reg_loja, j;
	
	system("cls");
	consulta_carro(p_carro, 1);
	printf("Informe o registro do carro a ser realizado o termino da reserva: ");
	scanf("%i", &reg);
	
	if((fptr_carro = fopen("carro.bin", "rb+")) == 0)
		printf("Erro ao abrir o arquivo 'carro.bin'");
	else
	{
		for(i = 0; i < tam_carro; i++)
		{
			fseek(fptr_carro, i*sizeof(montadora), 0);
			fread(p_carro, sizeof(montadora), 1, fptr_carro);
			if(p_carro->regcarro == reg)
			{
				if(p_carro->status.sigla != 'L')
				{
					reg_loja = busca(p_loja, p_carro->status.reserva.CNPJ);
					printf("O carro selecionado sera comprado [1] ou liberado da reserva [2]: ");
					scanf("%i", &op);
					if(op == 1)
					{
						strcpy(p_carro->modelo, "vago");
						strcpy(p_carro->cor, "vago");
						p_carro->valor = 0;
					}
					p_carro->status.sigla = 'L';
					if((fptr_loja = fopen("concessionaria.bin", "rb+")) == 0)
						printf("Erro ao abrir o arquivo 'concessionaria.bin'");
					else
					{
						fseek(fptr_loja, reg_loja*sizeof(loja), 0);
						fread(p_loja, sizeof(loja), 1, fptr_loja);
						for(j = 0; j < 3; j++)
						{
							if(p_loja->tabela[j].reservado.regcarro == reg)
								p_loja->tabela[j].sigla = 'L';
						}
						if(op == 1)
						{
							p_loja->reserved -= 1;
							p_loja->sold += 1;
						}
						else
							p_loja->reserved -= 1;
						fseek(fptr_loja, reg_loja*sizeof(loja), 0);
						fwrite(p_loja, sizeof(loja), 1, fptr_loja);
						fclose(fptr_loja);
					}
					fseek(fptr_carro, i*sizeof(montadora), 0);
					fwrite(p_carro, sizeof(montadora), 1, fptr_carro);
					fclose(fptr_carro);
					
					printf("Termino de reserva realizado com sucesso!");
					break;
				}
			}	
		}
		printf("Este carro ja foi vendido ou ainda nao foi reservado!");	
	}	
	
}

int busca(loja *p_loja, char *cnpj)
{
	FILE *fptr = NULL;
	int i, result = -1, tam = verifica("concessionaria");
	
	if((fptr = fopen("concessionaria.bin", "rb")) == NULL)
		printf("Erro ao abrir o arquivo 'carro.bin'");
	else
	{
		for(i = 0; i < tam; i++)
		{
			fseek(fptr, i*sizeof(loja), 0);
			fread(p_loja, sizeof(loja), 1, fptr);
			if(strcmp(p_loja->CNPJ, cnpj) == 0)
			{
				result = i;
				break;
			}
		}
		fclose(fptr);
	}
	return result;						
}











































