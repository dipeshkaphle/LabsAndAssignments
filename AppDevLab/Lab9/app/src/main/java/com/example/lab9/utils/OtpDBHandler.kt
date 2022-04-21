package com.example.lab9.utils

import android.content.Context
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import com.google.android.gms.tasks.Tasks
import com.google.firebase.database.DataSnapshot
import com.google.firebase.database.DatabaseError
import com.google.firebase.database.DatabaseReference
import com.google.firebase.database.ValueEventListener
import com.google.firebase.database.ktx.database
import com.google.firebase.database.ktx.getValue
import com.google.firebase.ktx.Firebase
import kotlinx.coroutines.runBlocking

class OtpDBHandler{
    var mDatabase: DatabaseReference = Firebase.database.getReference("otps")

    fun getOtp(phone: String): String? = runBlocking {
        val phn = mDatabase.child(phone).get()
        return@runBlocking Tasks.await(phn).getValue<String>()
    }
    fun insertOtp(phone: String) = runBlocking{
          val otp  = (Math.random()* 1000000).toInt().toString()
          Tasks.await(mDatabase.child(phone).setValue( otp ))
    }
}