#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <GL/glew.h>
#include <SDL.h>

static bool g_run = true;
static float g_width = 800;
static float g_height = 600;

struct Point2 {
	float x, y;

	Point2() {
		x = 0.0f;
		y = 0.0f;
	}

	Point2(float x, float y) {
		this->x = x;
		this->y = y;
	}
};

struct Point3 {
	float x, y, z;

	Point3() {
		x = 0.0f;
		y = 0.0f;
	}

	Point3(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
};

struct Point4 {
	float x, y, z, w;

	Point4() {
		x = 0.0f;
		y = 0.0f;
	}

	Point4(float x, float y, float z, float w) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}
};

struct Triangle {
	int v1;
	int v2;
	int v3;

	Triangle() {
		v1 = 0;
		v2 = 0;
		v3 = 0;
	}

	Triangle(int v1, int v2, int v3) {
		this->v1 = v1;
		this->v2 = v2;
		this->v3 = v3;
	}
};

template<typename T>
class VertexBuffer {
	std::vector<T> vlist;
	unsigned int id;
public:

	VertexBuffer() {
		id = 0;
	}

	void add(T t) {
		vlist.push_back(t);
	}

	void clear() {
		vlist.clear();
	}

	void initialize() {

		if(id == 0) {
			glGenBuffers(1, &id);
		}

		glBindBuffer(GL_ARRAY_BUFFER, id);

		glBufferData(
			GL_ARRAY_BUFFER,
			this->size(),
			&this->vlist[0],
			GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	// Part C: All non-star, Part D: All - non-star
	void bind() {
		glBindBuffer(GL_ARRAY_BUFFER, id);
	}

	void unbind() {
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	
	void release() {
		glDeleteBuffers(1, &id);
		this->clear();
	}

	unsigned int typeSize() {
		return sizeof(T);
	}

	unsigned int count() {
		return vlist.size();
	}

	unsigned int size() {
		return typeSize() * count();
	}
};

class Texture2D {
	unsigned int id;
	int width, height;

public:

	Texture2D() {
		id = 0;
	}

	void initialize(std::string fn) {

	}

	void bind() {
		glBindTexture(GL_TEXTURE_2D, id);
	}

	void unbind() {
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void release() {
		glDeleteTextures(1, &id);
	}
};

class SM3Mesh {

};

int main(int argc, char** argv) {

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_WM_SetCaption("Physics Tests", 0);
	SDL_SetVideoMode(g_width, g_height, 32, SDL_OPENGL);

	glewInit();

	// enables / disables
	glEnable(GL_DEPTH_TEST);

	SDL_Event ev;

	float rot = 0.0f;

	while(g_run) {
		while(SDL_PollEvent(&ev)) {
			if(ev.type == SDL_QUIT) {
				g_run = false;
			}
		}


		rot += 1.0f;

		if(rot >= 360.0f) {
			rot -= 360.0f;
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45.0f, g_width/g_height, 1.0, 1000.0f);
		glMatrixMode(GL_MODELVIEW);

		glLoadIdentity();


		glPushMatrix();
		glTranslatef(0.0f, 0.0f, -5.0f);

		glBegin(GL_TRIANGLES);

		glVertex3f(-1.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, 0.0f);

		glVertex3f(-1.0f, -1.0f, 0.0f);
		glVertex3f(1.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, 0.0f);

		glEnd();

		glPopMatrix();

		SDL_GL_SwapBuffers();


		SDL_Delay(1000/60);
	}

	SDL_Quit();

	return 0;
}
