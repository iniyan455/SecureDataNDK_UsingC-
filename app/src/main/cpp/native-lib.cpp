#include <jni.h>
#include <string>

extern "C" JNIEXPORT jstring JNICALL
Java_com_digitap_secureapi_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hero function";
    return env->NewStringUTF(hello.c_str());
}
