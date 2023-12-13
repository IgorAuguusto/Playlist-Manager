# Playlist Manager

Este é um aplicativo para gerenciar playlists de músicas em formato MP3, permitindo a criação, organização e busca por músicas e artistas.

## Funcionalidades

### 1. Criar Playlist
Permite ao usuário fornecer um diretório contendo arquivos de músicas em formato MP3 com o seguinte formato:

![image](https://github.com/IgorAuguusto/Trabalho-LP/assets/82172424/44a80d50-6d1b-41d5-837a-36b0f27d308c)

Para o funcionamento é obrigatório que todas as músicas tenha o formato da imagem acima sendo: ```titulo - nome.mp3```

Os arquivos são lidos e armazenados em um arquivo de acesso aleatório chamado Playlist.dat. O programa extrai o nome do artista e o título da música do nome do arquivo MP3.

### 2. Exibir Playlist Ordenada por Título
Apresenta um relatório com todas as músicas do arquivo Playlist.dat ordenadas em ordem alfabética pelo título da música, mostrando o título seguido pelo nome do artista.

### 3. Exibir Playlist Ordenada por Nome do Artista
Apresenta um relatório com todas as músicas do arquivo Playlist.dat ordenadas em ordem alfabética pelo nome do artista, mostrando o nome do artista seguido pelo título da música.

### 4. Pesquisar Música
Permite ao usuário pesquisar uma música pelo título. O programa consulta o arquivo de índice ArqIndTituloMusica.dat para localizar a música no arquivo Playlist.dat e exibe o título da música seguido pelo nome do artista.

### 5. Pesquisar Artista
Permite ao usuário pesquisar um artista pelo nome. O programa consulta o arquivo de índice ArqIndArtista.dat para localizar as músicas associadas ao artista no arquivo Playlist.dat e exibe o nome do artista seguido pelo título das músicas.

## Implementação
O programa foi desenvolvido em C++ utilizando recursos do ISO C++20 Standard e Microsoft Visual Studio Community 2022. O acesso aos arquivos binários é feito usando a classe BinaryFile fornecida no projeto anexo Playlist.7z.

## Instruções de Uso
Para compilar e executar o programa:
1. Clone o repositório.
2. Abra o projeto no Visual Studio.
3. Compile o código.
4. Execute o programa e siga as instruções do menu para acessar as funcionalidades.

## Entrega
O programa foi desenvolvido individualmente para a entrega do trabalho acadêmico, seguindo todas as especificações fornecidas no enunciado.
