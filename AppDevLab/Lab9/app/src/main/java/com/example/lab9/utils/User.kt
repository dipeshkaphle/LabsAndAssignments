package com.example.lab9.utils

import com.google.firebase.database.IgnoreExtraProperties
import com.google.firebase.database.PropertyName
import java.io.Serializable

// create user dataclass
@IgnoreExtraProperties
data class User(@set:PropertyName("username") @get:PropertyName("username") var username: String?=null,
                @set:PropertyName("phone")@get:PropertyName("phone") var phone: String?=null,
                @set:PropertyName("password") @get:PropertyName("password")var password: String?=null,
                @get:PropertyName("balance")  @set:PropertyName("balance") var balance: Int?=null,
                @set:PropertyName("isVerified") @get:PropertyName("isVerified") var isVerified: Int?=null,
                @set:PropertyName("benificiaryList") @get:PropertyName("benificiaryList")
                var benificiaryList: List<String>? =null
) : Serializable
