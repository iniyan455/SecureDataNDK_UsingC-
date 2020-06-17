package com.iniyan.secureapi

object Keys  {

    init {
        System.loadLibrary("native-lib")
    }

     external fun data(buildType:String): Array<String?>?
    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI(): String


    external fun objectJNI(firstname:String,secondName:String): Any

    external fun apiKey(): String


}