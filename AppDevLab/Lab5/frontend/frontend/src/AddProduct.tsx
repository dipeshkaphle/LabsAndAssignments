import { useState } from "react";
import { Form, Button, Col, Row, Container } from "react-bootstrap";
import { Navigate } from "react-router-dom";
import { API_URL } from "../config";

export default function AddProduct(): JSX.Element {
  // Create a form to add a new product using react-bootstrap
  // {
  //     "name": "string",
  //     "description": "string",
  //     "category": "string",
  //     "price": 0,
  //     "bought_count": 0,
  //     "stock_count": 0
  // }
  // submission route is $API_URL/api/add/product

  const [name, setName] = useState<string>("");
  const [description, setDescription] = useState<string>("");
  const [category, setCategory] = useState<string>("");
  const [price, setPrice] = useState<number>(0);
  const [boughtCount, setBoughtCount] = useState<number>(0);
  const [stockCount, setStockCount] = useState<number>(0);
  const [isLoggedIn, setIsLoggedIn] = useState(
    localStorage.getItem("token") !== null
  );

  const categories = ["Men", "Women", "Kids"];

  const handleSubmit = (e: React.FormEvent<HTMLFormElement>): void => {
    e.preventDefault();
    fetch(`${API_URL}/api/add/product`, {
      method: "POST",
      headers: {
        "Content-Type": "application/json",
        Authorization: `Bearer ${localStorage.getItem("token")}`,
      },
      body: JSON.stringify({
        name,
        description,
        category,
        price,
        bought_count: boughtCount,
        stock_count: stockCount,
      }),
    })
      .then((res) => res.json())
      .then((data) => {
        if (data.success) {
          alert("Product added successfully");
        }
      });
  };

  return !isLoggedIn ? (
    <Navigate to="/login" />
  ) : (
    <Container>
      <Container className="d-flex justify-content-center  align-content-center">
        <h2>Add Product</h2>
      </Container>
      <Container className="d-flex justify-content-center align-content-center">
        <Form onSubmit={handleSubmit} style={{ width: "50%" }}>
          <Form.Group>
            <Form.Label>Name</Form.Label>
            <Form.Control
              type="text"
              name="name"
              value={name}
              onChange={(e) => setName(e.target.value)}
            />
          </Form.Group>
          <Form.Group>
            <Form.Label>Description</Form.Label>
            <Form.Control
              type="text"
              name="description"
              value={description}
              onChange={(e) => setDescription(e.target.value)}
            />
          </Form.Group>

          <Form.Group>
            <Form.Label>Category</Form.Label>
            <Form.Control
              as="select"
              name="category"
              onChange={(e) => setCategory(e.target.value)}
            >
              {categories.map((category) => (
                <option key={category}>{category}</option>
              ))}
            </Form.Control>
          </Form.Group>
          <Form.Group>
            <Form.Label>Price</Form.Label>
            <Form.Control
              type="number"
              name="price"
              value={price}
              onChange={(e) => setPrice(Number(e.target.value))}
            />
          </Form.Group>
          <Form.Group>
            <Form.Label>Bought Count</Form.Label>
            <Form.Control
              type="number"
              name="boughtCount"
              value={boughtCount}
              onChange={(e) => setBoughtCount(Number(e.target.value))}
            />
          </Form.Group>
          <Form.Group>
            <Form.Label>Stock Count</Form.Label>
            <Form.Control
              type="number"
              name="stockCount"
              value={stockCount}
              onChange={(e) => setStockCount(Number(e.target.value))}
            />
          </Form.Group>
          <Button variant="primary" type="submit">
            Submit
          </Button>
        </Form>
      </Container>
    </Container>
  );
}
