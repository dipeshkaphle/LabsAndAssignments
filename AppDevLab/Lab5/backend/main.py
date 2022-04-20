import json
from typing import Dict, Optional, Any

from datetime import datetime, timedelta
from fastapi import Depends, FastAPI, HTTPException, status
from fastapi.security import OAuth2PasswordBearer, OAuth2PasswordRequestForm
from jose import JWTError, jwt
import motor.motor_asyncio
from fastapi.middleware.cors import CORSMiddleware

from models import user, product
from server_types import token
import utils
from server_types import priviliges

MONGODB_URL="mongodb://localhost:27017/"

# to get a string like this run:
# openssl rand -hex 32
SECRET_KEY = "09d25e094faa6ca2556c818166b7a9563b93f7099f6f0f4caa6cf63b88e8d3e7"
ALGORITHM = "HS256"
ACCESS_TOKEN_EXPIRE_MINUTES = 60 *12


client = motor.motor_asyncio.AsyncIOMotorClient(MONGODB_URL)

db = client.lab5
user_collection = db.get_collection("user")
product_collection = db.get_collection("product")
cart_collection = db.get_collection("cart")


app = FastAPI()

origins = [
       "*" 
]

app.add_middleware(
    CORSMiddleware,
    allow_origins=origins,
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)


oauth2_scheme = OAuth2PasswordBearer(tokenUrl="api/login")


def create_access_token(data: dict, expires_delta: Optional[timedelta] = None):
    to_encode = data.copy()
    if expires_delta:
        expire = datetime.utcnow() + expires_delta
    else:
        expire = datetime.utcnow() + timedelta(minutes=15)
    to_encode.update({"exp": expire})
    encoded_jwt = jwt.encode(to_encode, SECRET_KEY, algorithm=ALGORITHM)
    return encoded_jwt


@app.post("/")
async def main():
    return {"message": "Hello World"}

@app.get("/{username}")
async def read_user(username: str):
    return {"message": "Hello %s" % username}


@app.post("/api/register")
async def create_user(user: user.UserInDB):
    db_user = user
    db_user.password = utils.get_password_hash(db_user.password)
    await user_collection.insert_one(db_user.dict()) 
    return {"success": True, "message": "User created successfully"}

def verify_jwt_token(tok: str = Depends(oauth2_scheme)) -> token.TokenData:
    try:
        payload = jwt.decode(tok, SECRET_KEY, algorithms=[ALGORITHM])
        username: str = payload.get("sub")
        priv : str = payload.get("privilige")

        if username is None:
            raise HTTPException(
                status_code=status.HTTP_401_UNAUTHORIZED,
                detail="F Could not validate credentials",
                headers={"WWW-Authenticate": "Bearer"},
            )
        if priv is None:
            priv = 'customer'
        return token.TokenData(username=username, privilige=priv)
    except JWTError:
        raise HTTPException(
            status_code=status.HTTP_401_UNAUTHORIZED,
            detail="G Could not validate credentials",
            headers={"WWW-Authenticate": "Bearer"},
        )
        

@app.get("/api/products")
async def products(token: token.TokenData = Depends(verify_jwt_token) ):
    all_products = await product_collection.find().to_list(None)
    for item in all_products:
        item['_id'] = str(item['_id'])
    return { "user": token.username,  "products": all_products}

@app.post("/api/add/product")
async def add_product(prod: product.Product, token: token.TokenData = Depends(verify_jwt_token) ):
    if token.privilige in [priviliges.ADMIN, priviliges.PRODUCER] :
        product_in_db = product.ProductInDB(**prod.dict(), producer=token.username)
        await product_collection.insert_one(product_in_db.dict())
        return {"success": True,  "message": "Successfully added product"}
    else:
        return {"success": False,  "message": "Failed to added product"}

@app.get("/api/my_products")
async def get_my_products (tok: token.TokenData = Depends(verify_jwt_token) ):
    if tok.privilige in [priviliges.ADMIN, priviliges.PRODUCER]:
        all_products = await product_collection.find({"producer": tok.username}).to_list(None)
        for item in all_products:
            item['_id'] = str(item['_id'])
        return { "user": tok.username,  "products": all_products}
    else:
        raise HTTPException(
            status_code=status.HTTP_401_UNAUTHORIZED,
            detail="Failed to get products",
            headers={"WWW-Authenticate": "Bearer"},
        )

@app.delete("/api/my_products/{id}")
async def get_my_products (id: str, tok: token.TokenData = Depends(verify_jwt_token) ):
    if tok.privilige in [priviliges.ADMIN, priviliges.PRODUCER]:
        # get_object_id from str
        print(utils.get_object_id(id))
        await product_collection.delete_one({"_id": utils.get_object_id(id)})
        return { "success": True,  "message": "Successfully deleted product"}
    else:
        return { "success": False,  "message": "Failed to delete product"}


@app.get("/api/my_cart")
async def get_my_cart(tok: token.TokenData = Depends(verify_jwt_token)):

    # all_products = await product_collection.find().to_list(None)
    my_cart = await cart_collection.find({"user": tok.username}).to_list(None)
    for item in my_cart:
        item['_id'] = str(item['_id'])
    return { "user": tok.username, "cost": 0 if my_cart==[] else my_cart[0]['total_price'], 
     "cart": my_cart[0]['products'] if my_cart!=[] else [] }
    
@app.delete("/api/my_cart/{id}")
async def delete_from_cart(id: str, tok: token.TokenData = Depends(verify_jwt_token)):
    try:
        # await cart_collection.delete_one({"_id": utils.get_object_id(id)})

        prod_in_db = await product_collection.find_one({"_id": utils.get_object_id(id)})
        # get user's cart
        my_cart = await cart_collection.find({"user": tok.username}).to_list(None)
        if my_cart==[]:
            return { "success": False,  "message": "Failed to delete product"}
        else:
            new_cart = my_cart[0]
            cart_id = new_cart['_id']
            cart_products = my_cart[0]['products']
            # get product's id
            prod_id = utils.get_object_id(id)
            # get product's price
            prod_price = prod_in_db['price']
            # get cart's total price
            cart_total_price = my_cart[0]['total_price']
            # get cart's total price
            cart_total_price = cart_total_price - prod_price
            
            cart_products_new = []
            found_one = False
            for prod in cart_products:
                if prod['_id'] == id and found_one == False:
                    found_one = True
                else:
                    cart_products_new.append(prod)
            new_cart['products'] = cart_products_new
            new_cart['total_price'] = cart_total_price
            
            # update cart
            print(new_cart)
            await cart_collection.update_one({"user": tok.username}, {"$set": new_cart})
            return { "success": True,  "message": "Successfully deleted product"}
    except :
        return { "success": False,  "message": "F"}

@app.post("/api/add_to_cart")
async def add_to_cart(req: Dict[str,Any], tok: token.TokenData = Depends(verify_jwt_token)):
    prod_in_db = await product_collection.find_one({"_id": utils.get_object_id(req['prod_id'])})
    prod_in_db['_id'] = str(prod_in_db['_id'])
    my_cart = await cart_collection.find({"user": tok.username}).to_list(None)
    if my_cart:
        my_cart = my_cart[0]
        my_cart['products'].append(prod_in_db)
        my_cart['total_price'] += prod_in_db['price']
        await cart_collection.update_one({"user": tok.username}, {"$set": my_cart})
    else:
        my_cart = {
            "user": tok.username,
            "products": [prod_in_db],
            "total_price": prod_in_db['price']
        }
        await cart_collection.insert_one(my_cart)
    return { "success": True,  "message": "Successfully added product to cart"}



@app.post("/api/login")
async def login(form_data: OAuth2PasswordRequestForm = Depends()):
    user = await user_collection.find_one({"username": form_data.username})
    if not user:
        raise HTTPException(status_code=400, detail="Incorrect username or password")
    if not utils.verify_password(form_data.password, user["password"]):
        raise HTTPException(status_code=400, detail="Incorrect username or password")
    access_token_expires = timedelta(minutes=ACCESS_TOKEN_EXPIRE_MINUTES)
    access_token = create_access_token(
        data={"sub": form_data.username, "privilige": user["privilige"]  }, 
        expires_delta=access_token_expires
    )
    return {"access_token": access_token, "token_type": "bearer"}

