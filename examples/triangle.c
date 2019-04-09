#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>

#include "../ggt_platform.h"
#include "../ggt_gl_utils.h"

float triangle_angle;

GLuint gl_program_id;
GLuint gl_position_location;
GLuint gl_color_location;

GLuint gl_buffer_position;
GLuint gl_buffer_color;

int ggtp_init(){
	// Create window
	if(ggtp_create_window(600, 600, "Triangle example"))
		return GGT_FAILURE;

	// Inititalize variables
	triangle_angle = 0.f;

	// Initialize OpenGL
	const char vertex_shader[] = ""
		"attribute vec4 a_position; \n"
		"attribute vec4 a_color; \n"
		"\n"
		"varying vec4 v_color; \n"
		"\n"
		"void main(){ \n"
		"	gl_Position = a_position; \n"
		"	v_color = a_color; \n"
		"}";

	const char fragment_shader[] = ""
		"varying vec4 v_color; \n"
		"\n"
		"void main(){ \n"
		"	gl_FragColor = v_color; \n"
		"}";
	
	gl_program_id = ggtgl_load_shaders_by_text(vertex_shader, fragment_shader);
	gl_position_location = glGetAttribLocation(gl_program_id, "a_position");
	gl_color_location = glGetAttribLocation(gl_program_id, "a_color");

	glUseProgram(gl_program_id);
	
    glEnableVertexAttribArray(gl_position_location);
    glEnableVertexAttribArray(gl_color_location);
	
	glGenBuffers(1, &gl_buffer_position);
	glGenBuffers(1, &gl_buffer_color);

	ggtgl_check_error();

	return GGT_SUCCESS;
}

int ggtp_loop(ggt_u8 keys[GGTP_TOTAL_KEYS], ggt_platform_events events){
	for(unsigned int i = 0; i < events.size; i++){
		switch(events.data[i].type){
			case GGTP_EVENT_CLOSE: {
				return GGT_FAILURE;
			} break;
			case GGTP_EVENT_RESIZE: {
				glViewport(0, 0, events.data[i].info.size.x, events.data[i].info.size.y);
			} break;
			default: {
			} break;
		}
	}

	triangle_angle += 0.025f;

	ggtp_set_cursor(GGTP_CURSOR_ARROW);

	return GGT_SUCCESS;
}

void ggtp_draw(){
	// Update buffers
	float a0 = triangle_angle, a1 = triangle_angle + 0.6666666f * M_PI, a2 = triangle_angle + 1.3333333f * M_PI;
	GLfloat positions[] = {
		cos(a0), sin(a0), 0.f, 1.f,
		cos(a1), sin(a1), 0.f, 1.f,
		cos(a2), sin(a2), 0.f, 1.f,
	};
	ggtgl_set_buffer_data(gl_buffer_position, positions, 12, GL_DYNAMIC_DRAW);

	GLubyte colors[] = {
		255,   0,   0, 255,
		  0, 255,   0, 255,
		  0,   0, 255, 255,
	};
	ggtgl_set_buffer_data(gl_buffer_color, colors, 12, GL_DYNAMIC_DRAW);

	// Draw them
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
    glBindBuffer(GL_ARRAY_BUFFER, gl_buffer_position);
    glVertexAttribPointer(gl_position_location, 4, GL_FLOAT,         GL_FALSE, 0, (void *)0);
    glBindBuffer(GL_ARRAY_BUFFER, gl_buffer_color);
    glVertexAttribPointer(gl_color_location,    4, GL_UNSIGNED_BYTE, GL_TRUE,  0, (void *)0);

	glDrawArrays(GL_TRIANGLES, 0, 3);
}


#define GGT_PLATFORM_IMPLEMENTATION
#include "../ggt_platform.h"
#define GGT_GL_IMPLEMENTATION
#include "../ggt_gl_utils.h"