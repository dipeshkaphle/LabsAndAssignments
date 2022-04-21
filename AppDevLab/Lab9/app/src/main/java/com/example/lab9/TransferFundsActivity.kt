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

class TransferFundsActivity : AppCompatActivity() {
    private lateinit var fundTransferAmt : EditText
    private lateinit var toAccNum: EditText
    private lateinit var transferBtn: Button
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_transfer_funds)
        fundTransferAmt = findViewById(R.id.transfer_amt)
        toAccNum = findViewById(R.id.transfer_to)
        transferBtn = findViewById(R.id.fund_transfer_btn)
        val phoneNo = intent.getStringExtra("phoneNo")
        transferBtn.setOnClickListener {
            val destNo = toAccNum.text.toString()
            val amt = fundTransferAmt.text.toString().toInt()
            GlobalScope.launch {
                val wasSuccess= phoneNo?.let { it1 -> UserDBHandler().transferMoney(it1, destNo, amt) }
                val user = phoneNo?.let { it1 -> UserDBHandler().getUserByPhone(it1) }
                withContext(Dispatchers.Main) {
                    wasSuccess.let {
                        if(it == true) {
                            // Alert user that transfer was successful
                            AlertDialog.Builder(this@TransferFundsActivity)
                                .setTitle("Transfer Successful")
                                .setMessage("Transfer of $amt was successful")
                                .setPositiveButton("OK") { _, _ ->
                                    val intent = Intent(this@TransferFundsActivity, HomeActivity::class.java)
                                    intent.putExtra("user", user)
                                    startActivity(intent)

                                }
                                .show()
                        }else{
                            // Alert user that transfer was successful
                            AlertDialog.Builder(this@TransferFundsActivity)
                                .setTitle("Transfer Unsuccessful")
                                .setMessage("Transfer of $amt was unsuccessful")
                                .setPositiveButton("OK") { _, _ ->
                                    val intent = Intent(this@TransferFundsActivity, HomeActivity::class.java)
                                    intent.putExtra("user", user)
                                    startActivity(intent)
                                }
                                .show()
                        }
                    }
                }
            }
        }

    }
}