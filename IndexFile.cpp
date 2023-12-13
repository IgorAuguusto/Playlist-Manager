#include "Index.h"
#include "IndexFile.h"

IndexFile::IndexFile(string nameFile) : BinaryFile(nameFile) {
}//IndexFile

void IndexFile::write(Index music) {
	IndexRegistry indexRegistry;

	// Copia os atributos do Index para a estrutura.
	strncpy_s(indexRegistry.primarykey, Music::STRING_SIZE, music.getPrimarykey().c_str(), music.getPrimarykey().length());
	indexRegistry.registryNumber = music.getRegistryNumber();

	binaryFile.write(reinterpret_cast<const char*>(&indexRegistry), registrySize());

	binaryFile.flush();
}//write()

optional<Index> IndexFile::read(unsigned int registryNumber) {
	IndexRegistry indexRegistry;

	// Posiciona o ponteiro do arquivo no registro a ser lido.
	seek(registryNumber);

	// Lê os dados do registro e armazena na estrutura.
	binaryFile.read(reinterpret_cast<char*>(&indexRegistry), registrySize());
	
	
	return Index(indexRegistry.primarykey, indexRegistry.registryNumber);
}//read()

int IndexFile::search(string primarykey) {
	// Obtém o número de registros do arquivo.
	uintmax_t registries = registryQuantity();
	
	// Percorre o arquivo a procura da primarykey do Index.
	for (unsigned registry = 0; registry < registries; registry++) {
		optional<Index> optional = read(registry);

		// Verifica se a primaryKey procurado.
		if (optional.has_value() && primarykey == optional.value().getPrimarykey()) {
			return registry;
		}
	}
	return BinaryFile::REGISTRY_NOT_FOUND;
	binaryFile.flush();
}//search()

/**
 * Procura os registros que correspondem a uma chave primária em um vetor de Index ordenado
 * usando a busca binaria.
 */
vector<int> IndexFile::search(vector<Index> indexVector, string primarykey) {
	// Vetor para armazenar os números dos registros encontrados
	vector<int> foundIndices;

	// Procura a primeira ocorrência da primarykey no vetor usando a busca binaria
	auto it = std::lower_bound(indexVector.begin(), indexVector.end(), primarykey,
		[](Index& index, const std::string& key) {
			return index.getPrimarykey() < key;
		});

	// Enquanto houver ocorrências e a primarykey for encontrada, adiciona os números dos registros ao vetor
	while (it != indexVector.end() && it->getPrimarykey() == primarykey) {
		foundIndices.push_back(it->getRegistryNumber());
		it++;
	}

	// Retorna os números dos registros encontrados
	return foundIndices;
}


// Obtém o tamanho do registry em bytes.
uintmax_t IndexFile::registrySize() {
	return Music::STRING_SIZE * sizeof(char) + sizeof(unsigned);
}//registrySize()

