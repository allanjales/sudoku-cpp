/*
!--------------------------------
!proposito: Resolver sudoku
!--------------------------------	
!autor: Allan Jales
!--------------------------------
*/

#include <string>		//Possibilita mexer com strings
#include <fstream>		//Possibilita ler e escrever um arquivo
#include <iostream>

using namespace std;

string readfile  = "sudoku-facil.txt";			//Nome do arquivo a ser lido
string writefile = "sudoku-resultado.txt";		//Nome do arquivo a ser escrito

int sudoku[9][9];								//Sudoku[linha][coluna]


/*
!--------------------------
! Exibição
!--------------------------
*/

//Exibe o sudoku na tela
void exibirSudoku()
{
	int i, j;		//Variáveis de itineração [linha],[coluna]

	//Itinerando linhas
	for (i = 0; i < 9; i++)
	{
		//Itinerando colunas
		for (j = 0; j < 9; j++)
		{
			//Se o número exibido for -1
			if (sudoku[i][j] == -1)
			{
				//Exibe asterisco
				cout << "* ";
			}
			else
			{
				//Exibe o número
				cout << sudoku[i][j] << " ";
			}
		}

		//Finaliza linha
		cout << endl;
	}
}

/*
!--------------------------
! Verificação
!--------------------------
*/

//Verifica se a linha tem o número
bool verificarLinha(int linha, int numero)
{
	int j;			//Variável de itineração [coluna]

	//Em cada coluna verifica se tem o número
	for (j = 0; j < 9; j++)
	{
		if (sudoku[linha][j] == numero)
		{
			//Caso tenha o número, retorna verdadeiro
			return true;
		}
	}

	//Caso não tenha o número, retorna falso
	return false;
}

//Verifica se a coluna tem o número
bool verificarColuna(int coluna, int numero)
{
	int i;			//Variável de itineração [linha]

	//Em cada linha verifica se tem o número
	for (i = 0; i < 9; i++)
	{
		if (sudoku[i][coluna] == numero)
		{
			//Caso tenha o número, retorna verdadeiro
			return true;
		}
	}

	//Caso não tenha o número, retorna falso
	return false;
}

//Verifica se a grade tem o número
bool verificarGrade(int linha, int coluna, int numero)
{
	int i, j;		//Variáveis de itineração [linha],[coluna]

	//Itinerando linhas da grade
	for (i = 0; i < 3; i++)
	{
		//Itinerando colunas da grade
		for (j = 0; j < 3; j++)
		{
			//Se for o número
			if (sudoku[3*linha+i][3*coluna+j] == numero)
			{
				//Caso tenha o número, retorna verdadeiro
				return true;
			}
		}
	}

	//Caso não tenha o número, retorna falso
	return false;
}

/*
!--------------------------
! Substituição
!--------------------------
*/

//Substitui espaços vazios por -1 na linha
void substituirLinha(int linha)
{
	int j;			//Variável de itineração [coluna]

	//Em cada coluna verifica se é zero
	for (j = 0; j < 9; j++)
	{
		if (sudoku[linha][j] == 0)
		{
			//Substitui por -1
			sudoku[linha][j] = -1;
		}
	}
}

//Substitui espaços vazios por -1 na coluna
void substituirColuna(int coluna)
{
	int i;			//Variável de itineração [linha]

	//Em cada linha verifica se é zero
	for (i = 0; i < 9; i++)
	{
		if (sudoku[i][coluna] == 0)
		{
			//Substitui por -1
			sudoku[i][coluna] = -1;
		}
	}
}

//Substitui espaços vazios por -1 na grade
void substituirGrade(int linha, int coluna)
{
	int i, j;		//Variáveis de itineração [linha],[coluna]

	//Itinerando linhas da grade
	for (i = 0; i < 3; i++)
	{
		//Itinerando colunas da grade
		for (j = 0; j < 3; j++)
		{
			if (sudoku[3*linha+i][3*coluna+j] == 0)
			{
				//Substitui por -1
				sudoku[3*linha+i][3*coluna+j] = -1;
			}
		}
	}
}

//Substitui todos os espaços que não puderem ter o número por -1
void substituirParaNumero(int numero)
{
	int i, j;			//Variáveis de itineração [linha],[coluna]

	//Itinera entre as linhas e colunas (rs)
	for (i = 0; i < 9; i++)
	{
		//Verifica se na linha i tem o número
		if (verificarLinha(i,numero) == true)
		{
			//Substitui linha
			substituirLinha(i);
		}
		
		//Verifica se na coluna i tem o número
		if (verificarColuna(i,numero) == true)
		{
			//Substitui coluna
			substituirColuna(i);
		}
	}

	//Itinerando grades da linha
	for (i = 0; i < 3; i++)
	{
		//Itinerando grades da coluna
		for (j = 0; j < 3; j++)
		{
			//Verifica se na grade i,j tem o número
			if (verificarGrade(i,j,numero) == true)
			{
				//Substitui na grade
				substituirGrade(i,j);
			}
		}
	}
}

/*
!--------------------------
! Contadores
!--------------------------
*/

//Conta quantos zeros tem na linha
int contadorLinha(int linha)
{
	int j;				//Variável de itineração [coluna]
	int contador = 0;	//Variável de contagem

	//Em cada coluna verifica se é zero
	for (j = 0; j < 9; j++)
	{
		if (sudoku[linha][j] == 0)
		{
			///Acrescenta o contador
			contador++;
		}
	}

	//Retorna quantos tem
	return contador;
}

//Conta quantos zeros tem na coluna
int contadorColuna(int coluna)
{
	int i;				//Variável de itineração [linha]
	int contador = 0;	//Variável de contagem

	//Em cada linha verifica se é zero
	for (i = 0; i < 9; i++)
	{
		if (sudoku[i][coluna] == 0)
		{
			///Acrescenta o contador
			contador++;
		}
	}

	//Retorna quantos tem
	return contador;
}

//Conta quantos zeros tem na grade
int contadorGrade(int linha, int coluna)
{
	int i, j;			//Variáveis de itineração [linha],[coluna]
	int contador = 0;	//Variável de contagem

	//Itinerando linhas da grade
	for (i = 0; i < 3; i++)
	{
		//Itinerando colunas da grade
		for (j = 0; j < 3; j++)
		{
			if (sudoku[3*linha+i][3*coluna+j] == 0)
			{
				///Acrescenta o contador
				contador++;
			}
		}
	}

	//Retorna quantos tem
	return contador;
}

//Conta quantos zeros tem no sudoku
int contadorSudoku()
{
	int i;				//Variável de itineração [linha]
	int contador = 0;	//Variável de contagem

	//Itinera entre as linhas do sudoku
	for (i = 0; i < 9; i++)
	{
		///Acrescenta o contador
		contador += contadorLinha(i);
	}

	//Retorna quantos tem
	return contador;
}

/*
!--------------------------
! Preenchimento
!--------------------------
*/

//Preenche os espaços vazios da linha pelo número
void preencherLinha(int linha, int numero)
{
	int j;			//Variável de itineração [coluna]

	//Em cada coluna verifica se é zero
	for (j = 0; j < 9; j++)
	{
		if (sudoku[linha][j] == 0)
		{
			//Substitui por número
			sudoku[linha][j] = numero;
		}
	}
}

//Preenche os espaços vazios da coluna pelo número
void preencherColuna(int coluna, int numero)
{
	int i;			//Variável de itineração [linha]

	//Em cada linha verifica se é zero
	for (i = 0; i < 9; i++)
	{
		if (sudoku[i][coluna] == 0)
		{
			//Substitui por número
			sudoku[i][coluna] = numero;
		}
	}
}

//Preenche os espaços vazios da grade pelo número
void preencherGrade(int linha, int coluna, int numero)
{
	int i, j;		//Variáveis de itineração [linha],[coluna]

	//Itinerando linhas da grade
	for (i = 0; i < 3; i++)
	{
		//Itinerando colunas da grade
		for (j = 0; j < 3; j++)
		{
			if (sudoku[3*linha+i][3*coluna+j] == 0)
			{
				//Substitui por número
				sudoku[3*linha+i][3*coluna+j] = numero;
			}
		}
	}
}

/*
!--------------------------
! Limpeza
!--------------------------
*/

//Tira os negativos do sudoku
void limparSudoku()
{
	int i, j;			//Variáveis de itineração [linha],[coluna]

	//Itinerando linhas
	for (i = 0; i < 9; i++)
	{
		//Itinerando colunas
		for (j = 0; j < 9; j++)
		{
			//Se for igual a -1
			if (sudoku[i][j] == -1)
			{
				//Substitui pelo valor certo
				sudoku[i][j] = 0;
			}
		}
	}
}

/*
!--------------------------
! Solução
!--------------------------
*/

//Tenta resolver o sudoku
void resolverSudoku()
{
	int i, j, k;		//Variáveis de itineração [linha],[coluna],[numeros]
	int preenchidos;	//Variável de contagem de espaços preenchidos na vez
	int antes;			//Variável de contagem de espaços vazios antes
	int contador = 0;	//Variável de contagem de passos dados

	//Exibe quantos espaços vazios tem o arquivo aberto
	cout << "espaços vazios: " << contadorSudoku() << endl;

	//Preenchidos deve ter qualquer valor diferente de zero caso tenha espaços vazios
	preenchidos = contadorSudoku();

	//Loop até não conseguir preencher mais
	while (preenchidos != 0)
	{
		//Quantos espaços vazios têm no sudoku inicialmente
		antes = contadorSudoku();

		//Itinera entre os números
		for (k = 1; k <= 9; k++)
		{
			//Acrescenta 1 na contagem
			contador++;

			//Exibe qual número está analisando
			cout << endl;
			cout << "Para o número " << k << " (passo " << contador << "):" << endl;

			//Substitui todos os espaços vazios que não puderem ser ocupados pelo número k por -1
			substituirParaNumero(k);

			//Mostra o sudoku
			exibirSudoku();

			//Itinera entre as linhas e colunas (rs)
			for (i = 0; i < 9; i++)
			{
				//Verifica se na linha tem 1 espaço vazio
				if (contadorLinha(i) == 1)
				{
					//Preenche o espaço vazio da linha com o número k
					preencherLinha(i,k);

					//Substitui todos os espaços vazios que não puderem ser ocupados pelo número k por -1
					substituirParaNumero(k);
				}
				
				//Verifica se na linha tem 1 espaço vazio
				if (contadorColuna(i) == 1)
				{
					//Preenche o espaço vazio da coluna com o número k
					preencherColuna(i,k);

					//Substitui todos os espaços vazios que não puderem ser ocupados pelo número k por -1
					substituirParaNumero(k);
				}
			}

			//Itinerando grades da linha
			for (i = 0; i < 3; i++)
			{
				//Itinerando grades da coluna
				for (j = 0; j < 3; j++)
				{
					//Verifica se na grade i,j tem 1 espaço vazio
					if (contadorGrade(i,j) == 1)
					{
						//Substitui na grade
						preencherGrade(i,j,k);

						//Substitui todos os espaços vazios que não puderem ser ocupados pelo número k por -1
						substituirParaNumero(k);
					}
				}
			}

			cout << endl;
			cout << "Colocado " << k << " (passo " << contador << "):" << endl;

			//Mostra o sudoku
			exibirSudoku();

			//Limpa o sudoku antes de passar para o próximo número
			limparSudoku();

			//Exibe quantos espaços vazios tem
			cout << "Espaços vazios: " << contadorSudoku() << endl;

			//Se não tiver mais o que preencher, para o for.
			if (contadorSudoku() == 0)
			{
				break;
			}
		}

		//Atualiza a quantidade de preenchidos
		preenchidos = antes - contadorSudoku();

		//Se não tiver mais o que preencher, para o while.
		if (contadorSudoku() == 0)
		{
			break;
		}
	}
}

/*
!--------------------------
! Principal
!--------------------------
*/

int main()
{
	int i, j;				//Variáveis de itineração [linha],[coluna]
	string line;			//Variável que lerá as linhas do arquivo

	//Exibe qual arquivo será lido e qual será escrito
	cout << readfile << " -> " << writefile << endl;

	//Abre o arquivo
	ifstream sudokufile;
	sudokufile.open(readfile);

	//Verifica se abriu o arquivo
	if (sudokufile.is_open())
	{
		cout << "o arquivo foi aberto" << endl;
		cout << "conteúdo lido:" << endl;

		//Define linha inicial de preenchumento zero
		i = 0;

		//Lê as linhas
		while (getline(sudokufile,line))
		{
			//Exibe o que foi lido na tela
			cout << line << endl;

			//Transfere o conteúdo para a variável
			for (j = 0; j < 9; j++)
			{
				//cout << line[j*2] << "=";
				sudoku[i][j] = stoi(&line[j*2]);
				//cout << sudoku[i][j];
				//cout << endl;
			}

			//Pula para a próxima linha da variável sudoku
			i++;
		}

		//Fecha o arquivo
		sudokufile.close();

		//Avisa que vai exibir o sudoku
		cout << endl;
		cout << "conteudo guardado: " << endl;
		exibirSudoku();

		//Resolve sudoku
		resolverSudoku();
	}
	else
	{
		cout << "o arquivo não pôde ser aberto" << endl;
	}

	return 0;
}