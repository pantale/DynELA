/***************************************************************************
 *                                                                         *
 *  DynELA Finite Element Code v 3.0                                       *
 *  By Olivier PANTALE                                                     *
 *                                                                         *
 *  (c) Copyright 1997-2019                                                *
 *                                                                         *
 **************************************************************************/

/*!
  \file NodeSet.h
  \brief Declaration file for the NodeSet class

  This file is the declaration file for the NodeSet class.

  \ingroup dnlFEM
  \author &copy; Olivier PANTALE
  \date 1997-2019
*/

#ifndef __dnlBC_BoundaryAcceleration_h__
#define __dnlBC_BoundaryAcceleration_h__

#include <Boundary.h>
/* #include <Vec3D.h>
class Node; */

class BoundaryAcceleration : public Boundary
{

private:
  Vec3D _acceleration;

public:
  // constructeurs
  BoundaryAcceleration(char *newName = NULL);
  BoundaryAcceleration(const Vec3D &newAcceleration);
  BoundaryAcceleration(const BoundaryAcceleration &X);
  ~BoundaryAcceleration();

  Vec3D getValue();
  void setValue(const Vec3D &newAcceleration);
  void setValue(double accX, double accY, double accZ);
  void applyConstantOnNewFields(Node *node, double currentTime, double timeStep);
  void applyConstantOnCurrentFields(Node *node, double currentTime, double timeStep);
  void applyInitialOnCurrentFields(Node *node, double currentTime, double timeStep);

  // fonctions membres
  long getType()
  {
    return Boundary::Acceleration;
  }
};

#endif
