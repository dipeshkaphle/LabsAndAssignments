package com.example.lab10

import android.annotation.SuppressLint
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.os.Handler
import android.os.Looper
import android.speech.tts.TextToSpeech
import android.view.SurfaceHolder
import android.view.SurfaceView
import android.view.View
import android.widget.Button
import android.widget.TextView
import android.widget.Toast
import androidx.core.app.ActivityCompat
import com.google.android.gms.vision.CameraSource
import com.google.android.gms.vision.Detector
import com.google.android.gms.vision.text.TextBlock
import com.google.android.gms.vision.text.TextRecognizer
import java.util.*

class MainActivity : AppCompatActivity() {
    private lateinit var startBtn : Button
    private lateinit var cameraSource : CameraSource
    private lateinit var textRecognizer : TextRecognizer
    private lateinit var textToSpeech : TextToSpeech
    private var textRecognized : String = ""
    private lateinit var surfaceView : SurfaceView


    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        ActivityCompat.requestPermissions(
            this,
            arrayOf(android.Manifest.permission.CAMERA), 1
        )

//        textView = findViewById(R.id.textView)

        textToSpeech = TextToSpeech(this@MainActivity) {
            if (it == TextToSpeech.SUCCESS) {
                val result = textToSpeech.setLanguage(Locale.ENGLISH)
                if (result == TextToSpeech.LANG_MISSING_DATA || result == TextToSpeech.LANG_NOT_SUPPORTED) {
                    Toast.makeText(this@MainActivity, "Language not supported", Toast.LENGTH_SHORT)
                        .show()
                }
            } else {
                Toast.makeText(this@MainActivity, "Initialization failed", Toast.LENGTH_SHORT)
                    .show()
            }
        }


        startBtn = findViewById(R.id.start_btn)

        textRecognizer = TextRecognizer.Builder(this).build()

        textRecognizer.setProcessor(object : Detector.Processor<TextBlock> {
            override fun release() {

            }

            override fun receiveDetections(detections: Detector.Detections<TextBlock>) {
                val items = detections.detectedItems
                val handler = Handler(Looper.getMainLooper())
                handler.post {
                    if (items.size() != 0) {
                        textRecognized = items.valueAt(0).value
                        this@MainActivity.onResultObtained()
                    }
               }
            }
        })
    }

    fun onResultObtained(){
        setContentView(R.layout.activity_main)
        findViewById<TextView>(R.id.textView).text = textRecognized
//        Toast.makeText(this, textView.text, Toast.LENGTH_SHORT).show()
        textToSpeech.speak(textRecognized, TextToSpeech.QUEUE_FLUSH, null, null)
    }
    fun btnOnClick(view:View){
        if (!textRecognizer.isOperational) {
            Toast.makeText(this, "Error", Toast.LENGTH_SHORT).show()
        }else{
            setContentView(R.layout.surfaceview)
            cameraSource = CameraSource.Builder(this, textRecognizer)
                .setAutoFocusEnabled(true)
                .setFacing(CameraSource.CAMERA_FACING_BACK)
                .setRequestedPreviewSize(1280, 1024)
                .build()
            surfaceView = findViewById(R.id.surface_view)

            surfaceView.holder.addCallback(object : SurfaceHolder.Callback {
                override fun surfaceChanged(
                    p0: SurfaceHolder,
                    format: Int,
                    width: Int,
                    height: Int
                ) {
                }

                override fun surfaceDestroyed(p0: SurfaceHolder) {
                    cameraSource.stop()
                }

                @SuppressLint("MissingPermission")
                override fun surfaceCreated(p0: SurfaceHolder) {
                    try {
                        cameraSource.start(surfaceView.holder)
                    } catch (e: Exception) {
                        e.printStackTrace()
                    }
                }
            })

        }
    }

    override fun onDestroy() {
        super.onDestroy()
        cameraSource.release()
    }
}