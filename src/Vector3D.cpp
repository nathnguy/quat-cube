//
//  Vector3D.cpp
//  quat-cube
//
//  Created by Nathan on 5/24/23.
//

#include "Vector3D.hpp"
#include <math.h>

const Vector3D Vector3D::ZERO;

Vector3D::Vector3D() {
    this->x = 0.0f;
    this->y = 0.0f;
    this->z = 0.0f;
}

Vector3D::Vector3D(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector3D::Vector3D(const Vector3D& vec) {
    this->x = vec.x;
    this->y = vec.y;
    this->z = vec.z;
}

Vector3D* Vector3D::add(const Vector3D& vec) const {
    return new Vector3D(this->x + vec.x, this->y + vec.y, this->z + vec.z);
}

Vector3D* Vector3D::subtract(const Vector3D& vec) const {
    return new Vector3D(this->x - vec.x, this->y - vec.y, this->z - vec.z);
}

Vector3D* Vector3D::multiply(const Vector3D& vec) const {
    return new Vector3D(this->x * vec.x, this->y * vec.y, this->z * vec.z);
}

Vector3D* Vector3D::divide(const Vector3D& vec) const {
    return new Vector3D(this->x / vec.x, this->y / vec.y, this->z / vec.z);
}

float Vector3D::dot(const Vector3D& vec) const {
    return this->x * vec.x + this->y * vec.y + this->z * vec.z;
}

Vector3D* Vector3D::cross(const Vector3D& vec) const {
    Vector3D* result = new Vector3D();
    
    result->x = this->y * vec.z - this->z * vec.y;
    result->y = this->z * vec.x - this->x * vec.z;
    result->z = this->x * vec.y - this->y * vec.x;
    
    return result;
}

void Vector3D::set(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

void Vector3D::set(const Vector3D& vec) {
    set(vec.x, vec.y, vec.z);
}

bool Vector3D::equals(const Vector3D& vec) {
    return (this->x == vec.x) &&
           (this->y == vec.y) &&
           (this->z == vec.z);
}

Vector3D* Vector3D::scale(float scalar) const {
    return new Vector3D(this->x * scalar, this->y * scalar, this->z * scalar);
}

Vector3D* Vector3D::add_inplace(const Vector3D& vec) {
    this->x += vec.x;
    this->y += vec.y;
    this->z += vec.z;
    
    return this;
}

Vector3D* Vector3D::subtract_inplace(const Vector3D& vec) {
    this->x -= vec.x;
    this->y -= vec.y;
    this->z -= vec.z;
    
    return this;
}

Vector3D* Vector3D::scale_inplace(float scalar) {
    this->x *= scalar;
    this->y *= scalar;
    this->z *= scalar;
    
    return this;
}

float Vector3D::length() {
    return sqrtf(
        this->x * this->x +
        this->y * this->y +
        this->z * this->z
    );
}

Vector3D* Vector3D::normalize() {
    float length = this->length();
    scale_inplace(1.0f / length);
    
    return this;
}
