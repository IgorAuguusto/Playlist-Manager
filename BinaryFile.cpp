#include <iostream>
#include <filesystem>
#include "BinaryFile.h"

// Abre o arquivo com o nome especificado em fileName para escrita e leitura de dados no fim do arquivo. Se o arquivo não existir ele será criado.
BinaryFile::BinaryFile(string fileName) {
	this->fileName = fileName;

	// Define o modo de abertura do arquivo binário para leitura e escrita de dados no fim do arquivo.
	openningMode = ios::in | ios::app | ios::binary;

	// Abre o arquivo binário para leitura e escrita de dados no fim do arquivo.
	open(openningMode);
}//BinaryFile

// Obtém o nome do arquivo.
string BinaryFile::getFileName() {
	return fileName;
}//getFileName()

// Abre o arquivo usando o modo de abertura fornecido. Retorna true se o arquivo foi aberto ou false se não.
bool BinaryFile::open(ios_base::openmode openningMode) {
	binaryFile.open(fileName, openningMode);
	return binaryFile ? true : false;
}//open()

// Fecha o arquivo e reabre usando o modo de abertura atual. Retorna true em caso de sucesso ou false caso contrário.
bool BinaryFile::reopen() {
	return reopen(openningMode);
}//reopen()

// Fecha o arquivo e reabre usando o modo de abertura fornecido. Retorna true em caso de sucesso ou false caso contrário.
bool BinaryFile::reopen(ios_base::openmode openningMode)  {
	return close() ? open(openningMode) : false;
}//reopen()

// Fecha o arquivo. Retorna true se o arquivo foi fechado ou false se não.
bool BinaryFile::close() {
	if (binaryFile.is_open()) {
		binaryFile.flush();
		binaryFile.close();
		return true;
	}
	return false;
}//close()

// Obtém o tamanho do arquivo em bytes.
uintmax_t BinaryFile::fileSize() {
	return filesystem::file_size(fileName);
}//fileSize()

// Obtém a quantidade de registros do arquivo.
uintmax_t BinaryFile::registryQuantity() {
	return fileSize() / registrySize();
}//registryQuantity()

// Posiciona o ponteiro do arquivo no registro indicado.
void BinaryFile::seek(uintmax_t registryNumber) {
	binaryFile.seekp(static_cast<streampos>(registryNumber) * registrySize());
}//seek()

// // Remove o arquivo do sistema caso exista e cria um novo.
void BinaryFile::remove() {
	close();
	filesystem::remove(fileName);
	open(openningMode);
}//remove()


// Diminui o tamanho do arquivo apagando o último registro.  Retorna true se o último registro foi excluído ou false se não.
bool BinaryFile::truncate() {
	if (fileSize() >= registrySize()) {
		filesystem::resize_file(filesystem::path(getFileName()), fileSize() - registrySize());
		return true;
	}
	return false;
}//truncate()