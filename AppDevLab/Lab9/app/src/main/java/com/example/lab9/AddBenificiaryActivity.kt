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

class AddBenificiaryActivity : AppCompatActivity() {
    private lateinit var benificiaryTxt: EditText
    private lateinit var addBtn : Button
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_add_benificiary)
        benificiaryTxt = findViewById(R.id.benificiary_no)
        val phoneNo = intent.getStringExtra("phoneNo")
        addBtn = findViewById(R.id.add)
        addBtn.setOnClickListener {
            GlobalScope.launch {
                val wasAdded = phoneNo?.let { it1 -> UserDBHandler().addBenificiary(it1, benificiaryTxt.text.toString()) }
                val user = phoneNo?.let { it1 -> UserDBHandler().getUserByPhone(it1) }
                withContext(Dispatchers.Main){
                    wasAdded?.let {
                        if(it){
                            //Alert Dialog saying that benificiary was added
                            AlertDialog.Builder(this@AddBenificiaryActivity)
                                .setTitle("Success")
                                .setMessage("Benificiary added successfully")
                                .setPositiveButton("OK"){ _, _ ->
                                    val intent = Intent(this@AddBenificiaryActivity, HomeActivity::class.java)
                                    intent.putExtra("user", user)
                                    startActivity(intent)
                                }
                                .show()
                        }else{
                            //Alert Dialog saying that benificiary was not added
                            AlertDialog.Builder(this@AddBenificiaryActivity)
                                .setTitle("Error")
                                .setMessage("Benificiary was not added")
                                .setPositiveButton("OK"){ _, _ ->
                                    val intent = Intent(this@AddBenificiaryActivity, HomeActivity::class.java)
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