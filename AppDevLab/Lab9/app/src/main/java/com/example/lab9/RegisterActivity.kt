package com.example.lab9

import android.app.AlertDialog
import android.app.PendingIntent
import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.telephony.SmsManager
import android.widget.Button
import android.widget.EditText
import android.widget.Toast
import com.example.lab9.utils.OtpDBHandler
import com.example.lab9.utils.UserDBHandler
import kotlinx.coroutines.GlobalScope
import kotlinx.coroutines.launch

@Suppress("DEPRECATION")
class RegisterActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_register)
        val regUserName = findViewById<EditText>(R.id.reg_username)
        val phoneNo = findViewById<EditText>(R.id.reg_phone_no)
        val password = findViewById<EditText>(R.id.reg_password)
        val retypedPassword = findViewById<EditText>(R.id.reg_retype_password)
        val submitBtn = findViewById<Button>(R.id.submit_registration)
        submitBtn.setOnClickListener {
            val username = regUserName.text.toString()
            val phoneNoText = phoneNo.text.toString()
            val passwordText = password.text.toString()
            val retypedPasswordText = retypedPassword.text.toString()
            if(phoneNoText.length!=10 && phoneNoText.all { it.isDigit() }){
                Toast.makeText(this, "Phone number should be of 10 digits", Toast.LENGTH_SHORT).show()
                return@setOnClickListener
            }

            if(passwordText == retypedPasswordText){
                var otp: String? = null
                GlobalScope.launch {
                    // firebase get instance
                    val userDBHandler = UserDBHandler()
                    userDBHandler.addUser(username, phoneNoText, passwordText, 0, 0)
                    val otpDBHandler = OtpDBHandler()
                    otpDBHandler.insertOtp(phoneNoText)

                    otp = otpDBHandler.getOtp(phoneNoText)
                }.invokeOnCompletion {
                    otp?.let { it1 -> this.sendSMS(phoneNoText, it1) }
                    startActivity(Intent(this, OtpActivity::class.java).putExtra("phoneNo", phoneNoText))
                }

            }else{
                val alertDialogBuilder = AlertDialog.Builder(this)
                alertDialogBuilder.setMessage("Password not matching")
                alertDialogBuilder.setPositiveButton("OK") { _, _ ->
                }
                val alertDialog = alertDialogBuilder.create()
                alertDialog.show()
            }
        }
    }
    fun sendSMS(phone: String, otpMsg: String){
        // ask for permission if not there
        if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.M) {
            if (checkSelfPermission(android.Manifest.permission.SEND_SMS) ==
                android.content.pm.PackageManager.PERMISSION_DENIED
            ) {
                requestPermissions(
                    arrayOf(android.Manifest.permission.SEND_SMS),
                    1
                )
            }
        }
        val sentPI: PendingIntent =
            PendingIntent.getBroadcast(this, 0, Intent("SMS_SENT"), 0)
        SmsManager.getDefault().sendTextMessage(phone, null, otpMsg, sentPI, null)
    }

}