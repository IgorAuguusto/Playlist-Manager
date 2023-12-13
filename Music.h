#pragma once

#include <string>

using namespace std;

/*
	Esta classe representa os atributos da música.
*/
class Music {
public:
	static const size_t STRING_SIZE = 128;

	Music(string performer = "", string title = "");

	Music& setTitle(string title);
	Music& setPerformer(string performer);

	string getTitle() const;
	string getPerformer() const;
	// retorna a quantidade de músicas
	static unsigned quantityOfMusics();

	/* Retorna os atributos da música usando o formato <performer> - <title>.
	 
			Exemplos: Imagine Dragons - My Live (Live in Vegas)
					  Imagine Dragons - Whatever It Takes (Live in Vegas)
	*/ 
	string toString() const;

	/* Retorna os atributos da música usando o formato <title> - <performer>.

			Exemplos: My Live (Live in Vegas) - Imagine Dragons 
					  Whatever It Takes (Live in Vegas) - Imagine Dragons
	*/
	string toString(bool isFirstTitle) const;
private:
	string title, // Título da música.
		   performer; // Nome do cantor(a) ou banda.

	// Contabiliza o número de objetos criados.
	inline static unsigned quantityOfMusic = 0;
};

