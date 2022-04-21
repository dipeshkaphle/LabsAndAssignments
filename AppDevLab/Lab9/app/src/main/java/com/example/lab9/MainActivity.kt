package com.example.lab9

import android.app.AlertDialog
import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.os.Looper
import android.widget.Button
import android.widget.EditText
import android.widget.Toast
import com.example.lab9.utils.User
import com.example.lab9.utils.UserDBHandler
import kotlinx.coroutines.*

// Login  Activity


//Create a mobile banking application for user registration.
// Get username, passwordand Retype password.
// Verify the registration by sending OTP to the mobile number.
// After registration, allow the user to do following activities by
// sending OTP :
// - Adding new Beneficiary
// - External Fund transfer
// - Online Bill payment

class MainActivity : AppCompatActivity() {
    private lateinit var phoneNo: EditText
    private lateinit var password: EditText
    private lateinit var login: Button
    private lateinit var register: Button
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        phoneNo = findViewById(R.id.login_phone_no)
        password = findViewById(R.id.password)
        login = findViewById(R.id.login)
        register = findViewById(R.id.register)

        register.setOnClickListener {
            val intent = Intent(this, RegisterActivity::class.java)
            startActivity(intent)
        }

        login.setOnClickListener {
            val phone = phoneNo.text.toString()
            val pass = password.text.toString()
            if (phone.isEmpty() || pass.isEmpty()) {
                // show the error message
                AlertDialog.Builder(this)
                    .setTitle("Error")
                    .setMessage("Please enter username and password")
                    .setPositiveButton("OK") { _, _ -> }
                    .create()
                    .show()
                return@setOnClickListener
            } else {
                //get the user from the database from phone number
                var user : User? = null
                GlobalScope.launch(Dispatchers.Default) {
                    user = UserDBHandler().getUserByPhone(phone)
                    withContext(Dispatchers.Main){
                        if (user == null) {
                            // show the error message
                            AlertDialog.Builder(this@MainActivity)
                                .setTitle("Error")
                                .setMessage("User not found")
                                .setPositiveButton("OK") { _, _ ->
                                    // go to RegisterActivity
                                    val intent = Intent(this@MainActivity, RegisterActivity::class.java)
                                    startActivity(intent)
                                }
                                .create()
                                .show()
                        }
                        if (user?.isVerified == 0) {
                            AlertDialog.Builder(this@MainActivity)
                                .setTitle("Error")
                                .setMessage("Please verify your account")
                                .setPositiveButton("OK") { _, _ ->
                                    // go to OtpActivity with phone
                                    val intent = Intent(this@MainActivity, OtpActivity::class.java)
                                    intent.putExtra("phoneNo", phone)
                                    startActivity(intent)
                                }
                                .create()
                                .show()
                        }else {
                            if (user?.password.equals(pass)) {
                                AlertDialog.Builder(this@MainActivity)
                                    .setTitle("Success")
                                    .setMessage("Login Successful")
                                    .setPositiveButton("OK") { _, _ ->
                                        val intent = Intent(this@MainActivity, HomeActivity::class.java)
                                        intent.putExtra("user", user)
                                        startActivity(intent)

                                    }
                                    .create()
                                    .show()
                            } else {
                                AlertDialog.Builder(this@MainActivity)
                                    .setTitle("Error")
                                    .setMessage("Incorrect Password")
                                    .setPositiveButton("OK") { _, _ -> }
                                    .create()
                                    .show()
                            }
                        }
                    }
                }
            }
        }
    }
}