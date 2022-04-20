function changeToRegister() {
  // change the visibility of all class loginPart to none
  document.getElementById("header").innerHTML = "<h2>Register</h2>";
  document.getElementById("loginForm").style.display = "none";
  document.getElementById("registerForm").style.display = "block";
  //   // change the visibility of all class registerPart to block
  //   let lis2 = [...document.querySelectorAll(".registerPart")];
  //   for (i of lis2) {
  //     i.style.display = "block";
  //   }
}

function changeToLogin() {
  document.getElementById("header").innerHTML = "<h2>Login</h2>";
  document.getElementById("registerForm").style.display = "none";
  document.getElementById("loginForm").style.display = "block";
}
window.onload = changeToLogin;

function login() {
  // send data using ldata
  let obj = {};
  let lis = [...document.querySelectorAll(".logindata")];
  for (i of lis) {
    obj[i.name] = i.value;
  }
  console.log(obj);
  fetch("/login", {
    method: "POST",
    headers: {
      "Content-Type": "application/json",
    },
    body: JSON.stringify(obj),
  })
    .then((res) => res.json())
    .then((data) => {
      console.log(data);
      if (data.status != 200) {
        alert(data.message);
      } else {
        alert(data.message);
        window.location.href = "/";
      }
    })
    .catch((err) => {
      console.log(err);
    });
}

function reg() {
  // send data usinf rdata
  let obj = {};
  let lis = [...document.querySelectorAll(".regdata")];
  for (i of lis) {
    obj[i.name] = i.value;
  }
  fetch("/register", {
    method: "POST",
    headers: {
      "Content-Type": "application/json",
    },
    body: JSON.stringify(obj),
  })
    .then((res) => res.json())
    .then((data) => {
      if (data.status != 200) {
        alert(data.message);
      } else {
        alert(data.message);
        window.location.href = "/";
      }
    });
}
