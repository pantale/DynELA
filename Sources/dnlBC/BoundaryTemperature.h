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

#ifndef __dnlBC_BoundaryTemperature_h__
#define __dnlBC_BoundaryTemperature_h__

#include <Boundary.h>
/* #include <Vec3D.h>
class Node; */

class BoundaryTemperature : public Boundary
{

private:
  double _temperature;

public:
  // constructeurs
  BoundaryTemperature(char *newName = NULL);
  BoundaryTemperature(double newTemperaure);
  BoundaryTemperature(const BoundaryTemperature &X);
  ~BoundaryTemperature();

  // fonctions membres
  long getType()
  {
    return Boundary::Temperature;
  }
  void applyConstantOnNewFields(Node *node, double currentTime, double timeStep);
  void applyConstantOnCurrentFields(Node *node, double currentTime, double timeStep);
  void applyInitialOnCurrentFields(Node *node, double currentTime, double timeStep);
  double getValue();
  void setValue(double newTemperaure);
};
#endif