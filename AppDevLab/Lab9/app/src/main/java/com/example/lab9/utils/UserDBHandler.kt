package com.example.lab9.utils

import com.google.android.gms.tasks.Tasks
import com.google.firebase.database.DatabaseReference
import com.google.firebase.database.ktx.database
import com.google.firebase.database.ktx.getValue
import com.google.firebase.ktx.Firebase
import kotlinx.coroutines.runBlocking

class UserDBHandler{

    private var mDatabase: DatabaseReference = Firebase.database.getReference("users")

    fun addUser(username: String, phone: String, password: String, balance: Int,  isVerified: Int,
                benificiaryList: List<String> = emptyList()) = runBlocking{
        val user = User(username, phone, password,balance, isVerified, benificiaryList)
        Tasks.await(mDatabase.child(phone).setValue(user))
    }

    fun getUserByPhone(phone: String): User? = runBlocking {
        val task = mDatabase.child(phone).get()
        return@runBlocking Tasks.await(task).getValue<User>()
    }

    fun setVerifyToTrueForPhone(phone: String) {
        mDatabase.child(phone).child("isVerified").setValue(1)
    }
    fun addBenificiary(phoneNo: String,  benificiaryPhone: String):Boolean = runBlocking{
        val user = getUserByPhone(phoneNo)

        user?.let { usr ->
            var benificiaryList = usr.benificiaryList?.toHashSet()
            if(benificiaryList==null)
                benificiaryList = hashSetOf()
            benificiaryList.add(benificiaryPhone)
            benificiaryList.let { usr.benificiaryList = it.toList() }
            Tasks.await(mDatabase.child(phoneNo).setValue(usr))
            return@runBlocking true
        }
        return@runBlocking false
    }

    fun transferMoney(fromAcc: String, toAcc: String, amount: Int):Boolean = runBlocking {
        val fromUser = getUserByPhone(fromAcc)
        val toUser = getUserByPhone(toAcc)
        if(fromUser != null && toUser != null){
            if(fromUser.balance!! >= amount){
                mDatabase.child(fromAcc).child("balance").setValue(fromUser.balance?.minus(amount))
                mDatabase.child(toAcc).child("balance").setValue(toUser.balance?.plus(amount))
                return@runBlocking true
            }
        }
        return@runBlocking false

    }

    fun deposit(phone: String, amount: Int) = runBlocking{
        //get current balance
        var balance = 0

        val task = mDatabase.child(phone).child("balance").get()
        balance = Tasks.await(task).getValue<Int>()!!
        //update balance
        Tasks.await(mDatabase.child(phone).child("balance").setValue(balance + amount))
    }
}
