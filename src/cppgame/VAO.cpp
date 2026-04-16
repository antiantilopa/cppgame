#include "include/VAO.h"
#include <glad/glad.h>
#include <iostream>

VAO::VAO(){
	glGenVertexArrays(1, &ID);
}
VAO::~VAO(){
	std::cout << "fuck...\n";
	return;
}
void VAO::LinkVBO(VBO& VBO, unsigned char mode, char dim){
	VBO.bind();
	if (dim == 2){
		glVertexAttribPointer(0, Vertex2d::POS_SIZE, GL_FLOAT, GL_FALSE, sizeof(Vertex2d), (void*)0);
		glEnableVertexAttribArray(0);
		if (mode && Vertex2d::POS_COLOR){
			glVertexAttribPointer(1, Vertex2d::COLOR_SIZE, GL_FLOAT, GL_FALSE, sizeof(Vertex2d), (void*)((long long)Vertex2d::offset_lookup[Vertex2d::POS]));
			glEnableVertexAttribArray(1);
		}
		if (mode && Vertex2d::POS_TEXTURE){
			glVertexAttribPointer(2, Vertex2d::TEXTURE_SIZE, GL_FLOAT, GL_FALSE, sizeof(Vertex2d), (void*)((long long)Vertex2d::offset_lookup[Vertex2d::POS_COLOR]));
			glEnableVertexAttribArray(2);
		}
	}
	if (dim == 3){
		glVertexAttribPointer(0, Vertex3d::POS_SIZE, GL_FLOAT, GL_FALSE, sizeof(Vertex3d), (void*)0);
		glEnableVertexAttribArray(0);
		if (mode && Vertex3d::POS_NORMAL){
			glVertexAttribPointer(1, Vertex3d::NORMAL_SIZE, GL_FLOAT, GL_FALSE, sizeof(Vertex3d), (void*)((long long)Vertex3d::offset_lookup[Vertex3d::POS]));
			glEnableVertexAttribArray(1);
		}
		if (mode && Vertex3d::POS_COLOR){
			glVertexAttribPointer(2, Vertex3d::COLOR_SIZE, GL_FLOAT, GL_FALSE, sizeof(Vertex3d), (void*)((long long)Vertex3d::offset_lookup[Vertex3d::POS_NORMAL]));
			glEnableVertexAttribArray(2);
		}
		if (mode && Vertex3d::POS_TEXTURE){
			glVertexAttribPointer(3, Vertex3d::TEXTURE_SIZE, GL_FLOAT, GL_FALSE, sizeof(Vertex3d), (void*)((long long)Vertex3d::offset_lookup[Vertex3d::POS_NORMAL_COLOR]));
			glEnableVertexAttribArray(3);
		}
	}
}

void VAO::LinkVBO(VBO& VBO, unsigned int layout, int size, int type, unsigned int stride, void* offset){
	VBO.bind();
	glVertexAttribPointer(layout, size, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	VBO.unbind();
}

void VAO::bind(){
	glBindVertexArray(ID);
}
void VAO::unbind(){
	glBindVertexArray(0);
}
void VAO::Delete(){
	glDeleteVertexArrays(1, &ID);
}