#include<format>
#include "Playlist.h"
#include <iostream>
#include "Music.h"

Music::Music(string performer, string title) : performer(performer), title(title) {
	this->quantityOfMusic++;
}//Music

Music& Music::setTitle(string title) {
	this->title = title;
	return *this;
}//setTitle()

Music& Music::setPerformer(string performer) {
	this->performer = performer;
	return *this;
}//setPerformer()

string Music::getTitle() const {
	return title;
}//getTitle()

string Music::getPerformer() const {
	return performer;
}

unsigned Music::quantityOfMusics() {
	return quantityOfMusic;
}
//getPerformer()

/* Retorna os atributos da música usando o formato <performer> - <title>.

			Exemplos: Imagine Dragons - My Live (Live in Vegas)
					  Imagine Dragons - Whatever It Takes (Live in Vegas)
	*/
string Music::toString() const {
	return format("{} - {}", getPerformer(), getTitle());
}//toString()

string Music::toString(bool isFirstTitle) const {
	return format("{} - {}", getTitle(), getPerformer());
}//toString()
