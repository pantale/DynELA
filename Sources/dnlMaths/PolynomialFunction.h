/***************************************************************************
 *                                                                         *
 *  DynELA Finite Element Code v 3.0                                       *
 *  By Olivier PANTALE                                                     *
 *                                                                         *
 *  (c) Copyright 1997-2019                                                *
 *                                                                         *
 **************************************************************************/

/*!
  \file DiscreteFunction.h
  \brief Declaration file for the discrete function class

  This file is the declaration file for the discrete function class. A discrete function is a function with the following form: \f[ y=f(x) \f] defined from a set of points.
  Linear interpolation is used to obtain data between given points.
  \ingroup linearAlgebra
  \author &copy; Olivier PANTALE
  \since DynELA 1.0
  \date 1997-2019
*/

#ifndef __dnlMaths_PolynomialFunction_h__
#define __dnlMaths_PolynomialFunction_h__

#include <List.h>
#include <Function.h>

struct PolynomialFragment
{
  int factor;
  double value;
};

class PolynomialFunction : public Function
{
private:
  List<PolynomialFragment> fragment;

public:
public:
  PolynomialFunction(char *newName = NULL);
  ~PolynomialFunction();

  double getValue(double x);
  void set(long i, double val);
  double get(long i);
  double getSlope(double x);
  long getNumberOfFragments();
  double getFactor(long i);
  double getCoefficient(long i);
  void toGnuplot(String filename, double xmin, double xmax, double steps);
  void flush();
  String convertToDynELASourceFile();

#ifndef SWIG
  void print();
#endif
};

#endif
