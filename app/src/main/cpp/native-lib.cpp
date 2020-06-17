#include <jni.h>
#include <string>
#include <android/log.h>
#include <iostream>
#include <cstring>
#include <strings.h>
using namespace std;

jstring envirnoment_stage= (jstring) "stage", envirnoment_uat= (jstring) "uat";

char* TAG= (char *)"native_lib";

extern "C" JNIEXPORT jstring JNICALL
Java_com_iniyan_secureapi_Keys_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hero function";
    return env->NewStringUTF(hello.c_str());
}


extern "C"
JNIEXPORT jobject JNICALL
Java_com_iniyan_secureapi_Keys_objectJNI(JNIEnv *env, jobject thiz, jstring firstname,
                                                  jstring second_name) {
    char returnString[100];
    const char *fN = env->GetStringUTFChars(firstname, nullptr);
    const char *lN = env->GetStringUTFChars(second_name, nullptr);

    strcpy(returnString,fN); // copy string one into the result.
    strcat(returnString,lN); // append string two to the result.

    env->ReleaseStringUTFChars(firstname, fN);
    env->ReleaseStringUTFChars(second_name, lN);

    if(envirnoment_stage == envirnoment_uat){
        __android_log_print(ANDROID_LOG_INFO, TAG, "Envirnoment  == %s", (char *)envirnoment_stage);

    }else {
        __android_log_print(ANDROID_LOG_INFO, TAG, "Envirnoment != %s", (char *)envirnoment_uat);

    }

    __android_log_print(ANDROID_LOG_INFO, TAG, "The value is %s", returnString);
    __android_log_write(ANDROID_LOG_DEBUG, TAG, returnString);

    return env->NewStringUTF(returnString);


}



extern "C"
JNIEXPORT jobjectArray JNICALL
Java_com_iniyan_secureapi_Keys_data(JNIEnv *env, jobject thiz, jstring build_type) {
    jobjectArray ret;
    int i;

    char *message[2];
    ret= (jobjectArray)env->NewObjectArray(2,
                                           env->FindClass("java/lang/String"),
                                           env->NewStringUTF(""));


    char * envirnoment_data=(char *) env -> GetStringUTFChars(build_type, nullptr);

    __android_log_print(ANDROID_LOG_INFO, TAG, "Input Data    == %s", envirnoment_data);

    if(strcmp(reinterpret_cast<const char *>(envirnoment_stage), envirnoment_data) == 0){
        message[0]= (char *)"123456";
        message[1]=(char *)"abcdefghijklmnoproqss";
        __android_log_print(ANDROID_LOG_INFO, TAG, "Envirnoment  == %s", envirnoment_data);

    }else {
        message[0]= (char *)"123456";
        message[1]=(char *) "abcdefghijklmnoproqss";
        __android_log_print(ANDROID_LOG_INFO, TAG, "Envirnoment != %s", envirnoment_data);

    }

    for(i=0;i<2;i++) {
        env->SetObjectArrayElement(
                ret,i,env->NewStringUTF(message[i]));
    }

    return(ret);
}





extern "C" JNIEXPORT jstring
JNICALL
Java_com_iniyan_secureapi_Keys_apiKey(JNIEnv *env, jobject object) {
    std::string api_key = "sample_apikey";
    return env->NewStringUTF(api_key.c_str());
}extern "C"
JNIEXPORT jobjectArray JNICALL
Java_com_iniyan_secureapi_MainActivity_data(JNIEnv *env, jobject thiz, jstring build_type) {
    jobjectArray ret;
    int i;

    char *message[2];
    ret= (jobjectArray)env->NewObjectArray(2,
                                           env->FindClass("java/lang/String"),
                                           env->NewStringUTF(""));


    char * envirnoment_data=(char *) env -> GetStringUTFChars(build_type, nullptr);

    __android_log_print(ANDROID_LOG_INFO, TAG, "Input Data    == %s", envirnoment_data);

    if(strcmp(reinterpret_cast<const char *>(envirnoment_stage), envirnoment_data) == 0){
        message[0]= (char *)"123456";
        message[1]=(char *) "abcdefghijklmnoproqss";
        __android_log_print(ANDROID_LOG_INFO, TAG, "Envirnoment  == %s", envirnoment_data);

    }else {
        message[0]= (char *)"123456";
        message[1]=(char *)"abcdefghijklmnoproqss";
        __android_log_print(ANDROID_LOG_INFO, TAG, "Envirnoment != %s", envirnoment_data);

    }

    for(i=0;i<2;i++) {
        env->SetObjectArrayElement(
                ret,i,env->NewStringUTF(message[i]));
    }

    return(ret);
}