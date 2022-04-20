import "./App.css";
import "bootstrap/dist/css/bootstrap.min.css";
import { Button, Card } from "react-bootstrap";

function App() {
  return (
    <div className="container d-flex  justify-content-center align-items-center vh-100">
      <Card
        className="text-center"
        style={{
          width: "50%",
          marginLeft: "auto",
          marginRight: "auto",
        }}
      >
        <Card.Header></Card.Header>
        <Card.Body>
          <Card.Title>Hello From Shopping App</Card.Title>
          <Button
            variant="primary"
            href="#/register"
            style={{ marginLeft: "auto", marginRight: "auto" }}
          >
            Register
          </Button>
          <Button
            variant="primary"
            href="#/login"
            style={{ marginLeft: "auto", marginRight: "auto" }}
          >
            Login
          </Button>
        </Card.Body>
      </Card>
    </div>
  );
}

export default App;
