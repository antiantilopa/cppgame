#include "include/mesh.h"
#include <iostream>

std::vector<Texture> Mesh::EMPTY_TEXTURE_VECTOR = {};

Mesh::Mesh(std::vector <Vertex3d>& vertices, unsigned char mode, std::vector <unsigned int>& indices, std::vector <Texture>& textures){
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;

	VAO* new_vao = new VAO();
    this->vao = new_vao;
	vao->bind();
	// Generates Vertex Buffer Object and links it to vertices
	vbo = new VBO(vertices, mode);
	// Generates Element Buffer Object and links it to indices
	ebo = new EBO(indices);
	// Links VBO attributes such as coordinates and colors to VAO
	vao->LinkVBO(*vbo, mode, (char)3);
	// Unbind all to prevent accidentally modifying them
	vao->unbind();
	vbo->unbind();
	ebo->unbind();
}

void Mesh::draw(Shader& shader, Camera* camera){
	if (camera == nullptr){
		camera = Camera::main_camera_ptr;
	}
	if (camera == nullptr){
		std::cerr << "camera was not given, and main camera not initialized.\n";
		throw "forgot the camera ahh error";
	}
	// Bind shader to be able to access uniforms
	shader.activate();
	this->vao->bind();
	this->vbo->bind();
	this->ebo->bind();

	// Keep track of how many of each type of textures we have
	unsigned int numDiffuse = 0;
	unsigned int numSpecular = 0;

	for (unsigned int i = 0; i < textures.size(); i++)
	{
		std::string num;
		std::string type = textures[i].type;
		if (type == "diffuse")
		{
			num = std::to_string(numDiffuse++);
		}
		else if (type == "specular")
		{
			num = std::to_string(numSpecular++);
		}
		textures[i].texUnit(shader, (type + num).c_str(), i);
		textures[i].bind();
	}
	// Take care of the camera Matrix
	glm::vec3 cam_pos = camera->getPos();
	glUniform3f(glGetUniformLocation(shader.ID, "cam_pos"), cam_pos.x, cam_pos.y, cam_pos.z);
	camera->setMatrixUniform(shader, "cam_matrix");
	// draw the actual mesh
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	this->vao->unbind();
	this->vbo->unbind();
	this->ebo->unbind();
}
