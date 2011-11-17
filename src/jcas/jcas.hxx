#include <jni.h>
#include <Standard_ExtString.hxx>

#define GetSString(SStream) (char*)SStream.rdbuf()->str().c_str()

#ifdef __cplusplus
extern "C" {
#endif

Standard_EXPORT int	 jcas_GetaVirer(JNIEnv *env, jobject anobj);
Standard_EXPORT void jcas_SetaVirer(JNIEnv *env, jobject anobj, int aVirer);
Standard_EXPORT void* jcas_GetHandle(JNIEnv *env, jobject anobj);
Standard_EXPORT void jcas_SetHandle(JNIEnv *env, jobject anobj, const void* ahand);
Standard_EXPORT jobject jcas_CreateObject(JNIEnv *env, char * aJavaClass,const void* ahand, const int aVirer = 1);

Standard_EXPORT void jcas_ThrowException(JNIEnv *env, char* message);
Standard_EXPORT void jcas_Lock(JNIEnv *env);
Standard_EXPORT void jcas_Unlock(JNIEnv *env);

Standard_EXPORT jstring jcas_ConvertTojstring(JNIEnv *env, const Standard_ExtString astr);
Standard_EXPORT const Standard_ExtString jcas_ConvertToExtString(JNIEnv *env, jstring astr);
Standard_EXPORT const Standard_ExtString jcas_ConvertSBToExtString(JNIEnv *env, jobject astr);
Standard_EXPORT void jcas_SetExtStringToStringBuffer(JNIEnv *env, jobject astr,const Standard_ExtString fromstr);
Standard_EXPORT const Standard_CString jcas_ConvertToCString(JNIEnv *env, jobject astr);
Standard_EXPORT void jcas_SetCStringValue(JNIEnv *env, jobject astr,const Standard_CString fromstr);

Standard_EXPORT Standard_Boolean jcas_GetBoolean(JNIEnv *env, jobject abool);
Standard_EXPORT Standard_Real jcas_GetReal(JNIEnv *env, jobject areal);
Standard_EXPORT Standard_Character jcas_GetCharacter(JNIEnv *env, jobject anobj);
Standard_EXPORT Standard_Integer jcas_GetInteger(JNIEnv *env, jobject anobj);
Standard_EXPORT Standard_ExtCharacter jcas_GetExtCharacter(JNIEnv *env, jobject anobj);
Standard_EXPORT Standard_Byte jcas_GetByte(JNIEnv *env, jobject anobj);
Standard_EXPORT Standard_ShortReal jcas_GetShortReal(JNIEnv *env, jobject anobj);
Standard_EXPORT short jcas_GetShort(JNIEnv *env, jobject anobj);

Standard_EXPORT void jcas_SetBoolean(JNIEnv *env, jobject abool,Standard_Boolean aval);
Standard_EXPORT void jcas_SetReal(JNIEnv *env, jobject areal,Standard_Real aval);
Standard_EXPORT void jcas_SetCharacter(JNIEnv *env, jobject anobj,Standard_Character aval);
Standard_EXPORT void jcas_SetInteger(JNIEnv *env, jobject anobj,Standard_Integer aval);
Standard_EXPORT void jcas_SetExtCharacter(JNIEnv *env, jobject anobj,Standard_ExtCharacter aval);
Standard_EXPORT void jcas_SetByte(JNIEnv *env, jobject anobj,Standard_Byte aval);
Standard_EXPORT void jcas_SetShortReal(JNIEnv *env, jobject anobj,Standard_ShortReal aval);
Standard_EXPORT void jcas_SetShort(JNIEnv *env, jobject anobj,short aval);


class jcas_Locking {

public:
  Standard_EXPORT jcas_Locking(JNIEnv *env);
  
  Standard_EXPORT void Release();

  Standard_EXPORT ~jcas_Locking();

private:
  JNIEnv *myenv;
};

  
#ifdef __cplusplus
}
#endif
