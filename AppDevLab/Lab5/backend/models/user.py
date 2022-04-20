from typing import Optional
from pydantic import BaseModel, Field

from bson.objectid import ObjectId
from . import pyobjectid

class User(BaseModel):
    _id: pyobjectid.PyObjectId = Field(default_factory=pyobjectid.PyObjectId, alias="_id")
    username: str = Field(...)
    email: str = Field(...)
    full_name: str = Field(...)
    privilige: Optional [str]= None
    class Config:
        allow_population_by_field_name = True
        arbitrary_types_allowed = True
        json_encoders = {ObjectId: str}

class UserInDB(User):
    password: str=Field(...)