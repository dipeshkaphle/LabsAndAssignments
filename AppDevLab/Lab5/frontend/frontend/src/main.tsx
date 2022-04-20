import React from "react";

import ReactDOM from "react-dom";
import "./index.css";
import App from "./App";
import AllRoutes from "./AllRoutes";
import { HashRouter } from "react-router-dom";

ReactDOM.render(
  <React.StrictMode>
    <HashRouter>
      <AllRoutes />
    </HashRouter>
    {/* <App /> */}
  </React.StrictMode>,
  document.getElementById("root")
);
