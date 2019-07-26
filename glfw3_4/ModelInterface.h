#ifndef MODELINTERFACE_H
#define MODELINTERFACE_H

class ModelInterface {

public:

	ModelInterface() = delete;

	ModelInterface(const Material& mat) : material(mat) {};
	
	const Material& material;
	
	virtual void RenderModel()  = 0;

	virtual ~ModelInterface() {};

};

#endif //MODELINTERFACE_H