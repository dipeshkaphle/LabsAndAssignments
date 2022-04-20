import { useEffect, useState } from "react";
import { Button, Card, CardGroup, Col, Container, Row } from "react-bootstrap";
import { Navigate, useNavigate } from "react-router-dom";
import { API_URL, BASE_URL } from "../config";
import Product from "../types/Product";
import Paginate from "./Paginate";

export default function MyCart(): JSX.Element {
  // is logged in check
  const [isLoggedIn, setIsLoggedIn] = useState(
    localStorage.getItem("token") !== null
  );
  const navigate = useNavigate();

  const [userName, setUserName] = useState<String>("");
  const [products, setProducts] = useState<Product[]>([]);
  const [toBeShowedProducts, setToBeShowedProducts] = useState<Product[]>([]);
  const [activePage, setActivePage] = useState<number>(0);
  const [totalPages, setTotalPages] = useState<number>(0);
  const [totalCost, setTotalCost] = useState<number>(0);
  const perPage = 4;

  useEffect((): void => {
    fetch(`${API_URL}/api/my_cart`, {
      method: "GET",
      headers: {
        "Content-Type": "application/json",
        Authorization: `Bearer ${localStorage.getItem("token")}`,
      },
    })
      .then((res) => res.json())
      .then((data: { user: String; cart: Product[]; cost: number }) => {
        setProducts(data.cart);
        setTotalPages(Math.ceil(data.cart.length / perPage));
        setUserName(data.user);
        setTotalCost(data.cost);
        // take perPage products from products array
        setToBeShowedProducts(data.cart.slice(0, perPage));
      })
      .catch(() => {
        navigate("/login");
        // window.location.href = `${BASE_URL}/#/login`;
      });
  }, []);

  useEffect((): void => {
    setToBeShowedProducts(
      products.slice(activePage * perPage, (activePage + 1) * perPage)
    );
  }, [activePage, products]);

  const handleLogout = (): void => {
    localStorage.removeItem("token");
    setIsLoggedIn(false);
  };
  const handleHomeClick = (): void => {
    navigate("/home");
  };

  const handleRemoval = (productId: string, price: number): void => {
    // send delete request to /api/my_cart/:id
    fetch(`${API_URL}/api/my_cart/${productId}`, {
      method: "DELETE",
      headers: {
        "Content-Type": "application/json",
        Authorization: `Bearer ${localStorage.getItem("token")}`,
      },
    })
      .then((res) => res.json())
      .then((x) => {
        setTotalCost(totalCost - price);
        let newProducts = [];
        let foundOne = false;
        products.forEach((product) => {
          if (product._id === productId && foundOne == false) {
            foundOne = true;
          } else {
            newProducts.push(product);
          }
        });
        setProducts(newProducts);
      });
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
          <h2>Cart</h2>
        </Col>
      </Row>
      <Row>
        <Col className="d-flex  justify-content-center align-items-center">
          <h3>Total Cost: {totalCost}</h3>
        </Col>
      </Row>

      <Row xs={1} md={2} className="g-4">
        {toBeShowedProducts.map((prod: Product, idx) => (
          <Col key={idx}>
            <Card>
              <Card.Body>
                <Card.Title>{prod.name}</Card.Title>
                <Card.Text>{prod.description}</Card.Text>
              </Card.Body>
              <Card.Footer>
                Price: {prod.price} | Stocks Left: {prod.stock_count}
              </Card.Footer>
              <Card.Footer>
                <Button
                  variant="danger"
                  onClick={(_) => handleRemoval(prod._id, prod.price)}
                >
                  Remove From Cart
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
          <Button onClick={handleLogout} style={{ marginRight: "10px" }}>
            Logout
          </Button>
          <Button onClick={handleHomeClick} style={{ marginLeft: "10px" }}>
            Home
          </Button>
        </Col>
      </Row>
    </Container>
  );
}
