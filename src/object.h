#pragma once
#ifndef OBJECT_LOADER
#define OBJECT_LOADER

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

#include "GL/freeglut.h"

using namespace std;

class objectLoader 
{
public:
	typedef struct vec3f
	{
		float x;
		float y;
		float z;
	} vec3f;
	typedef struct fdata
	{
		vector<GLint> position;
		vector<GLint> normal;
		vector<GLint> texture;
	} fdata;
	objectLoader(const char*);
	void Draw(float);
private:
	vector<vec3f> v;
	vector<vec3f> vt;
	vector<vec3f> vn;
	vector<fdata> f;
};

#endif // !OBJECT_LOADER
