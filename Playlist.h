#pragma once
#include <vector>
#include <memory>
#include "Music.h"
#include "Index.h"
#include "IndexFile.h"
#include "MusicFile.h"

// Arquivos 
#define PLAYLIST_FILE "Playlist.dat"
#define TITLE_INDEX_FILE "ArqIndTituloMusica.dat"
#define ARTIST_INDEX_FILE "ArqIndArtista.dat"

// Mensagens de Texto
#define INSERT_DIRECTORY_MESSAGE "Forneça o nome do diretório: "
#define PLAYLIST_CREATED_SUCCESS_MESSAGE "Playlist criada com {} músicas."
#define INDEX_FILES_MESSAGE "Arquivos de índice criados."
#define ERROR_DIRECTORY_MESSAGE "Não foi possível criar a playlist. Verifique o diretório fornecido."
#define CLASSIFIED_BY_TITLE_MESSAGE "Playlist classificada pelo título da música"
#define CLASSIFIED_BY_ARTIST_MESSAGE "Playlist classificada pelo artista"
#define PLAYLIST_TITLE_MESSAGE "- Playlist"
#define OPTION_EXIT_MESSAGE "0. Sair"
#define OPTION_CREATE_MESSAGE "1. Criar"
#define OPTION_SHOW_BY_TITLE_MESSAGE "2. Exibir playlist ordenada por título"
#define OPTION_SHOW_BY_ARTIST_MESSAGE "3. Exibir playlist ordenada por nome"
#define OPTION_SEARCH_TITLE_MESSAGE "4. Pesquisar música"
#define OPTION_SEARCH_ARTIST_MESSAGE "5. Pesquisar artista"
#define OPTION_CHOICE_MESSAGE "Escolha: "
#define ENTER_THE_MUSIC_MESSAGE "Entre com o título da musica a ser pesquisada: "
#define ENTER_THE_ARTIST_MESSAGE "Entre com o Artista da musica a ser pesquisado: "
#define NUMBER_OF_SONGS_FOUND "Número de músicas encontradas: "
#define ERROR_THERE_ARE_NO_MATCHES_MESSAGE "Não há correspondências de ({}) na Playlist."
#define ERROR_EMPTY_PLAYLIST_MESSAGE "Não há playlist criadas"
#define ERROR_INVALID_OPTION_MESSAGE "Opção Inválida"

// Formatações
#define NEW_LINE '\n'
#define TAB '\t'
#define DOT "."
#define SPACE " "
#define NUMBER_OF_MUSIC_MESSAGE "Número de Músicas = {}"
#define UTF ".utf-8"


// Extensão e Delimitadores
#define EXTENSION ".mp3"
#define DELIMITER " - "

// Comandos do Sistema
#define PAUSE "pause"
#define CLEAR "cls"


using namespace std;

class Playlist {
public:
	Playlist();
	
	~Playlist();

	int playList();
private:
	void displayOption();

	/* Cria uma nova Playlist a partir de arquivos em um diretório fornecido pelo usuário
	   Remove arquivos antigos antes de criar a nova Playlist */
	void create();
	
	// Cria a Playlist a partir dos arquivos encontrados em um diretório fornecido
	bool createPlayList(const string& directoryPath);
	
	// Cria os arquivos de índice por título e por artista para a Playlist
	void createIndexFiles();

	// Cria o arquivo de índice por título usando os dados da Playlist
	bool createTitleIndexFile();
	
	// Cria o arquivo de índice por artista usando os dados da Playlist
	bool createArtistIndexFile();
	
	// Exibe a Playlist ordenada por título
	bool displayByTitle();
	
	// Exibe a Playlist ordenada por artista
	bool displayByArtist();

	// Realiza uma busca na Playlist por título ou artista e exibe os resultados
	void searchDisplay(bool isTitle);
	
	// Limpa o buffer do stream de entrada
	void clearBuffer();
	
	// Realiza uma busca na Playlist por título e retorna um vetor de índices dos resultados
	vector<int> searchSong(string song);
	
	// Realiza uma busca na Playlist por Artista e retorna um vetor de índices dos resultados
	vector<int> searchArtist(string artist);
	
	// Limpa a tela da console quando uma tecla for precionada
	void clearDisplay();
	
	// Obtém entrada do usuário a partir de uma mensagem fornecida
	string getUserInput(const string& message);
	
	// Exibe os resultados da busca por título ou artista na Playlist.
	void displaySearchResults(const vector<int>& indexVector, bool isTitle);
	
	// Carrega os índices dos arquivos se necessário para realizar operações de busca.
	void loadIndexesIfNeeded();
	
	// Remove os arquivos relacionados à Playlist
	void removeFiles();

	// Enum que representa as o~perações
	enum PlaylistOptions {
		EXIT,
		CREATE,
		DISPLAY_BY_TITLE,
		DISPLAY_BY_ARTIST,
		SEARCH_SONG,
		SEARCH_ARTIST
	};
	
	// Ponteiro para os arquivos
	unique_ptr<MusicFile> musicFilePtr;
	unique_ptr<IndexFile> titleIndexFilePtr;
	unique_ptr<IndexFile> artistIndexFilePtr;
	
	// vectors para auxiliar nas logicas.
	vector<Music> vectorMusic;
	vector<Index> vectorIndexTitle;
	vector<Index> vectorIndexArtist;
};

