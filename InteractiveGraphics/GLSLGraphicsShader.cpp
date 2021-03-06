#include <glad\glad.h>
#include <glm/gtc/type_ptr.hpp>
#include "GLSLGraphicsShader.h"
#include <sstream>
#include <fstream>
#include "TextFileReader.h"
using std::stringstream;
using std::ifstream;

void GLSLGraphicsShader::SetUpDefaultSources()
{
   _vertexSource =
      "#version 400\n"\
      "layout(location = 0) in vec3 position;\n"\
      "layout(location = 1) in vec3 vertexColor;\n"\
      "out vec4 fragColor;\n"\
      "void main()\n"\
      "{\n"\
      "   gl_Position = vec4(position, 1.0)\n" \
      "   fragColor = vec4(vertexColor, 1.0);\n" \
      "}\n";

   _fragmentSource =
      "#version 400\n"\
      "in vec4 fragColor;\n"\
      "out vec4 color;\n"\
      "void main()\n"\
      "{\n"\
      "   color = fragColor;\n"\
      "}\n";
}

bool GLSLGraphicsShader::ReadShaderSources(const string& vertexFilePath, const string& fragmentFilePath)
{
   if (!ReadVertexShaderSource(vertexFilePath)) {
      return false;
   }
   if (!ReadFragmentShaderSource(fragmentFilePath)) {
      return false;
   }
   return true;
}

bool GLSLGraphicsShader::ReadVertexShaderSource(const string& filePath)
{
   TextFileReader* reader = (TextFileReader*)_reader;
   reader->SetFilePath(filePath);
   bool result = reader->Read();
   if (result) {
      _vertexSource = reader->GetData();
   }
   return result;
}

bool GLSLGraphicsShader::ReadFragmentShaderSource(const string& filePath)
{
   TextFileReader* reader = (TextFileReader*)_reader;
   reader->SetFilePath(filePath);
   bool result = reader->Read();
   if (result) {
      _fragmentSource = reader->GetData();
   }
   return result;
}

string GLSLGraphicsShader::ReportErrors()
{
   return _errorReport;
}

bool GLSLGraphicsShader::Create()
{
   GLuint vertexShader = 
      CompileShader(GL_VERTEX_SHADER, _vertexSource.c_str());
   if (vertexShader == 0) return false;
   GLuint fragmentShader = 
      CompileShader(GL_FRAGMENT_SHADER, _fragmentSource.c_str());
   if (fragmentShader == 0) return false;
   _shaderProgram = LinkShader(vertexShader, fragmentShader);
   glDeleteShader(vertexShader);
   glDeleteShader(fragmentShader);
   if (_shaderProgram == 0) return false;
   return true;
}

void GLSLGraphicsShader::Select()
{
   glUseProgram(_shaderProgram);
}

void GLSLGraphicsShader::SendMatrixToGPU(const string& uniformName, const glm::mat4& matrix)
{
   unsigned int uniformLocation = glGetUniformLocation(_shaderProgram, uniformName.c_str());
   glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(matrix));
}

void GLSLGraphicsShader::SendMatricesToGPU()
{
   SendMatrixToGPU("view", view);
   SendMatrixToGPU("projection", projection);
}

GLuint GLSLGraphicsShader::CompileShader(GLenum type, const GLchar* source)
{
   GLint length = (GLint)(sizeof(GLchar) * strlen(source));
   GLuint shader = glCreateShader(type);
   glShaderSource(shader, 1, (const GLchar**)&source, &length);
   glCompileShader(shader);
   GLint shaderOk = 0;
   glGetShaderiv(shader, GL_COMPILE_STATUS, &shaderOk);
   if (!shaderOk) {
      LogError(shader, glGetShaderiv, glGetShaderInfoLog);
      glDeleteShader(shader);
      shader = 0;
   }
   return shader;
}

GLuint GLSLGraphicsShader::LinkShader(GLuint vertexShader, GLuint fragmentShader)
{
   GLuint program = glCreateProgram();
   glAttachShader(program, vertexShader);
   glAttachShader(program, fragmentShader);
   glLinkProgram(program);
   GLint programOk = 0;
   glGetProgramiv(program, GL_LINK_STATUS, &programOk);
   if (!programOk) {
      LogError(program, glGetProgramiv, glGetProgramInfoLog);
      glDeleteShader(program);
      program = 0;
   }
   return program;
}

void GLSLGraphicsShader::LogError(GLuint shader, PFNGLGETSHADERIVPROC glGet__iv, PFNGLGETSHADERINFOLOGPROC glGet__InfoLog)
{
   GLint logLength;
   glGet__iv(shader, GL_INFO_LOG_LENGTH, &logLength);
   char* info = (char*)malloc(logLength);
   glGet__InfoLog(shader, logLength, NULL, info);
   stringstream ss;
   ss << info;
   getline(ss, _errorReport);
   free(info);
}

