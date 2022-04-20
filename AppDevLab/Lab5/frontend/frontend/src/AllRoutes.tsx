import { Route, Routes } from "react-router-dom";
import App from "./App";
import Login from "./Login";
import Register from "./Register";
import Home from "./Home";
import Producer from "./Producer";
import AddProduct from "./AddProduct";
import MyCart from "./MyCart";

export default function AllRoutes(): JSX.Element {
  return (
    <Routes>
      <Route path="/" element={<App />} />
      <Route path="/login" element={<Login />} />
      <Route path="/register" element={<Register />} />
      <Route path="/home" element={<Home />} />
      <Route path="/producer" element={<Producer />} />
      <Route path="/add_product" element={<AddProduct />} />
      <Route path="/cart" element={<MyCart />} />
    </Routes>
  );
}
