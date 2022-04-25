package com.example.lab11

import android.Manifest
import android.content.pm.PackageManager
import android.os.Build
import android.os.Bundle
import android.widget.Button
import android.widget.EditText
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import androidx.core.content.ContextCompat

class MainActivity : AppCompatActivity() {
    private lateinit var phone: EditText
    private lateinit var call: Button
    private val Call_req = 10001
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        phone= findViewById(R.id.input)
        call = findViewById(R.id.call)
        val permissionCall = ContextCompat.checkSelfPermission(this,
            Manifest.permission.CALL_PHONE)
        if (permissionCall != PackageManager.PERMISSION_GRANTED) {
            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
                requestPermissions(arrayOf(Manifest.permission.CALL_PHONE), Call_req)
                Toast.makeText(this@MainActivity,
                    "call Permission is required for this app to run",
                    Toast.LENGTH_SHORT)
                    .show()
            }
        }
        call.setOnClickListener {
            val phoneNumber = phone.text.toString()
            val intent = android.content.Intent(
                android.content.Intent.ACTION_CALL,
                android.net.Uri.parse("tel:$phoneNumber")
            )
            startActivity(intent)
        }
    }
}