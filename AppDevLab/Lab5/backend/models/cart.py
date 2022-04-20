from typing import List
from pydantic import BaseModel, Field

from backend.models.product import ProductInDB
from . import pyobjectid

from bson.objectid import ObjectId

class Cart(BaseModel):
    _id: pyobjectid.PyObjectId = Field(default_factory=pyobjectid.PyObjectId, alias="_id")
    user_name: str = Field(...)
    products : List[ProductInDB]
    total_price: int = Field(...)
    class Config:
        allow_population_by_field_name = True
        arbitrary_types_allowed = True
        json_encoders = {ObjectId: str}
