//
//  Vector3D.hpp
//  quat-cube
//
//  Created by Nathan on 5/24/23.
//

#ifndef Vector3D_hpp
#define Vector3D_hpp

class Vector3D {
public:
    
    static const Vector3D ZERO;
    
    float x;
    float y;
    float z;
    
    Vector3D();
    Vector3D(float x, float y, float z);
    Vector3D(const Vector3D& vec);
    
    Vector3D* add(const Vector3D& vec) const;
    Vector3D* subtract(const Vector3D& vec) const;
    Vector3D* multiply(const Vector3D& vec) const;
    Vector3D* divide(const Vector3D& vec) const;
    float dot(const Vector3D& vec) const;
    Vector3D* cross(const Vector3D& vec) const;
    Vector3D* scale(float scalar) const;
    
    // in place operations
    Vector3D* add_inplace(const Vector3D& vec);
    Vector3D* subtract_inplace(const Vector3D& vec);
    Vector3D* scale_inplace(float scalar);
    Vector3D* normalize();
    
    void set(float x, float y, float z);
    void set(const Vector3D& vec);
    bool equals(const Vector3D& vec);
    float length();
    
};

#endif /* Vector3D_hpp */
