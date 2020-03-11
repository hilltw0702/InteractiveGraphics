#include "Generate.h"

OpenGLGraphicsObject* Generate::FlatSurface(float width, float depth, RGBA color)
{
    auto flatSurface = new OpenGLGraphicsObject();
    float halfWidth = width / 2;
    float halfDepth = depth / 2;
    Vertex V1 = { -halfWidth, 0.0f, -halfDepth, color.red, color.green, color.blue };
    Vertex V2 = { -halfWidth, 0.0f,  halfDepth, color.red, color.green, color.blue };
    Vertex V3 = { halfWidth, 0.0f,  halfDepth, color.red, color.green, color.blue };
    Vertex V4 = { halfWidth, 0.0f, -halfDepth, color.red, color.green, color.blue };
    flatSurface->AddVertex(V1);
    flatSurface->AddVertex(V2);
    flatSurface->AddVertex(V3);
    flatSurface->AddVertex(V1);
    flatSurface->AddVertex(V3);
    flatSurface->AddVertex(V4);
    return flatSurface;
}

OpenGLGraphicsObject* Generate::Cuboid(float width, float height, float depth, RGBA color)
{
    auto cuboid = new OpenGLGraphicsObject();

    float halfWidth = width / 2;
    float halfHeight = height / 2;
    float halfDepth = depth / 2;

    Vertex V1 = { -halfWidth, halfHeight, halfDepth, color.red, color.green, color.blue };
    Vertex V2 = { -halfWidth, -halfHeight, halfDepth, color.red, color.green, color.blue };
    Vertex V3 = { halfWidth, -halfHeight, halfDepth, color.red, color.green, color.blue };
    Vertex V4 = { halfWidth, halfHeight, halfDepth, color.red, color.green, color.blue };
    Vertex V5 = { halfWidth, halfHeight, -halfDepth, color.red, color.green, color.blue };
    Vertex V6 = { halfWidth, -halfHeight, -halfDepth, color.red, color.green, color.blue };
    Vertex V7 = { -halfWidth, -halfHeight, -halfDepth, color.red, color.green, color.blue };
    Vertex V8 = { -halfWidth, halfHeight, -halfDepth, color.red, color.green, color.blue };

    // side 1
    cuboid->AddVertex(V1);
    cuboid->AddVertex(V2);
    cuboid->AddVertex(V3);
    cuboid->AddVertex(V1);
    cuboid->AddVertex(V3);
    cuboid->AddVertex(V4);

    // side 2
    cuboid->AddVertex(V4);
    cuboid->AddVertex(V3);
    cuboid->AddVertex(V6);
    cuboid->AddVertex(V4);
    cuboid->AddVertex(V6);
    cuboid->AddVertex(V5);

    // side 3
    cuboid->AddVertex(V5);
    cuboid->AddVertex(V6);
    cuboid->AddVertex(V7);
    cuboid->AddVertex(V5);
    cuboid->AddVertex(V7);
    cuboid->AddVertex(V8);

    // side 4
    cuboid->AddVertex(V8);
    cuboid->AddVertex(V7);
    cuboid->AddVertex(V2);
    cuboid->AddVertex(V8);
    cuboid->AddVertex(V2);
    cuboid->AddVertex(V1);

    // top
    cuboid->AddVertex(V8);
    cuboid->AddVertex(V1);
    cuboid->AddVertex(V4);
    cuboid->AddVertex(V8);
    cuboid->AddVertex(V4);
    cuboid->AddVertex(V5);

    // bottom
    cuboid->AddVertex(V6);
    cuboid->AddVertex(V3);
    cuboid->AddVertex(V2);
    cuboid->AddVertex(V6);
    cuboid->AddVertex(V2);
    cuboid->AddVertex(V7);

    return cuboid;
}

OpenGLIndexedGraphicsObject* Generate::IndexedFlatSurface(float width, float depth, RGBA color)
{
    auto flatSurface = new OpenGLIndexedGraphicsObject();
    float halfWidth = width / 2;
    float halfDepth = depth / 2;
    Vertex V1 = { -halfWidth, 0.0f, -halfDepth, color.red, color.green, color.blue };
    Vertex V2 = { -halfWidth, 0.0f,  halfDepth, color.red, color.green, color.blue };
    Vertex V3 = { halfWidth, 0.0f,  halfDepth, color.red, color.green, color.blue };
    Vertex V4 = { halfWidth, 0.0f, -halfDepth, color.red, color.green, color.blue };
    flatSurface->AddVertex(V1);
    flatSurface->AddVertex(V2);
    flatSurface->AddVertex(V3);
    flatSurface->AddVertex(V4);
    flatSurface->AddIndex(0);
    flatSurface->AddIndex(1);
    flatSurface->AddIndex(2);
    flatSurface->AddIndex(0);
    flatSurface->AddIndex(2);
    flatSurface->AddIndex(3);
    return flatSurface;
}
