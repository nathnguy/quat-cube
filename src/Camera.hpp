//
//  Camera.hpp
//  quat-cube
//
//  Created by Nathan on 5/28/23.
//

#ifndef Camera_hpp
#define Camera_hpp

#include "Vector3D.hpp"

class Camera {
public:
    
    static const int WINDOW_WIDTH = 500;
    static const int WINDOW_HEIGHT = 500;
    constexpr static const float FOCAL_DISTANCE = 300.0f;
    constexpr static const float ZOOM_SPEED = 3.0f;
    
    Vector3D* position;
    Vector3D* normal;
    
    Camera();
    ~Camera();
    
    bool inView(const Vector3D& point);
};

#endif /* Camera_hpp */
