#include "swTriangle.h"

namespace sw {

bool Triangle::intersect(const Ray &r, Intersection &isect) const {
    Vec3 p = r.orig;
    Vec3 d = r.dir;

    Vec3 e1 = vertices[1] - vertices[0];
    Vec3 e2 = vertices[2] - vertices[0];

    Vec3 n = e1 % e2;
    float m = -n * vertices[0];
    float t = ((n * p) + m) / (-n * d);
    Vec3 Q = p + t * d;

    if (t < r.minT || t > r.maxT) {
        return false;
    }

    Vec3 coplanar = Q - vertices[0];

    float v = (e1 % coplanar).norm() / n.norm();
    float w = (coplanar % e2).norm() / n.norm();

    float v_in = (e1 % coplanar) * n;
    float w_in = (coplanar % e2) * n;

    if (v + w < 1 && v_in > 0 && w_in > 0) { // Q inside triangle
        isect.hitT = t;
        isect.normal = n;
        isect.normal.normalize();
        isect.frontFacing = (-d * isect.normal) > 0.0f;
        if (!isect.frontFacing) isect.normal = -isect.normal;
        isect.position = Q;
        isect.material = material;
        isect.ray = r;
        return true;
    }

    return false;
}

} // namespace sw
