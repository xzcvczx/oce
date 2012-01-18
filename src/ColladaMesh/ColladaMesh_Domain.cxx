//=======================================================================
// File:	ColladaMesh_MeshDomain.cxx
// Created:	Mon Sep 25 11:24:02 1995
// Author:	Philippe GIRODENGO
// Copyright:    Matra Datavision	

#include <ColladaMesh_MeshDomain.ixx>
#include <ColladaMesh_MeshTriangle.hxx>
#include <Precision.hxx>
#include <gp_XYZ.hxx>
#include <gp_Vec.hxx>

//=======================================================================
//function : ColladaMesh_MeshDomain
//design   : 
//warning  : 
//=======================================================================

ColladaMesh_MeshDomain::ColladaMesh_MeshDomain() : deflection (Precision::Confusion ()), nbVertices (0), nbTriangles (0) 
{ 
}


//=======================================================================
//function : ColladaMesh_MeshDomain
//design   : 
//warning  : 
//=======================================================================

ColladaMesh_MeshDomain::ColladaMesh_MeshDomain(const Standard_Real Deflection)
     : deflection (Deflection), nbVertices (0), nbTriangles (0) { }


//=======================================================================
//function : AddTriangle
//design   : 
//warning  : 
//=======================================================================

     Standard_Integer ColladaMesh_MeshDomain::AddTriangle(const Standard_Integer V1, 
						      const Standard_Integer V2, const Standard_Integer V3, 
						      const Standard_Real n1x, const Standard_Real n1y, const Standard_Real n1z,
						      const Standard_Real n2x, const Standard_Real n2y, const Standard_Real n2z,
						      const Standard_Real n3x, const Standard_Real n3y, const Standard_Real n3z)
{
  const Handle (ColladaMesh_MeshTriangle) tri = new ColladaMesh_MeshTriangle (V1, V2, V3, n1x, n1y, n1z, n2x, n2y, n2z, n3x, n3y, n3z);
  trianglesVertex.Append (tri);
  nbTriangles++;
  return nbTriangles;
}

//=======================================================================
//function : AddVertex
//design   : 
//warning  : 
//=======================================================================

Standard_Integer ColladaMesh_MeshDomain::AddVertex(const Standard_Real X, const Standard_Real Y, const Standard_Real Z)
{
  gp_XYZ Vx (X, Y, Z);
  vertexCoords.Append (Vx);
  nbVertices++;
  return nbVertices;
}

//=======================================================================
//function : AddOnlyNewVertex
//design   : Adds the vertex only if X and Y and Z doesn`t already exists.
//=======================================================================

Standard_Integer ColladaMesh_MeshDomain::AddOnlyNewVertex(const Standard_Real X, 
						      const Standard_Real Y, 
						      const Standard_Real Z, 
						      Standard_Boolean& IsNew)
{
  gp_XYZ Vx (X, Y, Z);
  IsNew = Standard_True;
  vertexCoords.Append (Vx);
  nbVertices++;
  return nbVertices;
}






