#include "Roomba.hpp"
#include "Constants.hpp"

Roomba::Roomba(float xInit, float yInit, float yawInit, float radiusInit,
	Program *program, const float *colorIn) :
	AnimatedEntity(Constants::defaultSpeed,
		Constants::roombaMass,xInit,yInit,yawInit,radiusInit,program),

	roombaBody {Circle(xInit,yInit,yawInit,radiusInit,
		Constants::white,program)},

	panelLarge {Rectangle(xInit,yInit,yawInit,radiusInit,
		color,program,radiusInit * 0.8f,radiusInit * 0.3f)},

	panelSmall {Rectangle(xInit,yInit,
		yawInit,radiusInit,color,program,radiusInit * 0.3f,radiusInit * 0.14f)}
{
	// Initialize color
	color[0] = colorIn[0];
	color[1] = colorIn[1];
	color[2] = colorIn[2];
	update();
}

void Roomba::update()
{
	// Set the position of the large panel
	float panelX {radius * 0.15f * (float)cos(yaw) * -1.0f + x};
	float panelY {radius * 0.15f * (float)cos(yaw) * -1.0f + y};
	panelLarge.setPosition(panelX,panelY);
	panelLarge.setYaw(yaw);
	panelLarge.update();
	// Set the position of the small panel
	panelSmall.setPosition(x,y);
	panelSmall.setYaw(yaw);
	panelSmall.update();
	// Set the position of the roombaBody
	roombaBody.setPosition(x,y);
	roombaBody.setYaw(yaw);
	roombaBody.update();
}

void Roomba::render()
{
	// Renders the parts of the roomba starting from the body and then the panels
	roombaBody.render();
	panelLarge.render();
	panelSmall.render();
}

char Roomba::getColor()
{
	if (color[0] > color[1] && color[0] > color[2])
	{
		return 'r';
	}
	else if (color[1] > color[0] && color[1] > color[2])
	{
		return 'g';
	}
	else if (color[2] > color[0] && color[2] > color[1])
	{
		return 'b';
	}
}
