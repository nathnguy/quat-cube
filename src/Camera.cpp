//
//  Camera.cpp
//  quat-cube
//
//  Created by Nathan on 5/28/23.
//

#include "Camera.hpp"

Camera::Camera() {
    this->position = new Vector3D(0, 0, -350.0f);
    this->normal = new Vector3D(0, 0, 1);
}

Camera::~Camera() {
    delete this->position;
    delete this->normal;
}

bool Camera::inView(const Vector3D &point) {
    Vector3D* vec = point.subtract(*this->position);
    bool result = this->normal->dot(*vec) >= 0.0f;
    delete vec;
    return result;
}
