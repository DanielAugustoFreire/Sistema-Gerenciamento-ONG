/*
Cada voluntário pode estar em um ou mais projetos
para cada projeto pode-se ter uma ou mais empresas parceiras
*/


#include <stdio.h>
#include <string.h>
#include<windows.h>
#include<stdlib.h>
#include <ctype.h>
#define TF 10
//Struct Data
typedef struct{
	int dia, mes, ano;
}data;

//Struct Endereço
typedef struct{
	char rua[30], bairro[20], cidade[20];
	int num;
}endereco;
//Struct Pessoa para usar em Geral com data de nascimento
typedef struct{
	char nome[50],telefone[20],CPF[15];
	data data_nasc;
}pessoa;

//Struct Doação
typedef struct{
	char tipo[40], descricao[40],o_que[50],pres_din;
	int cod;
	pessoa p_d;//Pessoa nome e data de nascimento
}doar_;






//Struct Projeto/Horas para o voluntario
typedef struct{
	int cod_projetos;//quais projetos participa, Inserir codigo do projeto
	int horas_cada;//Quantas Horas participa de cada Projeto
}Projeto_ind;

//Struct Voluntario
typedef struct{
	int id;//ID unico por voluntario
	pessoa p_v;//Pessoa e data de nascimento
	endereco end;
	Projeto_ind projeto;//***Lembrar, fazer um Vetor para o voluntario participar mais de um projeto.
}voluntario;

//Struct Empresa
typedef struct{
    int codigo;
    char nome[20],CNPJ;
    endereco end;
}empresa;//***Lembrar, fazer um Vetor para empresa quando for registrar o projeto

//struct Projeto
typedef struct{
    int codigo;//Codigo 0, nao existe projeto
    char descricao[100], local[50], atividade[50];
    int cod_empresa;//Codigo das Empresas participante do Projeto.	proj.cod_empresa[i]
    data d_p;//data do Projeto
}projeto;

void  cadastrarVoluntario()
{
	SYSTEMTIME st;
	// Obtém a data e a hora locais
    GetLocalTime(&st);
	int ano_atual= st.wYear;//armazenar o ano atual em uma variavel
	FILE* cadastro;
	voluntario vol;
	int retorno;
	char confirmacao;
	
	cadastro=fopen("voluntarios.bin","ab+");
	if(cadastro==NULL)
		printf("\nErro na abertura do arquivo, tento novamente mais tarde");
	else{
		system("cls");
		printf("\nBem Vindo");
		printf("\n---Cadastro de Voluntario---");
		do{
			printf("\nID: ");
			do{		
				scanf("%d",&vol.id);
				retorno=buscaV(cadastro,vol.id);
				
				if(retorno==0)
					printf("\nId de voluntario Existente\nDigite um ID que nao tenha sido utilizado: ");
				
			}while(retorno==0);

			printf("\nNome: ");
			fflush(stdin);
			gets(vol.p_v.nome);
			
			printf("\nCPF: ");
			fflush(stdin);
			gets(vol.p_v.CPF);
			
			printf("\nTelefone: ");
			fflush(stdin);
			gets(vol.p_v.telefone);
			
			do
			{
				printf("\nData de Nascimento (dd/mm/aa):");
				scanf("%d %d %d",&vol.p_v.data_nasc.dia,&vol.p_v.data_nasc.mes,&vol.p_v.data_nasc.ano);
				
				if(vol.p_v.data_nasc.dia<1||vol.p_v.data_nasc.dia>31||vol.p_v.data_nasc.mes<1||vol.p_v.data_nasc.mes>12||vol.p_v.data_nasc.ano<(ano_atual-150)||vol.p_v.data_nasc.ano>(ano_atual-18))
				{
					printf("\nData Inserida Invalida");
					if(vol.p_v.data_nasc.dia<1||vol.p_v.data_nasc.dia>31)
						printf("\nO Dia %d nao existe, ele tem que estar no intervalo de 1 a 31",vol.p_v.data_nasc.dia);
					if(vol.p_v.data_nasc.mes<1||vol.p_v.data_nasc.mes>12)
						printf("\nO Mes %d nao existe, ele tem que estar no intervalo do mes 1 ao 12",vol.p_v.data_nasc.mes);
					if(vol.p_v.data_nasc.ano<(ano_atual-150)||vol.p_v.data_nasc.ano>ano_atual-18)
					{
						if(vol.p_v.data_nasc.ano<(ano_atual-150))
							printf("\nCaso voce tenha %d anos, favor entre em contato com o suporte",ano_atual-vol.p_v.data_nasc.ano);
						if(vol.p_v.data_nasc.ano>(ano_atual-18))
							printf("\nNossa Ong nao aceita menores de 18 anos como voluntario, por favor leia os termos de contrato da ONG ");
					}
					printf("\n\n");
				}
			}while(vol.p_v.data_nasc.dia<1||vol.p_v.data_nasc.dia>31||vol.p_v.data_nasc.mes<1||vol.p_v.data_nasc.mes>12||vol.p_v.data_nasc.ano<(ano_atual-150)||vol.p_v.data_nasc.ano>(ano_atual-18));
			
			printf("\n---Endereco---");
			printf("\nRua: ");
			fflush(stdin);
			gets(vol.end.rua);
			
			printf("\nNumero da Casa: ");
			scanf("%d",&vol.end.num);
			
			printf("\nBairro: ");
			fflush(stdin);
			gets(vol.end.bairro);
			
			printf("\nCidade: ");
			fflush(stdin);
			gets(vol.end.cidade);
			
			fwrite(&vol,sizeof(voluntario),1,cadastro);//Cadastrar Voluntarios
			
			printf("\nCadastro feito com Sucesso\n\n");
			
			printf("\nDeseja Continuar?\nUse S/N\n");
			scanf(" %c",&confirmacao);
			confirmacao=toupper(confirmacao);
			
			if(confirmacao=='S')
				system("cls");
		}while(confirmacao=='S');
		fclose(cadastro);
	}
}

//Funcao para buscar o ID e nao ser registrado o mesmo ID de Voluntario.
int buscaV(FILE *busca,int idVol)
{
	voluntario vol;

	rewind(busca);
	fread(&vol,sizeof(voluntario),1,busca);
	while(!feof(busca))
	{
		if(idVol==vol.id)
			return 0;	
		else
			return 1;
	}
}

void cadastrarEmpresa()
{
	int retorno;
	char continuar;
	FILE* cadastro;
	empresa emp;
	cadastro=fopen("empresas.bin","ab+");
	if(cadastro==NULL)
		printf("\nErro na abertura do arquivo");
	else
	{
		system("cls");
		printf("\nBem Vindo");
		printf("\n---Cadastro de Empresas---");
		do{
			printf("\nCodigo: ");
			do{
				scanf("%d",&emp.codigo);
				retorno = buscaE(cadastro, emp.codigo);
				
				if(retorno==0)
					printf("\nCodigo de Empresa ja cadastrado\nDigite um codigo valido: ");
				
			}while(retorno==0)
		
			printf("\nNome da Empresa: ");
			fflush(stdin);
			gets(emp.nome);
			
			printf("\nCNPJ: ");
			fflush(stdin);
			gets(emp.CNPJ);
			
			printf("\nEndereco:");
			printf("\n\nRua: ");
			fflush(stdin);
			gets(emp.end.rua);
			
			printf("\nNumero: ");
			scanf("%d",&emp.end.num)
			
			printf("\nBairro: ");
			fflush(stdin);
			gets(emp.end.bairro);
			
			printf("\nCidade: ");
			fflush(stdin);
			gets(emp.end.cidade);
				
			fwrite(&emp,sizeof(empresa),1,cadastro);
		
			printf("\nCadastro feito com Sucesso\n\n");
			
			printf("\nDeseja Continuar?\nUse S/N\n");
			scanf(" %c",&confirmacao);
			confirmacao=toupper(confirmacao);
			
			if(confirmacao=='S')
				system("cls");
		}while(confirmacao=='S');
		fclose(cadastro);
	}
}

buscaE(FILE* busca, int codigo)
{
	empresa emp;

	rewind(busca);
	fread(&emp,sizeof(empresa),1,busca);
	while(!feof(busca))
	{
		if(codigo==emp.codigo)
			return 0;	
		else
			return 1;
	}
}
void cadastrarProjeto()
{
	printf("\nArea em Contrucao\n");
}

void excluirVoluntario()
{
	printf("\nArea em Contrucao\n");
}

void excluirEmpresa()
{
	printf("\nArea em Contrucao\n");
}

void excluirProjeto()
{
	printf("\nArea em Contrucao\n");
}

void lancarHoras()
{
	printf("\nArea em Contrucao\n");
}

void verVoluntario()
{
	printf("\nArea em Contrucao\n");
}

void verEmpresa()
{
	printf("\nArea em Contrucao\n");
}

void verProjeto()
{
	printf("\nArea em Contrucao\n");
}

void verHoras()
{
	printf("\nArea em Contrucao\n");
}

void editarVoluntario()
{
	printf("\nArea em Contrucao\n");
}

void editarEmpresa()
{
	printf("\nArea em Contrucao\n");
}

void editarProjeto()
{
	printf("\nArea em Contrucao\n");
}

int opcao_sel()
{
	int retorno;

	system("cls"); 
	printf("Bem-vindo!\n\n");
	do
	{

		printf("Menu:\n");
	    printf("1. Cadastro\n");//case 1
	    printf("2. Exclusao\n");//case 2
	    printf("3. Lancamento\n");//case 3
	    printf("4. Relatorio\n");//case 4
	    printf("5. Editar\n");//case 5
	    printf("6. Doacao\n");//case 6
	    printf("7. Finalizar\n\n");//case 7
	    
    	printf("Digite o numero correspondente a opcao desejada: ");
    	scanf("%d", &retorno);
    	
    	if(retorno<1||retorno>7)
    	{
    		system("cls");
    		printf("\nSelecione uma opcao Valida\n\n");	
    	}
    	
	}while(retorno<1||retorno>7);
	
	return retorno;
}
int op_cadastro()//case 1
{
	int retorno;
	
	system("cls");
	
	do
	{
		printf("\nMenu de Cadastro:\n");
	    printf("1. Voluntario \n");
    	printf("2. Empresa\n");
    	printf("3. Projeto\n");
    	printf("4. Retornar\n\n");
    
    	printf("Digite o numero correspondente a opcao desejada: ");
   		scanf("%d", &retorno);
   		
    	if(retorno<1||retorno>4)
    	{
    		system("cls");
    		printf("\nInsira uma opcao valida\n");
    	}
	}while(retorno<1||retorno>4);
	
	return retorno;
                
}
int op_exclusao()//case 2
{
	int retorno;
	system("cls");	
	do
	{
		printf("\nMenu de Exclusao:\n");
		printf("1. Voluntario \n");
		printf("2. Empresa\n");
		printf("3. Projeto\n");
		printf("4. Retornar\n\n");
	
		printf("Digite o numero correspondente a opcao desejada: ");
		scanf("%d", &retorno);
	
		if(retorno<1||retorno>4)
		{
			system("cls");
    		printf("\nInsira uma opcao valida\n\n");
    	}
	}while(retorno<1||retorno>4);
	
	return retorno;
}
int op_relatorio()//case 4
{
	int retorno;
	
	
	do
	{
		printf("\nMenu de Relatorio:\n");
		printf("1. Voluntario \n");
		printf("2. Empresa\n");
		printf("3. Projeto\n");
		printf("4. Horas\n");
		printf("5. Retornar\n\n");
		
		printf("Digite o numero correspondente a opcao desejada: ");
		scanf("%d", &retorno);
		
		if(retorno<1||retorno>5)
		{
			system("cls");
			printf("\nInsira uma opcao valida\n\n");
		}	
		
	}while(retorno<1||retorno>5);
	return retorno;
	            
}
int op_editar()//case 5
{
	int retorno;
	
	do
	{
		printf("\nMenu de Edicao:\n");
	    printf("1. Voluntario \n");
	    printf("2. Empresa\n");
	    printf("3. Projeto\n");
	    printf("4. Retornar\n\n");
	
	    printf("Digite o numero correspondente a opcao desejada: ");
	    scanf("%d", &retorno);
	    
	    if(retorno>4||retorno<=0)
	    {
	    	system("cls");
	    	printf("\nOpcao Invalida.\n\n");
	    }
	}while(retorno>4||retorno<=0);
    
    return retorno;
}
int op_doar()//case 6
{
	int retorno;
	
	
	do
	{
		printf("\nOpcoes do Doador:\n");
		printf("1. Cadastrar Doador e tipo de Doacao\n");
		printf("2. Editar Doador\n");
		printf("3. Listar Doadores\n");
		printf("4. Excluir Doador\n(*AVISO*)\nEssa acao e irreversivel\n");
		printf("5. Retornar\n\n");
		
		printf("Digite o numero correspondente a opcao desejada: ");
		scanf("%d", &retorno);
		if(retorno<1||retorno>5)
		{
			system("cls");
			printf("\nOpcao Invalida.\n\n");	
		}
	
	}while(retorno<1||retorno>5);
}
main()
{
	voluntario vol;
	empresa emp;
	projeto pro;
	int opcao;
	int i;
	

    opcao = opcao_sel();
    while(opcao != 7)
    {
	    switch(opcao)
	    {
	    	case 1://Cadastro
	    		opcao=op_cadastro();//Menu de cadastro
                switch(opcao)
                {
                	case 1:
                        cadastrarVoluntario();
                        break;
                    case 2:
                        cadastrarEmpresa();
                        break;
                    case 3:
                        cadastrarProjeto();
                        break;
                    case 4:
                        printf("Retornando:\n");
                        break;
                }
                break;
                
            case 2://Exclusao
	            opcao=op_exclusao;//Menu de exclusao
	            switch(opcao)
                {
                	case 1:
                        excluirVoluntario();
                        break;
                    case 2:
                        excluirEmpresa();
                        break;
                    case 3:
                    	excluirProjeto();
                        break;
                    case 4:
                        printf("Retornando:\n");
                        break;
                }
                break;
                
            case 3://Lancamento de Horas
            	lancarHoras();
            	break;
            
            case 4://Relatorio
				opcao=op_relatorio;//Menu de Relatorio
	            switch(opcao)
                {
                	case 1:
                        verVoluntario();
                        break;
                    case 2:
                        verEmpresa();
                        break;
                    case 3:
                    	verProjeto();
                        break;
                    case 4:
                        verHoras();
                        break;
                    case 5:
                    printf("Retornando:\n");
                    break;
                }
                break;
            case 5://Editar
                opcao=op_editar();//Menu de Editar
                switch(opcao)
                {
                	case 1:
                        editarVoluntario();
                        break;
                    case 2:
                        editarEmpresa();
                        break;
                    case 3:
                        editarProjeto();
                        break;
                    case 4:
                        printf("Retornando:\n");
                        break;
                }
                break;
            case 6://Doacao
            	opcao=op_doar();
            	switch(opcao)
            	{
            		
            	}
            	break;
	    }
	    opcao = opcao_sel();
	    
	}
}
