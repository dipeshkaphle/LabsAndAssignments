import { API_URL, BASE_URL } from "../config";

import { Button, Container, Form, FormGroup } from "react-bootstrap";
import { useState } from "react";
import { useNavigate } from "react-router-dom";

export default function Login(): JSX.Element {
  // Login page with react-bootstrap
  const [form, setForm] = useState({
    username: "",
    password: "",
  });
  let navigate = useNavigate();

  const handleSubmit = (e: any): void => {
    e.preventDefault();
    const body = `username=${form.username}&password=${form.password}`;
    fetch(`${API_URL}/api/login`, {
      method: "POST",
      headers: {
        "Content-Type": "application/x-www-form-urlencoded",
      },
      body: body,
    })
      .then((res) => res.json())
      .then((data) => {
        localStorage.setItem("token", data.access_token);
        // window href to #/home
        navigate("/home");
        // window.location.href = `${BASE_URL}/#/home`;
      })
      .catch(() => alert("FAILUREEEEEE!!!!"));
  };

  return (
    <Container>
      <Container className="d-flex justify-content-center align-items-center">
        <h2>Login</h2>
      </Container>
      <Container className="d-flex  justify-content-center align-items-center ">
        <Form onSubmit={handleSubmit} style={{ width: "50%" }}>
          <FormGroup>
            <Form.Label>Username</Form.Label>
            <Form.Control
              type="text"
              placeholder="Enter username"
              value={form.username}
              onChange={(e) => setForm({ ...form, username: e.target.value })}
            />
          </FormGroup>
          <FormGroup>
            <Form.Label>Password</Form.Label>
            <Form.Control
              type="password"
              placeholder="Enter password"
              value={form.password}
              onChange={(e) => setForm({ ...form, password: e.target.value })}
            />
          </FormGroup>
          <Button variant="primary" type="submit">
            Submit
          </Button>
        </Form>
      </Container>
    </Container>
  );
}
