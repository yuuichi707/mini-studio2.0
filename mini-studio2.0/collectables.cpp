#include "collectables.h"

collectables::collectables() : isCollected(false), isColectible(true)
{
}

collectables::~collectables()
{
}

bool collectables::getIsColectible() const
{
	return false;
}

bool collectables::getIsCollected() const
{
	return false;
}