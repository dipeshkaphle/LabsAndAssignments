import { useEffect, useState } from "react";
import { Button, Card, Col, Container, Row } from "react-bootstrap";
import { Navigate } from "react-router-dom";
import { API_URL } from "../config";
import Product from "../types/Product";
import Paginate from "./Paginate";

export default function Producer(): JSX.Element {
  // get user's products from backend and display them. The route to be used is $BASE_URL/api/my_products
  // is logged in check

  const [isLoggedIn, setIsLoggedIn] = useState(
    localStorage.getItem("token") !== null
  );
  const [userName, setUserName] = useState<String>("");
  const [products, setProducts] = useState<Product[]>([]);
  const [toBeShowedProducts, setToBeShowedProducts] = useState<Product[]>([]);
  const [activePage, setActivePage] = useState<number>(0);
  const [totalPages, setTotalPages] = useState<number>(0);
  const perPage = 4;
  useEffect(() => {
    fetch(`${API_URL}/api/my_products`, {
      method: "GET",
      headers: {
        "Content-Type": "application/json",
        Authorization: `Bearer ${localStorage.getItem("token")}`,
      },
    })
      .then((res) => res.json())
      .then((data: { user: String; products: Product[] }) => {
        setUserName(data.user);
        setProducts(data.products);
        // take perPage products from products array
        setToBeShowedProducts(data.products.slice(0, perPage));
      });
  }, []);
  /// handle delete product
  const handleDelete = (id: String): void => {
    fetch(`${API_URL}/api/my_products/${id}`, {
      method: "DELETE",
      headers: {
        "Content-Type": "application/json",
        Authorization: `Bearer ${localStorage.getItem("token")}`,
      },
    })
      .then((res) => res.json())
      .then((data) => {
        if (data.success) {
          setProducts(products.filter((product) => product._id !== id));
        }
      });
  };

  useEffect((): void => {
    setTotalPages(Math.ceil(products.length / perPage));
  }, [products]);

  useEffect((): void => {
    setToBeShowedProducts(
      products.slice(activePage * perPage, (activePage + 1) * perPage)
    );
  }, [activePage, products]);

  const handleLogout = (): void => {
    localStorage.removeItem("token");
    setIsLoggedIn(false);
  };

  return !isLoggedIn ? (
    <Navigate to="/login" />
  ) : (
    <Container>
      <Row>
        <Col className="d-flex  justify-content-center align-items-center">
          <h1>Welcome {userName}</h1>
        </Col>
      </Row>
      <Row>
        <Col className="d-flex  justify-content-center align-items-center">
          <h2> Available Products</h2>
        </Col>
      </Row>

      <Row xs={1} md={2} className="g-4">
        {toBeShowedProducts.map((prod: Product, idx) => (
          <Col key={prod._id}>
            <Card>
              <Card.Body>
                <Card.Title>{prod.name}</Card.Title>
                <Card.Text>{prod.description}</Card.Text>
              </Card.Body>
              <Card.Footer>
                Price: {prod.price} | Stocks Left: {prod.stock_count}
              </Card.Footer>
              <Card.Footer>
                <Button variant="danger" onClick={() => handleDelete(prod._id)}>
                  Delete
                </Button>
              </Card.Footer>
            </Card>
          </Col>
        ))}
      </Row>
      <Row>
        <Col className="d-flex  justify-content-center align-items-center">
          <Paginate
            active={activePage}
            total={totalPages}
            setActive={setActivePage}
          />
        </Col>
      </Row>
      <Row>
        <Col className="d-flex  justify-content-center align-items-center">
          <Button onClick={handleLogout}>Logout</Button>
        </Col>
      </Row>
    </Container>
  );
}
