import axios from 'axios';
const apiURL = 'http://localhost:18080/api/'

document.addEventListener("DOMContentLoaded", (event) => {
    if(localStorage.getItem('userId') != -1)
    {
        location.replace('html/dashboard.html');
    }
});

document.getElementById('logInForm').addEventListener('submit', (event)=>{
    event.preventDefault();
    const formData = new FormData(event.target);
    const formJSON = Object.fromEntries(formData.entries());
    logIn(formJSON);
});

function logIn(body)
{
    axios.post(apiURL + `user/logIn`, body)
    .then(function (response) {
        if(response.status == 200)
        {
            debugger;

            if(response != null)
            {
                console.log(response.data);
                if(response.data.userId != -1)
                {
                    localStorage.setItem('userId', response.data.userId);
                    location.replace('html/dashboard.html');
                }
                else
                {
                    alert("Unauthorised");
                }
            }
        }
        else
        {
            console.log(error);
            alert("Unauthorised");
        }
    })
    .catch(function (error) {
        console.log(error);
        alert("Fatal error");
    });
}