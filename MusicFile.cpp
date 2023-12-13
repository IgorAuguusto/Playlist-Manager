#include <iostream>
#include <cstdio>
#include <filesystem>
#include "MusicFile.h"

MusicFile::MusicFile(string nameFile) : BinaryFile(nameFile) {
}//MusicFile

void MusicFile::write(Music music) {
	MusicRegistry musicRegistry;

	// Copia os atrinutos da Musica para o registro
	strncpy_s(musicRegistry.performer, Music::STRING_SIZE, music.getPerformer().c_str(), music.getPerformer().length());
	strncpy_s(musicRegistry.title, Music::STRING_SIZE, music.getTitle().c_str(), music.getTitle().length());
	
	// Escreve os dados da estrutura no arquivo.
	binaryFile.write(reinterpret_cast<const char*>(&musicRegistry), registrySize());

    binaryFile.flush();
}//write()

optional<Music> MusicFile::read(unsigned int registryNumber) {
	MusicRegistry musicRegistry;

	// Posiciona o ponteiro do arquivo no registro a ser lido.
	seek(registryNumber);
	
	// Lê os dados do registro e armazena na estrutura.
	binaryFile.read(reinterpret_cast<char*>(&musicRegistry), registrySize());

	return Music(musicRegistry.performer, musicRegistry.title);
}//read()

int MusicFile::search(string title) {
	// Obtém o número de registros do arquivo.
	uintmax_t registries = registryQuantity();

	// Percorre o arquivo a procura do nome do produto.
	for (unsigned registry = 0; registry < registries; registry++)
	{
		optional<Music> optional = read(registry);

		// Verifica se é o nome procurado.
		if (optional.has_value() && title == optional.value().getTitle())
			return registry;
	}
	return BinaryFile::REGISTRY_NOT_FOUND;
}//search()

int MusicFile::search(unique_ptr<Music> music) {
    static string lastPerformerSearched; 

    if (music) {
        // Se um novo music for fornecido, atualiza o último performer pesquisado
        lastPerformerSearched = music->getPerformer();
    }

    uintmax_t registries = registryQuantity();
    bool performerFound = false;

    for (unsigned registry = 0; registry < registries; registry++) {
        optional<Music> optional = read(registry);

        if (optional.has_value()) {
            string performer = optional.value().getPerformer();

            // Se for a primeira chamada (com music não nulo), ou se encontrou o próximo performer
            if ((!music && lastPerformerSearched.empty()) || performer == lastPerformerSearched) {
                if (!music || (music && optional.value().getTitle() == music->getTitle())) {
                    // Retorna o registro se o título for igual (ou procura o próximo performer se music for nullptr)
                    return registry;
                }
            }

            // Se encontrou um novo performer após o último pesquisado, atualiza e reinicia a busca
            if (performer != lastPerformerSearched) {
                lastPerformerSearched = performer;
                performerFound = true;
            }
        }
    }

    // Se não encontrou mais registros com o performer, retorna NOT_FOUND
    return (performerFound) ? REGISTRY_NOT_FOUND : REGISTRY_NOT_FOUND;
}//search()


uintmax_t MusicFile::registrySize() {
    return Music::STRING_SIZE * sizeof(char) + Music::STRING_SIZE * sizeof(char);
}//registrySize()
