#include "OpenGLGraphicsSystem.h"
#include "OpenGLGraphicsWindow.h"
#include "GLSLGraphicsShader.h"

#include <iostream>
#include <sstream>
#include <glm/gtc/matrix_transform.hpp>
#include "OpenGLGraphicsObject.h"

OpenGLGraphicsSystem::OpenGLGraphicsSystem() : 
   AbstractGraphicsSystem()
{
   _window = new OpenGLGraphicsWindow("OpenGL Window", 800, 600);
}

OpenGLGraphicsSystem::OpenGLGraphicsSystem(
   OpenGLGraphicsWindow* window, BaseCamera* camera, GLSLGraphicsShader* shader):
   AbstractGraphicsSystem(window, camera, shader)
{
}

OpenGLGraphicsSystem::~OpenGLGraphicsSystem()
{
   glfwTerminate();
}

bool OpenGLGraphicsSystem::InitializeContext()
{
   glfwInit();
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

   if (!_window->Create()) {
      glfwTerminate();
      return false;
   }
   if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
      _errorReport = "Failed to initialize GLAD\n";
      return false;
   }
   if (_shader != nullptr) {
      if (!_shader->Create()) {
         _errorReport = _shader->ReportErrors();
         return false;
      }
   }
   else {
      _errorReport = "A shader was not created.\n";
      return false;
   }
   return true;
}

void OpenGLGraphicsSystem::ShowWindow()
{
   _window->SetOnResize();
   _window->ShowMaximized();
}

void OpenGLGraphicsSystem::Setup()
{
   glEnable(GL_DEPTH_TEST);
   for (auto iterator = _objects.begin(); iterator != _objects.end(); iterator++) {
      iterator->second->Setup();
   }
}

void OpenGLGraphicsSystem::Run()
{
   auto shader = (GLSLGraphicsShader*)_shader;
   while (!_window->IsTimeToClose()) {
      ProcessInput();

      _camera->SetupProjectionAndView(_window->GetAspectRatio());
      _camera->SetupLookingForward();
      shader->projection = _camera->GetProjection();
      shader->view = _camera->GetView();
 
      _window->Clear();
      for (auto iterator = _objects.begin(); iterator != _objects.end(); iterator++) {
         iterator->second->Render();
      }

      _window->SwapBuffers();
   }
}

void OpenGLGraphicsSystem::ProcessInput()
{
   if (_window->GetKeyState(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      _window->Close();
   }

   auto xAxis = _camera->frame.GetXAxis();
   auto yAxis = _camera->frame.GetYAxis();
   auto zAxis = _camera->frame.GetZAxis();
   auto cube = (OpenGLGraphicsObject*)_objects["Cube"];
   auto cuboid1 = (OpenGLGraphicsObject*)_objects["Cuboid 1"];
   auto cuboid2 = (OpenGLGraphicsObject*)_objects["Cuboid 2"];

   if (_window->GetKeyState(GLFW_KEY_Y) == GLFW_PRESS) {
      //cube->frame.Rotate(1, glm::vec3(0, 1, 0));
      //cuboid1->frame.Rotate(1, glm::vec3(0, 1, 0));
      //cuboid2->frame.Rotate(1, glm::vec3(0, 1, 0));
      cube->frame.RotateWorld(1, glm::vec3(0, 1, 0));
      cuboid1->frame.RotateWorld(1, glm::vec3(0, 1, 0));
      cuboid2->frame.RotateWorld(1, glm::vec3(0, 1, 0));
   }
   if (_window->GetKeyState(GLFW_KEY_X) == GLFW_PRESS) {
      //cube->frame.Rotate(1, glm::vec3(1, 0, 0));
      //cuboid1->frame.Rotate(1, glm::vec3(1, 0, 0));
      //cuboid2->frame.Rotate(1, glm::vec3(1, 0, 0));
      cube->frame.RotateWorld(1, glm::vec3(1, 0, 0));
      cuboid1->frame.RotateWorld(1, glm::vec3(1, 0, 0));
      cuboid2->frame.RotateWorld(1, glm::vec3(1, 0, 0));
   }
   if (_window->GetKeyState(GLFW_KEY_Z) == GLFW_PRESS) {
      //cube->frame.Rotate(1, glm::vec3(0, 0, 1));
      //cuboid1->frame.Rotate(1, glm::vec3(0, 0, 1));
      //cuboid2->frame.Rotate(1, glm::vec3(0, 0, 1));
      cube->frame.RotateWorld(1, glm::vec3(0, 0, 1));
      cuboid1->frame.RotateWorld(1, glm::vec3(0, 0, 1));
      cuboid2->frame.RotateWorld(1, glm::vec3(0, 0, 1));
   }
   if (_window->GetKeyState(GLFW_KEY_R) == GLFW_PRESS) {
      cube->frame.Reset();
      cuboid1->frame.Reset();
      cuboid2->frame.Reset();
   }

   if (_window->GetKeyState(GLFW_KEY_D) == GLFW_PRESS) {
       _camera->frame.Rotate(-0.05f, yAxis);
   }
   if (_window->GetKeyState(GLFW_KEY_A) == GLFW_PRESS) {
       _camera->frame.Rotate(0.05f, yAxis);
   }
   if (_window->GetKeyState(GLFW_KEY_W) == GLFW_PRESS) {
       zAxis *= 0.01;
       _camera->frame.Move(-zAxis);
   }
   if (_window->GetKeyState(GLFW_KEY_S) == GLFW_PRESS) {
       zAxis *= 0.01;
      _camera->frame.Move(zAxis);
   }
   if (_window->GetKeyState(GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
   {
       if (_window->GetKeyState(GLFW_KEY_A) == GLFW_PRESS)
       {
           xAxis *= 0.01;
           _camera->frame.Move(-xAxis);
       }
   }
   if (_window->GetKeyState(GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
   {
       if (_window->GetKeyState(GLFW_KEY_D) == GLFW_PRESS)
       {
           xAxis *= 0.01;
           _camera->frame.Move(xAxis);
       }
   }
   if (_window->GetKeyState(GLFW_KEY_UP) == GLFW_PRESS) {
      _camera->frame.Move({ 0, 0.05f, 0 });
   }
   if (_window->GetKeyState(GLFW_KEY_DOWN) == GLFW_PRESS) {
      _camera->frame.Move({ 0, -0.05f, 0 });
   }

   if (_window->GetKeyState(GLFW_KEY_1) == GLFW_PRESS) {
       cube->frame.Scale(0.98f);
       cuboid1->frame.Scale(0.98f);
       cuboid2->frame.Scale(0.98f);
   }
   if (_window->GetKeyState(GLFW_KEY_2) == GLFW_PRESS) {
       cube->frame.Scale(1.02f);
       cuboid1->frame.Scale(1.02f);
       cuboid2->frame.Scale(1.02f);
   }

}


