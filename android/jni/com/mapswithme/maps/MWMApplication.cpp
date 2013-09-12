/*
 * MWMService.cpp
 *
 *  Created on: May 11, 2012
 *      Author: siarheirachytski
 */

#include "Framework.hpp"

#include "../core/jni_helper.hpp"

#include "../platform/Platform.hpp"

#include "../../../../../map/information_display.hpp"
#include "../../../../../map/location_state.hpp"
#include "../../../../../map/dialog_settings.hpp"

#include "../../../../../platform/settings.hpp"


extern "C"
{
  JNIEXPORT void JNICALL
  Java_com_mapswithme_maps_MWMApplication_nativeInit(
      JNIEnv * env, jobject thiz,
      jstring apkPath, jstring storagePath, jstring tmpPath, jstring obbGooglePath,
      jboolean isPro, jboolean isYota)
  {
    android::Platform::Instance().Initialize(
        env, apkPath, storagePath, tmpPath, obbGooglePath, isPro, isYota);

    LOG(LDEBUG, ("Creating android::Framework instance ..."));

    if (!g_framework)
      g_framework = new android::Framework();

    LOG(LDEBUG, ("android::Framework created"));
  }

  JNIEXPORT jboolean JNICALL
  Java_com_mapswithme_maps_MWMApplication_nativeIsBenchmarking(JNIEnv * env, jobject thiz)
  {
    return static_cast<jboolean>(g_framework->NativeFramework()->IsBenchmarking());
  }

  JNIEXPORT jboolean JNICALL
  Java_com_mapswithme_maps_MWMApplication_shouldShowDialog(
      JNIEnv * env, jobject thiz, jint dlg)
  {
    return static_cast<jboolean>(dlg_settings::ShouldShow(static_cast<dlg_settings::DialogT>(dlg)));
  }

  JNIEXPORT void JNICALL
  Java_com_mapswithme_maps_MWMApplication_submitDialogResult(
      JNIEnv * env, jobject thiz, jint dlg, jint res)
  {
    dlg_settings::SaveResult(static_cast<dlg_settings::DialogT>(dlg),
                             static_cast<dlg_settings::ResultT>(res));
  }

  JNIEXPORT jboolean JNICALL
  Java_com_mapswithme_maps_MWMApplication_nativeGetBoolean(JNIEnv * env,
                                                           jobject thiz,
                                                           jstring name,
                                                           jboolean defaultVal)
  {
    bool val = defaultVal;
    Settings::Get(jni::ToNativeString(env, name), val);
    return val;
  }

  JNIEXPORT void JNICALL
  Java_com_mapswithme_maps_MWMApplication_nativeSetBoolean(JNIEnv * env,
                                                           jobject thiz,
                                                           jstring name,
                                                           jboolean val)
  {
    bool flag = val;
    (void)Settings::Set(jni::ToNativeString(env, name), flag);
  }

  JNIEXPORT jboolean JNICALL
  Java_com_mapswithme_maps_MWMApplication_hasFreeSpace(JNIEnv * env, jobject thiz, jlong size)
  {
    return android::Platform::Instance().HasAvailableSpaceForWriting(size);
  }

  JNIEXPORT void JNICALL
  Java_com_mapswithme_maps_MWMApplication_nativeAddLocalization(JNIEnv * env, jobject thiz, jstring name, jstring value)
  {
    g_framework->AddString(jni::ToNativeString(env, name),
                           jni::ToNativeString(env, value));
  }

  JNIEXPORT jint JNICALL
  Java_com_mapswithme_maps_MWMApplication_nativeGetInt(JNIEnv * env, jobject thiz, jstring name, jint defaultValue)
  {
    jint value;
    if (Settings::Get(jni::ToNativeString(env, name), value))
      return value;

    return defaultValue;
  }

  JNIEXPORT void JNICALL
  Java_com_mapswithme_maps_MWMApplication_nativeSetInt(JNIEnv * env, jobject thiz, jstring name, jint value)
  {
    (void)Settings::Set(jni::ToNativeString(env, name), value);
  }

  JNIEXPORT jlong JNICALL
  Java_com_mapswithme_maps_MWMApplication_nativeGetLong(JNIEnv * env, jobject thiz, jstring name, jlong defaultValue)
  {
    jlong value;
    if (Settings::Get(jni::ToNativeString(env, name), value))
      return value;

    return defaultValue;
  }

  JNIEXPORT void JNICALL
  Java_com_mapswithme_maps_MWMApplication_nativeSetLong(JNIEnv * env, jobject thiz, jstring name, jlong value)
  {
    (void)Settings::Set(jni::ToNativeString(env, name), value);
  }

  JNIEXPORT jdouble JNICALL
  Java_com_mapswithme_maps_MWMApplication_nativeGetDouble(JNIEnv * env, jobject thiz, jstring name, jdouble defaultValue)
  {
    jdouble value;
    if (Settings::Get(jni::ToNativeString(env, name), value))
      return value;

    return defaultValue;
  }

  JNIEXPORT void JNICALL
  Java_com_mapswithme_maps_MWMApplication_nativeSetDouble(JNIEnv * env, jobject thiz, jstring name, jdouble value)
  {
    (void)Settings::Set(jni::ToNativeString(env, name), value);
  }
}
