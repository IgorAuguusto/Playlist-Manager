#include <iostream>
#include <fstream>
#include <filesystem>
#include <locale>
#include <string>
#include <stdlib.h>
#include <algorithm>
#include "IndexFile.h"
#include "Playlist.h"

Playlist::Playlist() : musicFilePtr(make_unique<MusicFile>(PLAYLIST_FILE)),
titleIndexFilePtr(make_unique<IndexFile>(TITLE_INDEX_FILE)),
artistIndexFilePtr(make_unique<IndexFile>(ARTIST_INDEX_FILE)) {
}//Construtor

Playlist::~Playlist() {
    // Fechando os arquivos
    musicFilePtr->close();
    titleIndexFilePtr->close();
    artistIndexFilePtr->close();
}//Destrutor

/* Cria uma nova Playlist a partir de arquivos em um diretório fornecido pelo usuário
Remove arquivos antigos antes de criar a nova Playlist */
void Playlist::create() {
    removeFiles();
    string directoryPath;
    directoryPath = getUserInput(INSERT_DIRECTORY_MESSAGE);

    bool result = createPlayList(directoryPath);

    if (result) {
        createIndexFiles();
        cout << NEW_LINE << TAB << format(PLAYLIST_CREATED_SUCCESS_MESSAGE, musicFilePtr->registryQuantity())
             << NEW_LINE << TAB << INDEX_FILES_MESSAGE << endl;
    }
    else {
        cout << NEW_LINE << TAB << ERROR_DIRECTORY_MESSAGE << endl;
    }
}//create()


// Cria a Playlist a partir dos arquivos encontrados em um diretório fornecido
bool Playlist::createPlayList(const string& directoryPath) {

    // Verifica se o diretório está vazio
    if (!filesystem::exists(directoryPath) || filesystem::is_empty(directoryPath)) {
        return false;
    }

    bool playlistCreated = false;

    for (const auto& entry : filesystem::directory_iterator(directoryPath)) {
        // Verifica se o arquivo possui extensão correspondente a EXTENSION
        if (entry.path().extension() == EXTENSION) {
            string filename = entry.path().filename().stem().string();

            // Extrai artista e título do nome do arquivo MP3 (considerando um formato específico "Artista - Título)
            size_t pos = filename.find(DELIMITER);

            // Se encontrar o delimitador no nome do arquivo
            if (pos != string::npos) {
                // Extrai artista e título
                Music music(filename.substr(0, pos), filename.substr(pos + sizeof(DELIMITER) - 1, filename.length() - pos));
                vectorMusic.push_back(music);
                // Escreve a música no arquivo
                musicFilePtr->write(music);

                playlistCreated = true;
            }
        }
    }
    return playlistCreated;
}//createPlayList()

// Remove os arquivos relacionados à Playlist
void Playlist::removeFiles() {
    musicFilePtr->remove();
    titleIndexFilePtr->remove();
    artistIndexFilePtr->remove();
}//removeFiles()

// Cria os arquivos de índice por título e por artista para a Playlist
void Playlist::createIndexFiles() {
    createArtistIndexFile();
    createTitleIndexFile();
}//createIndexFiles()

// Cria o arquivo de índice por título usando os dados da Playlist
bool Playlist::createTitleIndexFile() {
    if (musicFilePtr->registryQuantity() == 0) {
        return false;
    }
    for (unsigned i = 0; i < vectorMusic.size(); i++) {
        vectorIndexTitle.push_back(Index(vectorMusic[i].getTitle(), i));
    }
    //Ordenando pelo título
    sort(vectorIndexTitle.begin(), vectorIndexTitle.end(), [](Index& a, Index& b) {
        return a.getPrimarykey() < b.getPrimarykey();
    });

    //Adicionano ao arquivo
    for (const auto& music : vectorIndexTitle) {
        titleIndexFilePtr->write(music);
    }
    return true;
}//createTitleIndexFile()

// Cria o arquivo de índice por artista usando os dados da Playlist
bool Playlist::createArtistIndexFile() {
    if (musicFilePtr->registryQuantity() == 0) {
        return false;
    }
    for (unsigned i = 0; i < vectorMusic.size(); i++) {
        vectorIndexArtist.push_back(Index(vectorMusic[i].getPerformer(), i));
    }
    //Ordenando pelo Artista
    sort(vectorIndexArtist.begin(), vectorIndexArtist.end(), [](Index& a, Index& b) {
        return a.getPrimarykey() < b.getPrimarykey();
    });

    //Adicionano ao arquivo
    for (const auto& music : vectorIndexArtist) {
        artistIndexFilePtr->write(music);
    }
    return true;
}//createArtistIndexFile()

// Exibe a Playlist ordenada por título
bool Playlist::displayByTitle() {
    if (musicFilePtr->registryQuantity() == 0) {
        cout << NEW_LINE << TAB << ERROR_EMPTY_PLAYLIST_MESSAGE << endl;
        return false;
    }
    vectorMusic.clear();
    for (unsigned registry = 0; registry < musicFilePtr->registryQuantity(); registry++) {
        optional<Music> optionalMusic = musicFilePtr->read(registry);
        if (optionalMusic.has_value()) {
            vectorMusic.push_back(optionalMusic.value());
        }
    }
    //Ordenando pelo título
    sort(vectorMusic.begin(), vectorMusic.end(), [](Music& a, Music& b) {
        return a.getTitle() < b.getTitle();
    });

    cout << NEW_LINE << CLASSIFIED_BY_TITLE_MESSAGE << NEW_LINE 
         << format(NUMBER_OF_MUSIC_MESSAGE, vectorMusic.size()) << endl;
    for (unsigned i = 0; i < vectorMusic.size(); i++) {
        cout << TAB << i + 1 << DOT << SPACE << vectorMusic[i].toString(true) << endl;
    }

    return true;
}//displayByTitle()

// Exibe a Playlist ordenada por artista
bool Playlist::displayByArtist() {
    if (musicFilePtr->registryQuantity() == 0) {
        cout << NEW_LINE << TAB << ERROR_EMPTY_PLAYLIST_MESSAGE << endl;
        return false;
    }
    vectorMusic.clear();
    for (unsigned registry = 0; registry < musicFilePtr->registryQuantity(); registry++) {
        optional<Music> optionalMusic = musicFilePtr->read(registry);
        if (optionalMusic.has_value()) {
            vectorMusic.push_back(optionalMusic.value());
        }
    }
    //Ordenando pelo artista
    sort(vectorMusic.begin(), vectorMusic.end(), [](Music& a, Music& b) {
        return a.getPerformer() < b.getPerformer();
     });

    cout << NEW_LINE << CLASSIFIED_BY_ARTIST_MESSAGE
         << NEW_LINE << format(NUMBER_OF_MUSIC_MESSAGE, vectorMusic.size()) << endl;
    for (unsigned i = 0; i < vectorMusic.size(); i++) {
        cout << TAB << i + 1 << DOT << SPACE << vectorMusic[i].toString() << endl;
    }

    return true;
}//displayByArtist()

// Realiza uma busca na Playlist por título ou artista e exibe os resultados
void Playlist::searchDisplay(bool isTitle) {

    string searchMusic;
    vector<int> indexVector;

    loadIndexesIfNeeded();

    if (isTitle) {
        searchMusic = getUserInput(ENTER_THE_MUSIC_MESSAGE);
        indexVector = searchSong(searchMusic);
        displaySearchResults(indexVector, false);
    }
    else {
        searchMusic = getUserInput(ENTER_THE_ARTIST_MESSAGE);
        indexVector = searchArtist(searchMusic);
        displaySearchResults(indexVector, true);
    }

    if (indexVector.empty()) {
        cout << TAB << format(ERROR_THERE_ARE_NO_MATCHES_MESSAGE, searchMusic) << endl;
    }
}//searchDisplay()

// Obtém entrada do usuário a partir de uma mensagem fornecida
string Playlist::getUserInput(const string& message) {
    clearBuffer();
    cout << NEW_LINE << message;
    string input;
    getline(cin, input);
    return input;
}//getUserInput()

// Exibe os resultados da busca por título ou artista na Playlist.
void Playlist::displaySearchResults(const vector<int>& indexVector, bool isTitle) {
    cout << NEW_LINE << TAB << NUMBER_OF_SONGS_FOUND << indexVector.size() << endl;
    for (int i = 0; i < indexVector.size(); i++) {
        const Music music = musicFilePtr->read(indexVector[i]).value();
        cout << TAB << music.toString(isTitle) << endl;
    }
}//displaySearchResults()

// Carrega os índices dos arquivos se necessário para realizar operações de busca.
void Playlist::loadIndexesIfNeeded() {
    if (musicFilePtr->registryQuantity() > 0) {
        if (vectorIndexArtist.empty()) {
            for (int i = 0; i < artistIndexFilePtr->registryQuantity(); i++) {
                vectorIndexArtist.push_back(artistIndexFilePtr->read(i).value());
            }
        }
        if (vectorIndexTitle.empty()) {
            for (int i = 0; i < titleIndexFilePtr->registryQuantity(); i++) {
                vectorIndexTitle.push_back(titleIndexFilePtr->read(i).value());
            }
        }
    }
}//loadIndexesIfNeeded()

// Realiza uma busca na Playlist por título e retorna um vetor de índices dos resultados
vector<int> Playlist::searchSong(string title) {
    return titleIndexFilePtr->search(vectorIndexTitle, title);
}//searchSong()

// Realiza uma busca na Playlist por Artista e retorna um vetor de índices dos resultados
vector<int> Playlist::searchArtist(string artist) {
    return artistIndexFilePtr->search(vectorIndexArtist, artist);
}//searchArtist()

// Limpa a tela da console quando uma tecla for precionada
void Playlist::clearDisplay() {
    cout << endl;
    cout << endl;
    system(PAUSE);
    system(CLEAR);
}//clearDisplay()

// Limpa o buffer do stream de entrada
void Playlist::clearBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), NEW_LINE);
}//clearBuffer()

// Exibe as opções disponíveis para interação com a Playlist na console
void Playlist::displayOption() {
    cout << NEW_LINE << PLAYLIST_TITLE_MESSAGE << NEW_LINE << NEW_LINE << TAB << OPTION_EXIT_MESSAGE << NEW_LINE
         << TAB << OPTION_CREATE_MESSAGE << NEW_LINE << TAB << OPTION_SHOW_BY_TITLE_MESSAGE
         << NEW_LINE << TAB << OPTION_SHOW_BY_ARTIST_MESSAGE << NEW_LINE
         << TAB  << OPTION_SEARCH_TITLE_MESSAGE << NEW_LINE << TAB << OPTION_SEARCH_ARTIST_MESSAGE
         << NEW_LINE << NEW_LINE << OPTION_CHOICE_MESSAGE;
}//displayOption()

/* Função principal que gerencia as interações com a Playlist
   Loop contínuo para apresentar opções e executar as funcionalidades selecionadas pelo usuário. */
int Playlist::playList() {
    setlocale(LC_ALL, UTF);

    while (true) {
        displayOption();
        int userChoice;
        cin >> userChoice;
     
        switch (static_cast<PlaylistOptions>(userChoice)) {
        case EXIT:
            return EXIT_SUCCESS;
            break;
        case CREATE: create();
            break;
        case DISPLAY_BY_TITLE:
            displayByTitle();
            break;
        case DISPLAY_BY_ARTIST:
            displayByArtist();
            break;
        case SEARCH_SONG:
            searchDisplay(true);
            break;
        case SEARCH_ARTIST:
            searchDisplay(false);
            break;
        default:
            cout << NEW_LINE << TAB << ERROR_INVALID_OPTION_MESSAGE;
            break;
        }
        clearDisplay();
    }
}//playList()

int main() {
    return Playlist().playList();
}//main()