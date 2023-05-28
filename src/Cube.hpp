//
//  Cube.hpp
//  quat-cube
//
//  Created by Nathan on 5/24/23.
//

#ifndef Cube_hpp
#define Cube_hpp

#include <SDL.h>
#include "Vector3D.hpp"

class Cube {
public:
    float length;
    Vector3D* position; // center of cube
    
    Cube(float length);
    Cube(float length, float x, float y, float z);
    
    ~Cube();
    
    void draw(SDL_Renderer* renderer) const;
    void rotate(const Vector3D& axis, float radians);
    
private:
    static const int NUM_POINTS = 8;
    constexpr static const int COLORS[4][3] = {
        {99, 224, 96},
        {240, 50, 60},
        {163, 65, 224},
        {49, 79, 224}
    };
    
    // 0 - front top left
    // 1 - front top right
    // 2 - front bottom right
    // 3 - front bottom left
    // 4 - back bottom left
    // 5 - back bottom right
    // 6 - back top right
    // 7 - back top left
    Vector3D points[NUM_POINTS];
    
    void initPoints();
    
    void getDisplayPoints(Vector3D displayPoints[]) const;
    void drawLine(SDL_Renderer* renderer,
                  Vector3D displayPoints[],
                  int p1, int p2) const;
    
};

#endif /* Cube_hpp */
