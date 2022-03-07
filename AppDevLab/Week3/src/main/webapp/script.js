function next() {
  pageno++;
  if (pageno > maxpages) {
    pageno = maxpages - 1;
  }
  for (let i = 0; i < maxpages; i++) {
    document.getElementById("q" + i).hidden = true;
  }
  document.getElementById("q" + pageno).hidden = false;
}
function prev() {
  pageno--;
  if (pageno < 0) {
    pageno = 0;
  }
  for (let i = 0; i < maxpages; i++) {
    document.getElementById("q" + i).hidden = true;
  }
  document.getElementById("q" + pageno).hidden = false;
}
