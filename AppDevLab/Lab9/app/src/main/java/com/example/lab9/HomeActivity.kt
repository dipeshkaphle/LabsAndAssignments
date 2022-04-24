package com.example.lab9

import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Button
import android.widget.EditText
import android.widget.TextView
import com.example.lab9.utils.User

class HomeActivity : AppCompatActivity() {
    private lateinit var transferBtn: Button
    private lateinit var addBenificiaryBtn: Button
    private lateinit var addFundsBtn: Button
    private lateinit var balance : TextView
    private lateinit var user : User
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_home)
        transferBtn = findViewById(R.id.transfer)
        addBenificiaryBtn = findViewById(R.id.add_benificiary)
        balance = findViewById(R.id.balance)
        addFundsBtn =  findViewById(R.id.add_funds)
        user = intent.getSerializableExtra("user") as User

        balance.text = user.balance.toString()

        transferBtn.setOnClickListener {
            val intent = Intent(this, TransferFundsActivity::class.java)
            intent.putExtra("user", user)
            startActivity(intent)
        }
        addBenificiaryBtn.setOnClickListener {
            val intent = Intent(this, AddBenificiaryActivity::class.java)
            intent.putExtra("phoneNo", user.phone)
            startActivity(intent)
        }
        addFundsBtn.setOnClickListener {
            val intent = Intent(this, AddFundsActivity::class.java)
            intent.putExtra("phoneNo", user.phone)
            startActivity(intent)
        }
    }
}