#include "Artefact.h"

/// <summary>
/// This is the class of Artefacts 
/// </summary>
Artefact::Artefact() {
	itemDescription = "";
	healHealth = 0;
	dealDamage = 0;
	defenseAmount = 0;
}



void Artefact::getDetails() {
	cout << "**********************************" << endl;
	cout << "ARTEFACT NAME: " << getItemName() << endl;
	if (itemProperty == ARMOUR) {
		cout << "ARTEFACT DEFENSE: " << getItemDefense() << endl;
	}
	if (itemProperty == WEAPON) {
		cout << "ARTEFACT DAMAGE: " << getItemDamage() << endl;
	}
	if (itemProperty == ITEM) {
		cout << "ARTEFACT HEALING: " << getItemHealing() << endl;
	}
	if (itemProperty == ARTEFACT) {
		cout << "ARTEFACT DAMAGE: ??????" << endl; 
		cout << "ARTEFACT DEFENSE: ???????" << endl; 
		cout << "ARTEFACT HEALING: ???????" << endl;
	}
	cout << "ARTEFACT DESCRIPTION: " << getItemDescription() << endl;
}