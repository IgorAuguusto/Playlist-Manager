#pragma once

#include <memory>
#include <optional>
#include "BinaryFile.h"
#include "Music.h"

/* 
	Esta classe fornece operações para manipulação de uma música em um arquivo com acesso aleatório.
*/
class MusicFile : public BinaryFile {
public:
	// Abre o arquivo para leitura e escrita.
	MusicFile(string nameFile);

	// Escreve a música como um registro do arquivo.
	void write(Music music);

	// Lê os dados de um registro do arquivo e armazena-os no objeto Music. Retorna o objeto Music.
	optional<Music> read(unsigned int registryNumber);

	// Pesquisa o título da música no arquivo. Se achar a música retorna o número do registro onde ela está armazenada ou BinaryFile::REGISTRY_NOT_FOUND  se não achar.
	int search(string title);

	/* Pesquisa o nome do cantor(a) ou banda no arquivo. Em caso de sucesso retorna o número do registro onde a música está armazenada ou BinaryFile::REGISTRY_NOT_FOUND  se não achar.
	    O método retorna a primeira música da playlist que possui o título igual ao atributo título do objeto Music. Para obter todas as músicas do mesmo cantor(a) ou banda, basta na primeira
	    chamada do método passar o nome do cantor(a) ou banda e nas chamadas subsequentes passar nullptr. Assim, a pesquisa na playlist continuará após o performer anterior que possui o 
		nome fornecido inicialmente. Quando não existir mais performers na playlist com o mesmo nome o método deve retornar BinaryFile::REGISTRY_NOT_FOUND.

	Exemplo: Obtém todas as músicas da banda Imagine Dragons e usa o método toString da classe Music para exibir os seus dados.

					unique_ptr<Music> music = make_unique<Music>("Imagine Dragons");
					int registry = musicFile.search(performer);

					while (registry != NOT_FOUND)
					{
							cout << musicFile.read(registry)->toString();
							registry = musicFile.search(nullptr);
					}
*/
	int search(unique_ptr<Music> music);

	// Obtém o tamanho do registro em bytes.
	uintmax_t registrySize();

private:
	/* Os objetos da classe string não possuem tamanho fixo, eles usam memória alocada dinamicamente para acomodar strings de vários comprimentos.
		 Portanto, é necessário usar um vetor de caracteres para assegurar o tamanho fixo das strings literais que serão escritas e lidas no arquivo de acesso aleatório,
		 e consequentemente o tamanho fixo dos registros. A estrutura abaixo é usada para acomodar as variáveis de instância dos objetos que serão gravados e lidos do arquivo.
	*/
	struct MusicRegistry {
		char title[Music::STRING_SIZE],
			 performer[Music::STRING_SIZE];
	};
};

