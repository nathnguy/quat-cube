//
//  Quaternion.hpp
//  quat-cube
//
//  Created by Nathan on 5/26/23.
//

#ifndef Quaternion_hpp
#define Quaternion_hpp

#include "Vector3D.hpp"

class Quaternion {
public:
    Vector3D* vec;
    float scalar;
    
    Quaternion();
    Quaternion(float x, float y, float z, float w);
    Quaternion(const Vector3D& vec, float w);
    
    ~Quaternion();
    
    // result is a quaternion that is equivalent to a rotation by
    // quat then a rotation by this
    Quaternion* multiply(const Quaternion& quat);
    
    Quaternion* invert();
    Quaternion* invert_normalized();
    
    // axis must be normalized
    static Quaternion* angleAxisToQuat(float radians, const Vector3D& axis);
    
    float length();
    void normalize();
    
};

#endif /* Quaternion_hpp */
