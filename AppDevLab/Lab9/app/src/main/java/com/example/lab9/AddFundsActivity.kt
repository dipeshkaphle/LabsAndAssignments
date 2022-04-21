package com.example.lab9

import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Button
import android.widget.EditText
import androidx.appcompat.app.AlertDialog
import com.example.lab9.utils.UserDBHandler
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.GlobalScope
import kotlinx.coroutines.launch
import kotlinx.coroutines.withContext

class AddFundsActivity : AppCompatActivity() {
    private lateinit var depositBtn: Button
    private lateinit var fundsTxt : EditText
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_add_funds)
        depositBtn= findViewById(R.id.deposit)
        fundsTxt = findViewById(R.id.deposit_amt)
        val phoneNo = intent.getStringExtra("phoneNo")
        depositBtn.setOnClickListener {
            GlobalScope.launch {
                phoneNo?.let { it1 -> UserDBHandler().deposit(it1, fundsTxt.text.toString().toInt()) }
                val user = phoneNo?.let { it1 -> UserDBHandler().getUserByPhone(it1) }
                withContext(Dispatchers.Main){
                    //show alert saying funds added
                    AlertDialog.Builder(this@AddFundsActivity)
                        .setTitle("Success")
                        .setMessage("${user?.username}'s account has been credited with ${fundsTxt.text}")
                        .setPositiveButton("OK") { _, _ ->
                            user?.let {
                                val intent = Intent(this@AddFundsActivity, HomeActivity::class.java)
                                intent.putExtra("user", user)
                                startActivity(intent)
                            }
                        }
                        .show()
                }
            }
        }
    }
}