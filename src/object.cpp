#include "object.h"

objectLoader::objectLoader(const char* filename)
{
	ifstream file(filename, ios::in | ios::binary);
	string line;
	while (getline(file, line))
	{
		//printf("%s\n", line.c_str());
		if (line.substr(0, 1) == "v")
		{
			vec3f point;
			istringstream s(line.substr(2));
			s >> point.x; s >> point.y; s >> point.z;
			if (line.substr(0, 2) == "t")
				vt.push_back(point);
			else if (line.substr(0, 2) == "vn")
				vn.push_back(point);
			else
				v.push_back(point);
		}
		else if (line.substr(0, 1) == "f")
		{
			fdata face;
			GLint position, normal, texture;
			string symbol;
			istringstream vtns(line.substr(2));

			for (int i = 0; i < 4; ++i)
			{
				vtns >> position;
				face.position.push_back(position);
				vtns >> symbol;
				if (symbol == "")
					break;

				if (symbol.substr(1, 1) == "/")
				{
					istringstream s(symbol.substr(2));
					s >> normal;
					face.normal.push_back(normal);
				}
				else
				{
					istringstream s(symbol.substr(1));
					string symbol2;
					s >> texture;
					face.texture.push_back(texture);
					s >> symbol2;
					if (symbol2 != "") {
						istringstream ss(symbol2.substr(1));
						ss >> normal;
						face.normal.push_back(normal);
					}
				}
			}
			f.push_back(face);
		}
	}
	file.close();
	/*for (size_t i = 0; i < v.size(); ++i)
	{
		printf("v[%u]: vn: %f %f %f\n", i, v[i].x, v[i].y, v[i].z);
	}
	for (size_t i = 0; i < f.size(); ++i) {
		printf("f[%u]: vn: %d %d %d\n", i, f[i].normal[0], f[i].normal[1], f[i].normal[2]);
	}*/
	printf("load %s done.\n", filename);
}

void objectLoader::Draw(float zoom)
{
	glBegin(GL_TRIANGLES);

	for (size_t i = 0; i < f.size(); i++) {
		GLfloat VN[3];
		vec3f a, b, c;

		GLint firstVertexIndex = f[i].position[0] - 1;
		GLint secondVertexIndex = f[i].position[1] - 1;
		GLint thirdVertexIndex = f[i].position[2] - 1;

		a.x = v[firstVertexIndex].x / zoom;
		a.y = v[firstVertexIndex].y / zoom;
		a.z = v[firstVertexIndex].z / zoom;

		b.x = v[secondVertexIndex].x / zoom;
		b.y = v[secondVertexIndex].y / zoom;
		b.z = v[secondVertexIndex].z / zoom;

		c.x = v[thirdVertexIndex].x / zoom;
		c.y = v[thirdVertexIndex].y / zoom;
		c.z = v[thirdVertexIndex].z / zoom;

		GLfloat vec1[3], vec2[3], vec3[3];//计算法向量
		//(x2-x1,y2-y1,z2-z1)
		vec1[0] = a.x - b.x;
		vec1[1] = a.y - b.y;
		vec1[2] = a.z - b.z;

		//(x3-x2,y3-y2,z3-z2)
		vec2[0] = a.x - c.x;
		vec2[1] = a.y - c.y;
		vec2[2] = a.z - c.z;

		//(x3-x1,y3-y1,z3-z1)
		vec3[0] = vec1[1] * vec2[2] - vec1[2] * vec2[1];
		vec3[1] = vec2[0] * vec1[2] - vec2[2] * vec1[0];
		vec3[2] = vec2[1] * vec1[0] - vec2[0] * vec1[1];

		GLfloat D = (GLfloat)sqrt(pow(vec3[0], 2) + pow(vec3[1], 2) + pow(vec3[2], 2));

		VN[0] = vec3[0] / D;
		VN[1] = vec3[1] / D;
		VN[2] = vec3[2] / D;

		glNormal3f(VN[0], VN[1], VN[2]);

		glVertex3f(a.x, a.y, a.z);
		glVertex3f(b.x, b.y, b.z);
		glVertex3f(c.x, c.y, c.z);
	}
	glEnd();
}
