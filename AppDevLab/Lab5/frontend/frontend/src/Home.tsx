import { useEffect, useState } from "react";
import { Button, Card, CardGroup, Col, Container, Row } from "react-bootstrap";
import { Navigate, useNavigate } from "react-router-dom";
import { API_URL, BASE_URL } from "../config";
import Product from "../types/Product";
import Paginate from "./Paginate";

export default function Home(): JSX.Element {
  // is logged in check
  const [isLoggedIn, setIsLoggedIn] = useState(
    localStorage.getItem("token") !== null
  );
  let navigate = useNavigate();

  const [userName, setUserName] = useState<String>("");
  const [products, setProducts] = useState<Product[]>([]);
  const [operableProducts, setOperableProducts] = useState<Product[]>([]);
  const [toBeShowedProducts, setToBeShowedProducts] = useState<Product[]>([]);
  const [activePage, setActivePage] = useState<number>(0);
  const [totalPages, setTotalPages] = useState<number>(0);
  const [categories, setCategories] = useState<string[]>([]);
  const [category, setCategory] = useState<string>("all");
  const perPage = 4;

  useEffect((): void => {
    fetch(`${API_URL}/api/products`, {
      method: "GET",
      headers: {
        "Content-Type": "application/json",
        Authorization: `Bearer ${localStorage.getItem("token")}`,
      },
    })
      .then((res) => res.json())
      .then((data: { user: String; products: Product[] }) => {
        setProducts(data.products);
        setOperableProducts([...data.products]);
        setCategories(
          data.products
            .map((product) => product.category)
            .filter((value, index, self) => self.indexOf(value) === index)
        );
        setTotalPages(Math.ceil(data.products.length / perPage));
        setUserName(data.user);
        // take perPage products from products array
        setToBeShowedProducts(data.products.slice(0, perPage));
      })
      .catch(() => {
        navigate("/login");
      });
  }, []);

  useEffect((): void => {
    setToBeShowedProducts(
      operableProducts.slice(activePage * perPage, (activePage + 1) * perPage)
    );
  }, [activePage, operableProducts]);

  const handleLogout = (): void => {
    localStorage.removeItem("token");
    setIsLoggedIn(false);
  };
  const handleCartClick = (): void => {
    navigate("/cart");
  };

  const addToCart = (productId: string): void => {
    const body = {
      prod_id: productId,
    };
    console.log(body);
    fetch(`${API_URL}/api/add_to_cart`, {
      method: "POST",
      headers: {
        "Content-Type": "application/json",
        Authorization: `Bearer ${localStorage.getItem("token")}`,
      },
      body: JSON.stringify(body),
    })
      .then((res) => res.json())
      .then((data) => {
        console.log(data);
      })
      .catch((err) => {
        console.log(err);
      });
  };

  useEffect(() => {
    if (category === "all") {
      setOperableProducts([...products]);
      return;
    }
    const filteredProducts = products.filter((product) => {
      return product.category === category;
    });
    setOperableProducts(filteredProducts);
  }, [category]);

  const searchProduct = (e): void => {
    const search = e.target.value;
    const filteredProducts = products.filter((product) => {
      return product.name.toLowerCase().includes(search.toLowerCase());
    });
    setOperableProducts(filteredProducts);
  };

  const handleCategoryChange = (e): void => {
    // const category = e.target.value;
    setCategory(e.target.value);
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
      <Row></Row>
      <Row>
        <Col className="d-flex  justify-content-center align-items-center">
          <input
            type="text"
            placeholder="Search"
            className="form-control"
            onChange={searchProduct}
          />
        </Col>
      </Row>
      <Row></Row>
      <Row>
        <Col
          className="d-flex justify-content-center align-items-center"
          md="2"
        >
          Categorize By
        </Col>
        <Col className="d-flex  justify-content-center align-items-center">
          <select className="form-control" onChange={handleCategoryChange}>
            <option value="all">All</option>
            {categories.map((category) => (
              <option value={category}>{category}</option>
            ))}
          </select>
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
                <Button variant="primary" onClick={(_) => addToCart(prod._id)}>
                  Add To Cart
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
            Logout{" "}
          </Button>
          <Button onClick={handleCartClick} style={{ marginLeft: "10px" }}>
            Go To Cart
          </Button>
        </Col>
      </Row>
    </Container>
  );
}
