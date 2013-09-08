/*
 * Copyright (c) 2011, Georgia Tech Research Corporation
 * All rights reserved.
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

#include <iostream>
#include <Eigen/Dense>
#include <gtest/gtest.h>

#include "math/Helpers.h"
#include "dynamics/BodyNode.h"
#include "dynamics/Skeleton.h"
#include "utils/Paths.h"
#include "utils/SkelParser.h"
#include "simulation/World.h"

using namespace dart;
using namespace math;
using namespace dynamics;
using namespace simulation;
using namespace utils;

#define DYNAMICS_TOL 0.000001

/******************************************************************************/
dart::dynamics::Skeleton* prepareSkeleton(const std::string& _fileName,
                                          Eigen::VectorXd& _q,
                                          Eigen::VectorXd& _qdot)
{
    // load skeleton
    World* myWorld = readSkelFile(_fileName);

    Skeleton* skel = myWorld->getSkeleton(0);
    assert(skel != NULL);

    // generate a random state
    _q = Eigen::VectorXd::Zero(skel->getDOF());
    _qdot = Eigen::VectorXd::Zero(skel->getDOF());

    for (int i = 0; i < skel->getDOF(); i++)
    {
        _q[i] = random(-1.0, 1.0);
        _qdot[i] = random(-5.0, 5.0);
    }

    skel->initDynamics();
    return skel;
}

///* ********************************************************************************************* */
//dart::dynamics::Skeleton* prepareSkeleton( Eigen::VectorXd& _q, Eigen::VectorXd& _qdot) {
//    using namespace dart;
//    using namespace dynamics;
//    using namespace dynamics;

//    // load skeleton
//    const char* skelfilename = DART_DATA_PATH"skel/Yuting.vsk";
//    FileInfoSkel<Skeleton>* skelFile = new FileInfoSkel<Skeleton>;
//    bool loadModelResult = skelFile->loadFile(skelfilename);
//    assert(loadModelResult);

//    Skeleton *skelDyn = static_cast<Skeleton*>(skelFile->getSkel());
//    assert(skelDyn != NULL);

//    // generate a random state
//    _q = VectorXd::Zero(skelDyn->getNumDofs());
//    _qdot = VectorXd::Zero(skelDyn->getNumDofs());
//    for(int i=0; i<skelDyn->getNumDofs(); i++){
//        _q[i] = math::random(-1.0, 1.0);
//        _qdot[i] = math::random(-5.0, 5.0);
//    }
//    skelDyn->initDynamics();
//    return skelDyn; }

/* ********************************************************************************************* */
dart::dynamics::Skeleton* prepareSkeletonChain( Eigen::VectorXd& _q, Eigen::VectorXd& _qdot) {
    using namespace dart;
    using namespace dynamics;
    using namespace dynamics;

    // load skeleton
    dart::simulation::World *myWorld = dart::utils::readSkelFile(
                DART_DATA_PATH"skel/test/chainwhipa.skel");
    assert(myWorld != NULL);

    Skeleton *skelDyn = myWorld->getSkeleton(0);
    assert(skelDyn != NULL);

    // generate a random state
    _q = Eigen::VectorXd::Zero(skelDyn->getDOF());
    _qdot = Eigen::VectorXd::Zero(skelDyn->getDOF());
    _q[6] = 1.5707963265;
        skelDyn->initDynamics();
    return skelDyn;
}

/* ********************************************************************************************* */
void addExternalForces(dart::dynamics::Skeleton* skelDyn) {
    using namespace dart;
    using namespace dynamics;
    using namespace dynamics;

    skelDyn->getBodyNode(7)->addExtForce(Eigen::Vector3d(0.1,0.2,0.3), Eigen::Vector3d(30,40,50), true, false );
    skelDyn->getBodyNode(7)->addExtForce(Eigen::Vector3d(0.5,0.5,0.5), -Eigen::Vector3d(20,4,5), true, false );
    skelDyn->getBodyNode(13)->addExtForce(Eigen::Vector3d(0,0,0), Eigen::Vector3d(30,20,10), true, false );
    skelDyn->getBodyNode(2)->addExtTorque(Eigen::Vector3d(30,20,10), false );
}

/* ********************************************************************************************* */
void addExternalForcesChain(dart::dynamics::Skeleton* skelDyn) {
    using namespace dart;
    using namespace dynamics;
    using namespace dynamics;

    skelDyn->getBodyNode(2)->addExtForce(skelDyn->getBodyNode(2)->getLocalCOM(), Eigen::Vector3d(0,19.6,0), true, false );
}

///* ********************************************************************************************* */
//TEST(DYNAMICS, COMPARE_VELOCITIES) {
//    using namespace dart;
//    using namespace dynamics;
//    using namespace dynamics;

//    const double TOLERANCE_EXACT = 1.0e-10;
//    Vector3d gravity(0.0, -9.81, 0.0);
   
//    VectorXd q, qdot;
//    Skeleton *skelDyn = prepareSkeleton(q,qdot);
//    skelDyn->setPose(q, false, false);

//    // test the velocities computed by the two methods
//    skelDyn->computeInverseDynamicsLinear(gravity, &qdot);
//    for(int i=0; i<skelDyn->getNumNodes(); i++){
//        BodyNode *nodei = static_cast<BodyNode*>(skelDyn->getNode(i));
//        EXPECT_TRUE(nodei != NULL);
//        // compute velocities using regular method
//        nodei->updateTransform();
//        nodei->updateFirstDerivatives();
//        nodei->evalJacobian();
//        Vector3d v1 = Vector3d::Zero();
//        Vector3d w1 = Vector3d::Zero();
//        for(int j=0; j<nodei->getNumDependentDofs(); j++){
//            int dj = nodei->getDependentDof(j);
//            for(int k=0; k<3; k++) {
//                v1[k] += nodei->getJacobianLinear() (k, j)*qdot[dj];
//                w1[k] += nodei->getJacobianAngular()(k, j)*qdot[dj];
//            }
//        }

//        // compute velocities using inverse dynamics routine
//        Vector3d v2 = nodei->getWorldTransform().topLeftCorner<3,3>()*nodei->mVelBody;
//        Vector3d w2 = nodei->getWorldTransform().topLeftCorner<3,3>()*nodei->mOmegaBody;

//        for(int k=0; k<3; k++) {
//            EXPECT_NEAR(v1[k], v2[k], TOLERANCE_EXACT);
//            EXPECT_NEAR(w1[k], w2[k], TOLERANCE_EXACT);
//        }

//        // Angular Jacobian regular
//        MatrixXd Jw_regular = (nodei->getJacobianAngular()).rightCols(nodei->getParentJoint()->getNumDofsRot());
//        // Angular jacobian inverse dynamics
//        MatrixXd Jw_invdyn = nodei->mJwJoint;
//        if(nodei->getParentNode()) Jw_invdyn = nodei->getParentNode()->getWorldTransform().topLeftCorner<3,3>()*Jw_invdyn;
//        ASSERT_TRUE(Jw_regular.rows()==Jw_invdyn.rows());
//        ASSERT_TRUE(Jw_regular.cols()==Jw_invdyn.cols());
//        for(int ki=0; ki<Jw_regular.rows(); ki++){
//            for(int kj=0; kj<Jw_regular.cols(); kj++){
//                EXPECT_NEAR(Jw_regular(ki,kj), Jw_invdyn(ki,kj), TOLERANCE_EXACT);
//            }
//        }
//    }
//}

///* ********************************************************************************************* */
//TEST(DYNAMICS, FINITEDIFF_ACCELERATIONS_INVERSEDYNAMICS) {
//    using namespace dart;
//    using namespace dynamics;
//    using namespace dynamics;
    
//    Vector3d gravity(0.0, -9.81, 0.0);
//    double TOLERANCE_APPROX = 1.1e-3;
    
//    VectorXd q, qdot;
//    Skeleton* skelDyn = prepareSkeleton(q, qdot);
//    skelDyn->setPose(q, false, false);
    
//    double dt = 1.0e-6;
//    VectorXd origq = q;
//    VectorXd newq = q + qdot*dt;
//    for(int i=0; i<skelDyn->getNumNodes(); i++){
//        BodyNode *nodei = static_cast<BodyNode*>(skelDyn->getNode(i));
//        EXPECT_TRUE(nodei != NULL);

//        skelDyn->setPose(origq);
//        skelDyn->computeInverseDynamicsLinear(gravity, &qdot);
//        Matrix3d Ri = nodei->getWorldTransform().topLeftCorner<3,3>();

//        MatrixXd JwOrig = nodei->mJwJoint;
//        MatrixXd JwDotOrig = nodei->mJwDotJoint;
//        Vector3d wOrig = Ri*nodei->mOmegaBody;
//        Vector3d wDotOrig = Ri*nodei->mOmegaDotBody;
//        Vector3d vOrig = Ri*nodei->mVelBody;
//        Vector3d vDotOrig = Ri*nodei->mVelDotBody + gravity;

//        skelDyn->setPose(newq);
//        skelDyn->computeInverseDynamicsLinear(gravity, &qdot);
//        Matrix3d Rinew = nodei->getWorldTransform().topLeftCorner<3,3>();

//        MatrixXd JwNew = nodei->mJwJoint;
//        MatrixXd JwDotApprox = (JwNew-JwOrig)/dt;
//        Vector3d wNew = Rinew*nodei->mOmegaBody;
//        Vector3d wDotApprox = (wNew-wOrig)/dt;
//        Vector3d vNew = Rinew*nodei->mVelBody;
//        Vector3d vDotApprox = (vNew-vOrig)/dt;

//        for(int ki=0; ki<JwDotOrig.rows(); ki++){
//            EXPECT_NEAR(vDotOrig[ki], vDotApprox[ki], TOLERANCE_APPROX);
//            EXPECT_NEAR(wDotOrig[ki], wDotApprox[ki], TOLERANCE_APPROX);
//            for(int kj=0; kj<JwDotOrig.cols(); kj++){
//                EXPECT_NEAR(JwDotOrig(ki,kj), JwDotApprox(ki,kj), TOLERANCE_APPROX);
//            }
//        }

//    }
//}

///* ********************************************************************************************* */
//TEST(DYNAMICS, COMPARE_CORIOLIS) {
//    using namespace dart;
//    using namespace dynamics;
//    using namespace dynamics;

//    const double TOLERANCE_EXACT = 1.0e-10;
//    Vector3d gravity(0.0, -9.81, 0.0);

//    VectorXd q, qdot;
//    Skeleton* skelDyn = prepareSkeleton(q, qdot);
//    skelDyn->setPose(q, false, false);

//    // test/compare the dynamics result for both methods
//    VectorXd Cginvdyn = skelDyn->computeInverseDynamicsLinear(gravity, &qdot);
//    skelDyn->computeDynamics(gravity, qdot, false); // compute dynamics by not using inverse dynamics

//    for(int ki=0; ki<Cginvdyn.size(); ki++){
//        EXPECT_NEAR(Cginvdyn[ki], skelDyn->getCombinedVector()[ki], TOLERANCE_EXACT);
//    }
//}

///* ********************************************************************************************* */
//TEST(DYNAMICS, COMPARE_MASS) {
//    using namespace dart;
//    using namespace dynamics;
//    using namespace dynamics;
    
//    const double TOLERANCE_EXACT = 1.0e-10;
//    Vector3d gravity(0.0, -9.81, 0.0);

//    VectorXd q, qdot;
//    Skeleton* skelDyn = prepareSkeleton(q, qdot);
//    skelDyn->setPose(q, false, false);

//    // test/compare the dynamics result for both methods
//    // test the mass matrix
//    skelDyn->computeDynamics(gravity, qdot, true); // compute dynamics by using inverse dynamics
//    MatrixXd Minvdyn( skelDyn->getMassMatrix() );
//    skelDyn->computeDynamics(gravity, qdot, false); // compute dynamics by NOT using inverse dynamics: use regular dynamics
//    MatrixXd Mregular( skelDyn->getMassMatrix() );

//    for(int ki=0; ki<Minvdyn.rows(); ki++){
//        for(int kj=0; kj<Minvdyn.cols(); kj++){
//            EXPECT_NEAR(Minvdyn(ki,kj), Mregular(ki,kj), TOLERANCE_EXACT);
//        }
//    }
//}


///* ********************************************************************************************* */
//TEST(DYNAMICS, COMPARE_EXTERNAL_FORCES) {
//    using namespace dart;
//    using namespace dynamics;
//    using namespace dynamics;

//    const double TOLERANCE_EXACT = 1.0e-10;
//    Vector3d gravity(0.0, -9.81, 0.0);

//    VectorXd q, qdot;
//    Skeleton* skelDyn = prepareSkeleton(q, qdot);
//    skelDyn->setPose(q, true, true);
    
//    addExternalForces(skelDyn); // adding external force may require transformations to be computed to convert points and forces to local coordinates
//    skelDyn->computeInverseDynamicsLinear(gravity, &qdot, NULL, true, false); // some computation in inverse dynamics is required even when only external forces are desired
//    skelDyn->evalExternalForces(true); // use recursive
//    VectorXd Frec = skelDyn->getExternalForces();
    
//    skelDyn->clearExternalForces();
//    addExternalForces(skelDyn);
//    skelDyn->evalExternalForces(false); // use non-recursive Jacobian method; assume first derivatives are computed already
//    VectorXd Fnon = skelDyn->getExternalForces();

//    for(int i=0; i<skelDyn->getNumDofs(); i++)
//        EXPECT_NEAR(Frec(i), Fnon(i), TOLERANCE_EXACT);
//}


///* ********************************************************************************************* */
//TEST(DYNAMICS, COMPARE_DYN_EXTERNAL_FORCES) {
//    using namespace dart;
//    using namespace dynamics;
//    using namespace dynamics;

//    const double TOLERANCE_EXACT = 1.0e-10;
//    Vector3d gravity(0.0, -9.81, 0.0);

//    VectorXd q, qdot;
//    Skeleton* skelDyn = prepareSkeleton(q, qdot);
//    skelDyn->setPose(q, true, true);
    
//    addExternalForces(skelDyn);
//    skelDyn->computeDynamics(gravity, qdot, true); // compute dynamics by using inverse dynamics
//    MatrixXd MRec = skelDyn->getMassMatrix();
//    VectorXd CRec = skelDyn->getCombinedVector();

//    addExternalForces(skelDyn);
//    skelDyn->computeDynamics(gravity, qdot, false); // compute dynamics by NOT using inverse dynamics: use regular dynamics
//    MatrixXd MNon = skelDyn->getMassMatrix();
//    VectorXd CNon = skelDyn->getCombinedVector();

//    for(int i=0; i<skelDyn->getNumDofs(); i++)
//        EXPECT_NEAR(CRec(i), CNon(i), TOLERANCE_EXACT);

//    for(int i=0; i<skelDyn->getNumDofs(); i++)
//        for(int j=i; j<skelDyn->getNumDofs(); j++)
//            EXPECT_NEAR(MRec(i,j), MNon(i,j), TOLERANCE_EXACT);
//}

/* ********************************************************************************************* */
TEST(DYNAMICS, COMPARE_JOINT_TOQUE_W_EXTERNAL_FORCES) {
    using namespace dart;
    using namespace dynamics;
    using namespace math;
    using namespace dynamics;

    const double TOLERANCE_EXACT = 1.0e-10;
    Eigen::Vector3d gravity(0.0, -9.8, 0.0);

    Eigen::VectorXd q, qdot;
    Skeleton* skelDyn = prepareSkeletonChain(q, qdot);
    skelDyn->setPose(q, true, true);

    addExternalForcesChain(skelDyn);
    skelDyn->updateExternalForces();
    Eigen::VectorXd Cginvdyn = skelDyn->computeInverseDynamics(gravity, &qdot, NULL, true, true);

    for(int i=0; i<skelDyn->getDOF(); i++)
        EXPECT_NEAR(Cginvdyn(i), 0.0, TOLERANCE_EXACT);
}

/* ********************************************************************************************* */
// TODO
TEST(DYNAMICS, CONVERSION_VELOCITY) {
}

/* ********************************************************************************************* */
TEST(DYNAMICS, CONVERSION_FORCES) {
}

/******************************************************************************/
TEST(DYNAMICS, INERTIA)
{
    for (int k = 0; k < 100; ++k)
    {
        // com, moment of inertia, mass
        double min = -10;
        double max = 10;
        double Ixx = random(0.1,max);
        double Iyy = random(0.1,max);
        double Izz = random(0.1,max);
        double Ixy = random(0.1,max);
        double Ixz = random(0.1,max);
        double Iyz = random(0.1,max);
        Eigen::Vector3d com(random(min,max), random(min,max), random(min,max));
        double mass = random(0.1,max);

        // G = | I - m * [r] * [r]   m * [r] |
        //     |          -m * [r]     m * 1 |
        Eigen::Matrix3d I = Eigen::Matrix3d::Zero();
        I(0,0) = Ixx;
        I(1,1) = Iyy;
        I(2,2) = Izz;
        I(0,1) = Ixy;
        I(0,2) = Ixz;
        I(1,2) = Iyz;
        I(1,0) = Ixy;
        I(2,0) = Ixz;
        I(2,1) = Iyz;
        Eigen::Matrix6d G = Eigen::Matrix6d::Zero();
        Eigen::Matrix3d r = math::makeSkewSymmetric(com);
        G.topLeftCorner<3,3>() = I - mass*r*r;
        G.topRightCorner<3,3>() = mass*r;
        G.bottomLeftCorner<3,3>() = -mass*r;
        G.bottomRightCorner<3,3>() = mass*Eigen::Matrix3d::Identity();

        // G of bodynode
        dynamics::BodyNode bodyNode;
        bodyNode.setMass(mass);
        bodyNode.setLocalCOM(com);
        bodyNode.setMomentOfInertia(Ixx, Iyy, Izz, Ixy, Ixz, Iyz);
        Eigen::Matrix6d bodyNodeG = bodyNode.getGeneralizedInertia();

        // compare
        for (int i = 0; i < 6; i++)
            for (int j = 0; j < 6; j++)
                EXPECT_NEAR(bodyNodeG(i,j), G(i,j), DYNAMICS_TOL);
    }
}

/* ********************************************************************************************* */
int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
/* ********************************************************************************************* */
