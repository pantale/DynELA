/***************************************************************************
 *                                                                         *
 *  DynELA Finite Element Code v 3.0                                       *
 *  By Olivier PANTALE                                                     *
 *                                                                         *
 *  (c) Copyright 1997-2019                                                *
 *                                                                         *
 **************************************************************************/

/*!
  \file MatrixDiag.C
  \brief Declaration file for the Matrix class

  This file is the declaration file for the Matrix class. A Matrix class is a Matrix with the following form:
  \f[ M=\left[\begin{array}{cccc}
  M_{11}&M_{12}&...&M_{1n}\\
  M_{21}&M_{22}&...&M_{2n}\\
  ...\\
  M_{n1}&M_{n2}&...&M_{nn}\\
  \end{array}\right] \f]

  \ingroup dnlMaths
  \author &copy; Olivier PANTALE
  \date 1997-2019
*/

#include "NumpyInterface.h"
#include "MatrixDiag.h"

//!constructeur de la classe MatrixDiag
/*!
  Cette m�thode construit une matrice de lignes/colonnes elements. Par d�faut, le contenu de la matrice est mis � z�rho
  \param numberOfTerms nombre de lignes
  \author Olivier PANTALE
  \version 0.9.4
*/
//-----------------------------------------------------------------------------
MatrixDiag::MatrixDiag(const long numberOfTerms, double value)
//-----------------------------------------------------------------------------
{
  // allocation memoire;
  allocate(numberOfTerms);

  // initialisation
  setToValue(value);
}

//!constructeur par recopie d'une matrice
/*!
  Ce constructeur recopie les valeurs contenues dans une matrice. Selon la valeur du flag \ref MEM_funct, la copie est faite soit terme � terme (flag non d�fini) ou par appel � memcopy() (flag d�fini).
  \author Olivier PANTALE
  \version 0.9.4
*/
//-----------------------------------------------------------------------------
MatrixDiag::MatrixDiag(const MatrixDiag &mat)
//-----------------------------------------------------------------------------
{
  allocate(mat._rows);

  memcpy(_data, mat._data, _rows * sizeof(double));
}

//!destructeur de la classe MatrixDiag
/*!
  \author Olivier PANTALE
  \version 0.9.4
*/
//-----------------------------------------------------------------------------
MatrixDiag::~MatrixDiag()
//-----------------------------------------------------------------------------
{
  desallocate();
}

//!Maximum _data in a MatrixDiag
/*!
  This method returns the maximum _data of a MatrixDiag
*/
//-----------------------------------------------------------------------------
double MatrixDiag::maxValue()
//-----------------------------------------------------------------------------
{
  double val = _data[0];

  for (long i = 1; i < _rows; i++)
    if (_data[i] > val)
      val = _data[i];

  return val;
}

//!Minimum _data in a MatrixDiag
/*!
  This method returns the minimum _data of a MatrixDiag
*/
//-----------------------------------------------------------------------------
double MatrixDiag::minValue()
//-----------------------------------------------------------------------------
{
  double val = _data[0];

  for (long i = 1; i < _rows; i++)
    if (_data[i] < val)
      val = _data[i];

  return val;
}

//!Absolute maximum _data in a MatrixDiag
/*!
  This method returns the absolute maximum _data of a MatrixDiag
*/
//-----------------------------------------------------------------------------
double MatrixDiag::maxAbsoluteValue()
//-----------------------------------------------------------------------------
{
  double val = abs(_data[0]);

  for (long i = 1; i < _rows; i++)
    if (abs(_data[i]) > val)
      val = abs(_data[i]);

  return val;
}

//!Absolute minimum _data in a MatrixDiag
/*!
  This method returns the absolute minimum _data of a MatrixDiag
*/
//-----------------------------------------------------------------------------
double MatrixDiag::minAbsoluteValue()
//-----------------------------------------------------------------------------
{
  double val = abs(_data[0]);

  for (long i = 1; i < _rows; i++)
    if (abs(_data[i]) < val)
      val = abs(_data[i]);

  return val;
}

//-----------------------------------------------------------------------------
void MatrixDiag::allocate(const long numberOfTerms)
//-----------------------------------------------------------------------------
{
  _rows = numberOfTerms;
  _cols = numberOfTerms;

  // allocation dynamique de memoire
  _data = new double[_rows];
}

//-----------------------------------------------------------------------------
void MatrixDiag::desallocate()
//-----------------------------------------------------------------------------
{
  _rows = 0;
  _cols = 0;

  delete[] _data;
}

//!redimensionne la matrice
/*!
  Cette m�thode est utilis�e pour sp�cifier une nouvelle dimension de matrice de celle donn�e lors de l'initialisation par le constructeur
  \param newSize nombre de lignes
  \author Olivier PANTALE
  \version 0.9.4
*/
//-----------------------------------------------------------------------------
void MatrixDiag::redim(const long newSize)
//-----------------------------------------------------------------------------
{
  if (newSize == _rows)
  {
    setToValue(0.0);
    return;
  }
  desallocate();
  allocate(newSize);

  // initialisation
  setToValue(0.0);
}

//!affichage du contenu d'une matrice
/*!
  Cette m�thode est une surd�finition de << pour les flux de sortie, son utilisation est donn�e comme suit
  
  Exemple
  \code
  MatrixDiag t;
  cout << t << endl;
  \endcode
  \param os flux de sortie
  \author Olivier PANTALE
  \version 0.9.4
*/
//-----------------------------------------------------------------------------
std::ostream &operator<<(std::ostream &os, const MatrixDiag &mat)
//-----------------------------------------------------------------------------
{
  mat.print(os);
  return os;
}

//!affichage du contenu d'une matrice
/*!
  Cette methode permet d'afficher le contenu d'une matrice sur la sortie std::ostream
  \param os flux de sortie
  \author Olivier PANTALE
  \version 0.9.4
*/
//-----------------------------------------------------------------------------
void MatrixDiag::print(std::ostream &os) const
//-----------------------------------------------------------------------------
{
  long i, j;

  os << "diagonal matrix " << _rows << "x" << _cols << " ={{";
  for (i = 0; i < _rows; i++)
  {
    for (j = 0; j < _cols; j++)
    {
      if (j != 0)
        os << ",";
      os << (i == j ? _data[i] : 0.0);
    }
    if (i != _rows - 1)
      os << "},{";
  }
  os << "}}";
}

//!affectation d'�galit�
/*! 
  Cette m�thode est une surd�finition de la methode d'�galit� permettant d'�crire simplement le remplissage des valeurs d'une matrice par un scalaire
  
  Exemple :
  \code
  MatrixDiag t1;
  t1=setToValue(1.); // affecte 1 � toutes les composantes de la matrice
  \endcode
  \author Olivier PANTALE
  \version 0.9.4
*/
//-----------------------------------------------------------------------------
void MatrixDiag::setToValue(double val)
//-----------------------------------------------------------------------------
{
  long i;
  for (i = 0; i < _rows; i++)
    _data[i] = val;
}

//!renvoie une matrice identit� � partir d'une matrice quelconque
/*!
  Cette m�thode prend en argument une matrice quelconque et renvoie une matrice identit�. Par d�finition une matrice diagonale identit� est enti�rement remplie de 1.
  
  Exemple :
  \code
  MatrixDiag t1;
  t1.setToUnity(); // renvoie identit�
  \endcode
  \warning Cette m�thode modifie son argument
  \author Olivier PANTALE
  \version 0.9.4
*/
//-----------------------------------------------------------------------------
void MatrixDiag::setToUnity()
//-----------------------------------------------------------------------------
{
  long i;
  for (i = 0; i < _rows; i++)
    _data[i] = 1.0;
}

//!affectation d'�galit�
/*! 
  Cette m�thode est une surd�finition de la methode d'�galit� permettant d'�crire simplement le remplissage des valeurs d'une matrice par un scalaire
  
  Exemple :
  \code
  MatrixDiag t1;
  t1=1.; // affecte 1 � toutes les composantes de la matrice
  \endcode
  \author Olivier PANTALE
  \version 0.9.4
*/
//-----------------------------------------------------------------------------
MatrixDiag &MatrixDiag::operator=(const double &val)
//-----------------------------------------------------------------------------
{
  setToValue(val);
  return *this;
}

//!affectation d'�galit�
/*! 
  Cette m�thode est une surd�finition de la methode d'�galit� permettant d'�crire simplement l'affectation sous la forme donn�e en exemple
  
  Exemple :
  \code
  MatrixDiag t1,t2;
  t1=t2; // egalit� de deux matrices
  \endcode
  \author Olivier PANTALE
  \version 0.9.4
*/
//-----------------------------------------------------------------------------
MatrixDiag &MatrixDiag::operator=(const MatrixDiag &mat)
//-----------------------------------------------------------------------------
{
  // redimension de la matrice resultat
  redim(mat._rows);

  // recopie des valeurs
  memcpy(_data, mat._data, _rows * sizeof(double));

  return *this;
}

//!addition de deux matrices
/*!
  Cette methode permet de surd�finir l'op�ration d'addition des matrices et d'�crire simplement la somme de deux matrices sous la forme donn�e en exemple
  
  Exemple :
  \code
  MatrixDiag t1,t2,t3;
  t3=t1+t2; // somme de deux matrices
  \endcode
  \author Olivier PANTALE
  \version 0.9.4
*/
//-----------------------------------------------------------------------------
MatrixDiag MatrixDiag::operator+(const MatrixDiag &mat) const
//-----------------------------------------------------------------------------
{
  // test si egalite de dimensions
  if (_rows != mat._rows)
  {
    fatalError("MatrixDiag::operator +",
               "matrix sizes incompatible\n"
               "You're about to add a [%d,%d] and a [%d,%d] matrix",
               _rows,
               _cols, mat._rows, mat._cols);
  }

  // creation d'une nouvelle matrice
  MatrixDiag resu(mat._rows, mat._cols);

  // calcul de la somme
  for (long i = 0; i < _rows; i++)
    resu._data[i] = _data[i] + mat._data[i];

  // renvoi de l'objet
  return resu;
}

//!soustraction de deux matrices
/*!
  Cette methode permet de surd�finir l'op�ration de soustraction des matrices et d'�crire simplement la soustraction de deux matrices sous la forme donn�e en exemple
  
  Exemple :
  \code
  MatrixDiag t1,t2,t3;
  t3=t1-t2; // soustraction de deux matrices
  \endcode
  \author Olivier PANTALE
  \version 0.9.4
*/
//-----------------------------------------------------------------------------
MatrixDiag MatrixDiag::operator-(const MatrixDiag &mat) const
//-----------------------------------------------------------------------------
{
  if (_rows != mat._rows)
  {
    fatalError("MatrixDiag::operator -",
               "matrix sizes incompatible\n"
               "You're about to substract [%d,%d] and [%d,%d] matrix",
               _rows,
               _cols, mat._rows, mat._cols);
  }

  // creation d'une nouvelle matrice
  MatrixDiag resu(_rows, _cols);

  // calcul de la difference
  for (long i = 0; i < _rows; i++)
    resu._data[i] = _data[i] - mat._data[i];

  // renvoi de l'objet
  return resu;
}

//-----------------------------------------------------------------------------
MatrixDiag MatrixDiag::operator-() const
//-----------------------------------------------------------------------------
{
  // creation d'une nouvelle matrice
  MatrixDiag resu(_rows, _cols);

  // calcul de la difference
  for (long i = 0; i < _rows; i++)
    resu._data[i] = -_data[i];

  // renvoi de l'objet
  return resu;
}

//!addition de deux matrices
/*!
  Cette methode permet de surd�finir l'op�ration d'addition des matrices et d'�crire simplement la somme de deux matrices sous la forme donn�e en exemple
  
  Exemple :
  \code
  MatrixDiag t1,t2;
  t2+=t1; // somme de deux matrices
  \endcode
  \author Olivier PANTALE
  \version 0.9.4
*/
//-----------------------------------------------------------------------------
void MatrixDiag::operator+=(const MatrixDiag &mat)
//-----------------------------------------------------------------------------
{
  // test si egalite de dimensions
  if (_rows != mat._rows)
  {
    fatalError("MatrixDiag::operator +=",
               "matrix sizes incompatible\n"
               "You're about to add a [%d,%d] and a [%d,%d] matrix",
               _rows,
               _cols, mat._rows, mat._cols);
  }

  // calcul de la somme
  for (long i = 0; i < _rows; i++)
    _data[i] += mat._data[i];
}

//!soustraction de deux matrices
/*!
  Cette methode permet de surd�finir l'op�ration de soustraction des matrices et d'�crire simplement la soustraction de deux matrices sous la forme donn�e en exemple
  
  Exemple :
  \code
  MatrixDiag t1,t2;
  t2-=t1; // soustraction de deux matrices
  \endcode
  \author Olivier PANTALE
  \version 0.9.4
*/
//-----------------------------------------------------------------------------
void MatrixDiag::operator-=(const MatrixDiag &mat)
//-----------------------------------------------------------------------------
{
  if (_rows != mat._rows)
  {
    fatalError("MatrixDiag::operator -=",
               "matrix sizes incompatible\n"
               "You're about to substract [%d,%d] and [%d,%d] matrix",
               _rows,
               _cols, mat._rows, mat._cols);
  }

  // calcul de la difference
  for (long i = 0; i < _rows; i++)
    _data[i] -= mat._data[i];
}

//!multiplication d'une matrice par un scalaire
/*!
  Cette methode permet de surd�finir l'op�ration de multiplication des matrices et d'�crire simplement la multiplication d'une matrice par un scalaire sous la forme donn�e en exemple
  
  Exemple :
  \code
  MatrixDiag t1,t2;
  double l;
  t2=t1*l; // multiplication par un scalaire
  \endcode
  \author Olivier PANTALE
  \version 0.9.4
*/
//-----------------------------------------------------------------------------
MatrixDiag MatrixDiag::operator*(const double &lambda) const
//-----------------------------------------------------------------------------
{
  MatrixDiag resu(_rows, _cols);

  for (long i = 0; i < _rows; i++)
    resu._data[i] = lambda * _data[i];
  return resu;
}

//!division d'une matrice par un scalaire
/*!
  Cette methode permet de surd�finir l'op�ration de division des matrices et d'�crire simplement la division d'une matrice par un scalaire sous la forme donn�e en exemple
  
  Exemple :
  \code
  MatrixDiag t1;
  double l;
  t1/=l; // division par un scalaire
  \endcode
  \author Olivier PANTALE
  \version 0.9.4
*/
//-----------------------------------------------------------------------------
MatrixDiag MatrixDiag::operator/(const double &lambda) const
//-----------------------------------------------------------------------------
{
  MatrixDiag resu(_rows, _cols);

  for (long i = 0; i < _rows; i++)
    resu._data[i] = _data[i] / lambda;
  return resu;
}

//!multiplication d'une matrice par un scalaire
/*!
  Cette methode permet de surd�finir l'op�ration de multiplication des matrices et d'�crire simplement la multiplication d'une matrice par un scalaire sous la forme donn�e en exemple. Elle est identique � la forme pr�c�dente (et commutative).
  
  Exemple :
  \code
  MatrixDiag t1,t2;
  double l;
  t2=l*t1; // multiplication par un scalaire
  \endcode
  \author Olivier PANTALE
  \version 0.9.4
*/
//-----------------------------------------------------------------------------
MatrixDiag operator*(const double &lambda, const MatrixDiag &mat)
//-----------------------------------------------------------------------------
{
  MatrixDiag resu(mat._rows, mat._cols);

  for (long i = 0; i < mat._rows; i++)
    resu._data[i] = lambda * mat._data[i];
  return resu;
}

//!multiplication de deux matrices
/*!
  Cette methode permet de surd�finir l'op�ration de multiplication des matrices et d'�crire simplement la multiplication de deux matrice sous la forme donn�e en exemple. Cette op�ration correspond � la notion de produit contract� de deux matrices.
  
  Exemple :
  \code
  MatrixDiag t1,t2,t3;
  t3=t1*t2; // produit contract�
  \endcode
  \author Olivier PANTALE
  \version 0.9.4
*/
//-----------------------------------------------------------------------------
MatrixDiag MatrixDiag::operator*(const MatrixDiag &mat) const
//-----------------------------------------------------------------------------
{
  return singleProduct(mat);
}

//-----------------------------------------------------------------------------
MatrixDiag MatrixDiag::singleProduct(const MatrixDiag &mat) const
//-----------------------------------------------------------------------------
{
  if (_cols != mat._rows)
  {
    fatalError("MatrixDiag::operator *",
               "matrix sizes incompatible\n"
               "You're about to multiply a [%d,%d] and a [%d,%d] matrix",
               _rows, _cols, mat._rows, mat._cols);
  }

  MatrixDiag resu(_rows, mat._cols);

  for (long i = 0; i < _rows; i++)
    resu._data[i] = _data[i] * mat._data[i];

  return resu;
}

//!multiplication d'une matrice par un vecteur
/*!
  Cette m�thode calcule le produit d'une matrice A de taille N-x-N par un vecteur x de taille N. ceci g�n�re un vecteur y de taille N.
  Cette m�thode retourne un vecteur
  Exemple :
  \code
  MatrixDiag t1;
  Vector v1,v2;
  v2=t1*v1; // produit
  \endcode
  \param vec vecteur du second membre
  \return vecteur r�sultant de l'op�ration de multiplication
  \author Olivier PANTALE
  \version 0.9.4
*/
//-----------------------------------------------------------------------------
Vector MatrixDiag::operator*(const Vector &vec) const
//-----------------------------------------------------------------------------
{
  if (_cols != vec.getSize())
  {
    fatalError("MatrixDiag::operator *",
               "matrix and vector sizes incompatible\n"
               "You're about to multiply a [%d,%d] matrix and a [%d] vector",
               _rows, _cols, vec.getSize());
  }

  Vector resu(_rows);
  double *Res = resu._data;
  double *Mat = _data;
  double *Vec = vec._data;

  for (long i = 0; i < _rows; i++)
    *Res++ = *Mat++ * *Vec++;

  return resu;
}

//-----------------------------------------------------------------------------
void MatrixDiag::productBy(Vector &vec) const
//-----------------------------------------------------------------------------
{
  if (_cols != vec.getSize())
  {
    fatalError("MatrixDiag::operator *",
               "matrix and vector sizes incompatible\n"
               "You're about to multiply a [%d,%d] matrix and a [%d] vector",
               _rows, _cols, vec.getSize());
  }

  double *Vec = vec._data;
  double *Mat = _data;
  for (long i = _rows - 1; i >= 0; i--)
    *Vec++ *= *Mat++;
}

//-----------------------------------------------------------------------------
void MatrixDiag::divideBy(Vector &vec) const
//-----------------------------------------------------------------------------
{
  if (_cols != vec.getSize())
  {
    fatalError("MatrixDiag::operator *",
               "matrix and vector sizes incompatible\n"
               "You're about to multiply a [%d,%d] matrix and a [%d] vector",
               _rows, _cols, vec.getSize());
  }

  double *Vec = vec._data;
  double *Mat = _data;
  for (long i = _rows - 1; i >= 0; i--)
    *Vec++ /= *Mat++;
}

//!calcule la trace d'une matrice
/*!
  Cette m�thode calcule la trace d'une matrice carr�e
  \return valeur de la trace de la matrice
  \author Olivier PANTALE
  \version 0.9.4
*/
//-----------------------------------------------------------------------------
double MatrixDiag::getTrace()
//-----------------------------------------------------------------------------
{
  double trace = 0.;
  for (long i = 0; i < _rows; i++)
    trace += _data[i];
  return trace;
}

//!transpos�e d'une matrice
/*!
  Cette m�thode renvoie la transpos�e d'une matrice
  \return transpos�e de la matrice
  \author Olivier PANTALE
  \version 0.9.4
*/
//-----------------------------------------------------------------------------
MatrixDiag MatrixDiag::getTranspose()
//-----------------------------------------------------------------------------
{
  return *this;
}

//!r�solution d'un syst�me lin�aire
/*!
  Cette m�thode calcule la solution du syst�me lin�aire  \f[ A x = b \f] avec A matrice N-x-N et x et y vecteurs de taille N.

  \param x vecteur du second membre
  \return vecteur solution du syst�me lin�aire
  \author Olivier PANTALE
  \version 0.9.6
*/
//-----------------------------------------------------------------------------
Vector MatrixDiag::getSolve(Vector &vec)
//-----------------------------------------------------------------------------
{
  Vector resu(_rows);

  if (_rows != vec.getSize())
  {
    fatalError("MatrixDiag::Solve",
               "matrix and vector sizes incompatible\n"
               "You're about to Solve a linear system with a [%d,%d]"
               " matrix and a [%d] vector",
               _rows, _cols, vec.getSize());
  }

  for (long component = 0; component < _rows; component++)
    resu(component) = vec(component) / _data[component];

  return resu;
}

//-----------------------------------------------------------------------------
void MatrixDiag::solve(Vector &vec)
//-----------------------------------------------------------------------------
{
  for (long component = 0; component < _rows; component++)
    vec(component) /= _data[component];
}

//-----------------------------------------------------------------------------
MatrixDiag MatrixDiag::getInverse() const
//-----------------------------------------------------------------------------
{
  MatrixDiag res(_rows, _rows);

  double *Res = res._data;
  double *Loc = _data;

  for (long i = _rows; i > 0; i--)
    *Res++ = 1.0 / (*Loc++);

  return res;
}

//!egalit� de deux matrices
/*!
  Cette m�thode teste l'�galit� de deux matrices
  \return true si les deux matrices sont identiques, false dans la cas contraire
  \author Olivier PANTALE
  \version 0.9.4
*/
//-----------------------------------------------------------------------------
bool MatrixDiag::operator==(const MatrixDiag &mat) const
//-----------------------------------------------------------------------------
{
  if ((_rows != mat._rows) && (_cols != mat._cols))
  {
    fatalError("MatrixDiag::operator ==",
               "The dimensions of the two matrix are'nt corresponding\n"
               "they are respectively a [%d,%d] and a [%d,%d] matrix",
               _rows, _cols, mat._rows, mat._cols);
  }

  for (long i = 0; i < _rows; i++)
    if (_data[i] != mat._data[i])
      return false;
  return true;
}

//!in�galit� de deux matrices
/*!
  Cette m�thode teste l'in�galit� de deux matrices
  \return true si les deux matrices sont differentes, false dans la cas contraire
  \author Olivier PANTALE
  \version 0.9.4
*/
//-----------------------------------------------------------------------------
bool MatrixDiag::operator!=(const MatrixDiag &mat) const
//-----------------------------------------------------------------------------
{
  return !(*this == mat);
}

//!sortie sur flux std::ofstream
/*!
  Cette m�thode permet d'�crire une matrice dans un fichier (notament) binaire
  
  Exemple :
  \code
  std::ofstream pfile("fichier");
  Matrix t;
  t.write(pfile);
  t.close();
  \endcode
  \author Olivier PANTALE
  \version 0.9.4
*/
//-----------------------------------------------------------------------------
void MatrixDiag::write(std::ofstream &ofs) const
//-----------------------------------------------------------------------------
{
  ofs.write((char *)&_rows, sizeof(long));
  ofs.write((char *)_data, _rows * sizeof(double));
}

//!lecture sur flux std::ifstream
/*!
  Cette m�thode permet de lire une matrice depuis un fichier (notament) binaire
  
  Exemple :
  \code
  std::ifstream pfile("fichier");
  Matrix t;
  t.read(pfile);
  \endcode
  \author Olivier PANTALE
  \version 0.9.4
*/
//-----------------------------------------------------------------------------
void MatrixDiag::read(std::ifstream &ifs)
//-----------------------------------------------------------------------------
{
  long rows;

  ifs.read((char *)&rows, sizeof(long));
  redim(rows);
  ifs.read((char *)_data, _rows * sizeof(double));
}

//!sortie sur flux std::ofstream
/*!
  Cette m�thode permet d'�crire une matrice dans un fichier (notament) binaire
  
  Exemple :
  \code
  std::ofstream pfile("fichier");
  Matrix t;
  pfile << t;
  \endcode
  \author Olivier PANTALE
  \version 0.9.4
*/
//-----------------------------------------------------------------------------
std::ofstream &operator<<(std::ofstream &os, const MatrixDiag &mat)
//-----------------------------------------------------------------------------
{
  mat.write(os);
  return os;
}

//!lecture sur flux std::ifstream
/*!
  Cette m�thode permet de lire une matrice depuis un fichier (notament) binaire
  
  Exemple :
  \code
  std::ifstream pfile("fichier");
  Matrix t;
  pfile >> t;
  \endcode
  \author Olivier PANTALE
  \version 0.9.4
*/
//-----------------------------------------------------------------------------
std::ifstream &operator>>(std::ifstream &is, MatrixDiag &mat)
//-----------------------------------------------------------------------------
{
  mat.read(is);
  return is;
}

//-----------------------------------------------------------------------------
long MatrixDiag::Memory() const
//-----------------------------------------------------------------------------
{
  return (0);
}

//!Saves the content of a Matrix into a NumPy file
/*!
  This method saves the content of a Matrix object into a NumPy file defined by its filename. If the flag initialize is true, the current file will be concatenated.

  Example
  \code
  Matrix t;
  t.numpyWrite("numpy.npy", true);
  \endcode
*/
//-----------------------------------------------------------------------------
void MatrixDiag::numpyWrite(std::string filename, bool initialize) const
//-----------------------------------------------------------------------------
{
  std::string mode = "a";
  if (initialize)
    mode = "w";
  NumpyInterface::npySave(filename, &_data[0], {_rows}, mode);
}

//!Saves the content of a MatrixDiag into a NumPyZ file
/*!
  This method saves the content of a vec3D object into a NumPyZ file defined by its filename. If the flag initialize is true, the current file will be concatenated.

  Example
  \code
  MatrixDiag t;
  t.numpyWriteZ("numpy.npz", true);
  \endcode
*/
//-----------------------------------------------------------------------------
void MatrixDiag::numpyWriteZ(std::string filename, std::string name, bool initialize) const
//-----------------------------------------------------------------------------
{
  std::string mode = "a";
  if (initialize)
    mode = "w";
  NumpyInterface::npzSave(filename, name, &_data[0], {_rows}, mode);
}

//!Read the content of a MatrixDiag from a NumPy file
/*!
  This method reads the content of a vec3D object from a NumPy file defined by its filename.

  Example
  \code
  MatrixDiag t;
  t.numpyRead("numpy.npy");
  \endcode
*/
//-----------------------------------------------------------------------------
void MatrixDiag::numpyRead(std::string filename)
//-----------------------------------------------------------------------------
{
  NumpyInterface::NumpyArray arr = NumpyInterface::npyLoad(filename);
  redim(arr.num_vals);

  if (arr.num_vals != _rows)
  {
    std::cout << "ERROR\n";
  }

  memcpy(_data, arr.data<double *>(), arr.num_vals * arr.word_size);
}

//!Read the content of a MatrixDiag from a NumPyZ file
/*!
  This method reads the content of a vec3D object from a NumPyZ file defined by its filename.

  Example
  \code
  MatrixDiag t;
  t.numpyReadZ("numpy.npz");
  \endcode
*/
//-----------------------------------------------------------------------------
void MatrixDiag::numpyReadZ(std::string filename, std::string name)
//-----------------------------------------------------------------------------
{
  NumpyInterface::NumpyArray arr = NumpyInterface::npzLoad(filename, name);
  redim(arr.num_vals);

  if (arr.num_vals != _rows)
  {
    std::cout << "ERROR\n";
  }

  memcpy(_data, arr.data<double *>(), arr.num_vals * arr.word_size);
}

//!Assemblage d'un vecteur dans un autre
/*!
  Cette methode effectue la phase d'assemblage d'ue vecteur dans un autre conformement e ce qui se fait classiquement en Elements Finis.
  
  \param M Vecteur elementaire e assembler dans le grand vecteur
  \param int tableau d'long correspondant au nombre de NOEUDS de l'element et contenant les Id des noeuds que l'on utilise
  \param numberOfDimensions nombre de dimensions du probleme
  \code
  MatrixDiag Ve;
  long numberOfDimensions=...; // nombre de dimensions du probleme
  long *ind=new long[loop_I]; // allocation memoire pour ind
  for (long I=0; I < loop_I; I++) ind[I]=pel->nodes (I)->Id; // affectation des indices
  K.gatherFrom(Ve, ind, numberOfDimensions); 
  delete [] ind;
  \endcode
  \author Olivier PANTALE
  \version 1.1.0
*/
//-----------------------------------------------------------------------------
void MatrixDiag::gatherFrom(const MatrixDiag &M, long *ind0, int numberOfDimensions)
//-----------------------------------------------------------------------------
{
  long loop_I = M._rows / numberOfDimensions;
  long *ind = new long[loop_I];

  // preparation
  long *pind = ind;
  long *pind0 = ind0;
  for (long I = loop_I; I > 0; I--)
    *pind++ = *pind0++ * numberOfDimensions;

  // boucle principale
  switch (numberOfDimensions)
  {
  case 1:
  {
    for (long I = loop_I - 1; I >= 0; I--)
    {
      _data[ind[I]] += M._data[I];
    }
  }
  break;
  case 2:
  {
    for (long I = loop_I - 1; I >= 0; I--)
    {
      double *gl = &_data[ind[I]];
      double *lo = &M._data[I * numberOfDimensions];
      *gl++ += *lo++;
      *gl += *lo;
    }
  }
  break;
  case 3:
  {
    for (long I = loop_I - 1; I >= 0; I--)
    {
      double *gl = &_data[ind[I]];
      double *lo = &M._data[I * numberOfDimensions];
      *gl++ += *lo++;
      *gl++ += *lo++;
      *gl += *lo;
    }
  }
  break;

    // cas general
  default:
  {
    for (long I = loop_I - 1; I >= 0; I--)
    {
      // boucle sur les ddl
      long i = I * numberOfDimensions;
      long globI = ind[I];
      for (long Ii = 0; Ii < numberOfDimensions; Ii++)
        (*this)(globI + Ii) += M(i + Ii);
    }
  }
  }
  delete[] ind;
}

//!Assemblage d'un vecteur dans un autre
/*!
  Cette methode effectue la phase d'assemblage d'ue vecteur dans un autre conformement e ce qui se fait classiquement en Elements Finis.
  
  \param M Vecteur elementaire e assembler dans le grand vecteur
  \param int tableau d'long correspondant au nombre de NOEUDS de l'element et contenant les Id des noeuds que l'on utilise
  \param numberOfDimensions nombre de dimensions du probleme
  \code
  MatrixDiag Ve;
  long numberOfDimensions=...; // nombre de dimensions du probleme
  long *ind=new long[loop_I]; // allocation memoire pour ind
  for (long I=0; I < loop_I; I++) ind[I]=pel->nodes (I)->Id; // affectation des indices
  K.scatterFrom(Ve, ind, numberOfDimensions); 
  delete [] ind;
  \endcode
  \author Olivier PANTALE
  \version 1.1.0
*/
//-----------------------------------------------------------------------------
void MatrixDiag::scatterFrom(const MatrixDiag &M, long *ind0, int numberOfDimensions)
//-----------------------------------------------------------------------------
{
  // long mr=_rows;
  long loop_I = _rows / numberOfDimensions;
  long *ind = new long[loop_I];

  // preparation
  long *pind = ind;
  long *pind0 = ind0;
  for (long I = loop_I; I > 0; I--)
    *pind++ = *pind0++ * numberOfDimensions;

  // boucle principale
  switch (numberOfDimensions)
  {
  case 1:
  {
    for (long I = loop_I - 1; I >= 0; I--)
    {
      _data[I] += M._data[ind[I]];
    }
  }
  break;
  case 2:
  {
    for (long I = loop_I - 1; I >= 0; I--)
    {
      double *lo = &M._data[ind[I]];
      double *gl = &_data[I * numberOfDimensions];
      *gl++ += *lo++;
      *gl += *lo;
    }
  }
  break;
  case 3:
  {
    for (long I = loop_I - 1; I >= 0; I--)
    {
      double *lo = &M._data[ind[I]];
      double *gl = &_data[I * numberOfDimensions];
      *gl++ += *lo++;
      *gl++ += *lo++;
      *gl += *lo;
    }
  }
  break;

    // cas general
  default:
  {
    // boucle sur les ddl
    for (long I = loop_I - 1; I >= 0; I--)
    {
      long i = I * numberOfDimensions;
      long globI = ind[I];
      for (long Ii = 0; Ii < numberOfDimensions; Ii++)
        (*this)(i + Ii) += M(globI + Ii);
    }
  }
  }
  delete[] ind;
}