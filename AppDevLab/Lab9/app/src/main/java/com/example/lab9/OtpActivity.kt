package com.example.lab9

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
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.GlobalScope
import kotlinx.coroutines.launch
import kotlinx.coroutines.withContext

class OtpActivity : AppCompatActivity() {
    private lateinit var phoneNo : String
    private lateinit var submitOtp: Button
    private lateinit var resendOtp: Button
    private lateinit var otpText: EditText
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_otp)
        intent.extras?.let {
            phoneNo = it.getString("phoneNo").toString()
        }
        submitOtp = findViewById(R.id.submitOtp)
        otpText = findViewById(R.id.otpText)
        resendOtp = findViewById(R.id.resend_otp)

        resendOtp.setOnClickListener {
            GlobalScope.launch {
                val otp = OtpDBHandler().getOtp(phoneNo)
                withContext(Dispatchers.Main) {
                    otp?.let { otp ->
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
                            PendingIntent.getBroadcast(this@OtpActivity, 0, Intent("SMS_SENT"), 0)
                        @Suppress("DEPRECATION")
                        SmsManager.getDefault().sendTextMessage(phoneNo, null, otp, sentPI, null)
                        val intent = Intent(this@OtpActivity, OtpActivity::class.java)
                        intent.putExtra("phoneNo", phoneNo)
                        startActivity(intent)
                        Toast.makeText(this@OtpActivity, "OTP sent successfully", Toast.LENGTH_SHORT).show()
                    }

                }
            }
        }
        submitOtp.setOnClickListener {

            var otpFromDb: String?= null
            GlobalScope.launch {
                otpFromDb = OtpDBHandler().getOtp(phoneNo)

                withContext(Dispatchers.Main) {
                    if (otpFromDb?.equals(otpText.text.toString()) == true) {
                        UserDBHandler().setVerifyToTrueForPhone(phoneNo)
                        //Toast to show that the otp is correct
                        Toast.makeText(this@OtpActivity, "OTP is correct", Toast.LENGTH_SHORT).show()
                        val intent = Intent(this@OtpActivity, MainActivity::class.java)
                        startActivity(intent)
                    } else {
                        Toast.makeText(this@OtpActivity, "OTP is incorrect", Toast.LENGTH_SHORT).show()
                    }
                }
            }.invokeOnCompletion {
            }


        }
    }
}
