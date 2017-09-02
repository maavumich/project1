#include "Obstacle.hpp"

Obstacle::Obstacle(float xInit, float yInit, float yawInit, float radiusInit,
	const float *colorIn,Program *program) :

	AnimatedEntity(Constants::roombaMass, xInit, yInit, yawInit, radiusInit,
		Constants::obstacleRestitution, program),

	border {Circle(xInit,yInit,yawInit,radiusInit,
		colorIn,program)},

	roombaBody {Circle(xInit,yInit,yawInit,radiusInit * 0.98f,
		Constants::white,program)},

	pillar {Circle(xInit,yInit,yawInit,radiusInit * 0.5f,
		Constants::pillarWhite,program)},

	outerBorder {Circle(xInit,yInit,yawInit,radiusInit * 0.52f,
		Constants::black,program)},

	innerBorder {Circle(xInit,yInit,yawInit,radiusInit * 0.46f,
		Constants::black,program)},

	insidePillar {Circle(xInit,yInit,yawInit,radiusInit * 0.44f,
		Constants::inPillar,program)}
{
	update(0);
}

void Obstacle::update(unsigned dt)
{
	// update position based on velocity
	AnimatedEntity::update(dt);
	// Updates the posiion of all subobjects and calls their update functions
	border.setPosition(x,y);
	border.update(dt);
	roombaBody.setPosition(x,y);
	roombaBody.update(dt);
	pillar.setPosition(x,y);
	pillar.update(dt);
	outerBorder.setPosition(x,y);
	outerBorder.update(dt);
	innerBorder.setPosition(x,y);
	innerBorder.update(dt);
	insidePillar.setPosition(x,y);
	insidePillar.update(dt);
}

void Obstacle::render()
{
	// Renders all subcomponents in the correct order
	border.render();
	roombaBody.render();
	outerBorder.render();
	pillar.render();
	innerBorder.render();
	insidePillar.render();
}
