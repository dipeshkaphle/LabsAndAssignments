package com.example.lab6

import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.View
import android.widget.Button
import android.widget.EditText
import android.widget.TextView

class MainActivity : AppCompatActivity() {
    private lateinit var Username: EditText
    private lateinit var Password:  EditText
    private lateinit var LoginBtn:  Button
    private lateinit var ErrorMsg: TextView


    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        Username = findViewById<EditText>(R.id.username)
        Password = findViewById<EditText>(R.id.password)
        LoginBtn = findViewById<Button>(R.id.loginBtn)
        ErrorMsg = findViewById<TextView>(R.id.errorMsg)

        LoginBtn.setOnClickListener(
            View.OnClickListener { _ -> validate(Username.text.toString(), Password.text.toString()) }
        )
    }

    private fun validate(userName: String, password: String){
        if((userName.equals("admin")) && password.equals("root")){
            ErrorMsg.text = "Login Successful"
            val intent = Intent(this, MenuActivity::class.java)
            startActivity(intent)
        }else{
            ErrorMsg.text = "Invalid Creds"
        }

    }
}