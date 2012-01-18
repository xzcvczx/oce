// File:	RWCollada.cxx
// Created:	Thu Oct 13 13:41:29 1994
// Author:	Marc LEGAY
//		<mle@bourdon>

// Copyright:    Matra Datavision

// Collada implementation
// Author: Thomas Paviot
//		<tpaviot@gmail.com>

// Copyright: Thomas Paviot
#include <time.h>

#include <RWCollada.ixx>
#include <OSD_Protection.hxx>
#include <OSD_File.hxx>
#include <Message_ProgressSentry.hxx>
#include <TCollection_AsciiString.hxx>
#include <Standard_NoMoreObject.hxx>
#include <Standard_TypeMismatch.hxx>
#include <Precision.hxx>
#include <ColladaMesh_MeshExplorer.hxx>
#include <OSD.hxx>
#include <OSD_Host.hxx>
#include <gp_XYZ.hxx>
#include <gp.hxx>
#include <stdio.h>
#include <gp_Vec.hxx>
#include <Standard_NotImplemented.hxx>


// constants
static const int IND_THRESHOLD         = 1000; // increment the indicator every 1k triangles

//=======================================================================
//function : WriteZAE
//purpose  : write a archive COLLADA file
//=======================================================================

Standard_Boolean RWCollada::WriteZAE (const Handle(ColladaMesh_Mesh)& theMesh,
                                     const OSD_Path& thePath,
                                     const Handle(Message_ProgressIndicator)& theProgInd)
{
  Standard_NotImplemented::Raise ("RWCollada::WriteZAE is not implemented");
}

//=======================================================================
//function : WriteDAE
//purpose  : write an XML COLLADA file
//=======================================================================

Standard_Boolean RWCollada::WriteDAE (const Handle(ColladaMesh_Mesh)& theMesh,
                                    const OSD_Path& thePath,
                                    const Handle(Message_ProgressIndicator)& theProgInd)
{
  OSD_File theFile (thePath);
  theFile.Build(OSD_WriteOnly,OSD_Protection());
  // write header
  TCollection_AsciiString header_node ("<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n");
  header_node += "<COLLADA xmlns=\"http://www.collada.org/2005/11/COLLADASchema\" version=\"1.4.1\">\n";
  header_node += "<asset>\n\t<contributor>\n\t\t<authoring_tool>OCE</authoring_tool>\n\t</contributor>\n";
  char date_time_buf[512];
  time_t t;
  time(&t);
  sprintf (date_time_buf,"\t<created>%s</created>\n<modified>%s</modified>\n",ctime(&t),ctime(&t));
  header_node += date_time_buf;
  header_node += "\t<unit meter=\"0.001\" name=\"millimeter\"/>\n\t<up_axis>Z_UP</up_axis>\n</asset>\n";
  theFile.Write (header_node,header_node.Length());header_node.Clear();
  
  // library_geometry
  TCollection_AsciiString library_geometry_node("");
  library_geometry_node += "<library_geometries>\n\t<geometry id=\"shape-id\">\n";
  theFile.Write (library_geometry_node,library_geometry_node.Length());library_geometry_node.Clear();
  
  //mesh
  TCollection_AsciiString mesh_node("");
  mesh_node += "\t\t\t<mesh>\n";
  theFile.Write (mesh_node,mesh_node.Length());mesh_node.Clear();
  
  //source position (float array for vertices)
  TCollection_AsciiString source_position_node("");
  source_position_node += "\t\t\t\t<source id=\"shape-mesh-skin-positions\">\n";
  
  // source position for normals coord
  TCollection_AsciiString source_normals_node("");
  source_normals_node += "\t\t\t\t<source id=\"shape-mesh-skin-normals\">\n";
  
  char sval[512];
  // vertices coordinates
  Standard_Real x1=0., y1=0., z1=0.;
  Standard_Real x2=0., y2=0., z2=0.;
  Standard_Real x3=0., y3=0., z3=0.;
  // normals coordinates
  Standard_Real n1x=0., n1y=0., n1z=0.;
  Standard_Real n2x=0., n2y=0., n2z=0.;
  Standard_Real n3x=0., n3y=0., n3z=0.;
  
  TCollection_AsciiString buf("");
  sprintf (sval,"<float_array id=\"shape-mesh-skin-positions-array\" count=\"%i\">\n",theMesh->NbTriangles()*9);
  source_position_node += sval;
  sprintf (sval,"<float_array id=\"shape-mesh-skin-normals-array\" count=\"%i\">\n",theMesh->NbTriangles()*9);
  source_normals_node += sval;
  
  // compute mesh vertices and normals
  Standard_Integer aNbDomains = theMesh->NbDomains();
  Message_ProgressSentry aDPS (theProgInd, "Mesh domains", 0, aNbDomains, 1);
  ColladaMesh_MeshExplorer aMexp (theMesh);
  for (Standard_Integer nbd = 1; nbd <= aNbDomains && aDPS.More(); nbd++, aDPS.Next())
  {
    // create progress sentry for triangles in domain
    Message_ProgressSentry aTPS (theProgInd, "Triangles", 0,
        theMesh->NbTriangles (nbd), IND_THRESHOLD);
    Standard_Integer aTriangleInd = 0;
    for (aMexp.InitTriangle (nbd); aMexp.MoreTriangle(); aMexp.NextTriangle())
    {
      // get vertices coords  
      aMexp.TriangleVertices (x1,y1,z1,x2,y2,z2,x3,y3,z3);
      //sprintf(sval,"%12e %12e %12e %12e %12e %12e %12e %12e %12e ",x1,y1,z1,x2,y2,z2,x3,y3,z3);
      // by default, COLLADA precision requires 6 digits
      sprintf(sval,"%.6f %.6f %.6f %.6f %.6f %.6f %.6f %.6f %.6f ",x1,y1,z1,x2,y2,z2,x3,y3,z3);
      source_position_node += sval;
      // write normal coords : 6 digits after decimal point
      aMexp.TriangleOrientation(n1x,n1y,n1z,n2x,n2y,n2z,n3x,n3y,n3z);
      sprintf(sval,"%.6f %.6f %.6f %.6f %.6f %.6f %.6f %.6f %.6f ",n1x,n1y,n1z,n2x,n2y,n2z,n3x,n3y,n3z);
      source_normals_node += sval;
      
      // update progress only per 1k triangles
      if (++aTriangleInd % IND_THRESHOLD == 0)
      {
          cout << "1000 done.";
        if (!aTPS.More())
            break;
        aTPS.Next();
      }
    }
  }
  // finish source for positions
  source_position_node += "\n</float_array>\n";
  source_position_node += "<technique_common>\n";
  sprintf(sval,"<accessor count=\"%i\" source=\"#shape-mesh-skin-positions-array\" stride=\"3\">\n",theMesh->NbTriangles()*3);
  source_position_node += sval;
  source_position_node += "<param name=\"X\" type=\"float\"/>\n";
  source_position_node += "<param name=\"Y\" type=\"float\"/>\n";
  source_position_node += "<param name=\"Z\" type=\"float\"/>\n";
  source_position_node += "</accessor>\n</technique_common>\n";
  source_position_node += "</source>\n";

  //finish source for normals
  source_normals_node += "\n</float_array>\n";
  source_normals_node += "<technique_common>\n";
  sprintf(sval,"<accessor count=\"%i\" source=\"#shape-mesh-skin-normals-array\" stride=\"3\">\n",theMesh->NbTriangles()*3);
  source_normals_node += sval;
  source_normals_node += "<param name=\"nx\" type=\"float\"/>\n";
  source_normals_node += "<param name=\"ny\" type=\"float\"/>\n";
  source_normals_node += "<param name=\"nz\" type=\"float\"/>\n";
  source_normals_node += "</accessor>\n</technique_common>\n";
  source_normals_node += "</source>\n";
  
  // write position source
  theFile.Write (source_position_node, source_position_node.Length()); source_position_node.Clear();
  theFile.Write (source_normals_node, source_normals_node.Length()); source_normals_node.Clear();
  
  buf +="<vertices id=\"shape-mesh-skin-vertices\">\n<input semantic=\"POSITION\" source=\"#shape-mesh-skin-positions\"/>\n</vertices>\n";
  sprintf(sval,"<triangles count=\"%i\">\n",theMesh->NbTriangles());
  buf += sval;
  buf += "<input semantic=\"VERTEX\" source=\"#shape-mesh-skin-vertices\" offset=\"0\"/>\n";
  buf += "<input semantic=\"NORMAL\" source=\"#shape-mesh-skin-normals\" offset=\"1\"/>\n";
  // write vertex indices
  buf += "<p>\n";
  for (int i=0;i<theMesh->NbTriangles()*3;i++) {
      //sprintf(sval,"%i ",i);
      sprintf(sval,"%i %i ",i,i);
      buf += sval;
  }
  buf += "\n</p>\n";
  buf += "</triangles>\n";
  buf += "</mesh>\n";
  buf += "</geometry>\n";
  buf += "</library_geometries>\n";
  // write geometry
  theFile.Write (buf, buf.Length()); buf.Clear();
  // write scene
  // library visual scene
  TCollection_AsciiString visual_scene_node("");
  visual_scene_node += "<library_visual_scenes>\n";
  visual_scene_node += "\t<visual_scene id=\"ID1\">\n";
  visual_scene_node += "\t\t<node name=\"OCE\">\n";
  visual_scene_node += "\t\t\t<instance_geometry url=\"#shape-id\">\n";
  visual_scene_node += "\t\t\t</instance_geometry>\n";
  visual_scene_node += "\t\t</node>\n";
  visual_scene_node += "\t</visual_scene>\n";
  visual_scene_node += "</library_visual_scenes>\n";
  theFile.Write (visual_scene_node,visual_scene_node.Length());visual_scene_node.Clear();
  
  // close tags
  buf += "<scene>\n\t<instance_visual_scene url=\"#ID1\" />\n</scene>\n";
  buf += "</COLLADA>\n";
  theFile.Write (buf, buf.Length()); buf.Clear();
  theFile.Close();
  Standard_Boolean isInterrupted = !aDPS.More();
  return !isInterrupted;
}
//=======================================================================
//function : ReadFile
//Design   :
//Warning  :
//=======================================================================

Handle_ColladaMesh_Mesh RWCollada::ReadFile (const OSD_Path& thePath,
                                     const Handle(Message_ProgressIndicator)& theProgInd)
{
  Standard_NotImplemented::Raise ("RWCollada::ReadBinary is not implemented");
}

//=======================================================================
//function : ReadZAE
//Design   :
//Warning  :
//=======================================================================

Handle_ColladaMesh_Mesh RWCollada::ReadZAE (const OSD_Path& thePath,
                                       const Handle(Message_ProgressIndicator)& /*theProgInd*/)
{
  Standard_NotImplemented::Raise ("RWCollada::ReadZAE is not implemented");

}
//=======================================================================
//function : ReadDAE
//Design   :
//Warning  :
//=======================================================================

Handle_ColladaMesh_Mesh RWCollada::ReadDAE (const OSD_Path& thePath,
                                      const Handle(Message_ProgressIndicator)& theProgInd)
{
  Standard_NotImplemented::Raise ("RWCollada::ReadDAE is not implemented");
}
