import { useEffect, useState } from "react";
import { API_URL, BASE_URL } from "../config";

//import bootstrap
import { Button, Container, Form, FormGroup } from "react-bootstrap";
import { useNavigate } from "react-router-dom";

export default function Register(): JSX.Element {
  // register form using bootstrap
  const [form, setForm] = useState({
    username: "",
    password: "",
    confirmPassword: "",
    email: "",
    name: "",
    privilige: "",
  });
  let navigate = useNavigate();

  useEffect(() => {
    fetch(`${API_URL}/`, {
      method: "POST",
    })
      .then((res) => res.json())
      .then((res) => {
        console.log(res);
      });
  }, []);

  //  Make form with react-bootstrap and submit to API_URL/api/register
  const handleSubmit = (e: any): void => {
    e.preventDefault();
    // if password  and confirm password are not the same, alert
    if (form.password !== form.confirmPassword) {
      alert("password and confirm password are not the same");
      return;
    }
    const body = {
      full_name: form.name,
      username: form.username,
      password: form.password,
      email: form.email,
      privilige: form.privilige,
    };
    console.log(body);

    fetch(`${API_URL}/api/register`, {
      //post request with form data
      method: "POST",
      headers: {
        "Content-Type": "application/json",
      },
      body: JSON.stringify(body),
    })
      .then((res) => res.json())
      .then((data: { success: Boolean; message: String }) => {
        if (data.success) {
          navigate("/login");
          // window.location.href = `${BASE_URL}/#/login`;
        } else {
          alert("FAILURE");
        }
      });
  };
  //  handle change of input
  const handleChange = (e: any): void => {
    setForm({
      ...form,
      [e.target.name]: e.target.value,
    });
  };
  const priviliges = ["Customer", "Admin", "Producer", "Business", "Logistics"];
  return (
    <Container>
      <Container className="d-flex  justify-content-center align-items-center">
        <h2>Register</h2>
      </Container>
      <Container className="d-flex  justify-content-center align-items-center ">
        <Form onSubmit={handleSubmit} style={{ width: "50%" }}>
          <FormGroup>
            <Form.Label for="name">Name</Form.Label>
            <Form.Control
              type="text"
              name="name"
              id="name"
              placeholder="Enter name"
              onChange={handleChange}
            />
          </FormGroup>
          <FormGroup>
            <Form.Label for="username">Username</Form.Label>
            <Form.Control
              type="text"
              name="username"
              id="username"
              placeholder="Enter username"
              onChange={handleChange}
            />
          </FormGroup>
          <FormGroup>
            <Form.Label for="password">Password</Form.Label>
            <Form.Control
              type="password"
              name="password"
              id="password"
              placeholder="Enter password"
              onChange={handleChange}
            />
          </FormGroup>
          <FormGroup>
            <Form.Label for="confirm-password">Confirm Password</Form.Label>
            <Form.Control
              type="password"
              name="confirmPassword"
              id="confirmPassword"
              placeholder="Enter password again"
              onChange={handleChange}
            />
          </FormGroup>
          <FormGroup>
            <Form.Label for="email">Email</Form.Label>
            <Form.Control
              type="email"
              name="email"
              id="email"
              placeholder="Enter email"
              onChange={handleChange}
            />
          </FormGroup>
          <FormGroup>
            <Form.Label for="privilige">Privilige</Form.Label>
            <Form.Control
              as="select"
              name="privilige"
              id="privilige"
              onChange={handleChange}
            >
              {priviliges.map((privilige) => (
                <option key={privilige}>{privilige}</option>
              ))}
            </Form.Control>
          </FormGroup>
          <Button type="submit">Submit</Button>
        </Form>
      </Container>
    </Container>
  );
}
