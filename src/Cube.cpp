//
//  Cube.cpp
//  quat-cube
//
//  Created by Nathan on 5/24/23.
//

#include "Cube.hpp"
#include "Quaternion.hpp"

Cube::Cube(float length) {
    this->length = length;
    this->position = new Vector3D();
    this->cam = new Camera();
    initPoints();
}

Cube::Cube(float length, float x, float y, float z) {
    this->length = length;
    this->position = new Vector3D(x, y, z);
    this->cam = new Camera();
    initPoints();
}

Cube::~Cube() {
    delete this->position;
    delete this->cam;
}

void Cube::draw(SDL_Renderer* renderer) const {
    // perspective projection
    // convert 3D points to display coordinates
    Vector3D displayPoints[NUM_POINTS];
    getDisplayPoints(displayPoints);
    
    // TODO: draw lines between points
    // draw front
    SDL_SetRenderDrawColor(renderer, COLORS[0][0], COLORS[0][1], COLORS[0][2], 255);
    for (int i = 0; i < 4; ++i) {
        drawLine(renderer, displayPoints, i, (i+1) % 4);
    }

    // draw left side
    SDL_SetRenderDrawColor(renderer, COLORS[2][0], COLORS[2][1], COLORS[2][2], 255);
    drawLine(renderer, displayPoints, 0, 7);
    drawLine(renderer, displayPoints, 3, 4);

    // draw right side
    SDL_SetRenderDrawColor(renderer, COLORS[3][0], COLORS[3][1], COLORS[3][2], 255);
    drawLine(renderer, displayPoints, 1, 6);
    drawLine(renderer, displayPoints, 2, 5);
    
    // draw back
    SDL_SetRenderDrawColor(renderer, COLORS[1][0], COLORS[1][1], COLORS[1][2], 255);
    for (int i = 4; i < NUM_POINTS; ++i) {
        drawLine(renderer, displayPoints, i, (i+1) % 4 + 4);
    }
    
}

void Cube::rotate(const Vector3D& axis, float radians) {
    Quaternion* quat = Quaternion::angleAxisToQuat(radians, axis);
    Quaternion* inverse = quat->invert_normalized();
    
    for (int i = 0; i < NUM_POINTS; ++i) {
        Quaternion* vector = new Quaternion(points[i], 0);
        Quaternion* mult1 = quat->multiply(*vector);
        Quaternion* mult2 = mult1->multiply(*inverse);
        
        points[i].set(*mult2->vec);
        
        delete vector; delete mult1; delete mult2;
    }
    
    delete quat; delete inverse;
}

// private

void Cube::drawLine(SDL_Renderer *renderer, Vector3D displayPoints[], int p1, int p2) const {
    if (displayPoints[p1].z != 0 &&
        displayPoints[p2].z != 0) {
        SDL_RenderDrawLine(renderer,
                           displayPoints[p1].x, displayPoints[p1].y,
                           displayPoints[p2].x, displayPoints[p2].y);
    }
}

void Cube::getDisplayPoints(Vector3D displayPoints[]) const {
//    Vector3D cam(0, 0, -350.0f); // TODO: movable camera
//    const float focalDistance = 300.0f;
    
    const float xOffset = Camera::WINDOW_WIDTH / 2.0f;
    const float yOffset = Camera::WINDOW_HEIGHT / 2.0f;
    
    for (int i = 0; i < NUM_POINTS; ++i) {
        float x = this->points[i].x - this->cam->position->x; // display x
        float y = this->points[i].y - this->cam->position->y; // display y
        float d_z = this->points[i].z - this->cam->position->z; // cam transform zs
        
        if (this->cam->inView(this->points[i])) {
            // check that point is in front of the camera
            // FUTURE: add more points so cube can be zoomed into
            x = (Camera::FOCAL_DISTANCE / d_z) * x + this->cam->position->x + xOffset;
            y = (Camera::FOCAL_DISTANCE / d_z) * y + this->cam->position->y + yOffset;
            
            displayPoints[i].x = x;
            displayPoints[i].y = y;
            displayPoints[i].z = 1.0f;
        } else {
            displayPoints[i].z = 0.0f;
        }
    }
}

void Cube::initPoints() {
    float offset = this->length / 2.0f;
    
    this->points[0].set(this->position->x - offset,
                        this->position->y - offset,
                        this->position->z - offset);

    this->points[1].set(this->position->x + offset,
                        this->position->y - offset,
                        this->position->z - offset);

    this->points[2].set(this->position->x + offset,
                        this->position->y + offset,
                        this->position->z - offset);

    this->points[3].set(this->position->x - offset,
                        this->position->y + offset,
                        this->position->z - offset);

    this->points[4].set(this->position->x - offset,
                        this->position->y + offset,
                        this->position->z + offset);

    this->points[5].set(this->position->x + offset,
                        this->position->y + offset,
                        this->position->z + offset);

    this->points[6].set(this->position->x + offset,
                        this->position->y - offset,
                        this->position->z + offset);

    this->points[7].set(this->position->x - offset,
                        this->position->y - offset,
                        this->position->z + offset);
    
    // points after rotating 200 length cube centered at origin
    // 45 degrees around y axis
//    this->points[0].set(-141.421f, -100.0f, 0.0f);
//    this->points[1].set(0.0f, -100.0f, -141.421f);
//    this->points[2].set(0.0f, 100.0f, -141.421f);
//    this->points[3].set(-141.421f, 100.0f, 0.0f);
//    this->points[4].set(0.0f, 100.0f, 141.421f);
//    this->points[5].set(141.421f, 100.0f, 0.0f);
//    this->points[6].set(141.421f, -100.0f, 0.0f);
//    this->points[7].set(0.0f, -100.0f, 141.421f);
}
