window.onload = ()=>{
    fetch('/mail',{
        method:'POST',
        headers:{
            'Content-Type':'application/json'
        }
    }).then(res=>res.json()).then(res=>{
        if(res.status===200) {
            console.log(res);
            document.querySelector('.otp').textContent = res.body;
        }
    });
}