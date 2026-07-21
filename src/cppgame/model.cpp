#include "include/model.h"
#include <iostream>


Model::Model(const char* file){
    this->file = file;
    std::string text = getFileContents(file);
    JSON = json::parse(text);
    data = getData();
    traverseNode(0);
}

Model::Model(std::filesystem::path& file){
    std::string temp = file.u8string();
    this->file = temp.c_str();
    std::string text = getFileContents(file);
    JSON = json::parse(text);
    data = getData();
    traverseNode(0);
}

Model::Model(std::string& file){
    this->file = file.c_str();
    std::string text = getFileContents(file);
    JSON = json::parse(text);
    data = getData();
    traverseNode(0);
}

void Model::draw(
    Shader& shader, 
    Camera& camera, 
    glm::vec3 trans, 
    glm::quat rot, 
    glm::vec3 scale){
    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    float white[3] = {1.0f, 1.0f, 1.0f};
    shader.setUniform("color", white, 3);
    if (glGetError() == GL_INVALID_OPERATION){
		std::cout << "this is written once btw flag 2\n";
		throw std::runtime_error("FUCK!!!!");
	}
    for (unsigned int i = 0; i < meshes.size(); i++){
        meshes[i].draw(shader, &camera, matrices[i], trans, rot, scale);
    }
}

std::vector<unsigned char> Model::getData(){
    // uri is a file name; file has binary data
    std::filesystem::path uri = std::filesystem::path(std::string(this->JSON["buffers"][0]["uri"]));
    std::filesystem::path file_path = std::filesystem::path(this->file);
    std::filesystem::path file_folder = file_path.parent_path();
    std::string binary_text = getFileContents(file_folder / uri);
    std::vector<unsigned char> data(binary_text.begin(), binary_text.end());
    return data;
}

std::vector<float> Model::getFloats(json accessor){
    std::vector<float> floats;

    unsigned int buffer_view_ind = accessor.value("bufferView", 1);
    // how many floats to get
    unsigned int count = accessor["count"]; 
    // where to get data with respect to buffer view byte offset
    unsigned int accessor_byte_offset = accessor.value("byteOffset", 0);
    
    // either 'SCALAR', 'VEC2', 'VEC3', 'VEC4'
    std::string type = accessor["type"];

    char num = 0;
    if (type == "SCALAR") num = 1;
    else if (type == "VEC2") num = 2;
    else if (type == "VEC3") num = 3;
    else if (type == "VEC4") num = 4;
    else throw "invalid type of accessor: '" + type + "'";

    json buffer_view = JSON["bufferViews"][buffer_view_ind];
    // where buffer view starts
    unsigned int byte_offset = buffer_view["byteOffset"];

    unsigned int beginning_of_data = byte_offset + accessor_byte_offset;
    unsigned int length_of_data = count * 4 * num;
    float val;
    floats.reserve(count * num);
    for (unsigned int i = beginning_of_data; i < beginning_of_data + length_of_data; i += 4){
        std::memcpy(&val, data.data() + i, 4);
        floats.push_back(val);
    }
    return floats;
}


std::vector<unsigned int> Model::getIndices(json accessor){
    std::vector<unsigned int> indices;

    unsigned int buffer_view_ind = accessor.value("bufferView", 1);
    // how many floats to get
    unsigned int count = accessor["count"]; 
    // where to get data with respect to buffer view byte offset
    unsigned int accessor_byte_offset = accessor.value("byteOffset", 0);
    
    // 
    unsigned int type = accessor["componentType"];
    char num = 0;
    if (type == 5125) num = 4;
    else if (type == 5123) num = 2;
    else if (type == 5122) num = 2;
    else throw "invalid type of accessor";

    json buffer_view = JSON["bufferViews"][buffer_view_ind];
    // where buffer view starts
    unsigned int byte_offset = buffer_view["byteOffset"];

    unsigned int beginning_of_data = byte_offset + accessor_byte_offset;
    unsigned int length_of_data = count * num;

    unsigned short val2;
    short val3;
    if (type == 5125){
        indices.resize(count);
        if (count > 0) {
            std::memcpy(indices.data(), data.data() + beginning_of_data, length_of_data);
        }
        return indices;
    }
    else if (type == 5123){
        indices.reserve(count);
        for (unsigned int i = beginning_of_data; i < beginning_of_data + length_of_data; i += num){
            std::memcpy(&val2, data.data() + i, num);
            indices.push_back((unsigned int) val2);
        }
        return indices;
    }
    else if (type == 5122){
        indices.reserve(count);
        for (unsigned int i = beginning_of_data; i < beginning_of_data + length_of_data; i += num){
            std::memcpy(&val3, data.data() + i, num);
            indices.push_back((unsigned int) val3);
        }
        return indices;
    }
    else{
        throw "umm, wtf ahh error.  Really, what the actual fuck?";
    }
}

std::vector<glm::vec2> Model::groupFloatsVec2(std::vector<float> floats){
    std::vector<glm::vec2> vectors;
    for (unsigned int i = 0; i < floats.size(); ){
        vectors.push_back(glm::vec2(floats[i++], floats[i++]));
    }
    return vectors;
}

std::vector<glm::vec3> Model::groupFloatsVec3(std::vector<float> floats){
    std::vector<glm::vec3> vectors;
    for (unsigned int i = 0; i < floats.size(); ){
        vectors.push_back(glm::vec3(floats[i++], floats[i++], floats[i++]));
    }
    return vectors;
}

std::vector<glm::vec4> Model::groupFloatsVec4(std::vector<float> floats){
    std::vector<glm::vec4> vectors;
    for (unsigned int i = 0; i < floats.size(); ){
        vectors.push_back(glm::vec4(floats[i++], floats[i++], floats[i++], floats[i++]));
    }
    return vectors;
}

std::vector<Vertex3d> Model::assembleVertices(
    std::vector<glm::vec3> positions,
    std::vector<glm::vec3> normals,
    std::vector<glm::vec2> tex_coords
){
    std::vector<Vertex3d> result;
    for (unsigned int i = 0; i < positions.size(); i++){
        result.push_back(Vertex3d{
            positions[i],
            normals[i],
            glm::vec3(1.0, 1.0, 1.0),
            tex_coords[i]
        });
    }
    return result;
}

std::vector<Texture> Model::getTextures(){
    std::vector<Texture> textures;

    std::filesystem::path file_path = std::filesystem::path(this->file);
    std::filesystem::path file_folder = file_path.parent_path();

    for (unsigned int i = 0; i < JSON["images"].size(); i++){
        std::string tex_path_str = JSON["images"][i]["uri"];

        bool skip = false;
        for (unsigned int j = 0; i < loaded_tex_names.size(); i++){
            if (tex_path_str == loaded_tex_names[j]){
                textures.push_back(loaded_textures[j]);
                skip = true;
                break;
            }
        }
        if (skip) continue;
        if (tex_path_str.find("baseColor") != std::string::npos){
            // this have to become a variable, and cannot be passed in as an argument right away
            std::filesystem::path tex_path = file_folder / std::filesystem::path(tex_path_str);
            Texture tex = Texture(tex_path, "diffuse", loaded_textures.size(), Texture::LINEAR);
            textures.push_back(tex); 
            loaded_textures.push_back(tex);
            loaded_tex_names.push_back(tex_path_str);
        }
        else if (tex_path_str.find("metallicRoughness") != std::string::npos){
            // this have to become a variable, and cannot be passed in as an argument right away
            std::filesystem::path tex_path = file_folder / std::filesystem::path(tex_path_str);
            Texture tex = Texture(tex_path, "specular", loaded_textures.size(), Texture::LINEAR);
            textures.push_back(tex); 
            loaded_textures.push_back(tex);
            loaded_tex_names.push_back(tex_path_str);
        }
    }
    return textures;
}

void Model::loadMesh(unsigned int mesh_ind){
    unsigned int position_accessor_ind = JSON["meshes"][mesh_ind]["primitives"][0]["attributes"]["POSITION"];
    unsigned int normal_accessor_ind = JSON["meshes"][mesh_ind]["primitives"][0]["attributes"]["NORMAL"];
    unsigned int tex_coord_accessor_ind = JSON["meshes"][mesh_ind]["primitives"][0]["attributes"]["TEXCOORD_0"];
    unsigned int indices_accessor_ind = JSON["meshes"][mesh_ind]["primitives"][0]["indices"];

    std::vector<glm::vec3> positions = groupFloatsVec3(getFloats(JSON["accessors"][position_accessor_ind]));
    std::vector<glm::vec3> normals = groupFloatsVec3(getFloats(JSON["accessors"][normal_accessor_ind]));
    std::vector<glm::vec2> tex_coords = groupFloatsVec2(getFloats(JSON["accessors"][tex_coord_accessor_ind]));

    for (unsigned int i = 0; i < tex_coords.size(); i++){
        tex_coords[i] = glm::mat2(0.0f, 1.0f, 1.0f, 0.0f) * tex_coords[i];
        tex_coords[i].y = 1 - tex_coords[i].y;
    }

    std::vector<unsigned int> indices = getIndices(JSON["accessors"][indices_accessor_ind]);

    std::vector<Vertex3d> vertices = assembleVertices(positions, normals, tex_coords);
    std::vector<Texture> textures = getTextures();

    meshes.push_back(Mesh(vertices, Vertex3d::POS_NORMAL_COLOR_TEXTURE, indices, textures));
}

void Model::traverseNode(unsigned int next_node_ind, glm::mat4 prev_matrix){
    json node = JSON["nodes"][next_node_ind];

    glm::vec3 _trans = glm::vec3(0.0f, 0.0f, 0.0f);
    if (node.find("translation") != node.end()){
        float temp_trans[3];
		for (unsigned int i = 0; i < node["translation"].size(); i++){
			temp_trans[i] = (node["translation"][i]);
        }
		_trans = glm::make_vec3(temp_trans);
    }

    glm::quat _rot = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
	if (node.find("rotation") != node.end()){
		float temp_rot[4] = {
			node["rotation"][3],
			node["rotation"][0],
			node["rotation"][1],
			node["rotation"][2]
		};
		_rot = glm::make_quat(temp_rot);
	}

    glm::vec3 _scale = glm::vec3(1.0f, 1.0f, 1.0f);
	if (node.find("scale") != node.end()){
		float temp_scale[3];
		for (unsigned int i = 0; i < node["scale"].size(); i++){
			temp_scale[i] = (node["scale"][i]);
        }
		_scale = glm::make_vec3(temp_scale);
	}

    glm::mat4 matrix = glm::mat4(1.0f);
	if (node.find("matrix") != node.end()){
		float temp_matrix[16];
		for (unsigned int i = 0; i < node["matrix"].size(); i++){
			temp_matrix[i] = (node["matrix"][i]);
        }
		matrix = glm::make_mat4(temp_matrix);
	}
    glm::mat4 trans = glm::translate(_trans);
	glm::mat4 rot = glm::mat4_cast(_rot);
	glm::mat4 scale = glm::scale(_scale);

    glm::mat4 full_mat = prev_matrix * matrix * trans * rot * scale;
    
    if (node.find("mesh") != node.end()){
		translations.push_back(_trans);
		rotations.push_back(_rot);
		scales.push_back(_scale);
		matrices.push_back(full_mat);
		loadMesh(node["mesh"]);
	}

    if (node.find("children") != node.end()){
		for (unsigned int i = 0; i < node["children"].size(); i++){
			traverseNode(node["children"][i], full_mat);
        }
	}
}
