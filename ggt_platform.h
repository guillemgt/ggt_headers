//
// GGT PLATFORM
//
// A cross-platform (though currently only for windows and wasm) platform layer
// for games and the such. It can open a window with opengl
// and provides some other useful functions.
// Feel free to use and/or modify this.
//
// Usage:
//  - You should have functions named ggtp_init, ggtp_loop and ggtp_draw that
//    will be called when the program is starting or every frame.
//    ggtp_init must call ggtp_create_window.
//  - To compile this, define GGT_PLATFORM_IMPLEMENTATION and include the header
//
// Options:
//  - GGT_PLATFORM_PROGRAM_STATE {TYPE} if you want to have a variable of type
//     {TYPE} whose pointer is passed to the user functions
//  - GGT_PLATFORM_MAX_EVENTS_PER_LOOP, which is 256 by default
//

#ifndef GGT_PLATFORM_H
#define GGT_PLATFORM_H

typedef unsigned           char ggt_u8;
typedef unsigned           int  ggt_u32;
typedef unsigned long long int  ggt_u64;

#ifndef GGT_PLATFORM_MAX_EVENTS_PER_LOOP
#define GGT_PLATFORM_MAX_EVENTS_PER_LOOP  256
#endif

typedef enum {
    GGTPE_KEY_DOWN,
    GGTPE_KEY_UP,
    GGTPE_MOUSE_LEFT_DOWN,
    GGTPE_MOUSE_LEFT_UP,
    GGTPE_MOUSE_RIGHT_DOWN,
    GGTPE_MOUSE_RIGHT_UP,
    GGTPE_MOUSE_MOVE,
    GGTPE_RESIZE,
    GGTPE_CLOSE,
    GGTPE_FOCUS_LOST,
} ggt_platform_event_type;


const char GGTPK_SHIFT  = 0x03;
const char GGTPK_RETURN = 0x0D;
const char GGTPK_ESC    = 0x1B;
const char GGTPK_SPACE  = 0x20;
const char GGTPK_LEFT   = 0x25;
const char GGTPK_UP     = 0x26;
const char GGTPK_RIGHT  = 0x27;
const char GGTPK_DOWN   = 0x28;

#define GGTP_TOTAL_KEYS 128

typedef enum {
	GGTP_CURSOR_ARROW,
	GGTP_CURSOR_POINTER,
	GGTP_CURSOR_WAIT,
	GGTP_CURSOR_WRITE,
} ggt_platform_cursor;
void ggt_platform_set_cursor(ggt_platform_cursor cursor);

typedef struct {
    int x, y;
} ggt_vec2i;

typedef struct {
    ggt_vec2i position, difference;
} ggt_platform_mouse_movement;

typedef union {
    char key;
    ggt_vec2i size;
    ggt_vec2i coords;
    ggt_platform_mouse_movement mouse_movement;
} ggt_platform_event_info;

typedef struct {
    ggt_platform_event_type type;
    ggt_platform_event_info info;
} ggt_platform_event;

typedef struct {
    ggt_u32 size;
    ggt_platform_event data[GGT_PLATFORM_MAX_EVENTS_PER_LOOP];
} ggt_platform_events;

#ifdef GGT_PLATFORM_PROGRAM_STATE
struct GGT_PLATFORM_PROGRAM_STATE;
int  ggtp_init(GGT_PLATFORM_PROGRAM_STATE* program_state);
int  ggtp_loop(GGT_PLATFORM_PROGRAM_STATE* program_state, ggt_u8 keys[GGTP_TOTAL_KEYS], ggt_platform_events events);
void ggtp_draw(GGT_PLATFORM_PROGRAM_STATE* program_state);
#else
int  ggtp_init();
int  ggtp_loop(ggt_u8 keys[GGTP_TOTAL_KEYS], ggt_platform_events events);
void ggtp_draw();
#endif

int ggtp_create_window(int width, int height, const char *window_name);

void ggtp_program_file_path(const char *name, char *dst);
void ggtp_user_file_path(const char *name, char *dst);
ggt_u64 ggtp_file_modification_date(const char *filename);

#if defined(_WIN32)
#include <Windows.h>

// For visual studio
int __cdecl printf_windows(const char* format, ...);
#define printf printf_windows


//
// GL preprocessor and function definitions
// (From https://www.khronos.org/registry/OpenGL/api/GL/glext.h)
//
#include <gl/gl.h>

#ifndef __gl_glext_h_

typedef char GLchar;
typedef ptrdiff_t GLsizeiptr;
typedef ptrdiff_t GLintptr;

#define GL_STREAM_DRAW                    0x88E0
#define GL_STATIC_DRAW                    0x88E4
#define GL_DYNAMIC_DRAW                   0x88E8

#define GL_ARRAY_BUFFER                   0x8892

#define GL_TEXTURE0                       0x84C0
#define GL_TEXTURE1                       0x84C1
#define GL_TEXTURE2                       0x84C2
#define GL_TEXTURE3                       0x84C3
#define GL_TEXTURE4                       0x84C4
#define GL_TEXTURE5                       0x84C5
#define GL_TEXTURE6                       0x84C6
#define GL_TEXTURE7                       0x84C7
#define GL_TEXTURE8                       0x84C8
#define GL_TEXTURE9                       0x84C9
#define GL_TEXTURE10                      0x84CA
#define GL_TEXTURE11                      0x84CB
#define GL_TEXTURE12                      0x84CC
#define GL_TEXTURE13                      0x84CD
#define GL_TEXTURE14                      0x84CE
#define GL_TEXTURE15                      0x84CF
#define GL_TEXTURE16                      0x84D0
#define GL_TEXTURE17                      0x84D1
#define GL_TEXTURE18                      0x84D2
#define GL_TEXTURE19                      0x84D3
#define GL_TEXTURE20                      0x84D4
#define GL_TEXTURE21                      0x84D5
#define GL_TEXTURE22                      0x84D6
#define GL_TEXTURE23                      0x84D7
#define GL_TEXTURE24                      0x84D8
#define GL_TEXTURE25                      0x84D9
#define GL_TEXTURE26                      0x84DA
#define GL_TEXTURE27                      0x84DB
#define GL_TEXTURE28                      0x84DC
#define GL_TEXTURE29                      0x84DD
#define GL_TEXTURE30                      0x84DE
#define GL_TEXTURE31                      0x84DF

#define GL_INVALID_FRAMEBUFFER_OPERATION  0x0506

#define GL_FRAGMENT_SHADER                0x8B30
#define GL_VERTEX_SHADER                  0x8B31
#define GL_COMPILE_STATUS                 0x8B81
#define GL_LINK_STATUS                    0x8B82
#define GL_VALIDATE_STATUS                0x8B83
#define GL_INFO_LOG_LENGTH                0x8B84

#endif

#define GGTP_GL_FUNCTION_LIST \
GL_FUNCTION(void, glTexImage2DMultisample, GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations) \
GL_FUNCTION(void, glBindFramebuffer, GLenum target, GLuint framebuffer) \
GL_FUNCTION(void, glGenFramebuffers, GLsizei n, GLuint* framebuffers) \
GL_FUNCTION(void, glFramebufferTexture2D, GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level) \
GL_FUNCTION(GLenum, glCheckFramebufferStatus, GLenum target) \
GL_FUNCTION(void, glBlitFramebuffer, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter) \
GL_FUNCTION(void, glAttachShader, GLuint program, GLuint shader) \
GL_FUNCTION(void, glCompileShader, GLuint shader) \
GL_FUNCTION(GLuint, glCreateProgram, void) \
GL_FUNCTION(GLuint, glCreateShader, GLenum type) \
GL_FUNCTION(void, glLinkProgram, GLuint program) \
GL_FUNCTION(void, glShaderSource, GLuint shader, GLsizei count, GLchar** string, GLint* length) \
GL_FUNCTION(void, glUseProgram, GLuint program) \
GL_FUNCTION(void, glGetProgramInfoLog, GLuint program, GLsizei bufSize, GLsizei* length, GLchar* infoLog) \
GL_FUNCTION(void, glGetShaderInfoLog, GLuint shader, GLsizei bufSize, GLsizei* length, GLchar* infoLog) \
GL_FUNCTION(void, glValidateProgram, GLuint program) \
GL_FUNCTION(void, glGetShaderiv, GLuint shader, GLenum pname, GLint* params) \
GL_FUNCTION(void, glGetProgramiv, GLuint program, GLenum pname, GLint* params) \
GL_FUNCTION(GLint, glGetUniformLocation, GLuint program, const GLchar* name) \
GL_FUNCTION(void, glUniform4fv, GLint location, GLsizei count, const GLfloat* value) \
GL_FUNCTION(void, glUniformMatrix4fv, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) \
GL_FUNCTION(void, glUniform1i, GLint location, GLint v0) \
GL_FUNCTION(void, glUniform1f, GLint location, GLfloat v0) \
GL_FUNCTION(void, glUniform2fv, GLint location, GLsizei count, const GLfloat* value) \
GL_FUNCTION(void, glUniform3f, GLint location, GLfloat v0, GLfloat v1, GLfloat v2) \
GL_FUNCTION(void, glUniform3fv, GLint location, GLsizei count, const GLfloat* value) \
GL_FUNCTION(void, glEnableVertexAttribArray, GLuint index) \
GL_FUNCTION(void, glDisableVertexAttribArray, GLuint index) \
GL_FUNCTION(GLint, glGetAttribLocation, GLuint program, const GLchar* name) \
GL_FUNCTION(void, glVertexAttribPointer, GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer) \
GL_FUNCTION(void, glVertexAttribIPointer, GLuint index, GLint size, GLenum type, GLsizei stride, const void* pointer) \
GL_FUNCTION(void, glBindVertexArray, GLuint array) \
GL_FUNCTION(void, glGenVertexArrays, GLsizei n, GLuint* arrays) \
GL_FUNCTION(void, glBindBuffer, GLenum target, GLuint buffer) \
GL_FUNCTION(void, glGenBuffers, GLsizei n, GLuint* buffers) \
GL_FUNCTION(void, glBufferData, GLenum target, GLsizeiptr size, const void* data, GLenum usage) \
GL_FUNCTION(void, glActiveTexture, GLenum texture) \
GL_FUNCTION(void, glDeleteProgram, GLuint program) \
GL_FUNCTION(void, glDeleteShader, GLuint shader) \
GL_FUNCTION(void, glDeleteFramebuffers, GLsizei n, const GLuint* framebuffers) \
GL_FUNCTION(void, glDrawBuffers, GLsizei n, const GLenum* bufs) \
GL_FUNCTION(void, glTexImage3D, GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void* pixels) \
GL_FUNCTION(void, glTexSubImage3D, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void* pixels) \
GL_FUNCTION(void, glDrawElementsBaseVertex, GLenum mode, GLsizei count, GLenum type, const void* indices, GLint basevertex) \
GL_FUNCTION(const GLubyte* WINAPI, glGetStringi, GLenum name, GLuint index) \

// Define gl function types
#define GL_FUNCTION(TYPE, NAME, ...) typedef TYPE ggt_gl_type_##NAME(__VA_ARGS__);
GGTP_GL_FUNCTION_LIST
#undef GL_FUNCTION

// Define the global variables for gl function pointers
#define GL_FUNCTION(TYPE, NAME, ...) extern ggt_gl_type_##NAME *NAME;
GGTP_GL_FUNCTION_LIST
#undef GL_FUNCTION

//
//
//

#elif defined(__EMSCRIPTEN__)

#include <GL/gl.h>
#include <GL/glext.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES2/gl2.h>
#include <GLES3/gl3.h>

#endif

#endif

#ifdef GGT_PLATFORM_IMPLEMENTATION

#define ggt_globals ggt_platform_globals

#define GGT_PLATFORM_ADD_EVENT(type_id, field, ...) if(ggt_globals.events.size < GGT_PLATFORM_MAX_EVENTS_PER_LOOP){ \
        ggt_globals.events.data[ggt_globals.events.size  ].type = type_id; \
        ggt_globals.events.data[ggt_globals.events.size++].info.field = __VA_ARGS__; \
} \

#if defined(_WIN32) // Windows implementation

#pragma comment(lib, "opengl32.lib")

#include <initguid.h>
#include <KnownFolders.h>
//#include <ShlObj.h>
#include <wchar.h>
#include <windowsx.h>
#include <WinUser.h>

#define GGT_PLATFORM_ALERT_ERROR(message, code) MessageBox(NULL, message "\n(ggt_platform error " code ")", "ERROR", MB_OK);



//
// WGL preprocessor and function definitions
// (From https://www.khronos.org/registry/OpenGL/api/GL/wglext.h)
//
void ggtp_gl_init();

#ifndef __wgl_wglext_h_

// Context creation
#define WGL_CONTEXT_DEBUG_BIT_ARB         0x00000001
#define WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB 0x00000002
#define WGL_CONTEXT_MAJOR_VERSION_ARB     0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB     0x2092
#define WGL_CONTEXT_LAYER_PLANE_ARB       0x2093
#define WGL_CONTEXT_FLAGS_ARB             0x2094
#define ERROR_INVALID_VERSION_ARB         0x2095
typedef HGLRC (WINAPI * PFNWGLCREATECONTEXTATTRIBSARBPROC) (HDC hDC, HGLRC hShareContext, const int *attribList);

// Swap interval
typedef BOOL (WINAPI * PFNWGLSWAPINTERVALEXTPROC) (int interval);
typedef int (WINAPI * PFNWGLGETSWAPINTERVALEXTPROC) (void);
BOOL WINAPI wglSwapIntervalEXT (int interval);
int WINAPI wglGetSwapIntervalEXT (void);

#endif

//
//
//
struct {
    ggt_platform_events events;
    ggt_u8 keys[128];
    ggt_vec2i last_mouse_position;
    
    HWND hWnd;
    HDC hDC;
    HGLRC hRC;
    HINSTANCE hInstance;
} ggt_globals;

ggt_u8 _ggt_platform_get_key_code(ggt_u32 code) {
	switch (code) {
        case VK_LEFT:
		return GGTPK_LEFT;
		break;
        case VK_UP:
		return GGTPK_UP;
		break;
        case VK_RIGHT:
		return GGTPK_RIGHT;
		break;
        case VK_DOWN:
		return GGTPK_DOWN;
        case VK_ESCAPE:
		return GGTPK_ESC;
        case VK_LSHIFT:
        case VK_RSHIFT:
        case VK_SHIFT:
		return GGTPK_SHIFT;
        case VK_SPACE:
		return GGTPK_SPACE;
        default:
		return (ggt_u8)code;
	}
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam){
    switch(msg){
        case WM_CREATE:
		break;
        
        case WM_SIZE:
        GGT_PLATFORM_ADD_EVENT(GGTPE_RESIZE, size, {GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)});
		break;
        
        case WM_SYSKEYDOWN:
        case WM_KEYDOWN: {
            ggt_u8 value = _ggt_platform_get_key_code((ggt_u32)wParam);
            ggt_globals.keys[value] = 1;
            GGT_PLATFORM_ADD_EVENT(GGTPE_KEY_DOWN, key, value);
        } break;
        
        case WM_SYSKEYUP:
        case WM_KEYUP: {
            ggt_u8 value = _ggt_platform_get_key_code((ggt_u32)wParam);
            ggt_globals.keys[value] = 0;
            GGT_PLATFORM_ADD_EVENT(GGTPE_KEY_UP, key, value);
        } break;
        
        case WM_LBUTTONDOWN:
        GGT_PLATFORM_ADD_EVENT(GGTPE_MOUSE_LEFT_DOWN, coords, {GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)});
		break;
        
        case WM_RBUTTONDOWN:
        GGT_PLATFORM_ADD_EVENT(GGTPE_MOUSE_RIGHT_DOWN, coords, {GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)});
        break;
        
        case WM_LBUTTONUP:
        GGT_PLATFORM_ADD_EVENT(GGTPE_MOUSE_LEFT_UP, coords, {GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)});
        break;
        
        case WM_RBUTTONUP:
        GGT_PLATFORM_ADD_EVENT(GGTPE_MOUSE_RIGHT_UP, coords, {GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)});
        break;
        
        case WM_MOUSEMOVE: {
            ggt_vec2i position = {GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)};
            GGT_PLATFORM_ADD_EVENT(GGTPE_MOUSE_MOVE, mouse_movement, {position.x, position.y, position.x - ggt_globals.last_mouse_position.x, position.y - ggt_globals.last_mouse_position.y});
            ggt_globals.last_mouse_position = position;
        } break;
        
        case WM_DESTROY:
        case WM_QUIT:
        case WM_CLOSE:
        ggt_globals.events.data[ggt_globals.events.size++].type = GGTPE_CLOSE;
        PostQuitMessage(0);
        break;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

// https://stackoverflow.com/questions/3009042/how-to-view-printf-output-in-a-win32-application-on-visual-studio-2010
int __cdecl printf_windows(const char *format, ...)
{
    char str[1024];
    
    va_list argptr;
    va_start(argptr, format);
    int ret = vsnprintf(str, 1024, format, argptr);
    va_end(argptr);
    
    OutputDebugString(str);
    
    return ret;
}

#define GGT_PLATFORM_WINDOW_CLASS_NAME "WINDOWCLASS"


int ggtp_create_window(int width, int height, const char *window_name){
	int screen_x = GetSystemMetrics(SM_CXSCREEN);
	int screen_y = GetSystemMetrics(SM_CYSCREEN);
    
    RECT actualSize;
    actualSize.left = (screen_x - width) / 2;
    actualSize.right = actualSize.left + width;
    actualSize.top = (screen_y - height) / 2;
    actualSize.bottom = actualSize.top + height;
    if(!AdjustWindowRect(&actualSize, WS_OVERLAPPEDWINDOW | WS_VISIBLE, FALSE)){
        
    }
    ggt_globals.hWnd = CreateWindow(GGT_PLATFORM_WINDOW_CLASS_NAME, window_name, WS_OVERLAPPEDWINDOW | WS_VISIBLE, actualSize.left, actualSize.top, actualSize.right - actualSize.left, actualSize.bottom - actualSize.top, NULL, NULL, ggt_globals.hInstance, NULL);
    
    if(!ggt_globals.hWnd){
		GGT_PLATFORM_ALERT_ERROR("Cannot create window.", "1");
        return 1;
    }
    
    ggt_globals.hDC = GetDC(ggt_globals.hWnd);
    PIXELFORMATDESCRIPTOR pfd;
    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1;
    pfd.iLayerType = PFD_MAIN_PLANE;
    pfd.dwFlags = PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER;
    pfd.cDepthBits = 24;
    pfd.cColorBits = 24;
    pfd.iPixelType = PFD_TYPE_RGBA;
    
    int PixelFormat = ChoosePixelFormat(ggt_globals.hDC, &pfd);
    if (!SetPixelFormat(ggt_globals.hDC, PixelFormat, &pfd)) {
		GGT_PLATFORM_ALERT_ERROR("Cannot set pixel format.", "2");
        return 1;
    }
    
    int attriblist[] = {
        WGL_CONTEXT_MAJOR_VERSION_ARB, 2,
        WGL_CONTEXT_MINOR_VERSION_ARB, 1,
        0
    };
    
    HGLRC hRCtmp = wglCreateContext(ggt_globals.hDC);
    wglMakeCurrent(ggt_globals.hDC, hRCtmp);
    
    
    PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB =
        (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");
    ggt_globals.hRC = wglCreateContextAttribsARB(ggt_globals.hDC, 0, attriblist);
    
	PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT =
		(PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");
	if (wglSwapIntervalEXT) {
		wglSwapIntervalEXT(1);
	} else {
		printf("Error: Could not find 'wglSwapIntervalEXT'\n");
	}
    
	if (!ggt_globals.hRC) {
		GGT_PLATFORM_ALERT_ERROR("Could not create OpenGL context.", "3");
		return 1;
	}
    
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hRCtmp);
    wglMakeCurrent(ggt_globals.hDC, ggt_globals.hRC);
    
	ggtp_gl_init();
    
    return 0;
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevious, LPSTR lpCmdLine, int nCmdShow){
    // We register the window class
    WNDCLASS wc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
    wc.hCursor = LoadCursor(hInstance, IDC_ARROW);
    wc.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
    wc.lpfnWndProc = WndProc;
    wc.lpszClassName = GGT_PLATFORM_WINDOW_CLASS_NAME;
    wc.lpszMenuName = NULL;
    wc.style = CS_VREDRAW | CS_HREDRAW;
    wc.hInstance = hInstance;
    if(!RegisterClass(&wc)){
		GGT_PLATFORM_ALERT_ERROR("Cannot register window.", "0");
        return 1;
    }
    
    ggt_globals.hInstance = hInstance;
    
#ifdef GGT_PLATFORM_PROGRAM_STATE
	//GGT_PLATFORM_PROGRAM_STATE* program_state = (GGT_PLATFORM_PROGRAM_STATE *)malloc(sizeof(GGT_PLATFORM_PROGRAM_STATE));
	GGT_PLATFORM_PROGRAM_STATE program_state;
#define GGTP_INIT() ggtp_init(&program_state)
#define GGTP_LOOP(a, b) ggtp_loop(&program_state, a, b)
#define GGTP_DRAW() ggtp_draw(&program_state)
#else
#define GGTP_INIT() ggtp_init()
#define GGTP_LOOP(a, b) ggtp_loop(a, b)
#define GGTP_DRAW() ggtp_draw()
#endif
    
    GGTP_INIT();
    
    for(int i=0; i<GGTP_TOTAL_KEYS; i++) {
        ggt_globals.keys[i] = 0;
    }
    ggt_globals.events.size = 0;
    
    MSG msg;
    while (1){
        while (PeekMessage(&msg, NULL, NULL, NULL, PM_NOREMOVE)){
            if (!GetMessage(&msg, NULL, 0, 0)){
                break;
            }
            DispatchMessage(&msg);
            TranslateMessage(&msg);
        }
        
        ggt_platform_events events;
        events.size = ggt_globals.events.size;
        for(ggt_u32 i=0; i<events.size; i++)
            events.data[i] = ggt_globals.events.data[i];
        ggt_globals.events.size = 0;
        if(GGTP_LOOP(ggt_globals.keys, events) == 0)
            return 0;
        
		GGTP_DRAW();
        
        SwapBuffers(ggt_globals.hDC);
    }
    
    return 0;
}

void ggt_platform_set_cursor(ggt_platform_cursor cursor_id) {
	LPCTSTR win_cursor = IDC_ARROW;
	switch (cursor_id) {
        case GGTP_CURSOR_ARROW:
		win_cursor = IDC_ARROW;
		break;
        case GGTP_CURSOR_POINTER:
		win_cursor = IDC_HAND;
		break;
        case GGTP_CURSOR_WAIT:
		win_cursor = IDC_WAIT;
		break;
        case GGTP_CURSOR_WRITE:
		win_cursor = IDC_IBEAM;
		break;
	}
	HCURSOR cursor = (HCURSOR)LoadImageA(NULL, win_cursor, IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_DEFAULTCOLOR | LR_SHARED);
	SetCursor(cursor);
}

void quitWindows() {
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(ggt_globals.hRC);
    ReleaseDC(ggt_globals.hWnd, ggt_globals.hDC);
}

void ggtp_program_file_path(const char *name, char *dst){
    sprintf(dst, "%s", name);
}
void ggtp_user_file_path(const char *name, char *dst){
    sprintf(dst, "%s", name);
}

#include <sys/types.h>
#include <sys/stat.h>
//#include <unistd.h>
ggt_u64 ggtp_file_modification_date(const char *path){
    struct _stat result;
    if(_stat(path, &result) == 0)
        return result.st_mtime;
    return 0;
}


//
// Loading OpenGL functions
//

#define GL_FUNCTION(TYPE, NAME, ...) ggt_gl_type_##NAME *NAME;
GGTP_GL_FUNCTION_LIST
#undef GL_FUNCTION

void ggtp_gl_init() {
#define GL_FUNCTION(TYPE, NAME, ...) NAME = (ggt_gl_type_##NAME *)wglGetProcAddress(#NAME);
    GGTP_GL_FUNCTION_LIST
#undef GL_FUNCTION
    
}

#elif defined(__EMSCRIPTEN__)

#include <emscripten.h>
#include <emscripten/html5.h>

struct {
    GameState game_state;
    ggt_u8 keys[GGTP_TOTAL_KEYS];
    ggt_platform_events events;
    
    ggt_vec2i last_mouse_position;
} ggt_globals;

EM_JS(int, window_width, (), {
      return window.innerWidth;
      });

EM_JS(int, window_height, (), {
      return window.innerHeight;
      });

EM_BOOL key_callback(int eventType, const EmscriptenKeyboardEvent *e, void *userData)
{
    char key = (char)e->keyCode;
    if(key == 16)
        key = GGTPK_SHIFT;
    
    if(eventType == EMSCRIPTEN_EVENT_KEYUP){
        GGT_PLATFORM_ADD_EVENT(GGTPE_KEY_UP, key, key);
        ggt_globals.keys[key] = 0;
    }else{
        GGT_PLATFORM_ADD_EVENT(GGTPE_KEY_DOWN, key, key);
        ggt_globals.keys[key] = 1;
    }
    
    return 0;
}

EM_BOOL mouse_callback(int eventType, const EmscriptenMouseEvent *e, void *userData){
    ggt_vec2i position = {e->canvasX, e->canvasY};
    switch(eventType){
        case EMSCRIPTEN_EVENT_MOUSEDOWN:
        GGT_PLATFORM_ADD_EVENT(GGTPE_MOUSE_LEFT_DOWN, coords, position);
        break;
        case EMSCRIPTEN_EVENT_MOUSEUP:
        GGT_PLATFORM_ADD_EVENT(GGTPE_MOUSE_LEFT_UP, coords, position);
        break;
        case EMSCRIPTEN_EVENT_MOUSEMOVE:
        GGT_PLATFORM_ADD_EVENT(GGTPE_MOUSE_MOVE, mouse_movement, {position.x, position.y, position.x - ggt_globals.last_mouse_position.x, position.y - ggt_globals.last_mouse_position.y});
        break;
    }
    ggt_globals.last_mouse_position = {e->canvasX, e->canvasY};
    
    return 0;
}


EM_BOOL resize_callback(int eventType, const EmscriptenUiEvent *e, void *userData){
    if(eventType == EMSCRIPTEN_EVENT_RESIZE){
        GGT_PLATFORM_ADD_EVENT(GGTPE_RESIZE, size, {e->windowInnerWidth, e->windowInnerHeight});
        emscripten_set_canvas_element_size("canvas", e->windowInnerWidth, e->windowInnerHeight);
    }
    
    return 0;
}

void ggt_platform_set_cursor(ggt_platform_cursor cursor){
}

void main_loop(){
    game_loop(&ggt_globals.game_state, ggt_globals.keys, ggt_globals.events);
    ggt_globals.events.size = 0;
    game_draw(&ggt_globals.game_state);
}

int main(void) {
    emscripten_set_mousedown_callback("#canvas", 0, 1, mouse_callback);
    emscripten_set_mouseup_callback("#canvas", 0, 1, mouse_callback);
    emscripten_set_mousemove_callback("#canvas", 0, 1, mouse_callback);
    emscripten_set_resize_callback("#window", 0, 1, resize_callback);
    emscripten_set_keydown_callback("#document", 0, 1, key_callback);
    emscripten_set_keyup_callback("#document", 0, 1, key_callback);
    
    int width = window_width();
    int height = window_height();
    emscripten_set_canvas_element_size("canvas", width, height);
    
    EmscriptenWebGLContextAttributes attrs;
    emscripten_webgl_init_context_attributes(&attrs);
    attrs.alpha = 8;
    attrs.depth = 24;
    attrs.stencil = 8;
    attrs.antialias = true;
    attrs.premultipliedAlpha = false;
    EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx = emscripten_webgl_create_context(NULL, &attrs);
    if(ctx != NULL)
        printf("Failed to create WebGL context");
    emscripten_webgl_make_context_current(ctx);
    
    for(int i=0; i<GGTP_TOTAL_KEYS; i++)
        ggt_globals.keys[i] = 0;
    ggt_globals.events.size = 0;
    
    init_game(&ggt_globals.game_state);
    
    GGT_PLATFORM_ADD_EVENT(GGTPE_RESIZE, size, {width, height});
    
    emscripten_set_main_loop(main_loop, 0, 1);
    
    return 0;
}

void ggtp_program_file_path(const char *name, char *dst){
    sprintf(dst, "../run_tree/%s", name);
}
void ggtp_user_file_path(const char *name, char *dst){
    sprintf(dst, "../run_tree/%s", name);
}

ggt_u64 ggtp_file_modification_date(const char *path){
    return 0;
}

#endif

#undef ggt_globals

#endif