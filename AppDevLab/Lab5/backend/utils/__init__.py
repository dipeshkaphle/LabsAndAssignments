
# use passlib to create hasher
from passlib.context import CryptContext
import motor

pwd_context = CryptContext(schemes=["bcrypt"], deprecated="auto")


# convert str to ObjectId
from bson.objectid import ObjectId

def get_object_id(s: str):
    return ObjectId(s)
    

# def get_object_id(s: str):
#     return motor.motor_asyncio.AsyncIOMotorObjectId(s)

def verify_password(plain_password, hashed_password):
    return pwd_context.verify(plain_password, hashed_password)


def get_password_hash(password):
    return pwd_context.hash(password)