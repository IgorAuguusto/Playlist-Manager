#include "Index.h"

Index::Index(string primaryKey, unsigned registryNumber) : primarykey(primaryKey), registryNumber(registryNumber) {
}//Index

Index& Index::setPrimarykey(string primarykey) {
	this->primarykey = primarykey;
	return *this;
}//setPrimarykey()

Index& Index::setRegistryNumber(unsigned registryNumber) {
	this->registryNumber = registryNumber;
	return *this;
}//setRegistryNumber()

string Index::getPrimarykey() {
	return primarykey;
}//getPrimarykey()

unsigned Index::getRegistryNumber() {
	return registryNumber;
}//getRegistryNumber()