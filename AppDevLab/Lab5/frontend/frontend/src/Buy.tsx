import { useEffect, useState } from "react";
import { Button, Container, Row } from "react-bootstrap";
import { useNavigate } from "react-router-dom";
import { API_URL } from "../config";

interface Response {
  success: boolean;
  message: string;
  transaction_cost: number;
  out_of_stock_cnt: number;
}

export default function Buy(): JSX.Element {
  const [respone, setResponse] = useState<Response>({
    success: false,
    message: "",
    transaction_cost: 0,
    out_of_stock_cnt: 0,
  });

  // con
  useEffect(() => {
    fetch(`${API_URL}/api/buy_cart`, {
      method: "GET",
      headers: {
        "Content-Type": "application/json",
        Authorization: `Bearer ${localStorage.getItem("token")}`,
      },
    }) //fetching the data from the server
      .then((res) => res.json())
      .then((data: Response) => {
        console.log(data);
        setResponse(data);
      })
      .catch((err) => console.log(err));
  }, []);

  const navigate = useNavigate();

  return (
    <Container>
      <Row className="d-flex justify-content-center align-items-center">
        <h2>Buy Summary</h2>
        {respone.success ? (
          <>
            All items in your cart have been purchased{" "}
            {respone.out_of_stock_cnt != 0 ? (
              <>
                except for {respone.out_of_stock_cnt} items which are out of
                stock.
              </>
            ) : (
              <>.</>
            )}
            <br />
            Your total transaction cost is {respone.transaction_cost}
          </>
        ) : (
          <h3>{respone.message}</h3>
        )}
      </Row>
      {/* // Add button to go back to home page */}
      <Row className="d-flex justify-content-center align-items-center">
        <Button variant="danger" onClick={(_) => navigate("/home")}>
          Home
        </Button>
      </Row>
    </Container>
  );
}
