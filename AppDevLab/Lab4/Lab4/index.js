const http = require("http");
const app = require("./src/app");

const port = 5000;

const server = http.createServer(app);

server.listen(port, () => {
  console.log(`Server Started On Port ${port}`);
});
