#include "Geode.h"

#include <iostream>

using namespace std;

Geode::Geode() 
{}

void Geode::draw(Matrix4 model)
{
	render(model);
}