#include "include/font.h"

using namespace CppGame;

FBO* Font::fbo = nullptr;
VAO* Font::vao = nullptr;
VBO* Font::vbo = nullptr;

void Font::init(){
    Font::fbo = new FBO();
    Font::vao = new VAO();
    vao->bind(); 
    Font::vbo = new VBO(std::vector<Vertex2d>(), Vertex2d::POS_TEXTURE, 196608); // 1024 characters
    vao->LinkVBO(*vbo, Vertex2d::POS_TEXTURE, (char)2);

    vao->unbind();
    vbo->unbind();
}

FontData& getFontdata(char* data){
    FontData& result = *new FontData();
    for (int i = 0; i < 256; i++){
        result.char_width[i]    = data[4 * i];
        result.char_height[i]   = data[4 * i + 1];
        result.char_offset_x[i] = data[4 * i + 2];
        result.char_offset_y[i] = data[4 * i + 3];
    }
    return result;
}

Font::Font(Texture& font_texture, FontData& font_data){
    this->font_texture = &font_texture;
    this->font_data = &font_data;
    this->cache = std::unordered_map<std::string, Texture*>();
}

Font::Font(std::filesystem::path& font_path){
    std::filesystem::path parent_folder = font_path.parent_path();
    std::string file = getFileContents(font_path);
    std::string data = file.substr(0, 512);
    FontData& font_data_ = getFontdata(data.data());
    std::filesystem::path texture_path = parent_folder / std::filesystem::path(file.substr(512, file.size()));
    Texture* font_texture = new Texture(texture_path);
    this->font_texture = font_texture;
    this->font_data = &font_data_;
    this->fbo = new FBO();
}

Font::Font(std::string& font_path_str){
    std::filesystem::path font_path = std::filesystem::path(font_path_str);
    std::filesystem::path parent_folder = font_path.parent_path();
    std::string file = getFileContents(font_path);
    std::string data = file.substr(0, 512);
    FontData& font_data_ = getFontdata(data.data());
    std::filesystem::path texture_path = parent_folder / std::filesystem::path(file.substr(512, file.size()));
    Texture* font_texture = new Texture(texture_path);
    this->font_texture = font_texture;
    this->font_data = &font_data_;
    this->fbo = new FBO();
}

Font::Font(const char* font_path_char){
    std::filesystem::path font_path = std::filesystem::path(font_path_char);
    std::filesystem::path parent_folder = font_path.parent_path();
    std::string file = getFileContents(font_path);
    std::string data = file.substr(0, 512);
    FontData& font_data_ = getFontdata(data.data());
    std::filesystem::path texture_path = parent_folder / std::filesystem::path(file.substr(512, file.size()));
    Texture* font_texture = new Texture(texture_path);
    this->font_texture = font_texture;
    this->font_data = &font_data_;
    this->fbo = new FBO();
}

void Font::render(std::string text, Texture& output, int x, int y, Shader& shader, int size){
    fbo->bindTexture(output);
    fbo->setup();
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
        std::cout << "FBO is not complete:" << glCheckFramebufferStatus(fbo->ID);
    }
    shader.activate();
    shader.setUniform("window_width", (float)output.width);
    shader.setUniform("window_height", (float)output.height);
    __raw_draw(text, x, y, shader);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
        std::cout << "FBO is not complete:" << glCheckFramebufferStatus(fbo->ID);
    }
    fbo->unbind();
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
        std::cout << "FBO is not complete:" << glCheckFramebufferStatus(fbo->ID);
    }
}

void Font::__raw_draw(std::string text, int x, int y, Shader& shader, int size){
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // glClear(GL_COLOR_BUFFER_BIT);
    // glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    shader.activate();
    font_texture->bind();
    font_texture->texUnit(shader, "font_texture");
    std::vector<Vertex2d> vertices;
    vertices.reserve(text.size() * 6);
    float char_w;
    float char_h;
    float char_real_w;
    float char_real_h;
    float next_char_pos_x = 0.0f;
    float next_char_pos_y = 0.0f;
    float char_offset_x;
    float char_offset_y;
    unsigned char c;
    bool await_stx = false;
    bool escape_dle = false;
    bool escape_esc = false;
    bool space_sp = false;
    for (unsigned int i = 0; i < text.size(); i++){
        c = text[i];
        if (escape_esc) {continue; escape_esc = false;}
        if (!escape_dle){
        if (c == '\x00') continue;        // nul
        if (c == '\x01') await_stx=true;  // soh
        if (c == '\x02') await_stx=false; // stx
        if (c == '\x03') return;          // etx
        if (c == '\x04') break;           // eot
        if (c == '\x05') continue;        // enq TODO (never)
        if (c == '\x06') continue;        // ack TODO (never)
        if (c == '\x07') continue;        // bel TODO
        if (c == '\x08') { next_char_pos_x -= char_real_w; continue;}                                 // bs
        if (c == '\x09') { next_char_pos_x += font_texture->width / 8.0f; continue; }     // ht 
        if (c == '\x0A') { next_char_pos_y += font_texture->height / 16.0f; continue; }   // lf
        if (c == '\x0B') continue;                                                                    // vt  TODO (never)
        if (c == '\x0C') continue;                                                                    // ff  TODO (never)
        if (c == '\x0D') { next_char_pos_x = 0.0f; continue; }                                        // cr
        if (c == '\x0E') continue;                                                                    // so  TODO (never)
        if (c == '\x0F') continue;                                                                    // si  TODO (never)
        if (c == '\x10') { escape_dle = true; continue; }                                             // dle
        if (c == '\x11') continue;                                                                    // dc1 TODO (never)
        if (c == '\x12') continue;                                                                    // dc2 TODO (never)
        if (c == '\x13') continue;                                                                    // dc3 TODO (never)
        if (c == '\x14') continue;                                                                    // dc4 TODO (never)
        if (c == '\x15') continue;                                                                    // nak TODO (never)
        if (c == '\x16') continue;                                                                    // syn TODO (never)
        if (c == '\x17') continue;                                                                    // etb TODO (never)
        if (c == '\x18') continue;                                                                    // can TODO (never)
        if (c == '\x19') continue;                                                                    // em  TODO (never)
        if (c == '\x1A') continue;                                                                    // sub TODO (never)
        if (c == '\x1B') { escape_esc = true; continue; }                                             // esc
        if (c == '\x1C') continue;                                                                    // fs  TODO (never)
        if (c == '\x1D') continue;                                                                    // gs  TODO (never)
        if (c == '\x1E') continue;                                                                    // rs  TODO (never)
        if (c == '\x1F') continue;                                                                    // us  TODO (never)
        if (c == '\x20') space_sp = true;                                                             // sp  
        if (c == '\x7F') continue;                                                                    // del TODO (never)
        }
        if (await_stx) continue;
        escape_dle = false;
        char_w = (float) font_data->char_width[c];
        char_h = (float) font_data->char_height[c]; 
        char_real_w = char_w * (float)size * font_texture->width / 256.0f;
        char_real_h = char_h * (float)size * font_texture->height / 256.0f;
        char_offset_x = ((float) font_data->char_offset_x[c]) / 16.0f;
        char_offset_y = ((float) font_data->char_offset_y[c]) / 16.0f;
        if (space_sp){ next_char_pos_x += char_real_w; space_sp = false; continue; }
        Vertex2d vert1 = Vertex2d();
        vert1.position = glm::vec2(x + next_char_pos_x, y + next_char_pos_y);
        vert1.texture = glm::vec2((c % 16) + char_offset_x, 16 - (c / 16) - char_offset_y);
        vertices.push_back(vert1);
        Vertex2d vert2 = Vertex2d();
        vert2.position = glm::vec2(x + next_char_pos_x + char_real_w, y + next_char_pos_y);
        vert2.texture = glm::vec2((c % 16) + char_offset_x + char_w / 16.0f, 16 - (c / 16) - char_offset_y);
        vertices.push_back(vert2);
        Vertex2d vert3 = Vertex2d();
        vert3.position = glm::vec2(x + next_char_pos_x, y + next_char_pos_y + char_real_h);
        vert3.texture = glm::vec2((c % 16) + char_offset_x, 16 - (c / 16) - char_offset_y - char_h / 16.0f);
        vertices.push_back(vert3);
        vertices.push_back(vert2);
        vertices.push_back(vert3);
        Vertex2d vert4 = Vertex2d();
        vert4.position = glm::vec2(x + next_char_pos_x + char_real_w, y + next_char_pos_y + char_real_h);
        vert4.texture = glm::vec2((c % 16) + char_offset_x + char_w / 16.0f, 16 - (c / 16) - char_offset_y - char_h / 16.0f);
        vertices.push_back(vert4);
        next_char_pos_x += char_real_w;
    }
    Font::vao->bind();
    Font::vbo->rewrite(vertices);
    Font::vbo->bind();
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    Font::vao->unbind();
    Font::vbo->unbind();
    glDisable(GL_BLEND);
}

Texture& Font::render(std::string text, Shader& shader){
    if (cache.find(text) != cache.end()){
        return *cache[text];
    }
    float char_w;
    float char_h;
    float char_real_w;
    float char_real_h;
    float next_char_pos_x = 0.0f;
    float next_char_pos_y = 0.0f;
    float char_offset_x;
    float char_offset_y;
    unsigned char c;
    bool await_stx = false;
    bool escape_dle = false;
    bool escape_esc = false;
    bool space_sp = false;
    float min_x = 0.0f;
    float max_x = 0.0f;
    float min_y = 0.0f;
    float max_y = 0.0f;
    for (unsigned int i = 0; i < text.size(); i++){
        c = text[i];
        if (escape_esc) {continue; escape_esc = false;}
        if (!escape_dle){
        if (c == '\x00') continue;        // nul
        if (c == '\x01') await_stx=true;  // soh
        if (c == '\x02') await_stx=false; // stx
        if (c == '\x03') break;          // etx
        if (c == '\x04') break;           // eot
        if (c == '\x05') continue;        // enq TODO (never)
        if (c == '\x06') continue;        // ack TODO (never)
        if (c == '\x07') continue;        // bel TODO
        if (c == '\x08') { next_char_pos_x -= char_real_w; continue;}                                 // bs
        if (c == '\x09') { next_char_pos_x += font_texture->width / 8.0f; continue; }     // ht 
        if (c == '\x0A') { next_char_pos_y -= font_texture->height / 16.0f; continue; }   // lf
        if (c == '\x0B') continue;                                                                    // vt  TODO (never)
        if (c == '\x0C') continue;                                                                    // ff  TODO (never)
        if (c == '\x0D') { next_char_pos_x = 0.0f; continue; }                                        // cr
        if (c == '\x0E') continue;                                                                    // so  TODO (never)
        if (c == '\x0F') continue;                                                                    // si  TODO (never)
        if (c == '\x10') { escape_dle = true; continue; }                                             // dle
        if (c == '\x11') continue;                                                                    // dc1 TODO (never)
        if (c == '\x12') continue;                                                                    // dc2 TODO (never)
        if (c == '\x13') continue;                                                                    // dc3 TODO (never)
        if (c == '\x14') continue;                                                                    // dc4 TODO (never)
        if (c == '\x15') continue;                                                                    // nak TODO (never)
        if (c == '\x16') continue;                                                                    // syn TODO (never)
        if (c == '\x17') continue;                                                                    // etb TODO (never)
        if (c == '\x18') continue;                                                                    // can TODO (never)
        if (c == '\x19') continue;                                                                    // em  TODO (never)
        if (c == '\x1A') continue;                                                                    // sub TODO (never)
        if (c == '\x1B') { escape_esc = true; continue; }                                             // esc
        if (c == '\x1C') continue;                                                                    // fs  TODO (never)
        if (c == '\x1D') continue;                                                                    // gs  TODO (never)
        if (c == '\x1E') continue;                                                                    // rs  TODO (never)
        if (c == '\x1F') continue;                                                                    // us  TODO (never)
        if (c == '\x20') space_sp = true;                                                             // sp  
        if (c == '\x7F') continue;                                                                    // del TODO (never)
        }
        if (await_stx) continue;
        escape_dle = false;
        char_w = (float) font_data->char_width[c];
        char_h = (float) font_data->char_height[c]; 
        char_real_w = char_w * font_texture->width / 256.0f;
        char_real_h = char_h * font_texture->height / 256.0f;
        char_offset_x = ((float) font_data->char_offset_x[c]) / 16.0f;
        char_offset_y = ((float) font_data->char_offset_y[c]) / 16.0f;
        if (space_sp){ next_char_pos_x += char_real_w; space_sp = false; continue; }
        
        if (next_char_pos_x < min_x)
            min_x = next_char_pos_x;
        if (next_char_pos_x + char_real_w > max_x)
            max_x = next_char_pos_x + char_real_w;
        if (next_char_pos_y < min_y)
            min_y = next_char_pos_y;
        if (next_char_pos_y + char_real_h > max_y)
            max_y = next_char_pos_y + char_real_h;
        next_char_pos_x += char_real_w;
    }
    unsigned int width = (unsigned int)(max_x - min_x);
    unsigned int height = (unsigned int)(max_y - min_y);
    Texture* new_texture = new Texture(width, height);
    render(text, *new_texture, 0, 0, shader, 1);
    cache[text] = new_texture;
    glViewport(0, 0, Window::window_ptr->width, Window::window_ptr->height);
    return *new_texture;
}


