/***************************************************************************
 *                                                                         *
 *  DynELA Finite Element Code v 3.0                                       *
 *  By Olivier PANTALE                                                     *
 *                                                                         *
 *  (c) Copyright 1997-2019                                                *
 *                                                                         *
 **************************************************************************/

/*!
  \file ElementAxi.C
  \brief Definition file for the ElementAxi class

  This file is the definition file for the ElementAxi class.

  \ingroup dnlElements
  \author &copy; Olivier PANTALE
  \date 1997-2019
*/

#include <ElementAxi.h>
#include <Node.h>
#include <NodalField.h>

/* #include <IntegrationPoint.h>
#include <Material.h>
#include <DynELA.h>
#include <io_Structure.h>
// #include <Physic.h>
#include <Model.h>
 */
//-----------------------------------------------------------------------------
ElementAxi::ElementAxi(long elementNumber) : ElementPlane(elementNumber)
//-----------------------------------------------------------------------------
{
}

//-----------------------------------------------------------------------------
ElementAxi::ElementAxi(const ElementAxi &element) : ElementPlane(element)
//-----------------------------------------------------------------------------
{
  std::cout << "recopie d'un ElementAxi\n";
}

//-----------------------------------------------------------------------------
ElementAxi::~ElementAxi()
//-----------------------------------------------------------------------------
{
}

//-----------------------------------------------------------------------------
double ElementAxi::getRadiusAtIntegrationPoint()
//-----------------------------------------------------------------------------
{
  // initialisation a zero de v
  double currentRadius = 0.0;

  // calcul de v courant
  for (short nodeId = 0; nodeId < nodes.getSize(); nodeId++)
  {
    currentRadius += _integrationPoint->integrationPointData->shapeFunction(nodeId) * nodes(nodeId)->coordinates(0);
  }

  return currentRadius;
}

//-----------------------------------------------------------------------------
void ElementAxi::computeDeformationGradient(Tensor2 &F, short time)
//-----------------------------------------------------------------------------
{
  NodalField *field;
  double Vr = 0.0;

  // initialisation a zero de F
  F.setToUnity();

  // calcul de F
  for (short nodeId = 0; nodeId < nodes.getSize(); nodeId++)
  {
    field = nodes(nodeId)->getNodalField(time);
    F(0, 0) += _integrationPoint->dShapeFunction(nodeId, 0) * field->displacementInc(0);
    F(0, 1) += _integrationPoint->dShapeFunction(nodeId, 1) * field->displacementInc(0);
    F(1, 0) += _integrationPoint->dShapeFunction(nodeId, 0) * field->displacementInc(1);
    F(1, 1) += _integrationPoint->dShapeFunction(nodeId, 1) * field->displacementInc(1);
    Vr += _integrationPoint->integrationPointData->shapeFunction(nodeId) * field->displacementInc(0);
  }

  // calcul F terme axisymetrique
  F(2, 2) += Vr / getRadiusAtIntegrationPoint();
}

//-----------------------------------------------------------------------------
bool ElementAxi::checkLevel2()
//-----------------------------------------------------------------------------
{
  // check for a negative value of x coordinate
  for (short nodeId = 0; nodeId < nodes.getSize(); nodeId++)
  {
    if (nodes(nodeId)->coordinates(0) < 0.)
    {
      if (nodes(nodeId)->coordinates(0) > -1e-8)
      {
        warning("Negative r value in an axisymetric element",
                "Element %d has an r value of %10.3E\nThis has been changed to 0.00\n",
                number, nodes(nodeId)->coordinates(0));
        nodes(nodeId)->coordinates(0) = 0.;
      }
      else
      {
        std::cerr << "Error in element " << number << "\nr coordinate (" << nodes(nodeId)->coordinates(0) << ") of the node " << nodes(nodeId)->number << " is negative\n";
        exit(-1);
      }
    }
  }
  return true;
}

//-----------------------------------------------------------------------------
void ElementAxi::getdV_atIntPoint(Tensor2 &dv, short time)
//-----------------------------------------------------------------------------
{
  NodalField *field;
  Vec3D v;

  // initialisation a zero de dv
  dv = 0.;

  // calcul de dv
  for (long nodeId = 0; nodeId < getNumberOfNodes(); nodeId++)
  {
    field = nodes(nodeId)->getNodalField(time);
    dv(0, 0) += _integrationPoint->dShapeFunction(nodeId, 0) * field->speed(0);
    dv(0, 1) += _integrationPoint->dShapeFunction(nodeId, 1) * field->speed(0);
    dv(1, 0) += _integrationPoint->dShapeFunction(nodeId, 0) * field->speed(1);
    dv(1, 1) += _integrationPoint->dShapeFunction(nodeId, 1) * field->speed(1);
  }

  // calcul du terme axisymetrique
  getV_atIntPoint(v, time);
  dv(2, 2) = v(0) / getRadiusAtIntegrationPoint();
}

/*


//-----------------------------------------------------------------------------
void ElementAxi::getdU_atIntPoint (Tensor2 & du, short time)
//-----------------------------------------------------------------------------
{
  NodalField *field;
  long k;
  double v;
  double R;

  // initialisation a zero de du
  du = 0.;
  v = 0.;

  // calcul de du
  for (k = 0; k < getNumberOfNodes(); k++)
    {
      field = nodes (k)->getNodalField (time);
      du (0, 0) += _integrationPoint->dShapeFunction (k, 0) * field->displacementInc (0);
      du (0, 1) += _integrationPoint->dShapeFunction (k, 1) * field->displacementInc (0);
      du (1, 0) += _integrationPoint->dShapeFunction (k, 0) * field->displacementInc (1);
      du (1, 1) += _integrationPoint->dShapeFunction (k, 1) * field->displacementInc (1);
       v += _integrationPoint->integrationPointData->shapeFunction (k) * field->displacementInc (0);
    }

  // calcul du terme axisymetrique
  R=getRadiusAtIntegrationPoint();
  du (2, 2) = v / R;
}


*/