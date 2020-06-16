package com.digitap.secureapi

import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import kotlinx.android.synthetic.main.activity_main.*

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        val data=Keys.data("stage")

        //sample_text.text=Keys.apiKey()

        //  sample_text.text = stringFromJNI() + objectJNI("iniyan","arul") +" print element ${data!!.contentToString()}}"
        sample_text.text = "print element ${data!!.contentToString()}}"

    }


    /** if you use object this code is not required if activity if you need to put static
    companion object {
    // Used to load the 'native-lib' library on application startup.
    init {
    System.loadLibrary("native-lib")
    }
    }
     **/
}
