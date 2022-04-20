from typing import Optional
from pydantic import BaseModel, Field
from . import pyobjectid

from bson.objectid import ObjectId

class Product(BaseModel):
    _id: pyobjectid.PyObjectId = Field(default_factory=pyobjectid.PyObjectId, alias="_id")
    name: str = Field(...)
    description: str = Field(...)
    category: str = Field(...)
    price: int = Field(...)
    bought_count : int = Field(...)
    stock_count: int =  Field(...)
    class Config:
        allow_population_by_field_name = True
        arbitrary_types_allowed = True
        json_encoders = {ObjectId: str}

class ProductInDB(Product):
    producer: str = Field(...)