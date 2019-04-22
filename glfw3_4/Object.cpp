#include "Object.h"



Object::Object(std::string name) : _name(name) , _model(), _transform(){};

void Object::UpdateDrawing() {
	std::cout << "\n update drawing not implemented";
}

Object::~Object()
{

}
