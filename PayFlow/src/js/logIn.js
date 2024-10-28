import { config } from "./app";
import axios from 'axios';

document.getElementById('logInForm').addEventListener('submit', (event)=>{
    event.preventDefault();
    const formData = new FormData(event.target);
    const formJSON = Object.fromEntries(formData.entries());
    logIn(formJSON);
});

function logIn(body)
{
    axios.post(config.apiURL + `user/logIn`, body)
    .then(function (response) {
        if(response.status == 200)
        {
            if(response != null)
            {
                console.log(response.data);
                if(response.data.userId != -1)
                {
                    sessionStorage.setItem('userId', response.data.userId);
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