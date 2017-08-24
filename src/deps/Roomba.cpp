#include "Roomba.hpp"
#include "Constants.hpp"

Roomba::Roomba(float xInit, float yInit, float angleInit, float radiusInit,
	Program *program, float *color) : AnimatedEntity() : Entity(xInit,yInit,yawInit,radiusInit,program),
	color {color[0],color[1],color[2]}, roombaBody {Circle(xInit,yInit,angleInit,radiusInit,
	program,[]{1.0f,1.0f,1.0f})}, panelLarge {Rectangle(xInit,yInit,angleInit,radiusInit,
	program,color,radiusInit * 0.7f,radiusInit * 0.3f)}, panelSmall {Rectangle(xInit,yInit,
	angleInit,radiusInit,program,color,radiusInit * 0.3f,radiusInit * 0.14f)}
{

}
