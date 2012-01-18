//=======================================================================
// File:	ColladaMesh_Mesh.cxx
// Created:	Mon Sep 25 11:27:03 1995
// Author:	Philippe GIRODENGO
// Copyright:    Matra Datavision	

#include <ColladaMesh_Mesh.ixx>
#include <ColladaMesh_MeshDomain.hxx>
#include <Precision.hxx>

//=======================================================================
//function : ColladaMesh_Mesh
//design   : 
//warning  : 
//=======================================================================


 ColladaMesh_Mesh::ColladaMesh_Mesh()
: nbTriangles (0), nbVertices (0), xyzmax (-(Precision::Infinite()), -(Precision::Infinite()), -(Precision::Infinite())), xyzmin (Precision::Infinite(), Precision::Infinite(), Precision::Infinite())
{ }

//=======================================================================
//function : AddDomain
//design   : 
//warning  : 
//=======================================================================

void ColladaMesh_Mesh::AddDomain()
{
  Handle(ColladaMesh_MeshDomain) MD = new ColladaMesh_MeshDomain;
  domains.Append (MD);
}

//=======================================================================
//function : AddDomain
//design   : 
//warning  : 
//=======================================================================

void ColladaMesh_Mesh::AddDomain(const Standard_Real Deflection)
{
  Handle(ColladaMesh_MeshDomain) MD = new ColladaMesh_MeshDomain (Deflection);
  domains.Append (MD);
}

//=======================================================================
//function : AddTriangle
//design   : 
//warning  : 
//=======================================================================

Standard_Integer ColladaMesh_Mesh::AddTriangle(const Standard_Integer V1, const Standard_Integer V2, 
					   const Standard_Integer V3,
					   const Standard_Real n1x, const Standard_Real n1y, const Standard_Real n1z,
					   const Standard_Real n2x, const Standard_Real n2y, const Standard_Real n2z,
					   const Standard_Real n3x, const Standard_Real n3y, const Standard_Real n3z)
{
  nbTriangles++;
  return (domains.Last())->AddTriangle (V1, V2, V3, n1x,n1y,n1z, n2x,n2y,n2z, n3x,n3y,n3z);
}

//=======================================================================
//function : AddVertex
//design   : 
//warning  : 
//=======================================================================

Standard_Integer ColladaMesh_Mesh::AddVertex(const Standard_Real X, const Standard_Real Y, const Standard_Real Z)
{
  nbVertices++;
  if (X > xyzmax.X()) xyzmax.SetX (X);
  if (Y > xyzmax.Y()) xyzmax.SetY (Y);
  if (Z > xyzmax.Z()) xyzmax.SetZ (Z);
  if (X < xyzmin.X()) xyzmin.SetX (X);
  if (Y < xyzmin.Y()) xyzmin.SetY (Y);
  if (Z < xyzmin.Z()) xyzmin.SetZ (Z);
  
  return (domains.Last())->AddVertex (X, Y, Z);
}

//=======================================================================
//function : AddOnlyNewVertex
//design   : 
//warning  : 
//=======================================================================

Standard_Integer ColladaMesh_Mesh::AddOnlyNewVertex(const Standard_Real X, const Standard_Real Y, const Standard_Real Z)
{
  Standard_Boolean IsNew = Standard_True;
  Standard_Integer VIndex = (domains.Last())->AddOnlyNewVertex (X, Y, Z, IsNew); 
  if (IsNew) nbVertices++;
  return VIndex;
}

//=======================================================================
//function : Bounds
//design   : 
//warning  : 
//=======================================================================

void ColladaMesh_Mesh::Bounds(gp_XYZ& XYZmax, gp_XYZ& XYZmin) const 
{
  XYZmax = xyzmax;
  XYZmin = xyzmin;
}

//=======================================================================
//function : Clear
//design   : 
//warning  : 
//=======================================================================

void ColladaMesh_Mesh::Clear()
{
  nbTriangles = 0;
  nbVertices  = 0;
  xyzmax.SetCoord(-(Precision::Infinite()),-(Precision::Infinite()),-(Precision::Infinite()));
  xyzmin.SetCoord(Precision::Infinite(),Precision::Infinite(),Precision::Infinite()); 
  domains.Clear ();
}

//=======================================================================
//function : Deflection
//design   : 
//warning  : 
//=======================================================================

Standard_Real ColladaMesh_Mesh::Deflection(const Standard_Integer DomainIndex) const 
{return (domains.Value (DomainIndex))->Deflection ();}

//=======================================================================
//function : NbTriangles
//design   : 
//warning  : 
//=======================================================================

Standard_Integer ColladaMesh_Mesh::NbTriangles(const Standard_Integer DomainIndex) const 
{ return (domains.Value(DomainIndex))->NbTriangles ();}

//=======================================================================
//function : NbVertices
//design   : 
//warning  : 
//=======================================================================

Standard_Integer ColladaMesh_Mesh::NbVertices(const Standard_Integer DomainIndex) const 
{ return (domains.Value(DomainIndex))->NbVertices ();}

//=======================================================================
//function : Triangles
//design   : 
//warning  : 
//=======================================================================

const ColladaMesh_SequenceOfMeshTriangle& ColladaMesh_Mesh::Triangles(const Standard_Integer DomainIndex) const 
{ return (domains.Value (DomainIndex))->Triangles ();}

//=======================================================================
//function : Vertices
//design   : 
//warning  : 
//=======================================================================

const TColgp_SequenceOfXYZ& ColladaMesh_Mesh::Vertices(const Standard_Integer DomainIndex) const 
{ return (domains.Value (DomainIndex))->Vertices ();}

