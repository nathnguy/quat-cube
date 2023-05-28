//
//  Quaternion.cpp
//  quat-cube
//
//  Created by Nathan on 5/26/23.
//

#include "Quaternion.hpp"
#include <math.h>

Quaternion::Quaternion() {
    this->vec = new Vector3D();
    this->scalar = 0;
}

Quaternion::Quaternion(float x, float y, float z, float w) {
    this->vec = new Vector3D(x, y, z);
    this->scalar = w;
}

Quaternion::Quaternion(const Vector3D& vec, float w) {
    this->vec = new Vector3D(vec);
    this->scalar = w;
}

Quaternion::~Quaternion() {
    delete this->vec;
}

Quaternion* Quaternion::multiply(const Quaternion& quat) {
    // result vector
    Vector3D* cross = this->vec->cross(*quat.vec);
    Vector3D* q2Scaled = quat.vec->scale(this->scalar);
    Vector3D* q1Scaled = this->vec->scale(quat.scalar);
    Vector3D* resultVec = cross->add(*q2Scaled)->add_inplace(*q1Scaled);
    
    // result scalar
    float resultScalar = (this->scalar * quat.scalar) - (this->vec->dot(*quat.vec));
    
    Quaternion* result = new Quaternion(*resultVec, resultScalar);
    
    delete cross; delete q2Scaled; delete q1Scaled; delete resultVec;
    
    return result;
}

Quaternion* Quaternion::invert() {
    float length = this->length();
    float lengthSquared = length * length;
    
    Vector3D* inverseVec = this->vec->scale(-1.0f / lengthSquared);
    float inverseScalar = this->scalar / lengthSquared;
    
    Quaternion* result = new Quaternion(*inverseVec, inverseScalar);
    
    delete inverseVec;
    
    return result;
}

Quaternion* Quaternion::invert_normalized() {
    Vector3D* inverseVec = this->vec->scale(-1);
    Quaternion* result = new Quaternion(*inverseVec, this->scalar);
    delete inverseVec;
    
    return result;
}

float Quaternion::length() {
    return sqrtf(
        this->vec->x * this->vec->x +
        this->vec->y * this->vec->y +
        this->vec->z * this->vec->z +
        this->scalar * this->scalar
    );
}

void Quaternion::normalize() {
    float length = this->length();
    this->vec->scale_inplace(length);
    this->scalar /= length;
}

Quaternion* Quaternion::angleAxisToQuat(float radians, const Vector3D& axis) {
    Vector3D* vec = axis.scale(sinf(radians * 0.5f));
    float scalar = cosf(radians * 0.5f);
    
    Quaternion* result = new Quaternion(*vec, scalar);
    delete vec;
    
    return result;
}
