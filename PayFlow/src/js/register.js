import { config } from "./app";
import axios from 'axios';

document.getElementById('registerForm').addEventListener('submit', (event)=>{
    event.preventDefault();
    const formData = new FormData(event.target);
    const formJSON = Object.fromEntries(formData.entries());
    register(formJSON);
});


function register(body)
{
    axios.post(config.apiURL + `user/register`, body)
    .then(function (response) {
        if(response.status == 200)
        {
            if(response != null)
            {
                console.log(response.data);
                if(response.data.userId != -1)
                {
                    sessionStorage.setItem('userId', response.data.userId);
                    window.location.href = '../html/dashboard.html';
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