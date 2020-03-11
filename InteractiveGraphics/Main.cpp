#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "opengl32.lib")
#include <Windows.h>

#include "OpenGLGraphicsSystem.h"
#include "OpenGLGraphicsObject.h"
#include "TextFileReader.h"
#include "GraphicsObjectReader.h"
#include "Generate.h"

void ReportError(const string& error) 
{
   // Quick way to convert from string to wstring
   wstring errorString(error.begin(), error.end());
   MessageBox(
      NULL,
      errorString.c_str(),
      L"An Error Occurred",
      MB_OK);
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
   _In_opt_ HINSTANCE hPrevInstance,
   _In_ LPWSTR    lpCmdLine,
   _In_ int       nCmdShow)
{
   OpenGLGraphicsWindow* window = 
      new OpenGLGraphicsWindow("Interactive Graphics Lec Week 7");
   //window->backgroundColor = { 0.5f, 0.0f, 0.5f };

   OpenGLGraphicsObject* object = nullptr;
   GraphicsObjectReader reader("cube.ig");
   if (reader.Read()) {
      object = reader.GetObject();
   }
   else {
      ReportError(reader.ReportErrors());
      return 0;
   }

   GLSLGraphicsShader* shader = 
      new GLSLGraphicsShader(new TextFileReader());
   if (!shader->ReadShaderSources(
      "Simple3DVertexShader.glsl", "SimpleFragmentShader.glsl")) {
      ReportError(shader->ReportErrors());
      return 0;
   }
   object->SetShader(shader);

   auto camera = new BaseCamera();
   camera->frame.SetPosition(2.0f, 5.0f, 7.0f);
   AbstractGraphicsSystem* graphics = new OpenGLGraphicsSystem(window, camera, shader);

   graphics->AddObject("Cube", object);
   object = Generate::IndexedFlatSurface(10, 10, { 0.0f, 0.0f, 0.4f, 1.0f });
   object->SetShader(shader);
   graphics->AddObject("Floor", object);

   /*graphics->AddObject("Cube", object);
   object = Generate::FlatSurface(10, 10, { 0.0f, 0.5f, 0.0f, 1.0f });
   object->SetShader(shader);
   graphics->AddObject("Floor", object);
   auto cube = (OpenGLGraphicsObject*)graphics->GetObject("Cube");
   cube->frame.Move({ 0.0f, 0.5f, 0.0f });*/

   graphics->AddObject("Cuboid", object);
   object = Generate::Cuboid(2, 1, 2, { 1.0f, 0.0f, 0.0f, 0.0f });
   object->SetShader(shader);
   graphics->AddObject("Cuboid 1", object);
   auto cuboid1 = (OpenGLGraphicsObject*)graphics->GetObject("Cuboid 1");
   cuboid1->SetColor(0, 6, { 0.0f, 0.25f, 0.35f });
   cuboid1->frame.Move({ -3.0f, 0.5f, 3.0f });

   graphics->AddObject("Cuboid", object);
   object = Generate::Cuboid(1, 3, 1, { 0.0f, 0.0f, 1.0f, 0.0f });
   object->SetShader(shader);
   graphics->AddObject("Cuboid 2", object);
   auto cuboid2 = (OpenGLGraphicsObject*)graphics->GetObject("Cuboid 2");
   cuboid2->SetColor(4, 6, { 0.15f, 0.75f, 0.35f });
   cuboid2->frame.Move({ 3.0f, 0.5f, -3.0f });

   if (graphics->InitializeContext()) {
      graphics->ShowWindow();
      graphics->Setup();
      graphics->Run();
   }
   else {
      ReportError(graphics->ReportErrors());
   }
   delete graphics;
   return 0;
}