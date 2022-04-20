window.onload = () => {
  fetch("/user", {
    method: "POST",
  })
    .then((res) => res.json())
    .then((res) => {
      if (res.status !== 200) {
        alert(res.message);
      } else {
        let lis = [...document.querySelectorAll(".editdata")];
        for (i of lis) {
          i.value = res.body[i.name];
        }
      }
    });
};

function newtab() {
  window.open("http://localhost:8080/otp", "_blank").focus();
}

function edit() {
  let obj = {};
  let lis = [...document.querySelectorAll(".editdata")];
  for (i of lis) {
    obj[i.name] = i.value;
  }

  console.log(obj);
  if (!(checkpass(obj.password) && checkname(obj.name))) {
    alert("password and username dont match criteria, try again");
    return;
  }
  fetch("/edit", {
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
        // console.log("changing editdiv");
        document.querySelector(".edit-div").innerHTML = `<input
          type="text"
          class="editdata"
          id="otp"
          name="otp"
          placeholder="Enter OTP"
          required
        />
        <button onclick="confirm()" class="btn btn-primary"> Confirm </button>`;
      }
    });
}

function confirm() {
  let obj = {};
  let lis = [...document.querySelectorAll(".editdata")];
  for (i of lis) {
    obj[i.name] = i.value;
  }
  if (!(checkpass(obj.password) && checkname(obj.name))) {
    alert("password and username dont match criteria, try again");
    return;
  }
  fetch("/confirmedit", {
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

function checkpass(str) {
  // check if str has 8 characters, contains alphabets numbers and special characters wihtout regex
  let charb, specialb, numb;
  charb = false;
  specialb = false;
  numb = false;
  str = str.split("");
  str.map((e) => {
    //if e is character set charb
    if (e.match(/[a-zA-Z]/)) {
      charb = true;
    }
    //if e is number set numb
    if (e.match(/[0-9]/)) {
      numb = true;
    }
    //if e is special character set specialb
    if (e.match(/[!@#$%^&*()_+\-=\[\]{};':"\\|,.<>\/?]/)) {
      specialb = true;
    }
  });
  return str.length == 8 && charb && numb && specialb;
}

function checkname(str) {
  // check if str has only alphabets
  let regex = /^[a-zA-Z]+$/;
  return regex.test(str);
}

function logout() {
  fetch("/logout", {
    method: "POST",
  })
    .then((res) => res.json())
    .then((data) => {
      if (data.status != 200) {
        alert(data.message);
      } else {
        alert(data.message);
        window.location.href = "/login";
      }
    });
}
