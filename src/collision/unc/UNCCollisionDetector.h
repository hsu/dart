/*
 * Copyright (c) 2011, Georgia Tech Research Corporation
 * All rights reserved.
 *
 * Author(s): Jeongseok Lee <jslee02@gmail.com>
 * Date: 06/08/2013
 *
 * Geoorgia Tech Graphics Lab and Humanoid Robotics Lab
 *
 * Directed by Prof. C. Karen Liu and Prof. Mike Stilman
 * <karenliu@cc.gatech.edu> <mstilman@cc.gatech.edu>
 *
 * This file is provided under the following "BSD-style" License:
 *   Redistribution and use in source and binary forms, with or
 *   without modification, are permitted provided that the following
 *   conditions are met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 *   CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 *   INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 *   MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 *   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 *   USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 *   AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *   LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *   ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *   POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef COLLISION_UNC_CONLLISION_DETECTOR_H
#define COLLISION_UNC_CONLLISION_DETECTOR_H

#include <vector>
#include <map>
#include <Eigen/Dense>

#include "math/LieGroup.h"
#include "collision/CollisionDetector.h"

namespace dart {

namespace dynamics {
class Shape;
}

using namespace math;

namespace collision {

class UNCCollisionNode;

/// @brief
class UNCCollisionDetector : public CollisionDetector {
public:
    /// @brief
    UNCCollisionDetector();

    /// @brief
    virtual ~UNCCollisionDetector();

    // Documentation inherited
    virtual CollisionNode* createCollisionNode(dynamics::BodyNode* _bodyNode);

    // Documentation inherited
    virtual bool checkCollision(bool _checkAllCollisions,
                                bool _calculateContactPoints);

    /// @brief
    int getNumMaxContacts() const { return mNumMaxContacts; }

    /// @brief
    void setNumMaxContacts(int _num) { mNumMaxContacts = _num; }

protected:

private:
    /// @brief
    int mNumMaxContacts;
};



struct vpCollisionInfo
{
    Vec3 point;			/*!< point of collision in a global frame */
    Vec3 normal;		/*!< surface normal of the right body at the collision point in a global frame */
    double penetration;	/*!< penetration depth */

//    Vec3 leftPosition;
//    Vec3 rightPosition;
//    Vec3 tangentialVelocity;
//    double collidingVelocity;
//    double spinningVelocity;
//    double contactForce;
};

typedef std::vector<vpCollisionInfo> vpCollisionInfoArray;

int collide(dynamics::Shape* shape0, const math::SE3& T0,
            dynamics::Shape* shape1, const math::SE3& T1,
            vpCollisionInfoArray& result, int n);

int	_BoxBox_____________MARK8(const Vec3& size0, const SE3& T0,
                              const Vec3& size1, const SE3& T1,
                              vpCollisionInfoArray& result);
int	_BoxSphere__________MARK8(const Vec3& size0, const SE3& T0,
                              double r1, const SE3& T1,
                              vpCollisionInfoArray& result);
//int	_BoxCylinder________MARK8();
//int	_BoxCapsule_________MARK8();

int	_SphereBox__________MARK8(const Vec3& size, const SE3& T0,
                              double r0, const SE3& T1,
                              vpCollisionInfoArray& result);
int	_SphereSphere_______MARK8(double r0, const SE3& T0,
                              double r1, const SE3& T1,
                              vpCollisionInfoArray& result);
//int	_SphereCylinder_____MARK8();
//int	_SphereCapsule______MARK8();

//int	_CylinderBox________MARK8();
//int	_CylinderSphere_____MARK8();
//int	_CylinderCylinder___MARK8();
//int	_CylinderCapsule____MARK8();

//int	_CapsuleBox_________MARK8();
//int	_CapsuleSphere______MARK8();
//int	_CapsuleCylinder____MARK8();
//int	_CapsuleCapsule_____MARK8();

//int	_PlaneBox___________MARK8();
//int	_PlaneSphere________MARK8();
//int	_PlaneCylinder______MARK8();
//int	_PlaneCapsule_______MARK8();

int	_BoxPlane___________MARK8(const SE3& T0,
                              const Vec3& size, const SE3& T1,
                              vpCollisionInfoArray& result);
//int	_SpherePlane________MARK8();
//int	_CylinderPlane______MARK8();
//int	_CapsulePlane_______MARK8();

//------------------------------------------------------------------------------
// Sphere-Sphere
bool ColDetSphereSphere(
        double r0, const Vec3& c0, double r1, const Vec3& c1,
        Vec3 &normal, Vec3 &point, double &rsum);
bool ColDetSphereSphere(
        double r0, const SE3 &c0, double r1, const SE3 &c1);
bool ColDetSphereSphere(
        double r0, const SE3 &c0, double r1, const SE3 &c1,
        Vec3 &normal, Vec3 &point, double &rsum);

// Sphere-Box
bool ColDetSphereBox(
        const double& r0, const SE3& T0,
        const Vec3& size, const SE3& T1);
bool ColDetSphereBox(
        const double& r0, const SE3& T0,
        const Vec3& size, const SE3& T1,
        Vec3 &normal, Vec3 &point, double &penetration);

// Sphere-Plane
bool ColDetSpherePlane(
        const double &rad, const Vec3 &c,
        const Vec3 &plane_normal, const SE3 &T,
        Vec3 &normal, Vec3 &point, double &penetration);

//------------------------------------------------------------------------------
// Box
//------------------------------------------------------------------------------
// Box-Box
bool ColDetBoxBox(
        const Vec3 &size0, const SE3 &T0,
        const Vec3 &size1, const SE3 &T1,
        vpCollisionInfoArray &info, int max_nc);
bool ColDetBoxBox(
        const Vec3 &size0, const SE3 &T0,
        const Vec3 &size1, const SE3 &T1,
        vpCollisionInfoArray &info, int max_nc);

bool ColDetBoxPlane(
        const Vec3 &halfSize, const SE3 &Tbox,
        const Vec3 &planeNormal, const SE3 &Tplane,
        vpCollisionInfoArray &info);

//------------------------------------------------------------------------------
// Capsule
//------------------------------------------------------------------------------
// Capsule-Capsule
bool ColDetCapsuleCapsule(
        const double &r0, const double &h0, const SE3 &T0,
        const double &r1, const double &h1, const SE3 &T1);
bool ColDetCapsuleCapsule(
        const double &r0, const double &h0, const SE3 &T0,
        const double &r1, const double &h1, const SE3 &T1,
        Vec3 &normal, Vec3 &point, double &penetration);

// Capsule-Sphere
bool ColDetCapsuleSphere(
        const double &r0, const double &h, const SE3 &T0,
        const double &r1, const SE3 &T1);
bool ColDetCapsuleSphere(
        const double &r0, const double &h, const SE3 &T0,
        const double &r1, const SE3 &T1,
        Vec3 &normal, Vec3 &point, double &penetration);

// Cpasule-Box
bool ColDetCapsuleBox(
        const double &r, const double &h, const SE3 &T0,
        const Vec3 &size, const SE3 &T1);
bool ColDetCapsuleBox(
        const double &r, const double &h, const SE3 &T0,
        const Vec3 &size, const SE3 &T1,
        Vec3 &normal, Vec3 &point, double &penetration);



//------------------------------------------------------------------------------
// Cylinder
//------------------------------------------------------------------------------
// Cylinder-Plane
bool ColDetCylinderPlane(
        const double &rad, const double &half_height, const SE3 &T0,
        const Vec3 &plane_normal, const SE3 &T1,
        Vec3 &normal, Vec3 &point, double &penetration);
// Cylinder-Sphere
bool ColDetCylinderSphere(
        const double &cyl_rad, const double &half_height, const SE3 &T0,
        const double &sphere_rad, const SE3 &T1,
        Vec3 &normal, Vec3 &point, double &penetration);

//------------------------------------------------------------------------------
// Torus
//------------------------------------------------------------------------------
// Torus-Plane
bool ColDetTorusPlane(
        const double &ring_rad, const double &tube_rad, const SE3 &T0,
        const Vec3 &plane_normal, const SE3 &T1,
        Vec3 &normal, Vec3 &point, double &penetration);
//bool ColDetTorusTorus(const double &, const double &, const SE3 &, const double &, const double &, const SE3 &, Vec3 &, Vec3 &, double &);
//bool ColDetTorusSphere(const double &, const double &, const SE3 &, const double &, const double &, const SE3 &, Vec3 &, Vec3 &, double &);

} // namespace collision
} // namespace dart

#endif // COLLISION_UNC_CONLLISION_DETECTOR_H
