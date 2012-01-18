// File:	ColladaMesh.cxx
// Created:	Fri Jun 21 15:48:55 1996
// Author:	Bruno TACCI
//		<bti@sgi44>

#include <ColladaMesh.ixx>
#include <ColladaMesh_SequenceOfMeshTriangle.hxx>
#include <ColladaMesh_MeshTriangle.hxx>
#include <TColgp_SequenceOfXYZ.hxx>

//=======================================================================
//function : Merge
//purpose  : 
//=======================================================================

Handle(ColladaMesh_Mesh) ColladaMesh::Merge(const Handle(ColladaMesh_Mesh)& mesh1, const Handle(ColladaMesh_Mesh)& mesh2)
{
  Handle(ColladaMesh_Mesh) mergeMesh = new ColladaMesh_Mesh;
  ColladaMesh_SequenceOfMeshTriangle aSeqOfTriangle;
  TColgp_SequenceOfXYZ aSeqOfVertex;
  Standard_Real n1x,n1y,n1z;
  Standard_Real n2x,n2y,n2z;
  Standard_Real n3x,n3y,n3z;
  Standard_Integer v1,v2,v3;

  // Chargement de mesh1 dans mergeMesh
  // Boucle sur les domaines puis sur les triangles

  Standard_Integer idom;
  for (idom = 1; idom <= mesh1->NbDomains(); idom++) {
    aSeqOfTriangle = mesh1->Triangles(idom);
    aSeqOfVertex = mesh1->Vertices(idom);
    mergeMesh->AddDomain(mesh1->Deflection(idom));
    
    for (Standard_Integer itri = 1; itri <= mesh1->NbTriangles(idom); itri++) {
      const Handle(ColladaMesh_MeshTriangle) aTrian = aSeqOfTriangle.Value(itri);
      aTrian->GetVertexAndOrientation(v1,v2,v3,n1x,n1y,n1z,n2x,n2y,n2z,n3x,n3y,n3z);
      mergeMesh->AddTriangle(v1,v2,v3,n1x,n1y,n1z,n2x,n2y,n2z,n3x,n3y,n3z);
    }
    
    for (Standard_Integer iver = 1; iver <= mesh1->NbVertices(idom); iver++) {
      mergeMesh->AddVertex(aSeqOfVertex.Value(iver).X(),
			   aSeqOfVertex.Value(iver).Y(),
			   aSeqOfVertex.Value(iver).Z());
    }
    
  }
  // Idem avec mesh2
  
  for (idom = 1; idom <= mesh2->NbDomains(); idom++) {
    aSeqOfTriangle = mesh2->Triangles(idom);
    aSeqOfVertex = mesh2->Vertices(idom);
    mergeMesh->AddDomain(mesh2->Deflection(idom));
    
    for (Standard_Integer itri = 1; itri <= mesh2->NbTriangles(idom); itri++) {
      const Handle(ColladaMesh_MeshTriangle) aTrian = aSeqOfTriangle.Value(itri);
      aTrian->GetVertexAndOrientation(v1,v2,v3,n1x,n1y,n1z,n2x,n2y,n2z,n3x,n3y,n3z);
      mergeMesh->AddTriangle(v1,v2,v3,n1x,n1y,n1z,n2x,n2y,n2z,n3x,n3y,n3z);
    }
    
    for (Standard_Integer iver = 1; iver <= mesh2->NbVertices(idom); iver++) {
      mergeMesh->AddVertex(aSeqOfVertex.Value(iver).X(),
			   aSeqOfVertex.Value(iver).Y(),
			   aSeqOfVertex.Value(iver).Z());
    }
  }
  return mergeMesh;
}
