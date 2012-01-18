//=======================================================================
// File:	ColladaMesh_MeshExplorer.cxx
// Created:	Mon Sep 25 11:28:00 1995
// Author:	Philippe GIRODENGO
// Copyright:    Matra Datavision	
#include <ColladaMesh_MeshExplorer.ixx>
#include <ColladaMesh_MeshTriangle.hxx>

//=======================================================================
//function : ColladaMesh_MeshExplorer
//design   : 
//warning  : 
//=======================================================================


ColladaMesh_MeshExplorer::ColladaMesh_MeshExplorer(const Handle(ColladaMesh_Mesh)& M)
     : domainIndex (0), nbTriangles (0) ,triangleIndex (0)  { mesh = M;}
     

//=======================================================================
//function : Deflection
//design   : 
//warning  : 
//=======================================================================

Standard_Real ColladaMesh_MeshExplorer::Deflection() const 
{ return mesh->Deflection (domainIndex);}


//=======================================================================
//function : InitTriangle
//design   : 
//warning  : 
//=======================================================================

void ColladaMesh_MeshExplorer::InitTriangle(const Standard_Integer DomainIndex)
{
  triangleIndex = 1;
  domainIndex = DomainIndex;
  nbTriangles = mesh->NbTriangles (domainIndex);
  if (nbTriangles > 0) {
    trianglesdef.Assign (mesh->Triangles (DomainIndex));
    trianglesVertex.Assign (mesh->Vertices (DomainIndex));
    const Handle (ColladaMesh_MeshTriangle) trian = trianglesdef.First();
    trian->GetVertexAndOrientation (v1,v2,v3,n1x,n1y,n1z,n2x,n2y,n2z,n3x,n3y,n3z);
  }
}

//=======================================================================
//function : NextTriangle
//design   : 
//warning  : 
//=======================================================================

void ColladaMesh_MeshExplorer::NextTriangle()
{
  triangleIndex++;
  if (triangleIndex <= nbTriangles) {
    const Handle (ColladaMesh_MeshTriangle) trian = trianglesdef.Value (triangleIndex);
    trian->GetVertexAndOrientation (v1,v2,v3,n1x,n1y,n1z,n2x,n2y,n2z,n3x,n3y,n3z);
  }
}

//=======================================================================
//function : TriangleVertices
//design   : 
//warning  : 
//=======================================================================

void ColladaMesh_MeshExplorer::TriangleVertices(Standard_Real& X1, Standard_Real& Y1, 
					    Standard_Real& Z1, Standard_Real& X2, 
					    Standard_Real& Y2, Standard_Real& Z2, 
					    Standard_Real& X3, Standard_Real& Y3, 
					    Standard_Real& Z3) const 
{
  Standard_NoSuchObject_Raise_if (triangleIndex > nbTriangles, " ColladaMesh_MeshExplorer::TriangleVertices");
  
  X1 = (trianglesVertex.Value(v1)).X();
  Y1 = (trianglesVertex.Value(v1)).Y();
  Z1 = (trianglesVertex.Value(v1)).Z();
  X2 = (trianglesVertex.Value(v2)).X();
  Y2 = (trianglesVertex.Value(v2)).Y();
  Z2 = (trianglesVertex.Value(v2)).Z();
  X3 = (trianglesVertex.Value(v3)).X();
  Y3 = (trianglesVertex.Value(v3)).Y();
  Z3 = (trianglesVertex.Value(v3)).Z();
}

//=======================================================================
//function : TriangleDirection
//design   : 
//warning  : 
//=======================================================================

void ColladaMesh_MeshExplorer::TriangleOrientation(Standard_Real& N1x, Standard_Real& N1y, Standard_Real& N1z,
                                                    Standard_Real& N2x, Standard_Real& N2y, Standard_Real& N2z,
                                                    Standard_Real& N3x, Standard_Real& N3y, Standard_Real& N3z) const 
{
  N1x = n1x;
  N1y = n1y;
  N1z = n1z;
  N2x = n2x;
  N2y = n2y;
  N2z = n2z;
  N3x = n3x;
  N3y = n3y;
  N3z = n3z;
  
}






