#include "Entity.hpp"

Entity::Entity(float xInit, float yInit, float angleInit, float radiusInit,
	unsigned int shaderProgramIdIn, float arenaSizeXIn, float arenaSizeYIn) :
	x {xInit}, y {yInit}, angle {angleInit}, radius {radiusInit},
	shaderProgramId {shaderProgramIdIn}, arenaSizeX {arenaSizeXIn}, arenaSizeY {arenaSizeYIn}
{

}
