/*
 * Copyright (c) 2011, Georgia Tech Research Corporation
 * All rights reserved.
 *
 * Author(s): Jeongseok Lee <jslee02@gmail.com>,
 *            Tobias Kunz <tobias@gatech.edu>
 * Date: 05/11/2013
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

#include "dynamics/BodyNode.h"
#include "dynamics/Skeleton.h"

#include "collision/CollisionNode.h"
#include "collision/CollisionDetector.h"

namespace dart {
namespace collision {

CollisionDetector::CollisionDetector()
{
    mNumMaxContacts = 100;
}

CollisionDetector::~CollisionDetector()
{
    for(int i = 0; i < mCollisionNodes.size(); i++)
        delete mCollisionNodes[i];
}

void CollisionDetector::addCollisionSkeletonNode(dynamics::BodyNode* _bodyNode,
                                                 bool _recursive)
{
    CollisionNode* collNode = createCollisionNode(_bodyNode);
    collNode->setIndex(mCollisionNodes.size());
    mCollisionNodes.push_back(collNode);
    mBodyCollisionMap[_bodyNode] = collNode;
    mCollidablePairs.push_back(std::vector<bool>(mCollisionNodes.size() - 1, true));

    if(_recursive)
    {
        for (int i = 0; i < _bodyNode->getNumChildJoints(); i++)
            addCollisionSkeletonNode(_bodyNode->getChildBodyNode(i), true);
    }
}

bool CollisionDetector::checkCollision(dynamics::BodyNode* _node1,
                                       dynamics::BodyNode* _node2,
                                       bool _calculateContactPoints)
{
    return checkCollision(getCollisionNode(_node1),
                          getCollisionNode(_node2),
                          _calculateContactPoints);
}

unsigned int CollisionDetector::getNumContacts()
{
    return mContacts.size();
}

Contact&CollisionDetector::getContact(int _idx)
{
    return mContacts[_idx];
}

void CollisionDetector::clearAllContacts()
{
    mContacts.clear();
}

int CollisionDetector::getNumMaxContacts() const
{
    return mNumMaxContacts;
}

void CollisionDetector::setNumMaxContacs(int _num)
{
    mNumMaxContacts = _num;
}

void CollisionDetector::enablePair(dynamics::BodyNode* _node1,
                                   dynamics::BodyNode* _node2)
{
    CollisionNode* collisionNode1 = getCollisionNode(_node1);
    CollisionNode* collisionNode2 = getCollisionNode(_node2);
    if(collisionNode1 && collisionNode2)
        getPairCollidable(collisionNode1, collisionNode2) = true;
}

void CollisionDetector::disablePair(dynamics::BodyNode* _node1,
                                    dynamics::BodyNode* _node2)
{
    CollisionNode* collisionNode1 = getCollisionNode(_node1);
    CollisionNode* collisionNode2 = getCollisionNode(_node2);
    if(collisionNode1 && collisionNode2)
        getPairCollidable(collisionNode1, collisionNode2) = false;
}

bool CollisionDetector::isCollidable(const CollisionNode* _node1,
                                     const CollisionNode* _node2)
{
    return getPairCollidable(_node1, _node2)
        && _node1->getBodyNode()->isCollidable()
        && _node2->getBodyNode()->isCollidable()
        && (_node1->getBodyNode()->getSkeleton() != _node2->getBodyNode()->getSkeleton()
            || _node1->getBodyNode()->getSkeleton()->getSelfCollidable());
}

std::vector<bool>::reference CollisionDetector::getPairCollidable(
        const CollisionNode* _node1, const CollisionNode* _node2)
{
    assert(_node1 != _node2);
    int index1 = _node1->getIndex();
    int index2 = _node2->getIndex();
    if(index1 < index2)
        std::swap(index1, index2);
    return mCollidablePairs[index1][index2];
}

CollisionNode* CollisionDetector::getCollisionNode(
        const dynamics::BodyNode *_bodyNode)
{
    if(mBodyCollisionMap.find(_bodyNode) != mBodyCollisionMap.end())
        return mBodyCollisionMap[_bodyNode];
    else
        return NULL;
}

} // namespace collision
} // namespace dart
