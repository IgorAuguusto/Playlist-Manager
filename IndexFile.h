#pragma once

#include <optional>
#include <vector>
#include "BinaryFile.h"
#include "Music.h"
#include "Index.h"


/* 
	Esta classe fornece operações para manipulação de um índice em um arquivo com acesso aleatório.
*/
class IndexFile : public BinaryFile {
public:
	// Abre o arquivo para leitura e escrita.
	IndexFile(string nameFile);

	// Escreve o índice como um registro do arquivo.
	void write(Index music);

	// Lê os dados de um registro do arquivo e armazena-os no objeto Index. Retorna o objeto Index.
	optional<Index> read(unsigned int registryNumber);

	// Pesquisa a chave primária no arquivo de índice. Se achar a chave primária retorna o número do registro onde ela está armazenada ou BinaryFile::REGISTRY_NOT_FOUND  se não achar.
	int search(string primarykey);


	vector<int> search(vector<Index> indexVector, string primarykey);

	// Obtém o tamanho do registro em bytes.
	uintmax_t registrySize();

private:
	/* Os objetos da classe string não possuem tamanho fixo, eles usam memória alocada dinamicamente para acomodar strings de vários comprimentos.
		 Portanto, é necessário usar um vetor de caracteres para assegurar o tamanho fixo das strings literais que serão escritas e lidas no arquivo de acesso aleatório,
		 e consequentemente o tamanho fixo dos registros. A estrutura abaixo é usada para acomodar as variáveis de instância dos objetos que serão gravados e lidos do arquivo.
	*/
	struct IndexRegistry {
		char primarykey[Music::STRING_SIZE];
		unsigned registryNumber;
	};
};
