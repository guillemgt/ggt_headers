//
// GGT GL UTILS - v0
//
// A header that provides some useful functions/macros for OpenGL, namely:
//  - ggtgl_check_error()
//  - ggtgl_set_buffer_data(GLuint buffer_id, T *vertices, GLuint draw_mode)
//  - ggtgl_load_texture(GLuint *texture_id, const char *image_path) if
//    stb_image.h was included before this
//  - ggtgl_load_shaders_by_text(const char *vertex_shader_text, const char
//    *fragment_shader_text)
//
// Usage:
//  - To compile this, #define GGT_GL_IMPLEMENTATION and #include the header
//
// Options:
//  - GGTGL_MAX_INFO_LOG_LENGTH for the maximum length of shader error info logs
//


#ifndef GGT_GL_H
#define GGT_GL_H

#define ggtgl_check_error() _ggtgl_check_error(__LINE__, __FILE__)
void _ggtgl_check_error(int line, const char *file);

void _ggtgl_set_buffer_data(GLuint buffer, void *vert, unsigned int size, GLuint mode);
#define ggtgl_set_buffer_data(b, v, s, t) _ggtgl_set_buffer_data(b, v, s*sizeof(v[0]), t)

GLuint ggtgl_load_shaders(const char *file_path);
GLuint ggtgl_load_shaders_by_text(const char *vertex_text, const char *fragment_text);

#ifdef STBI_INCLUDE_STB_IMAGE_H
void ggtgl_load_texture(GLuint *texture, const char *path);
#endif

#ifdef __EMSCRIPTEN__
#define GGTGL_OPENGL_ES 1
#endif

#endif

#ifdef GGT_GL_IMPLEMENTATION

void _ggtgl_check_error(int line, const char *file){
    GLenum err;
    while((err = glGetError()) != GL_NO_ERROR){
        printf("[%s:%i] OpenGL Error: ", file, line);
        switch(err){
            case GL_INVALID_ENUM:
            printf("GL_INVALID_ENUM");
            break;
            case GL_INVALID_VALUE:
            printf("GL_INVALID_VALUE");
            break;
            case GL_INVALID_OPERATION:
            printf("GL_INVALID_OPERATION");
            break;
#ifdef GL_STACK_OVERFLOW
            case GL_STACK_OVERFLOW:
            printf("GL_STACK_OVERFLOW");
            break;
#endif
#ifdef GL_STACK_UNDERFLOW
            case GL_STACK_UNDERFLOW:
            printf("GL_STACK_UNDERFLOW");
            break;
#endif
            case GL_OUT_OF_MEMORY:
            printf("GL_OUT_OF_MEMORY");
            break;
            case GL_INVALID_FRAMEBUFFER_OPERATION:
            printf("GL_INVALID_FRAMEBUFFER_OPERATION");
            break;
#ifdef GL_TABLE_TOO_LARGE
            case GL_TABLE_TOO_LARGE:
            printf("GL_TABLE_TOO_LARGE");
            break;
#endif
            default:
            printf("Unknown [0x%x]", err);
            break;
        }
        printf("\n");
    }
}

void _ggtgl_set_buffer_data(GLuint buffer, void *vert, unsigned int size, GLuint mode){
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, size, vert, mode);
}

#ifndef GGTGL_MAX_INFO_LOG_LENGTH
#define GGTGL_MAX_INFO_LOG_LENGTH 400
#endif

GLuint ggtgl_load_shaders_by_text(const char *vertex_text, const char *fragment_text){
    char error_message[GGTGL_MAX_INFO_LOG_LENGTH];
    
    // Create the shaders
    GLuint vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
    
    GLint result = GL_FALSE;
    GLsizei info_log_length = 0;
    
    // Compile Vertex Shader
    glShaderSource(vertex_shader_id, 1, &vertex_text, NULL);
    glCompileShader(vertex_shader_id);
    
    // Check Fragment Shader
    glGetShaderiv(vertex_shader_id, GL_COMPILE_STATUS, &result);
    if(result == GL_FALSE){
        glGetShaderiv(vertex_shader_id, GL_INFO_LOG_LENGTH, &info_log_length);
        if(info_log_length > 0){
            if(info_log_length > GGTGL_MAX_INFO_LOG_LENGTH)
                info_log_length = GGTGL_MAX_INFO_LOG_LENGTH;
            glGetShaderInfoLog(vertex_shader_id, info_log_length, NULL, error_message);
            printf("Couldn't compile vertex shader:\n%s\n\n", error_message);
        }
    }
    
    // Compile Fragment Shader
    glShaderSource(fragment_shader_id, 1, &fragment_text , NULL);
    glCompileShader(fragment_shader_id);
    
    // Check Fragment Shader
    glGetShaderiv(fragment_shader_id, GL_COMPILE_STATUS, &result);
    if(result == GL_FALSE){
        glGetShaderiv(fragment_shader_id, GL_INFO_LOG_LENGTH, &info_log_length);
        if(info_log_length > 0){
            if(info_log_length > GGTGL_MAX_INFO_LOG_LENGTH)
                info_log_length = GGTGL_MAX_INFO_LOG_LENGTH;
            glGetShaderInfoLog(fragment_shader_id, info_log_length, NULL, error_message);
            printf("Couldn't compile fragment shader:\n%s\n\n", error_message);
        }
    }
    
    // Link the program
    GLuint program_id = glCreateProgram();
    glAttachShader(program_id, vertex_shader_id);
    glAttachShader(program_id, fragment_shader_id);
    glLinkProgram(program_id);
    
    // Check the program
    glGetProgramiv(program_id, GL_LINK_STATUS, &result);
    if(result == GL_FALSE){
        glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &info_log_length);
        if(info_log_length > 0){
            if(info_log_length > GGTGL_MAX_INFO_LOG_LENGTH)
                info_log_length = GGTGL_MAX_INFO_LOG_LENGTH;
            glGetProgramInfoLog(program_id, info_log_length, NULL, error_message);
            printf("Couldn't link shader:\n%s\n\n", error_message);
            glValidateProgram(program_id);
        }
    }
    
    glDeleteShader(vertex_shader_id);
    glDeleteShader(fragment_shader_id);
    
    return program_id;
}

#ifdef STBI_INCLUDE_STB_IMAGE_H
void ggtgl_load_texture(GLuint *texture, const char *path){
    int width, height, channels;
    u8* image = stbi_load(path, &width, &height, &channels, 0);
    if(image == NULL){
        printf("ggtgl_load_texture error: Couldn't load image\n");
        return;
    }
    
    // Flip texture Y axis
    int i, j;
    for(j = 0; j*2<height; j++){
        int index1 = j * width * channels;
        int index2 = (height - 1 - j) * width * channels;
        for(i=width*channels; i>0; i--){
            u8 temp = image[index1];
            image[index1] = image[index2];
            image[index2] = temp;
            ++index1;
            ++index2;
        }
    }
    
    glGenTextures(1, texture);
    glBindTexture(GL_TEXTURE_2D, *texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    
    stbi_image_free(image);
}
#endif

#endif