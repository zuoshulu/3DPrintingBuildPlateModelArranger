#pragma once
#include "Model.h"

class BuildPlate
{
public:
	BuildPlate(int length_, int width_) : length(length_), width(width_), x(0), y(0), shelfWidth(0){}
	template <class M> bool arrangeModel(M models);
	
private:
	int length;
	int width;
	
	int x;
	int y;
	int shelfWidth;

	bool placing(Model& model);
};