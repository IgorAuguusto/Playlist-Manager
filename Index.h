#pragma once

#include <string>

using namespace std;

/* 
    O objetivo desta classe é servir de base para construir um arquivo de índice que permita localizar um registro em um arquivo binário com acesso aleatório de acordo com o seu campo de identificação única (chave primária). 
*/
class Index {
public:
    Index(string primaryKey = "", unsigned registryNumber = 0);

    Index& setPrimarykey(string primarykey);
    Index& setRegistryNumber(unsigned registryNumber);

    string getPrimarykey();
    unsigned getRegistryNumber();

private:
    //  Representa o valor de um campo usado como chave primária para acessar um registro do arquivo. 
    string primarykey; 

    // Número do registro que possui no seu campo-chave um valor igual ao atributo da chave primária.
    unsigned registryNumber; 
};

