package com.example.lab9

import android.annotation.SuppressLint
import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.*
import androidx.appcompat.app.AlertDialog
import com.example.lab9.utils.User
import com.example.lab9.utils.UserDBHandler
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.GlobalScope
import kotlinx.coroutines.launch
import kotlinx.coroutines.withContext

class TransferFundsActivity : AppCompatActivity() {
    private lateinit var fundTransferAmt : EditText
    private lateinit var toAccNum: Spinner
    private lateinit var transferBtn: Button
    @SuppressLint("ResourceType")
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_transfer_funds)
        fundTransferAmt = findViewById(R.id.transfer_amt)
        toAccNum = findViewById(R.id.transfer_to)

        transferBtn = findViewById(R.id.fund_transfer_btn)

        val usr: User? = intent.getSerializableExtra("user") as User?
        val phoneNo = usr?.phone

        // set spinner values to the user.beneficiaryList
        usr?.benificiaryList.let {
             val adapter = ArrayAdapter(this@TransferFundsActivity,
                 android.R.layout.simple_spinner_item, listOf("Select Benificiary")+ it
             )
             adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item)
             toAccNum.adapter = adapter
         }


        transferBtn.setOnClickListener {
            val destNo = toAccNum.selectedItem.toString()
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