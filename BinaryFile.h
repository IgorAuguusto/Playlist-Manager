#pragma once

#include <fstream>
#include <string>
#include <cstdint>
#include <ios>

using namespace std;

/*
   Fornece operações para manipular um arquivo binário com acesso aleatório.
*/
class BinaryFile {
public:
	static const short REGISTRY_NOT_FOUND = -1;

	BinaryFile() = default;

	// Abre o arquivo com o nome especificado em fileName para escrita e leitura de dados no fim do arquivo. Se o arquivo não existir ele será criado.
	BinaryFile(string fileName);

	// Obtém o nome do arquivo.
	string getFileName();

	// Abre o arquivo usando o modo de abertura fornecido. Retorna true se o arquivo foi aberto ou false se não.
	bool open(ios_base::openmode openningMode);

	// Fecha o arquivo e reabre usando o modo de abertura atual. Retorna true em caso de sucesso ou false caso contrário.
	bool reopen();

	// Fecha o arquivo e reabre usando o modo de abertura fornecido. Retorna true em caso de sucesso ou false caso contrário.
	bool reopen(ios_base::openmode openningMode);

	// Fecha o arquivo. Retorna true se o arquivo foi fechado ou false se não.
	bool close();

	// Remove o arquivo do sistema caso exista e cria um novo
	void remove();

	// Obtém o tamanho do arquivo em bytes.
	uintmax_t fileSize();

	// Obtém a quantidade de registros do arquivo.
	uintmax_t registryQuantity();

	// Posiciona o ponteiro do arquivo no registro indicado.
	void seek(uintmax_t registryNumber);

	// Diminui o tamanho do arquivo apagando o último registro.  Retorna true se o último registro foi excluído ou false se não.
	bool truncate();

	// Obtém o tamanho do registro em bytes.
	virtual uintmax_t registrySize() = 0;

protected:
	fstream binaryFile; // Arquivo binário para escrita e leitura de dados. 

private:
	string fileName;
	ios_base::openmode openningMode;
};
