let allRegistrations;

const makeTable = (data) => {
  let summaryContainer = document.querySelector("#summary-table");
  summaryContainer.innerHTML = "";
  let table = document.createElement("table");
  table.className = "table";
  table.innerHTML += `
  <thead>
    <tr>
      <th scope="col">Name</th>
      <th scope="col">Roll No</th>
      <th scope="col">Course</th>
      <th scope="col">Events</th>
      <th scope="col">Fees</th>
      <th scope="col">Modify</th>
    </tr>
  </thead>`;
  let tbody = document.createElement("tbody");
  for (let i = 0; i < data.length; i++) {
    let tr = document.createElement("tr");
    tr.innerHTML += `
    <td>${data[i].name}</td>
    <td>${data[i].roll_no}</td>
    <td>${data[i].course}</td>
    <td>${data[i].events.join(", ")}</td>
    <td>${data[i].fees}</td>
    <td>
      <button class="btn btn-secondary edit-btn" data-id="${
        data[i]._id
      }">Edit</button>
      <button class="btn btn-danger delete-btn" data-id="${
        data[i]._id
      }">Delete</button>
    </td>`;
    tbody.appendChild(tr);
  }
  table.appendChild(tbody);
  summaryContainer.appendChild(table);
  document.querySelectorAll(".edit-btn").forEach((btn) => {
    btn.addEventListener("click", () => {
      makeEditForm(btn.getAttribute("data-id"));
    });
  });
  document.querySelectorAll(".delete-btn").forEach((btn) => {
    btn.addEventListener("click", () => {
      handleDelete(btn.getAttribute("data-id"));
    });
  });
  console.log("table made");
};

const getSummaryData = () => {
  let xhr = new XMLHttpRequest();
  xhr.open("GET", "/api/summary", true);
  xhr.onload = function () {
    if (this.status == 200) {
      let summary = JSON.parse(this.responseText);
      allRegistrations = summary;
      makeTable(summary);
    }
  };
  xhr.send();
};

const cleanForm = (form) => {
  const inputs = form.querySelectorAll("input");
  for (let i = 0; i < inputs.length; i++) {
    if (inputs[i].type !== "checkbox") inputs[i].value = "";
    else inputs[i].checked = false;
  }
};

const submitRegistration = () => {
  let xhr = new XMLHttpRequest();
  const form = document.getElementById("my-form");
  const inputs = form.querySelectorAll("input");
  let formData = {};
  formData.events = [];
  for (let i = 0; i < inputs.length; i++) {
    if (inputs[i].type !== "checkbox")
      formData[inputs[i].name] = inputs[i].value;
    else if (inputs[i].checked) formData.events.push(inputs[i].name);
  }
  formData.fees = formData.events.length * 100;
  if (document.getElementById("current-id").value !== "")
    formData._id = document.getElementById("current-id").value;
  xhr.open("POST", "/api/register", true);
  xhr.setRequestHeader("Content-Type", "application/json");
  xhr.onload = function () {
    if (this.status == 200) {
      getSummaryData();
    }
  };
  xhr.send(JSON.stringify(formData));
  cleanForm(form);
};

const makeEditForm = (id) => {
  document.getElementById("current-id").value = id;
  const currentRegistration = allRegistrations.find((reg) => reg._id === id);
  document.querySelector("input[name=name]").value = currentRegistration.name;
  document.querySelector("input[name=roll_no]").value =
    currentRegistration.roll_no;
  document.querySelector("input[name=course]").value =
    currentRegistration.course;
  document.querySelector("input[name=fees]").value = currentRegistration.fees;
  currentRegistration.events.forEach((event) => {
    document.querySelector(`input[name="${event}"]`).checked = true;
  });
};

const handleDelete = (id) => {
  let xhr = new XMLHttpRequest();
  xhr.open("DELETE", "/api/delete", true);
  const formData = { _id: id };
  xhr.setRequestHeader("Content-Type", "application/json");
  xhr.onload = function () {
    if (this.status == 200) {
      getSummaryData();
    }
  };
  xhr.send(JSON.stringify(formData));
};

document.addEventListener("DOMContentLoaded", () => {
  getSummaryData();
  document
    .getElementById("submit")
    .addEventListener("click", submitRegistration);
  document.querySelectorAll("input[type=checkbox]").forEach((checkbox) => {
    checkbox.addEventListener("change", (e) => {
      let change = 0;
      if (e.target.checked) {
        change = 100;
      } else {
        change = -100;
      }
      document.querySelector("input[name=fees]").value =
        parseInt(document.querySelector("input[name=fees]").value) + change;
    });
  });
});
