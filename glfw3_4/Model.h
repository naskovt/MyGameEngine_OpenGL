#ifndef MODEL_H
#define MODEL_H


class Model
{
public:
	Model();
	~Model();

private:
	float* _vertices;
	unsigned int* _indices;
};

#endif
