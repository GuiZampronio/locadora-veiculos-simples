#include <stdio.h>
#include <string.h>

typedef enum e_cores{
	preta = 1, branca, prata
}CORES;

typedef enum e_categoria{
	hatch = 1, sedan, suv, jipe
}CATEGORIAS;

typedef enum e_tipo_pessoa{
	fisica = 1, juridica
}PESSOA_FJ;

typedef struct s_endereco{
	char rua[50];
	int numero_endereco;
	char bairro[50];
	char cidade[50];
}ENDERECO;

typedef struct s_data{
	int dia;
	int mes;
	int ano;
}DATA;

typedef struct s_cliente{
	char nome[50];
	ENDERECO endereco_cliente;
	char telefone[15];
	PESSOA_FJ tipo_pessoa;
	union u_tipo_pessoa{
		char pessoa_fisica[15];
		char pessoa_juridica[19];
	}TIPO_PESSOA;
}CLIENTE;

typedef struct s_carros{
	char renavam[12];
	char placa[9];
	char marca[50];
	char modelo[50];
	int ano;
	CORES cor;
	CATEGORIAS categoria;
	int locado;	
}CARRO;

typedef struct s_categoria{
	int valor_diaria;
	int pontos_fidelidade;
	CATEGORIAS categoria;
}INFO_CATEGORIAS;

typedef struct s_locacao{
	int cod_locacao;
	PESSOA_FJ tipo_cliente;             
	union u_cliente_locacao{
		char pessoa_fisica[15];
		char pessoa_juridica[19];
	}TIPO_CLIENTE;
	char renavam[12];
	DATA data_retirada;
	DATA data_devolucao;
	int status_locacao;   // -1 == N�o locado nesse espaco, 0 == Locacao em aberto, 1 == Locacao devolvida; 2 == Locacao cancelada;
}LOCACAO;

typedef struct s_indice{
	PESSOA_FJ tipo_pessoa;
	union u_tipo_do_cliente{
		char pessoa_fisica[15];
		char pessoa_juridica[19];
	}TIPO_PESSOAFJ;
	int posicao_matriz;
}INDICE_MATRIZ;

typedef struct s_tipocategoria{
	int qtd;
	int tipo_categoria;  // 1 == hatch , 2==sedan, 3 == suv, 4 == jipe //
}TIPOCATEGORIA;

void esvazia_structs(CLIENTE *banco_clientes, CARRO *banco_carros, LOCACAO matriz_locacao[][5], INFO_CATEGORIAS *informacoes_categorias, INDICE_MATRIZ *indice_matriz);
void cadastra_cliente(CLIENTE *banco_clientes, INDICE_MATRIZ *indice_matriz);
void atualiza_cadastro(CLIENTE *banco_clientes);
void lista_dadosCliente(CLIENTE *banco_clientes);
void cadastra_carro(CARRO *banco_carros);
void cadastra_dadoCategoria(INFO_CATEGORIAS *informacoes_categorias);
void cadastra_locacao(CLIENTE *banco_clientes, CARRO *banco_carros, LOCACAO matriz_locacao[][5], INDICE_MATRIZ *indice_matriz, int *qtd_locacao);
void devolve_carro(CLIENTE *banco_clientes, CARRO *banco_carros, LOCACAO matriz_locacao[][5], INDICE_MATRIZ *indice_matriz, INFO_CATEGORIAS *informacoes_categorias, int *qtd_locacao);
void lista_dadosLocacao(CLIENTE *banco_clientes, LOCACAO matriz_locacao[][5], INDICE_MATRIZ *indice_matriz);
void lista_locacaoCliente(CLIENTE *banco_clientes, LOCACAO matriz_locacao[][5], INDICE_MATRIZ *indice_matriz);
void lista_locacaoAberto(CLIENTE *banco_clientes, LOCACAO matriz_locacao[][5], INDICE_MATRIZ *indice_matriz);
void lista_locacaoCategoria(CLIENTE *banco_clientes, CARRO *banco_carros, LOCACAO matriz_locacao[][5], INDICE_MATRIZ *indice_matriz, TIPOCATEGORIA *vetorqtd);

int main(){
	int opcao = -1;
	int qtd_locacao = 0;
	
	LOCACAO matriz_locacao[15][5];
	CLIENTE banco_clientes[15];
	CARRO banco_carros[10];
	INFO_CATEGORIAS informacoes_categorias[4];
	INDICE_MATRIZ indice_matriz[15];
	TIPOCATEGORIA vetorqtd[4];	
	
	esvazia_structs(banco_clientes, banco_carros, matriz_locacao, informacoes_categorias, indice_matriz);
		
	while(opcao != 0){
		scanf(" %d", &opcao);
		switch(opcao){
			case 0:{
				break;
			}
			case 1:{
				cadastra_cliente(banco_clientes, indice_matriz);
				break;
			}
			case 2:{
				atualiza_cadastro(banco_clientes);
				break;
			}
			case 3:{
				lista_dadosCliente(banco_clientes);
				break;
			}
			case 4:{
				cadastra_carro(banco_carros);
				break;
			}
			case 5:{
				cadastra_dadoCategoria(informacoes_categorias);
				break;
			}
			case 6:{
				cadastra_locacao(banco_clientes, banco_carros, matriz_locacao, indice_matriz, &qtd_locacao);
				break;
			}
			case 7:{
				devolve_carro(banco_clientes, banco_carros, matriz_locacao, indice_matriz, informacoes_categorias, &qtd_locacao);
				break;
			}
			case 8:{
				lista_dadosLocacao(banco_clientes, matriz_locacao, indice_matriz);
				break;
			}
			case 9:{
				lista_locacaoCliente(banco_clientes, matriz_locacao, indice_matriz);
				break;
			}
			case 10:{
				lista_locacaoAberto(banco_clientes, matriz_locacao, indice_matriz);
				break;
			}
			case 11:{
				lista_locacaoCategoria(banco_clientes, banco_carros, matriz_locacao, indice_matriz, vetorqtd);
				break;
			}
			default:{
				printf("ERRO: opcao invalida\n");
				break;
			}
		}	
	}
}

void esvazia_structs(CLIENTE *banco_clientes, CARRO *banco_carros, LOCACAO matriz_locacao[][5], INFO_CATEGORIAS *informacoes_categorias, INDICE_MATRIZ *indice_matriz){
	int i, j;
	
	for(i=0; i<15; i++){
		strcpy(banco_clientes[i].nome, " ");
		strcpy(banco_clientes[i].endereco_cliente.bairro, " ");
		strcpy(banco_clientes[i].endereco_cliente.cidade, " ");
		strcpy(banco_clientes[i].endereco_cliente.rua, " ");
		strcpy(banco_clientes[i].telefone, " ");
		strcpy(banco_clientes[i].TIPO_PESSOA.pessoa_fisica, " ");
		strcpy(banco_clientes[i].TIPO_PESSOA.pessoa_juridica, " ");
		banco_clientes[i].endereco_cliente.numero_endereco = 0;
	}
	
	for(i=0; i<10; i++){
		strcpy(banco_carros[i].marca, " ");
		strcpy(banco_carros[i].modelo, " ");
		strcpy(banco_carros[i].placa, " ");
		strcpy(banco_carros[i].renavam, " ");
		banco_carros[i].ano = 0;
		banco_carros[i].categoria = 0;
		banco_carros[i].cor = 0;
	}
	
	for(i=0; i<15; i++){
		for(j=0; j<5; j++){
			strcpy(matriz_locacao[i][j].renavam, " ");
			strcpy(matriz_locacao[i][j].TIPO_CLIENTE.pessoa_fisica, " ");
			strcpy(matriz_locacao[i][j].TIPO_CLIENTE.pessoa_juridica, " ");
			matriz_locacao[i][j].cod_locacao = 1000;
			matriz_locacao[i][j].data_retirada.ano = 0;
			matriz_locacao[i][j].data_retirada.dia = 0;
			matriz_locacao[i][j].data_retirada.mes = 0;
			matriz_locacao[i][j].data_devolucao.ano = -1;
			matriz_locacao[i][j].data_devolucao.dia = -1;
			matriz_locacao[i][j].data_devolucao.mes = -1;
			matriz_locacao[i][j].tipo_cliente = 0;
			matriz_locacao[i][j].status_locacao = -1;
		}
	}
	
	for(i=0; i<4; i++){
		informacoes_categorias[i].pontos_fidelidade = 0;
		informacoes_categorias[i].valor_diaria = 0;
	}
	
	for(i=0; i<15; i++){
		indice_matriz[i].posicao_matriz = -1;
		indice_matriz[i].tipo_pessoa = 0;
		strcpy(indice_matriz[i].TIPO_PESSOAFJ.pessoa_fisica, " ");
		strcpy(indice_matriz[i].TIPO_PESSOAFJ.pessoa_juridica, " ");
	}
}

void cadastra_cliente(CLIENTE *banco_clientes, INDICE_MATRIZ *indice_matriz){
	int recebeTipoCliente;
	int i;
	int cont, comparacao;
	PESSOA_FJ tipocliente;
	cont = 0;
	char recebeCNPJ[19];
	char recebeCPF[15];
	
	for(i=0; i<15; i++){
		if(banco_clientes[i].endereco_cliente.numero_endereco != 0){
			cont++;
		}
	}
	
	if(cont == 15){
		printf("ERRO: sem espaco\n");
		return;
	}
	
	scanf(" %d", &recebeTipoCliente);
	
	if(recebeTipoCliente == 1){
		tipocliente = fisica;
		scanf(" %s", recebeCPF); 
		for(i=0; i<15; i++){
			comparacao = strcmp(banco_clientes[i].TIPO_PESSOA.pessoa_fisica, recebeCPF);
			if(comparacao == 0){
				printf("ERRO: ja cadastrado\n");
				return;
			}
		}	
	}
	if(recebeTipoCliente == 2){
		tipocliente = juridica;
		scanf(" %s", recebeCNPJ);
		for(i=0; i<15; i++){
			comparacao = strcmp(banco_clientes[i].TIPO_PESSOA.pessoa_juridica, recebeCNPJ);
			if(comparacao == 0){
				printf("ERRO: ja cadastrado\n");
				return;
			}
		}
	}
	
	if((recebeTipoCliente != 1) && (recebeTipoCliente != 2)){
		printf("ERRO: opcao invalida\n");
		return;
	}
	
	char recebeNome[50], recebeRua[50], recebeBairro[50], recebeCidade[50], recebeTelefone[15];
	int recebeNumCasa;
	
	scanf(" %[^\n]", recebeNome);
	scanf(" %[^\n]", recebeRua);
	scanf(" %d", &recebeNumCasa);
	scanf(" %[^\n]", recebeBairro);
	scanf(" %[^\n]", recebeCidade);
	scanf(" %s", recebeTelefone);   
	
	
	for(i=0; i<15; i++){
		if(banco_clientes[i].endereco_cliente.numero_endereco == 0){
			if(tipocliente == fisica){
				strcpy(banco_clientes[i].nome, recebeNome);
				strcpy(banco_clientes[i].telefone, recebeTelefone);
				strcpy(banco_clientes[i].endereco_cliente.bairro, recebeBairro);
				strcpy(banco_clientes[i].endereco_cliente.cidade, recebeCidade);
				strcpy(banco_clientes[i].endereco_cliente.rua, recebeRua);
				strcpy(banco_clientes[i].TIPO_PESSOA.pessoa_fisica, recebeCPF);
				strcpy(indice_matriz[i].TIPO_PESSOAFJ.pessoa_fisica, recebeCPF);
				banco_clientes[i].endereco_cliente.numero_endereco = recebeNumCasa;
				banco_clientes[i].tipo_pessoa = fisica;
				indice_matriz[i].tipo_pessoa = fisica;
				printf("Cadastrado com Sucesso\n");
				return;
			}
			if(tipocliente == juridica){
				strcpy(banco_clientes[i].nome, recebeNome);
				strcpy(banco_clientes[i].telefone, recebeTelefone);
				strcpy(banco_clientes[i].endereco_cliente.bairro, recebeBairro);
				strcpy(banco_clientes[i].endereco_cliente.cidade, recebeCidade);
				strcpy(banco_clientes[i].endereco_cliente.rua, recebeRua);
				strcpy(banco_clientes[i].TIPO_PESSOA.pessoa_juridica, recebeCNPJ);
				strcpy(indice_matriz[i].TIPO_PESSOAFJ.pessoa_juridica, recebeCNPJ);
				banco_clientes[i].endereco_cliente.numero_endereco = recebeNumCasa;
				banco_clientes[i].tipo_pessoa = juridica;
				indice_matriz[i].tipo_pessoa = juridica;
				printf("Cadastrado com Sucesso\n");
				return;
			}
		}
	}
}

void atualiza_cadastro(CLIENTE *banco_clientes){
	int recebeTipoCliente;
	int i, cont, comparacao, opcao;
	char recebeCPF[15], recebeCNPJ[19];
	
	scanf(" %d", &recebeTipoCliente);
	
	if(recebeTipoCliente == 1){
		cont = 0;
		scanf(" %s", recebeCPF);
		for(i=0; i<15; i++){
			comparacao = strcmp(banco_clientes[i].TIPO_PESSOA.pessoa_fisica, recebeCPF);
			if(comparacao != 0){
				cont++;
			}
		}
		if(cont == 15){
			printf("ERRO: nao cadastrado\n");
			return;
		}
	}
	if(recebeTipoCliente == 2){
		cont = 0;
		scanf(" %s", recebeCNPJ);
		for(i=0; i<15; i++){
			comparacao = strcmp(banco_clientes[i].TIPO_PESSOA.pessoa_juridica, recebeCNPJ);
			if(comparacao != 0){
				cont++;
			}
		}
		if(cont == 15){
			printf("ERRO: nao cadastrado\n");
			return;
		} 
	}
	if((recebeTipoCliente != 1) && (recebeTipoCliente != 2)){
		printf("ERRO: opcao invalida\n");
		return;	
	}
	
	scanf(" %d", &opcao);
	
	if(opcao == 1){
		char recebeRua[50], recebeBairro[50], recebeCidade[50];
		int recebeNumCasa;
		
		scanf(" %[^\n]", recebeRua);
		scanf(" %d", &recebeNumCasa);
		scanf(" %[^\n]", recebeBairro);
		scanf(" %[^\n]", recebeCidade);
		if(recebeTipoCliente == 1){
			for(i=0; i<15; i++){
				comparacao = strcmp(banco_clientes[i].TIPO_PESSOA.pessoa_fisica, recebeCPF);
				if(comparacao == 0){
					strcpy(banco_clientes[i].endereco_cliente.bairro, recebeBairro);
					strcpy(banco_clientes[i].endereco_cliente.rua, recebeRua);
					strcpy(banco_clientes[i].endereco_cliente.cidade, recebeCidade);
					banco_clientes[i].endereco_cliente.numero_endereco = recebeNumCasa;
					printf("Cadastrado com Sucesso\n");
					return;
				}
			}	
		}
		if(recebeTipoCliente == 2){
			for(i=0; i<15; i++){
				comparacao = strcmp(banco_clientes[i].TIPO_PESSOA.pessoa_juridica, recebeCNPJ);
				if(comparacao == 0){
					strcpy(banco_clientes[i].endereco_cliente.bairro, recebeBairro);
					strcpy(banco_clientes[i].endereco_cliente.rua, recebeRua);
					strcpy(banco_clientes[i].endereco_cliente.cidade, recebeCidade);
					banco_clientes[i].endereco_cliente.numero_endereco = recebeNumCasa;
					printf("Cadastrado com Sucesso\n");
					return;
				}
			}	
		}    
	}
	
	if(opcao == 2){
		char recebeTelefone[15];
		scanf(" %s", recebeTelefone);
		if(recebeTipoCliente == 1){
			for(i=0; i<15; i++){
				comparacao = strcmp(banco_clientes[i].TIPO_PESSOA.pessoa_fisica, recebeCPF);
				if(comparacao == 0){
					strcpy(banco_clientes[i].telefone, recebeTelefone);
					printf("Cadastrado com Sucesso\n");
					return;
				}
			}			
		}
		if(recebeTipoCliente == 2){
			for(i=0; i<15; i++){
				comparacao = strcmp(banco_clientes[i].TIPO_PESSOA.pessoa_juridica, recebeCNPJ);
				if(comparacao == 0){
					strcpy(banco_clientes[i].telefone, recebeTelefone);
					printf("Cadastrado com Sucesso\n");
					return;
				}
			}	
		}    
	}
	
	if((opcao != 1) && (opcao != 2)){
		printf("ERRO: opcao invalida\n");
		return;
	}
	
		
}

void lista_dadosCliente(CLIENTE *banco_clientes){
	int recebeTipoCliente;
	char recebeCPF[15], recebeCNPJ[19];
	int i, cont, comparacao;
	
	scanf(" %d", &recebeTipoCliente);
	
	if(recebeTipoCliente == 1){
		cont = 0;
		scanf(" %s", recebeCPF);
		for(i=0; i<15; i++){
			comparacao = strcmp(banco_clientes[i].TIPO_PESSOA.pessoa_fisica, recebeCPF);
			if(comparacao != 0){
				cont++;
			}
		}
		if(cont == 15){
			printf("ERRO: nao cadastrado\n");
			return;
		} 
	}
	if(recebeTipoCliente == 2){
		cont = 0;
		scanf(" %s", recebeCNPJ);
		for(i=0; i<15; i++){
			comparacao = strcmp(banco_clientes[i].TIPO_PESSOA.pessoa_juridica, recebeCNPJ);
			if(comparacao != 0){
				cont++;
			}
		}
		if(cont == 15){
			printf("ERRO: nao cadastrado\n");
			return;
		} 
	}
	if((recebeTipoCliente != 1) && (recebeTipoCliente != 2)){
		printf("ERRO: opcao invalida\n");
		return;
	}
	
	if(recebeTipoCliente == 1){
		for(i=0; i<15; i++){
			comparacao = strcmp(banco_clientes[i].TIPO_PESSOA.pessoa_fisica, recebeCPF);
			if(comparacao == 0){
				printf("nome: %s\n", banco_clientes[i].nome);
				printf("rua: %s\n", banco_clientes[i].endereco_cliente.rua);
				printf("num: %d\n", banco_clientes[i].endereco_cliente.numero_endereco);
				printf("bairro: %s\n",banco_clientes[i].endereco_cliente.bairro);
				printf("cidade: %s\n",banco_clientes[i].endereco_cliente.cidade);
				printf("telefone: %s\n", banco_clientes[i].telefone);
				return;
			}	
		}
	}
	
	if(recebeTipoCliente == 2){
		for(i=0; i<15; i++){
			comparacao = strcmp(banco_clientes[i].TIPO_PESSOA.pessoa_juridica, recebeCNPJ);
			if(comparacao == 0){
				printf("nome: %s\n", banco_clientes[i].nome);
				printf("rua: %s\n", banco_clientes[i].endereco_cliente.rua);
				printf("num: %d\n", banco_clientes[i].endereco_cliente.numero_endereco);
				printf("bairro: %s\n",banco_clientes[i].endereco_cliente.bairro);
				printf("cidade: %s\n",banco_clientes[i].endereco_cliente.cidade);
				printf("telefone: %s\n", banco_clientes[i].telefone);
				return;
			}	
		}
	}
}

void cadastra_carro(CARRO *banco_carros){
	int i, cont, comparacao;
	char recebeRenavam[12];
	CATEGORIAS recebeCategoria;
	CORES recebeCor;
	char recebePlaca[9], recebeMarca[50], recebeModelo[50];
	int recebeAno;
	
	cont = 0;
	
	for(i=0; i<10; i++){
		if(banco_carros[i].ano != 0){
			cont++;
		}
	}
	
	if(cont == 10){
		printf("ERRO: sem espaco\n");
		return;
	}
	
	scanf(" %s", recebeRenavam);
	
	for(i=0; i<10; i++){
		comparacao = strcmp(banco_carros[i].renavam, recebeRenavam);
		if(comparacao == 0){
			printf("ERRO: ja cadastrado\n");
			return;
		}
	}
	
	scanf(" %u", &recebeCategoria);
	
	if((recebeCategoria != hatch) && (recebeCategoria != sedan) && (recebeCategoria != suv) && (recebeCategoria != jipe)){
		printf("ERRO: opcao invalida\n");
		return;
	}   
	
	scanf(" %u", &recebeCor);
	
	if((recebeCor != preta) && (recebeCor != branca) && (recebeCor != prata)){
		printf("ERRO: opcao invalida\n");
		return;
	}
	
	scanf(" %s", recebePlaca);
	scanf(" %[^\n]", recebeMarca);
	scanf(" %[^\n]", recebeModelo);
	scanf(" %d", &recebeAno);
	
	for(i=0; i<10; i++){
		if(banco_carros[i].ano == 0){
			strcpy(banco_carros[i].renavam, recebeRenavam);
			strcpy(banco_carros[i].marca, recebeMarca);
			strcpy(banco_carros[i].modelo, recebeModelo);
			strcpy(banco_carros[i].placa, recebePlaca);
			banco_carros[i].ano = recebeAno;
			banco_carros[i].categoria = recebeCategoria;
			banco_carros[i].cor = recebeCor;
			banco_carros[i].locado = 0;
			printf("Cadastrado com Sucesso\n");
			return;
		}
	}
}

void cadastra_dadoCategoria(INFO_CATEGORIAS *informacoes_categorias){
	CATEGORIAS recebeCategoria;
	int recebeValorDiaria, recebePontosFidelidade;
	int i;

	scanf(" %u", &recebeCategoria);
	
	if((recebeCategoria != hatch) && (recebeCategoria != sedan) && (recebeCategoria != suv) && (recebeCategoria != jipe)){
		printf("ERRO: opcao invalida\n");
		return;
	}   
	
	scanf(" %d", &recebeValorDiaria);
	scanf(" %d", &recebePontosFidelidade);
	
	for(i=0; i<4; i++){
		if(informacoes_categorias[i].valor_diaria == 0){
			informacoes_categorias[i].pontos_fidelidade = recebePontosFidelidade;
			informacoes_categorias[i].valor_diaria = recebeValorDiaria;
			informacoes_categorias[i].categoria = recebeCategoria;
			printf("Cadastrado com Sucesso\n");
			return;
		}
	}	
}

void cadastra_locacao(CLIENTE *banco_clientes, CARRO *banco_carros, LOCACAO matriz_locacao[][5], INDICE_MATRIZ *indice_matriz, int *qtd_locacao){
	char recebeRenavam[12], recebeCPF[15], recebeCNPJ[19];
	int i, comparacao, cont;
	cont = 0;
	int recebeTipoCliente;
	int posicao_cliente, posicao_carro;
	int recebeDiaRetirada, recebeMesRetirada, recebeAnoRetirada;
	
	scanf(" %s", recebeRenavam);
	
	for(i=0; i<10; i++){
		comparacao = strcmp(banco_carros[i].renavam, recebeRenavam);
		if(comparacao != 0){
			cont++;
		}
		if(comparacao == 0){
			posicao_carro = i;
			if(banco_carros[i].locado == 1){
				printf("ERRO: locacao em aberto\n");
				return;
			}
		}
	}
	
	if(cont == 10){
		printf("ERRO: nao cadastrado\n");
		return;
	}
	
	scanf(" %d", &recebeTipoCliente);
	
	if((recebeTipoCliente != 1) && (recebeTipoCliente != 2)){
		printf("ERRO: opcao invalida\n");
		return;
	}
	
	if(recebeTipoCliente == 1){
		cont = 0;
		scanf(" %s", recebeCPF);
		for(i=0; i<15; i++){
			comparacao = strcmp(indice_matriz[i].TIPO_PESSOAFJ.pessoa_fisica, recebeCPF);
			if(comparacao != 0){
				cont++;
			}
			if(comparacao == 0){
				posicao_cliente = i; // ACHEI A POSICAO NO VETOR INDICE DO CPF INSERIDO PARA ME ORIENTAR NA MATRIZ
				break;
			}
			
		}
		if(cont == 15){
			printf("ERRO: nao cadastrado\n");
			return;	
		}
		
		if(indice_matriz[posicao_cliente].posicao_matriz != -1){
			cont = 0;
			for(i=0; i<5; i++){
				comparacao = strcmp(matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].TIPO_CLIENTE.pessoa_fisica, " ");
				if(comparacao != 0){
					cont++;
				}
			}
			if(cont == 5){
				printf("ERRO: sem espaco\n");
				return;
			}
			for(i=0; i<5; i++){
				if(matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].status_locacao == 0){
					printf("ERRO: locacao em aberto\n");
					return;
				}
			}
		}
		
		scanf(" %d", &recebeDiaRetirada);
		scanf(" %d", &recebeMesRetirada);
		scanf(" %d", &recebeAnoRetirada);
		*qtd_locacao += 1;
		
		if(indice_matriz[posicao_cliente].posicao_matriz == -1){
			for(i=0; i<15; i++){
				if(matriz_locacao[i][0].tipo_cliente == 0){
					strcpy(matriz_locacao[i][0].renavam, recebeRenavam);
					strcpy(matriz_locacao[i][0].TIPO_CLIENTE.pessoa_fisica, recebeCPF);
					matriz_locacao[i][0].cod_locacao += *qtd_locacao;
					matriz_locacao[i][0].data_retirada.ano = recebeAnoRetirada;
					matriz_locacao[i][0].data_retirada.dia = recebeDiaRetirada;
					matriz_locacao[i][0].data_retirada.mes = recebeMesRetirada;
					matriz_locacao[i][0].data_devolucao.ano = 00;
					matriz_locacao[i][0].data_devolucao.dia = 00;
					matriz_locacao[i][0].data_devolucao.mes = 00;
					matriz_locacao[i][0].tipo_cliente = 1;
					matriz_locacao[i][0].status_locacao = 0;
					indice_matriz[posicao_cliente].posicao_matriz = i;
					banco_carros[posicao_carro].locado = 1;
					printf("%d cadastrado com sucesso\n", matriz_locacao[i][0].cod_locacao);
					return;
				}
			}
		}	
		
		if(indice_matriz[posicao_cliente].posicao_matriz != -1){
			for(i=0; i<5; i++){
				if((matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].tipo_cliente == 0) && (matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].status_locacao != 2)){
					strcpy(matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].renavam, recebeRenavam);
					strcpy(matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].TIPO_CLIENTE.pessoa_fisica, recebeCPF);
					matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].cod_locacao += *qtd_locacao;
					matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].data_retirada.ano = recebeAnoRetirada;
					matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].data_retirada.dia = recebeDiaRetirada;
					matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].data_retirada.mes = recebeMesRetirada;
					matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].data_devolucao.ano = 00;
					matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].data_devolucao.dia = 00;
					matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].data_devolucao.mes = 00;
					matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].tipo_cliente = 1;
					matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].status_locacao = 0;
					banco_carros[posicao_carro].locado = 1;
					printf("%d cadastrado com sucesso\n", matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].cod_locacao);
					return;
				}
			}
		}	 
	}
	
	if(recebeTipoCliente == 2){
		cont = 0;
		scanf(" %s", recebeCNPJ);
		for(i=0; i<15; i++){
			comparacao = strcmp(indice_matriz[i].TIPO_PESSOAFJ.pessoa_juridica, recebeCNPJ);
			if(comparacao != 0){
				cont++;
			}
			if(comparacao == 0){
				posicao_cliente = i; // ACHEI A POSICAO NO VETOR INDICE DO CPF INSERIDO PARA ME ORIENTAR NA MATRIZ
				break;
			}
		}
		if(cont == 15){
			printf("ERRO: nao cadastrado\n");
			return;	
		}
		
		if(indice_matriz[posicao_cliente].posicao_matriz != -1){
			cont = 0;
			for(i=0; i<5; i++){
				comparacao = strcmp(matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].TIPO_CLIENTE.pessoa_juridica, " ");
				if(comparacao != 0){
					cont++;
				}
			}
			if(cont == 5){
				printf("ERRO: sem espaco\n");
				return;
			}
			for(i=0; i<5; i++){
				if(matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].status_locacao == 0){
					printf("ERRO: locacao em aberto\n");
					return;
				}
			}
		}
		
		scanf(" %d", &recebeDiaRetirada);
		scanf(" %d", &recebeMesRetirada);
		scanf(" %d", &recebeAnoRetirada);
		*qtd_locacao += 1;
		
		if(indice_matriz[posicao_cliente].posicao_matriz == -1){
			for(i=0; i<15; i++){
				if(matriz_locacao[i][0].tipo_cliente == 0){
					strcpy(matriz_locacao[i][0].renavam, recebeRenavam);
					strcpy(matriz_locacao[i][0].TIPO_CLIENTE.pessoa_juridica, recebeCNPJ);
					matriz_locacao[i][0].cod_locacao += *qtd_locacao;
					matriz_locacao[i][0].data_retirada.ano = recebeAnoRetirada;
					matriz_locacao[i][0].data_retirada.dia = recebeDiaRetirada;
					matriz_locacao[i][0].data_retirada.mes = recebeMesRetirada;
					matriz_locacao[i][0].data_devolucao.ano = 00;
					matriz_locacao[i][0].data_devolucao.dia = 00;
					matriz_locacao[i][0].data_devolucao.mes = 00;
					matriz_locacao[i][0].tipo_cliente = 2;
					matriz_locacao[i][0].status_locacao = 0;
					indice_matriz[posicao_cliente].posicao_matriz = i;
					banco_carros[posicao_carro].locado = 1;
					printf("%d cadastrado com sucesso\n", matriz_locacao[i][0].cod_locacao);
					return;
				}
			}
		}	
		
		if((indice_matriz[posicao_cliente].posicao_matriz != -1) ){
			for(i=0; i<5; i++){
				if((matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].tipo_cliente == 0) && (matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].status_locacao != 2)){
					strcpy(matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].renavam, recebeRenavam);
					strcpy(matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].TIPO_CLIENTE.pessoa_juridica, recebeCNPJ);
					matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].cod_locacao += *qtd_locacao;
					matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].data_retirada.ano = recebeAnoRetirada;
					matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].data_retirada.dia = recebeDiaRetirada;
					matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].data_retirada.mes = recebeMesRetirada;
					matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].data_devolucao.ano = 00;
					matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].data_devolucao.dia = 00;
					matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].data_devolucao.mes = 00;
					matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].tipo_cliente = 2;
					matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].status_locacao = 0;
					banco_carros[posicao_carro].locado = 1;
					printf("%d cadastrado com sucesso\n", matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].cod_locacao);
					return;
				}
			}
		} 	
	}	
}

void devolve_carro(CLIENTE *banco_clientes, CARRO *banco_carros, LOCACAO matriz_locacao[][5], INDICE_MATRIZ *indice_matriz, INFO_CATEGORIAS *informacoes_categorias, int *qtd_locacao){
	int recebeTipoCliente;
	int cont, i, comparacao, posicao_cliente, posicao_coluna, posicao_carro, posicao_categoria;
	char recebeCPF[50], recebeCNPJ[50];
	int recebeDiaEntrega, recebeMesEntrega, recebeAnoEntrega;
	
	scanf(" %d", &recebeTipoCliente);
	
	if((recebeTipoCliente != 1) && (recebeTipoCliente != 2)){
		printf("ERRO: opcao invalida\n");
		return;
	}
	
	if(recebeTipoCliente == 1){
		cont = 0;
		scanf(" %s", recebeCPF);
		
		for(i=0; i<15; i++){
			comparacao = strcmp(banco_clientes[i].TIPO_PESSOA.pessoa_fisica, recebeCPF);
			if(comparacao != 0){
				cont++;
			}
		}
		
		if(cont == 15){
			printf("ERRO: nao cadastrado\n");
			return;	
		}
		
		for(i=0; i<15; i++){
			comparacao = strcmp(indice_matriz[i].TIPO_PESSOAFJ.pessoa_fisica, recebeCPF);
			if(comparacao == 0){
				posicao_cliente = i;
				break;
			}
		}
		
		if(indice_matriz[posicao_cliente].posicao_matriz == -1){
			printf("ERRO: nenhuma locacao em aberto\n");
			return;
		}
		
		cont = 0;
		
		for(i=0; i<5; i++){
			if(matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].status_locacao != 0){
				cont++;
			}
		}
		
		if(cont == 5){
			printf("ERRO: nenhuma locacao em aberto\n");
			return;
		}
		
		for(i=0; i<5; i++){
			if(matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].status_locacao == 0){
				posicao_coluna = i;
				break;
			}
		}
		
		for(i=0; i<10; i++){
			comparacao = strcmp(banco_carros[i].renavam, matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][posicao_coluna].renavam);
			if(comparacao == 0){
				posicao_carro = i;
				break;
			}
		}		
		
		scanf(" %d", &recebeDiaEntrega);
		scanf(" %d", &recebeMesEntrega);
		scanf(" %d", &recebeAnoEntrega);
		
		
		// CANCELANDO A LOCACAO ( DATAS IGUAIS )
		if(recebeAnoEntrega == matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][posicao_coluna].data_retirada.ano){
			if(recebeMesEntrega == matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][posicao_coluna].data_retirada.mes){
				if(recebeDiaEntrega == matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][posicao_coluna].data_retirada.dia){
					matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][posicao_coluna].status_locacao = 2; // status de cancelado;
					banco_carros[posicao_carro].locado = 0;
					matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][posicao_coluna].tipo_cliente = 0;
					strcpy(matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][posicao_coluna].renavam, " ");
					//*qtd_locacao = *qtd_locacao - 1;
					matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][posicao_coluna].cod_locacao = 1000;
					matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][posicao_coluna].data_devolucao.dia = recebeDiaEntrega;
					matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][posicao_coluna].data_devolucao.mes = recebeMesEntrega;
					matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][posicao_coluna].data_devolucao.ano = recebeAnoEntrega; 
					printf("Locacao cancelada\n");
					return;		
				}
			}
		}
		//	
	
		if(recebeDiaEntrega > matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][posicao_coluna].data_retirada.dia){
			if(recebeMesEntrega < matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][posicao_coluna].data_retirada.mes){
				printf("ERRO: data invalida\n");
				return;
			}
		}else if(recebeMesEntrega < matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][posicao_coluna].data_retirada.mes){
			printf("ERRO: data invalida\n");
			return;
		}	
		
	
		matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][posicao_coluna].status_locacao = 1;
		banco_carros[posicao_carro].locado = 0;
		matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][posicao_coluna].data_devolucao.ano = recebeAnoEntrega;
		matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][posicao_coluna].data_devolucao.mes = recebeMesEntrega;
		matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][posicao_coluna].data_devolucao.dia = recebeDiaEntrega;
		
		int qtd_dias;
		float valor_devido;
		float desconto;
		char obtemRenavam[12];
		int posicaoCarroAnterior, posicaoCategoriaAnterior;
		float desconto_maximo;
		
		qtd_dias = ((recebeMesEntrega - matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][posicao_coluna].data_retirada.mes) * 30) + (recebeDiaEntrega - matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][posicao_coluna].data_retirada.dia); 		
	
	
		for(i=0; i<4; i++){
			if(banco_carros[posicao_carro].categoria == informacoes_categorias[i].categoria){
				posicao_categoria = i;
			}
		}
				
		valor_devido = qtd_dias * informacoes_categorias[posicao_categoria].valor_diaria;
	
		if(posicao_coluna == 0){
			printf("Valor devido: %.2f\n", valor_devido);
			printf("Desconto: 0.00\n");
			return;
		}
		
		strcpy(matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][posicao_coluna - 1].renavam, obtemRenavam);
		for(i=0; i<10; i++){
			comparacao = strcmp(banco_carros[i].renavam, obtemRenavam);
			if(comparacao == 0){
				posicaoCarroAnterior = i;
				break;
			}
		}
		for(i=0; i<4; i++){
			if(banco_carros[posicaoCarroAnterior].categoria == informacoes_categorias[i].categoria){
				posicaoCategoriaAnterior = i;
				break;
			}
		}
		
		desconto = (informacoes_categorias[posicaoCategoriaAnterior].pontos_fidelidade * 50.0) / 1000.0;
		desconto_maximo = 0.3 * valor_devido;
		
		if(desconto >= desconto_maximo){
			printf("Valor devido: %.2f\n", valor_devido);
			printf("Desconto: %.2f\n", desconto_maximo);
			return;
		}else{
			printf("Valor devido: %.2f\n", valor_devido);
			printf("Desconto: %.2f\n", desconto);
			return;	
		}		
	}
	
	if(recebeTipoCliente == 2){
		cont = 0;
		scanf(" %s", recebeCNPJ);
		
		for(i=0; i<15; i++){
			comparacao = strcmp(banco_clientes[i].TIPO_PESSOA.pessoa_juridica, recebeCNPJ);
			if(comparacao != 0){
				cont++;
			}
		}
		
		if(cont == 15){
			printf("ERRO: nao cadastrado\n");
			return;	
		}
		
		for(i=0; i<15; i++){
			comparacao = strcmp(indice_matriz[i].TIPO_PESSOAFJ.pessoa_juridica, recebeCNPJ);
			if(comparacao == 0){
				posicao_cliente = i;
				break;
			}
		}
		
		if(indice_matriz[posicao_cliente].posicao_matriz == -1){
			printf("ERRO: nenhuma locacao em aberto\n");
			return;
		}
		
		cont = 0;
		
		for(i=0; i<5; i++){
			if(matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].status_locacao != 0){
				cont++;
			}
		}
		
		if(cont == 5){
			printf("ERRO: nenhuma locacao em aberto\n");
			return;
		}
		
		for(i=0; i<5; i++){
			if(matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].status_locacao == 0){
				posicao_coluna = i;
				break;
			}
		}
		
		for(i=0; i<10; i++){
			comparacao = strcmp(banco_carros[i].renavam, matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][posicao_coluna].renavam);
			if(comparacao == 0){
				posicao_carro = i;
				break;
			}
		}		
		
		scanf(" %d", &recebeDiaEntrega);
		scanf(" %d", &recebeMesEntrega);
		scanf(" %d", &recebeAnoEntrega);
		
		// CANCELANDO A LOCACAO ( DATAS IGUAIS )
		if(recebeAnoEntrega == matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][posicao_coluna].data_retirada.ano){
			if(recebeMesEntrega == matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][posicao_coluna].data_retirada.mes){
				if(recebeDiaEntrega == matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][posicao_coluna].data_retirada.dia){
					matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][posicao_coluna].status_locacao = 2;
					banco_carros[posicao_carro].locado = 0;
					matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][posicao_coluna].tipo_cliente = 0;
					strcpy(matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][posicao_coluna].renavam, " ");
					//*qtd_locacao = *qtd_locacao - 1;
					matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][posicao_coluna].cod_locacao = 1000;
					matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][posicao_coluna].data_devolucao.dia = recebeDiaEntrega;
					matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][posicao_coluna].data_devolucao.mes = recebeMesEntrega;
					matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][posicao_coluna].data_devolucao.ano = recebeAnoEntrega;
					printf("Locacao cancelada\n");
					return;		
				}
			}
		}
		//
		
		if(recebeDiaEntrega > matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][posicao_coluna].data_retirada.dia){
			if(recebeMesEntrega < matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][posicao_coluna].data_retirada.mes){
				printf("ERRO: data invalida\n");
				return;
			}
		}else if(recebeMesEntrega < matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][posicao_coluna].data_retirada.mes){
			printf("ERRO: data invalida\n");
			return;
		}	
		

		matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][posicao_coluna].status_locacao = 1;
		banco_carros[posicao_carro].locado = 0;
		matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][posicao_coluna].data_devolucao.ano = recebeAnoEntrega;
		matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][posicao_coluna].data_devolucao.mes = recebeMesEntrega;
		matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][posicao_coluna].data_devolucao.dia = recebeDiaEntrega;	
		
		int qtd_dias;
		float valor_devido;
		float desconto;
		char obtemRenavam[12];
		int posicaoCarroAnterior, posicaoCategoriaAnterior;
		float desconto_maximo;
		
		qtd_dias = ((recebeMesEntrega - matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][posicao_coluna].data_retirada.mes) * 30) + (recebeDiaEntrega - matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][posicao_coluna].data_retirada.dia); 		
	
	
		for(i=0; i<4; i++){
			if(banco_carros[posicao_carro].categoria == informacoes_categorias[i].categoria){
				posicao_categoria = i;
			}
		}
				
		valor_devido = qtd_dias * informacoes_categorias[posicao_categoria].valor_diaria;
	
		if(posicao_coluna == 0){
			printf("Valor devido: %.2f\n", valor_devido);
			printf("Desconto: 0.00\n");
			return;
		}
		
		strcpy(matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][posicao_coluna - 1].renavam, obtemRenavam);
		for(i=0; i<10; i++){
			comparacao = strcmp(banco_carros[i].renavam, obtemRenavam);
			if(comparacao == 0){
				posicaoCarroAnterior = i;
				break;
			}
		}
		for(i=0; i<4; i++){
			if(banco_carros[posicaoCarroAnterior].categoria == informacoes_categorias[i].categoria){
				posicaoCategoriaAnterior = i;
				break;
			}
		}
		
		desconto = (informacoes_categorias[posicaoCategoriaAnterior].pontos_fidelidade * 50.0) / 1000.0;
		desconto_maximo = 0.3 * valor_devido;
		
		if(desconto >= desconto_maximo){
			printf("Valor devido: %.2f\n", valor_devido);
			printf("Desconto: %.2f\n", desconto_maximo);
			return;
		}else{
			printf("Valor devido: %.2f\n", valor_devido);
			printf("Desconto: %.2f\n", desconto);
			return;	
		}	
	}
	
}

void lista_dadosLocacao(CLIENTE *banco_clientes, LOCACAO matriz_locacao[][5], INDICE_MATRIZ *indice_matriz){
	int recebeCodLocacao;
	int i, j;
	int achouCodigo, locacaoCancelada;
	int posicao_linha, posicao_coluna;
	int comparacao, tipocliente;
	char obtemNome[50];
	
	achouCodigo = 0;
	locacaoCancelada = 0;
	
	scanf(" %d", &recebeCodLocacao);
	
	for(i=0; i<15; i++){
		for(j=0; j<5; j++){
			if(matriz_locacao[i][j].cod_locacao == recebeCodLocacao){
				achouCodigo = 1;
				if(matriz_locacao[i][j].status_locacao == 2){
					locacaoCancelada = 1;
				}
				posicao_linha = i;
				posicao_coluna = j;
				break;
			}
		}
	}
	
	if(achouCodigo == 0){
		printf("ERRO: nao cadastrado\n");
		return;
	}
	
	if(locacaoCancelada == 1){
		printf("ERRO: locacao foi cancelada\n");
		return;
	}
	
	comparacao = strcmp(matriz_locacao[posicao_linha][posicao_coluna].TIPO_CLIENTE.pessoa_fisica, " ");
	if(comparacao == 0){
		tipocliente = 2;
	}else{
		tipocliente = 1;
	}
	
	if(tipocliente == 1){
		for(i=0; i<15; i++){
			comparacao = strcmp(banco_clientes[i].TIPO_PESSOA.pessoa_fisica, matriz_locacao[posicao_linha][posicao_coluna].TIPO_CLIENTE.pessoa_fisica);
			if(comparacao == 0){
				strcpy(obtemNome, banco_clientes[i].nome);
				break;
			}
		}
	}	
	
	if(tipocliente == 2){
		for(i=0; i<15; i++){
			comparacao = strcmp(banco_clientes[i].TIPO_PESSOA.pessoa_juridica, matriz_locacao[posicao_linha][posicao_coluna].TIPO_CLIENTE.pessoa_juridica);
			if(comparacao == 0){
				strcpy(obtemNome, banco_clientes[i].nome);
				break;
			}
		}
	}	
	
	//printf("Print referente a funcao 8: \n");
	printf("codigo da locacao: %d\n", matriz_locacao[posicao_linha][posicao_coluna].cod_locacao);
	if(tipocliente == 1){
		printf("cpf: %s\n", matriz_locacao[posicao_linha][posicao_coluna].TIPO_CLIENTE.pessoa_fisica);
	}else{
		printf("cnpj: %s\n", matriz_locacao[posicao_linha][posicao_coluna].TIPO_CLIENTE.pessoa_juridica);
	}
	printf("nome: %s\n", obtemNome);
	printf("renavam: %s\n", matriz_locacao[posicao_linha][posicao_coluna].renavam);
	printf("data retirada: %02d/%02d/%02d\n", matriz_locacao[posicao_linha][posicao_coluna].data_retirada.dia, matriz_locacao[posicao_linha][posicao_coluna].data_retirada.mes, matriz_locacao[posicao_linha][posicao_coluna].data_retirada.ano);
	printf("data entrega: %02d/%02d/%02d\n", matriz_locacao[posicao_linha][posicao_coluna].data_devolucao.dia, matriz_locacao[posicao_linha][posicao_coluna].data_devolucao.mes, matriz_locacao[posicao_linha][posicao_coluna].data_devolucao.ano);
	
}

void lista_locacaoCliente(CLIENTE *banco_clientes, LOCACAO matriz_locacao[][5], INDICE_MATRIZ *indice_matriz){
	int recebeTipoCliente, opcao;
	char recebeCPF[15], recebeCNPJ[19];
	int comparacao, cont, i;
	char obtemNome[50];
	int posicao_cliente;
	
	scanf(" %d", &recebeTipoCliente);
	
	if((recebeTipoCliente != 1) && (recebeTipoCliente != 2)){
		printf("ERRO: opcao invalida\n");
		return;
	}
	
	
	if(recebeTipoCliente == 1){
		cont = 0;
		scanf(" %s", recebeCPF);
		for(i=0; i<15; i++){
			comparacao = strcmp(banco_clientes[i].TIPO_PESSOA.pessoa_fisica, recebeCPF);
			if(comparacao != 0){
				cont++;
			}
			if(comparacao == 0){
				strcpy(obtemNome, banco_clientes[i].nome);
				break;
			}
		}
		if(cont == 15){
			printf("ERRO: nao cadastrado\n");
			return;
		}
		
		for(i=0; i<15; i++){
			comparacao = strcmp(indice_matriz[i].TIPO_PESSOAFJ.pessoa_fisica, recebeCPF);
			if(comparacao == 0){
				posicao_cliente = i;
				break;
			}
		}
					
		scanf(" %d", &opcao);
		
		if(opcao == 1){
			cont = 0;
			
			for(i=0; i<5; i++){
				if((matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].status_locacao == -1) || (matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].status_locacao == 2)){
					cont++;
				}
			}
			
			if(cont == 5){
				printf("ERRO: nada cadastrado\n");
				return;
			}
			
			for(i=0; i<5; i++){
				if((matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].status_locacao != -1) && (matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].status_locacao != 2)){
					//printf("Print referente a funcao 9: \n");
					printf("codigo da locacao: %d\n", matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].cod_locacao);
					printf("cpf: %s\n", matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].TIPO_CLIENTE.pessoa_fisica);
					printf("nome: %s\n", obtemNome);
					printf("renavam: %s\n", matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].renavam);
					printf("data retirada: %02d/%02d/%02d\n", matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].data_retirada.dia, matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].data_retirada.mes, matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].data_retirada.ano);
					printf("data entrega: %02d/%02d/%02d\n", matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].data_devolucao.dia, matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].data_devolucao.mes, matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].data_devolucao.ano);
				}
			}
			return;
		}else if(opcao == 2){
			cont = 0;
			
			for(i=0; i<5; i++){
				if(matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].status_locacao != 1){
					cont++;
				}
			}
			
			if(cont == 5){
				printf("ERRO: nada cadastrado\n");
				return;
			}
					
			for(i=0; i<5; i++){
				if(matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].status_locacao == 1){
					//printf("Print referente a funcao 9: \n");
					printf("codigo da locacao: %d\n", matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].cod_locacao);
					printf("cpf: %s\n", matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].TIPO_CLIENTE.pessoa_fisica);
					printf("nome: %s\n", obtemNome);
					printf("renavam: %s\n", matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].renavam);
					printf("data retirada: %02d/%02d/%02d\n", matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].data_retirada.dia, matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].data_retirada.mes, matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].data_retirada.ano);
					printf("data entrega: %02d/%02d/%02d\n", matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].data_devolucao.dia, matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].data_devolucao.mes, matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].data_devolucao.ano);
				}
			}
			return;
		}else if(opcao == 3){
			cont = 0;
			
			for(i=0; i<5; i++){
				if(matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].status_locacao != 0){
					cont++;
				}
			}
			
			if(cont == 5){
				printf("ERRO: nada cadastrado\n");
				return;
			}
					
			for(i=0; i<5; i++){
				if(matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].status_locacao == 0){
					//printf("Print referente a funcao 9: \n");
					printf("codigo da locacao: %d\n", matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].cod_locacao);
					printf("cpf: %s\n", matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].TIPO_CLIENTE.pessoa_fisica);
					printf("nome: %s\n", obtemNome);
					printf("renavam: %s\n", matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].renavam);
					printf("data retirada: %02d/%02d/%02d\n", matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].data_retirada.dia, matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].data_retirada.mes, matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].data_retirada.ano);
					printf("data entrega: %02d/%02d/%02d\n", matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].data_devolucao.dia, matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].data_devolucao.mes, matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].data_devolucao.ano);
				}	
			}
			return;
		}else{
			printf("ERRO: opcao invalida\n");
			return;
		}	
	}
	
	
	if(recebeTipoCliente == 2){
		cont = 0;
		scanf(" %s", recebeCNPJ);
		for(i=0; i<15; i++){
			comparacao = strcmp(banco_clientes[i].TIPO_PESSOA.pessoa_juridica, recebeCNPJ);
			if(comparacao != 0){
				cont++;
			}
			if(comparacao == 0){
				strcpy(obtemNome, banco_clientes[i].nome);
				break;
			}
		}
		if(cont == 15){
			printf("ERRO: nao cadastrado\n");
			return;
		}
		
		for(i=0; i<15; i++){
			comparacao = strcmp(indice_matriz[i].TIPO_PESSOAFJ.pessoa_juridica, recebeCNPJ);
			if(comparacao == 0){
				posicao_cliente = i;
				break;
			}
		}
					
		scanf(" %d", &opcao);
		
		if(opcao == 1){
			cont = 0;
			
			for(i=0; i<5; i++){
				if((matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].status_locacao == -1) || (matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].status_locacao == 2)){
					cont++;
				}
			}
			
			if(cont == 5){
				printf("ERRO: nada cadastrado\n");
				return;
			}
						
			for(i=0; i<5; i++){
				if((matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].status_locacao != -1) && (matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].status_locacao != 2)){
					//printf("Print referente a funcao 9: \n");
					printf("codigo da locacao: %d\n", matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].cod_locacao);
					printf("cnpj: %s\n", matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].TIPO_CLIENTE.pessoa_juridica);
					printf("nome: %s\n", obtemNome);
					printf("renavam: %s\n", matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].renavam);
					printf("data retirada: %02d/%02d/%02d\n", matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].data_retirada.dia, matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].data_retirada.mes, matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].data_retirada.ano);
					printf("data entrega: %02d/%02d/%02d\n", matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].data_devolucao.dia, matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].data_devolucao.mes, matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].data_devolucao.ano);
				}
			}
			return;
		}else if(opcao == 2){
			cont = 0;
			
			for(i=0; i<5; i++){
				if(matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].status_locacao != 1){
					cont++;
				}
			}
			
			if(cont == 5){
				printf("ERRO: nada cadastrado\n");
				return;
			}
			
			for(i=0; i<5; i++){
				if(matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].status_locacao == 1){
					//printf("Print referente a funcao 9: \n");
					printf("codigo da locacao: %d\n", matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].cod_locacao);
					printf("cnpj: %s\n", matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].TIPO_CLIENTE.pessoa_juridica);
					printf("nome: %s\n", obtemNome);
					printf("renavam: %s\n", matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].renavam);
					printf("data retirada: %02d/%02d/%02d\n", matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].data_retirada.dia, matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].data_retirada.mes, matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].data_retirada.ano);
					printf("data entrega: %02d/%02d/%02d\n", matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].data_devolucao.dia, matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].data_devolucao.mes, matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].data_devolucao.ano);
				}
			}
			return;
		}else if(opcao == 3){
			cont = 0;
			
			for(i=0; i<5; i++){
				if(matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].status_locacao != 0){
					cont++;
				}
			}
			
			if(cont == 5){
				printf("ERRO: nada cadastrado\n");
				return;
			}
			
			for(i=0; i<5; i++){
				if(matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].status_locacao == 0){
					//printf("Print referente a funcao 9: \n");
					printf("codigo da locacao: %d\n", matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].cod_locacao);
					printf("cnpj: %s\n", matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].TIPO_CLIENTE.pessoa_juridica);
					printf("nome: %s\n", obtemNome);
					printf("renavam: %s\n", matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].renavam);
					printf("data retirada: %02d/%02d/%02d\n", matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].data_retirada.dia, matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].data_retirada.mes, matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].data_retirada.ano);
					printf("data entrega: %02d/%02d/%02d\n", matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].data_devolucao.dia, matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].data_devolucao.mes, matriz_locacao[indice_matriz[posicao_cliente].posicao_matriz][i].data_devolucao.ano);
				}	
			}
			return;
		}else{
			printf("ERRO: opcao invalida\n");
			return;
		}	
	}	
}

void lista_locacaoAberto(CLIENTE *banco_clientes, LOCACAO matriz_locacao[][5], INDICE_MATRIZ *indice_matriz){
	int recebeTipoCliente;
	int i, j, k, comparacao, cont;
	char obtemNome[50];
	
	scanf(" %d", &recebeTipoCliente);
	
	if((recebeTipoCliente != 1) && (recebeTipoCliente != 2)){
		printf("ERRO: opcao invalida\n");
		return;
	}
	
	if(recebeTipoCliente == 1){
		cont = 0;
		for(k=0; k<15; k++){
			for(i=0; i<15; i++){
				for(j=0; j<5; j++){
					if(matriz_locacao[i][j].status_locacao == 0){
						if(matriz_locacao[i][j].tipo_cliente == 1){
				
							if(matriz_locacao[i][j].cod_locacao == 1000){
								cont++;
							}
							
							if(matriz_locacao[i][j].cod_locacao != 1000){
								comparacao = strcmp(banco_clientes[k].TIPO_PESSOA.pessoa_fisica, matriz_locacao[i][j].TIPO_CLIENTE.pessoa_fisica);
								if(comparacao == 0){
									strcpy(obtemNome, banco_clientes[k].nome);
									printf("codigo da locacao: %d\n", matriz_locacao[i][j].cod_locacao);
									printf("cpf: %s\n", matriz_locacao[i][j].TIPO_CLIENTE.pessoa_fisica);
									printf("nome: %s\n", obtemNome);
									printf("renavam: %s\n", matriz_locacao[i][j].renavam);
									printf("data retirada: %02d/%02d/%02d\n", matriz_locacao[i][j].data_retirada.dia, matriz_locacao[i][j].data_retirada.mes, matriz_locacao[i][j].data_retirada.ano);
									printf("data entrega: %02d/%02d/%02d\n", matriz_locacao[i][j].data_devolucao.dia, matriz_locacao[i][j].data_devolucao.mes, matriz_locacao[i][j].data_devolucao.ano);	
								}	
							}	
						}
					}
				}
			}
		}
		if(cont == 15){
			printf("ERRO: nenhum dado cadastrado\n");
			return;
		}
		
	}
	
	if(recebeTipoCliente == 2){
		cont = 0;
		for(k=0; k<15; k++){
			for(i=0; i<15; i++){
				for(j=0; j<5; j++){
					if(matriz_locacao[i][j].status_locacao == 0){
						if(matriz_locacao[i][j].tipo_cliente == 2){
				
							if(matriz_locacao[i][j].cod_locacao == 1000){
								cont++;
							}
							
							if(matriz_locacao[i][j].cod_locacao != 1000){
								comparacao = strcmp(banco_clientes[k].TIPO_PESSOA.pessoa_juridica, matriz_locacao[i][j].TIPO_CLIENTE.pessoa_juridica);
								if(comparacao == 0){
									strcpy(obtemNome, banco_clientes[k].nome);
									printf("codigo da locacao: %d\n", matriz_locacao[i][j].cod_locacao);
									printf("cnpj: %s\n", matriz_locacao[i][j].TIPO_CLIENTE.pessoa_juridica);
									printf("nome: %s\n", obtemNome);
									printf("renavam: %s\n", matriz_locacao[i][j].renavam);
									printf("data retirada: %02d/%02d/%02d\n", matriz_locacao[i][j].data_retirada.dia, matriz_locacao[i][j].data_retirada.mes, matriz_locacao[i][j].data_retirada.ano);
									printf("data entrega: %02d/%02d/%02d\n", matriz_locacao[i][j].data_devolucao.dia, matriz_locacao[i][j].data_devolucao.mes, matriz_locacao[i][j].data_devolucao.ano);	
								}	
							}	
						}
					}
				}
			}
		}
		if(cont == 15){
			printf("ERRO: nenhum dado cadastrado\n");
			return;
		}
		
	}
	
}

void lista_locacaoCategoria(CLIENTE *banco_clientes, CARRO *banco_carros, LOCACAO matriz_locacao[][5], INDICE_MATRIZ *indice_matriz, TIPOCATEGORIA *vetorqtd){

	int recebeTipoCliente;
	int qtd_hatch, qtd_sedan, qtd_suv, qtd_jipe;
	int i, j, k, comparacao;
	CATEGORIAS obtemCategoria; 
	int aux, aux2;
	
	qtd_hatch = 0;
	qtd_sedan = 0;
	qtd_suv = 0;
	qtd_jipe = 0;
	
	scanf(" %d", &recebeTipoCliente);
	
	if((recebeTipoCliente != 1) && (recebeTipoCliente != 2)){
		printf("ERRO: opcao invalida\n");
		return;
	}
	
	if(recebeTipoCliente == 1){
		for(i=0; i<15; i++){
			for(j=0; j<5; j++){
				if(matriz_locacao[i][j].tipo_cliente == 1){
					for(k=0; k<10; k++){
						comparacao = strcmp(banco_carros[k].renavam, matriz_locacao[i][j].renavam);
						if(comparacao == 0){
							obtemCategoria = banco_carros[k].categoria;
							break;
						}
					}
					if(obtemCategoria == hatch){
						qtd_hatch++;
					}else if(obtemCategoria == sedan){
						qtd_sedan++;
					}else if(obtemCategoria == suv){
						qtd_suv++;
					}else{
						qtd_jipe++;
					}	
				}
			}
		}
		
		vetorqtd[0].qtd = qtd_hatch;
		vetorqtd[0].tipo_categoria = 1;
		vetorqtd[1].qtd = qtd_sedan;
		vetorqtd[1].tipo_categoria = 2;
		vetorqtd[2].qtd = qtd_suv;
		vetorqtd[2].tipo_categoria = 3;
		vetorqtd[3].qtd = qtd_jipe;
		vetorqtd[3].tipo_categoria = 4;
		
		for(i=0; i<3; i++){
			for(j=i; j<4; j++){
				if(vetorqtd[i].qtd < vetorqtd[j].qtd){
					aux = vetorqtd[i].qtd;
					aux2 = vetorqtd[i].tipo_categoria;
					vetorqtd[i].qtd = vetorqtd[j].qtd;
					vetorqtd[i].tipo_categoria = vetorqtd[j].tipo_categoria;
					vetorqtd[j].qtd = aux;
					vetorqtd[j].tipo_categoria = aux2;
				}
			}
		}
		
		if(qtd_hatch == qtd_sedan && qtd_hatch == qtd_suv && qtd_hatch == jipe){
			printf("Categoria hatch: %d\n", qtd_hatch);
			printf("Categoria sedan: %d\n", qtd_sedan);
			printf("Categoria suv: %d\n", qtd_suv);
			printf("Categoria jipe: %d\n", qtd_jipe);
			return;
		}
		
		for(i=0; i<4; i++){
			if(vetorqtd[i].tipo_categoria == 1){
				printf("Categoria hatch: %d\n", vetorqtd[i].qtd);
			}else if(vetorqtd[i].tipo_categoria == 2){
				printf("Categoria sedan: %d\n", vetorqtd[i].qtd);
			}else if(vetorqtd[i].tipo_categoria == 3){
				printf("Categoria suv: %d\n", vetorqtd[i].qtd);
			}else{
				printf("Categoria jipe: %d\n", vetorqtd[i].qtd);
			}
		}
		return;	
	}
	
	if(recebeTipoCliente == 2){
		for(i=0; i<15; i++){
			for(j=0; j<5; j++){
				if(matriz_locacao[i][j].tipo_cliente == 2){
					for(k=0; k<10; k++){
						comparacao = strcmp(banco_carros[k].renavam, matriz_locacao[i][j].renavam);
						if(comparacao == 0){
							obtemCategoria = banco_carros[k].categoria;
							break;
						}
					}
					if(obtemCategoria == hatch){
						qtd_hatch++;
					}else if(obtemCategoria == sedan){
						qtd_sedan++;
					}else if(obtemCategoria == suv){
						qtd_suv++;
					}else{
						qtd_jipe++;
					}	
				}
			}
		}
		
		vetorqtd[0].qtd = qtd_hatch;
		vetorqtd[0].tipo_categoria = 1;
		vetorqtd[1].qtd = qtd_sedan;
		vetorqtd[1].tipo_categoria = 2;
		vetorqtd[2].qtd = qtd_suv;
		vetorqtd[2].tipo_categoria = 3;
		vetorqtd[3].qtd = qtd_jipe;
		vetorqtd[3].tipo_categoria = 4;
		
		for(i=0; i<3; i++){
			for(j=i; j<4; j++){
				if(vetorqtd[i].qtd < vetorqtd[j].qtd){
					aux = vetorqtd[i].qtd;
					aux2 = vetorqtd[i].tipo_categoria;
					vetorqtd[i].qtd = vetorqtd[j].qtd;
					vetorqtd[i].tipo_categoria = vetorqtd[j].tipo_categoria;
					vetorqtd[j].qtd = aux;
					vetorqtd[j].tipo_categoria = aux2;
				}
			}
		}
		
		if(qtd_hatch == qtd_sedan && qtd_hatch == qtd_suv && qtd_hatch == jipe){
			printf("Categoria hatch: %d\n", qtd_hatch);
			printf("Categoria sedan: %d\n", qtd_sedan);
			printf("Categoria suv: %d\n", qtd_suv);
			printf("Categoria jipe: %d\n", qtd_jipe);
			return;
		}
		
		for(i=0; i<4; i++){
			if(vetorqtd[i].tipo_categoria == 1){
				printf("Categoria hatch: %d\n", vetorqtd[i].qtd);
			}else if(vetorqtd[i].tipo_categoria == 2){
				printf("Categoria sedan: %d\n", vetorqtd[i].qtd);
			}else if(vetorqtd[i].tipo_categoria == 3){
				printf("Categoria suv: %d\n", vetorqtd[i].qtd);
			}else{
				printf("Categoria jipe: %d\n", vetorqtd[i].qtd);
			}
		}
		return;	
	}	
}
