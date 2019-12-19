/***************************************************************************
 *                                                                         *
 *  DynELA Finite Element Code v 3.0                                       *
 *  By Olivier PANTALE                                                     *
 *                                                                         *
 *  (c) Copyright 1997-2019                                                *
 *                                                                         *
 **************************************************************************/

/*!
\file ElementPlane.h
\brief Declaration file for the ElementPlane class

This file is the declaration file for the ElementPlane class.

\ingroup dnlElements
\author &copy; Olivier PANTALE
\date 1997-2019
*/

#ifndef __dnlElements_ElementPlane_h__
#define __dnlElements_ElementPlane_h__

#include <Element.h>

class ElementPlane : public Element
{

public:
  ElementPlane(long elementNumber = 1);
  ElementPlane(const ElementPlane &element);
  ~ElementPlane();

  void getShapeFunctionAtPoint(Vector &shapeFunctions, const Vec3D &point) const = 0;
  void getDerShapeFunctionAtPoint(Matrix &derShapeFunctions, const Vec3D &point) const = 0;
  double getCharacteristicLength() = 0;
  double getRadiusAtIntegrationPoint() = 0;
  bool computeJacobian();
  void getV_atIntPoint (Vec3D & v, short time);

  /*  
  void getU_atIntPoint (Vec3D & u, short time);
  long numberOfUnderIntegrationPoints () = 0;
  void computeElasticStiffnessMatrix (Matrix & K, bool under=true);
  double getVolume () = 0;
  // bool getUnderIntegrPointCoords (long, Vec3D & coords, double& weight) = 0;
  //void getIntgtoNodes (Vector & N, const Vec3D & point) const = 0;
  void computeGlob2Loc () = 0;
  void glob2Loc (const Vec3D & point, Vec3D & local) = 0; */
};

#endif