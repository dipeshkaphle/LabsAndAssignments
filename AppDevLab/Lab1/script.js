let email = document.getElementById("email");
let phone = document.getElementById("phone");

email.oninvalid = function (event) {
  event.target.setCustomValidity("Invalid format: " + event.target.title);
};

phone.oninvalid = function (event) {
  event.target.setCustomValidity("Invalid format: " + event.target.title);
};

const form = document.querySelector("#loginForm");
form.addEventListener("submit", (event) => {
  console.log(form.elements["password"].value);
  event.preventDefault();
  if (
    form.elements["password"].value === form.elements["confirm_password"].value
  ) {
    alert(`Hello ${form.elements["fname"].value}`);
  } else {
    alert("Password's not matching");
  }
});
