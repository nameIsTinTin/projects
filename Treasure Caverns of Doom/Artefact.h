#ifndef ARTEFACT_H
#define ARTEFACT_H

#include "Item.h"

class Artefact : public Item {
protected: 
	string itemDescription;
public: 
	Artefact();
	
	
	virtual void getDetails();
};



#endif