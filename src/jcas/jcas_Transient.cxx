// Copyright: 	Open CASCADE 2004
// File:	jcas_Transient1.cxx
// Created:	Wed Jan 21 14:29:21 2004
// Author:	Roman LYGIN
//		<rln@TRIPLEX>


#include <jcas_Transient.h>
#include <jcas.hxx>
#include <Standard_Transient.hxx>
#include <Standard_ErrorHandler.hxx>
#include <Standard_Failure.hxx>
#include <Standard_SStream.hxx>

#include <Standard_Macro.hxx>

extern "C" {

JNIEXPORT void JNICALL Java_jcas_Transient_FinalizeID
  (JNIEnv *env , jclass theobj, jlong theid)
{

  if (theid) {
    Handle(Standard_Transient)* thehandleobj = (Handle(Standard_Transient)*) theid;
    delete thehandleobj;
  }


}

JNIEXPORT jboolean JNICALL Java_jcas_Transient_IsNullObj
  (JNIEnv *env, jobject theobj)
{
jboolean thejret = 0;
jcas_Locking alock(env);
{
try {
  OCC_CATCH_SIGNALS
Handle(Standard_Transient) the_this = *((Handle(Standard_Transient)*) jcas_GetHandle(env,theobj));
thejret = the_this.IsNull();

}
catch (Standard_Failure) {
  Standard_SStream Err;
  Err <<   Standard_Failure::Caught(); 
  Err << (char) 0;
  jcas_ThrowException(env,GetSString(Err));
}
}
alock.Release(); 
return thejret;
}

}


