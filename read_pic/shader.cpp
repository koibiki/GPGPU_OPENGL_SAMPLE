//
// Created by chengli on 5/23/18.
//
#include "shader.h"


void InitializeGeometry(GLuint program_id) {
    // Generate a vertex array object
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // 顶点缓存
    GLfloat tempv[12] = {1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, -1.0f};  //二维顶点坐标，分别为矩形的四个顶点坐标
    std::vector<GLfloat> vertex_buffer(tempv, tempv + 12);
    // Generate a vertex buffer object
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertex_buffer.size() * sizeof(GLfloat), vertex_buffer.data(), GL_STATIC_DRAW);

    // Setup vertex array lookup
    auto position_attrib = glGetAttribLocation(program_id, "Position");
    glVertexAttribPointer(position_attrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(position_attrib);

    // Generate another vertex buffer object for texture coordinates
    GLfloat temptex[8] = {1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f};
    std::vector<GLfloat> texcoord_buffer(temptex, temptex + 8);

    GLuint tbo;
    glGenBuffers(1, &tbo);
    glBindBuffer(GL_ARRAY_BUFFER, tbo);
    glBufferData(GL_ARRAY_BUFFER, texcoord_buffer.size() * sizeof(GLfloat), texcoord_buffer.data(), GL_STATIC_DRAW);

    GLint texcoord_attrib = glGetAttribLocation(program_id, "TexCoord");
    glVertexAttribPointer(texcoord_attrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(texcoord_attrib);

    glBindVertexArray(vao);
}

GLuint LoadImage(cv::Mat mat) {
    // Create new texture object
    GLuint texture_id;
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    // Set mipmaps
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    if (mat.empty()) {
        return -1;
    } else {
        glTexImage2D(GL_TEXTURE_2D, 0, 3, mat.cols, mat.rows, 0, GL_BGR, GL_UNSIGNED_BYTE, mat.data);
        return texture_id;
    }
}

GLuint ShaderProgram(const std::string &vertex_shader_file, const std::string &fragment_shader_file) {
    // 创建shader程序
    auto vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
    auto fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
    auto result = GL_FALSE;
    auto info_length = 0;

    // 读取shader源码
    std::ifstream vertex_shader_stream(vertex_shader_file);
    std::string vertex_shader_code((std::istreambuf_iterator<char>(vertex_shader_stream)),
                                   std::istreambuf_iterator<char>());

    std::ifstream fragment_shader_stream(fragment_shader_file);
    std::string fragment_shader_code((std::istreambuf_iterator<char>(fragment_shader_stream)),
                                     std::istreambuf_iterator<char>());

    // 编译顶点shader代码
    std::cout << "Compiling Vertex Shader ..." << std::endl;
    auto vertex_shader_code_ptr = vertex_shader_code.c_str();
    glShaderSource(vertex_shader_id, 1, &vertex_shader_code_ptr, NULL);
    glCompileShader(vertex_shader_id);

    // Check vertex shader log
    glGetShaderiv(vertex_shader_id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        glGetShaderiv(vertex_shader_id, GL_INFO_LOG_LENGTH, &info_length);
        std::string vertex_shader_log((unsigned int) info_length, ' ');
        glGetShaderInfoLog(vertex_shader_id, info_length, NULL, &vertex_shader_log[0]);
        std::cout << vertex_shader_log << std::endl;
    }

    // 编译片元着色器代码
    std::cout << "Compiling Fragment Shader ..." << std::endl;
    auto fragment_shader_code_ptr = fragment_shader_code.c_str();
    glShaderSource(fragment_shader_id, 1, &fragment_shader_code_ptr, NULL);
    glCompileShader(fragment_shader_id);

    // Check fragment shader log
    glGetShaderiv(fragment_shader_id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        glGetShaderiv(fragment_shader_id, GL_INFO_LOG_LENGTH, &info_length);
        std::string fragment_shader_log((unsigned long) info_length, ' ');
        glGetShaderInfoLog(fragment_shader_id, info_length, NULL, &fragment_shader_log[0]);
        std::cout << fragment_shader_log << std::endl;
    }

    // 创建链接程序
    std::cout << "Linking Shader Program ..." << std::endl;
    auto program_id = glCreateProgram();
    glAttachShader(program_id, vertex_shader_id);
    glAttachShader(program_id, fragment_shader_id);
    glBindFragDataLocation(program_id, 0, "FragmentColor");
    glLinkProgram(program_id);

    //打印编译信息，如果编译错误，就可以看见错误信息了
    glGetProgramiv(program_id, GL_LINK_STATUS, &result);
    if (result == GL_FALSE) {
        glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &info_length);
        std::string program_log((unsigned long) info_length, ' ');
        glGetProgramInfoLog(program_id, info_length, NULL, &program_log[0]);
        std::cout << program_log << std::endl;
    }
    glDeleteShader(vertex_shader_id);
    glDeleteShader(fragment_shader_id);

    return program_id;
}